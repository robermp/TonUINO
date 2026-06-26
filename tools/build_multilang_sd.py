#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
build_multilang_sd.py — Fusiona los packs de audio por idioma en una unica SD
multilenguaje para el firmware TonUINO_Custom (fork multilenguaje + Disney).

Contexto
--------
El firmware (flag LANGUAGE_SELECT) reproduce los prompts y numeros desde /mp3/
y los avisos desde /advert/ aplicando un prefijo por idioma:

    pista_final = (idioma + 1) * 1000 + pista_base

        idioma 0 (ES) -> 1xxx
        idioma 1 (IT) -> 2xxx
        idioma 2 (EN) -> 3xxx

(ver TonUINO/src/constants.hpp: languageMp3Step = 1000, numLanguages = 3,
 y TonUINO/src/mp3.cpp: Mp3::enqueueMp3FolderTrack / Mp3::playAdvertisement).

Este script toma tres packs ya generados con `create_audio_messages.py`
(uno por idioma, cada uno con subcarpetas mp3/ y advert/ y ficheros tipo
`0300.mp3` o `0300_new_tag.mp3`) y los combina en una sola SD renumerando el
prefijo de 4 digitos con el offset de cada idioma.

Tambien puede inyectar (opcionalmente) la pista que dice el nombre del idioma,
que el firmware reproduce con `languageNameMp3 = 309`:

    /mp3/1309.mp3 = "Espanol"   /mp3/2309.mp3 = "Italiano"   /mp3/3309.mp3 = "English"

NOTA: si los packs ya incluyen `0309.mp3` (porque `audio_messages_*.txt` tiene la
linea `mp3/0309.mp3|<nombre>`), ese fichero se renumera solo a 1309/2309/3309 y las
opciones `--lang-name-*` NO son necesarias. Usarlas en ese caso provoca una colision
de destino y el script aborta. Solo tienen sentido si tus packs no llevan el 0309.

Lo que NO hace este script
--------------------------
- No genera el audio (eso es trabajo de create_audio_messages.py / TTS).
- No toca el contenido de usuario (carpetas 1-99, incluidas las Disney 96-99):
  esas se copian aparte a la raiz de la SD.

Uso tipico
----------
    # 1) generar un pack por idioma (esquema TNG, 300+)
    python3 create_audio_messages.py --lang es --output ../sd-es
    python3 create_audio_messages.py --lang it --output ../sd-it
    python3 create_audio_messages.py --lang en --output ../sd-en

    # 2) fusionarlos con el offset por idioma
    python3 build_multilang_sd.py \
        --es ../sd-es --it ../sd-it --en ../sd-en \
        --out ../sd-final

    # (los nombres de idioma 1309/2309/3309 salen del 0309 de cada pack;
    #  solo usa --lang-name-* si tus packs NO incluyen el 0309)

    # 3) copiar el resultado y las carpetas 1-99 a la SD real

Ejecutar con --dry-run para ver el plan sin escribir nada.
"""

import argparse
import re
import shutil
import sys
from pathlib import Path

# --- Debe coincidir con TonUINO/src/constants.hpp -------------------------------
LANGUAGE_MP3_STEP = 1000          # languageMp3Step
LANGUAGE_NAME_MP3 = 309           # languageNameMp3
MAX_TRACK_NUMBER  = 9999          # limite de 4 digitos del DFPlayer

# idioma -> (codigo, offset). El orden/indice debe coincidir con el firmware:
#   0 = ES, 1 = IT, 2 = EN
LANGUAGES = [
    ("es", 1 * LANGUAGE_MP3_STEP),  # idioma 0
    ("it", 2 * LANGUAGE_MP3_STEP),  # idioma 1
    ("en", 3 * LANGUAGE_MP3_STEP),  # idioma 2
]

SUBFOLDERS = ("mp3", "advert")
NAME_RE = re.compile(r"^(\d+)(.*)\.mp3$", re.IGNORECASE)


def log(msg):
    print(msg, flush=True)


def err(msg):
    print(f"ERROR: {msg}", file=sys.stderr, flush=True)


def find_source_subdir(pack: Path, sub: str):
    """Devuelve la ruta a mp3/ o advert/ dentro de un pack, tolerando que el
    pack apunte directamente a esa subcarpeta."""
    cand = pack / sub
    if cand.is_dir():
        return cand
    # por si el usuario paso directamente la carpeta mp3/ o advert/
    if pack.name == sub and pack.is_dir():
        return pack
    return None


def plan_language(pack: Path, offset: int, out_dir: Path):
    """Genera la lista de (origen, destino) para un pack de idioma."""
    actions = []
    warnings = []
    for sub in SUBFOLDERS:
        src = find_source_subdir(pack, sub)
        if src is None:
            warnings.append(f"  (sin subcarpeta '{sub}/' en {pack})")
            continue
        out_sub = out_dir / sub
        for f in sorted(src.iterdir()):
            if not f.is_file():
                continue
            m = NAME_RE.match(f.name)
            if not m:
                warnings.append(f"  ignorado (nombre no NNNN.mp3): {sub}/{f.name}")
                continue
            base = int(m.group(1))
            suffix = m.group(2)
            new_num = base + offset
            if new_num > MAX_TRACK_NUMBER:
                warnings.append(
                    f"  DESCARTADO (pista {new_num} > {MAX_TRACK_NUMBER}): {sub}/{f.name}")
                continue
            dst = out_sub / f"{new_num:04d}{suffix}.mp3"
            actions.append((f, dst))
    return actions, warnings


def plan_language_name(audio: Path, offset: int, out_dir: Path):
    """Pista que dice el nombre del idioma -> /mp3/<offset+309>.mp3"""
    if audio is None:
        return None
    if not audio.is_file():
        err(f"fichero de nombre de idioma no encontrado: {audio}")
        return None
    num = offset + LANGUAGE_NAME_MP3
    dst = out_dir / "mp3" / f"{num:04d}.mp3"
    return (audio, dst)


def main():
    p = argparse.ArgumentParser(
        description="Fusiona packs de audio por idioma en una SD multilenguaje TonUINO.",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog=__doc__,
    )
    p.add_argument("--es", type=Path, help="pack de audio en espanol (idioma 0 -> 1xxx)")
    p.add_argument("--it", type=Path, help="pack de audio en italiano (idioma 1 -> 2xxx)")
    p.add_argument("--en", type=Path, help="pack de audio en ingles (idioma 2 -> 3xxx)")
    p.add_argument("--out", type=Path, required=True, help="carpeta SD de salida")
    p.add_argument("--lang-name-es", type=Path, help='audio "Espanol" -> /mp3/1309.mp3 (legado: innecesario si el pack ya trae 0309)')
    p.add_argument("--lang-name-it", type=Path, help='audio "Italiano" -> /mp3/2309.mp3 (legado: innecesario si el pack ya trae 0309)')
    p.add_argument("--lang-name-en", type=Path, help='audio "English" -> /mp3/3309.mp3 (legado: innecesario si el pack ya trae 0309)')
    p.add_argument("--clean", action="store_true",
                   help="vacia las carpetas mp3/ y advert/ de salida antes de copiar")
    p.add_argument("--dry-run", action="store_true",
                   help="muestra el plan sin escribir nada")
    args = p.parse_args()

    packs = {"es": args.es, "it": args.it, "en": args.en}
    lang_names = {"es": args.lang_name_es, "it": args.lang_name_it, "en": args.lang_name_en}

    if not any(packs.values()):
        err("indica al menos un pack de idioma (--es / --it / --en).")
        return 2

    out_dir = args.out
    all_actions = []
    all_warnings = []

    for code, offset in LANGUAGES:
        pack = packs[code]
        if pack is None:
            log(f"[{code}] (omitido: no se indico pack)")
            continue
        if not pack.is_dir():
            err(f"[{code}] no es una carpeta: {pack}")
            return 2
        actions, warnings = plan_language(pack, offset, out_dir)
        log(f"[{code}] offset {offset:+05d}  ->  {len(actions)} ficheros desde {pack}")
        for w in warnings:
            log(w)
        all_actions += actions
        all_warnings += warnings

        ln = plan_language_name(lang_names[code], offset, out_dir)
        if ln is not None:
            log(f"[{code}] nombre de idioma -> {ln[1].relative_to(out_dir)}")
            all_actions.append(ln)

    # deteccion de colisiones de destino
    seen = {}
    collisions = []
    for src, dst in all_actions:
        key = str(dst)
        if key in seen:
            collisions.append((seen[key], src, dst))
        seen[key] = src
    for prev, src, dst in collisions:
        err(f"colision en {dst.name}: '{prev}' y '{src}'")
    if collisions:
        err(f"{len(collisions)} colisiones; corrige los packs de entrada.")
        return 1

    log("")
    log(f"Total a copiar: {len(all_actions)} ficheros -> {out_dir}")

    if args.dry_run:
        log("(dry-run: no se ha escrito nada)")
        return 0

    # preparar carpetas de salida
    for sub in SUBFOLDERS:
        d = out_dir / sub
        if args.clean and d.is_dir():
            log(f"limpiando {d}")
            for f in d.glob("*.mp3"):
                f.unlink()
        d.mkdir(parents=True, exist_ok=True)

    copied = 0
    for src, dst in all_actions:
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        copied += 1

    log(f"Hecho: {copied} ficheros copiados en {out_dir}/mp3 y {out_dir}/advert")
    log("Recuerda copiar tambien las carpetas de contenido 1-99 (incl. Disney 96-99) a la raiz de la SD.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
