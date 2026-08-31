# TonUINO Arduino Nano — Manual de usuario / User Manual

- [Español](#manual-de-usuario-en-español)
- [English](#user-manual-in-english)

> Este manual corresponde a la compilación **TonUINO_Custom**: Arduino Nano
> ATmega328P, seis botones, mensajes en español/italiano/inglés y compatibilidad
> con determinadas tarjetas Disney.
>
> This manual covers the **TonUINO_Custom** build: Arduino Nano ATmega328P, six
> buttons, Spanish/Italian/English prompts, and selected Disney-card support.

---

# Manual de usuario en español

## 1. Descripción

TonUINO reproduce audio desde una tarjeta microSD. Las tarjetas RFID/NFC
indican qué carpeta o pista debe reproducirse y de qué forma. Los mensajes de
voz permiten manejar y configurar la caja sin pantalla.

Esta versión usa exactamente seis botones:

1. **Reproducir/Pausa**
2. **Siguiente**
3. **Anterior**
4. **Volumen +**
5. **Volumen −**
6. **Idioma**

No incluye los juegos Concurso, Memoria o Palabras polisémicas, Bluetooth,
Jukebox, placa 3 × 3, aro NeoPixel ni interfaz web ESP32.

## 2. Preparar la microSD

Para aprovechar los tres idiomas, copia el contenido de
`sd-card-multilang` en la raíz de la microSD. Debe conservar:

- `mp3/`: mensajes, números y sonidos del sistema en los tres idiomas.
- `advert/`: avisos del sistema en los tres idiomas.
- Carpetas de contenido `01` a `99`.

Guarda el contenido del usuario en carpetas de dos cifras (`01`, `02`, etc.) y
ordena sus pistas con nombres numéricos de tres cifras:

```text
01/
├── 001.mp3
├── 002.mp3
└── 003.mp3
```

No cambies los nombres de los archivos del sistema. Inserta siempre la microSD
antes de encender.

## 3. Encendido, idioma y apagado

### Encender

1. Inserta la microSD.
2. Enciende TonUINO.
3. Espera el saludo.
4. Acerca una tarjeta configurada para empezar.

**Atención:** mantener pulsados simultáneamente
**Reproducir/Pausa + Siguiente + Anterior** durante el arranque borra todos los
ajustes guardados.

### Cambiar el idioma

Pulsa **Idioma** para cambiar en este orden:

**Español → Italiano → Inglés → Español**

El sistema anuncia el idioma seleccionado. El cambio se aplica inmediatamente
a los menús, números y avisos, tanto en reposo como durante la reproducción o
la pausa. El botón Idioma no actúa dentro del menú de administración.

El cambio con el botón es temporal. Tras reiniciar se recupera el **idioma
inicial** guardado en la opción 15 del menú de administración.

Las tarjetas Disney compatibles que dependen del idioma también usan el idioma
activo en el momento de leerlas.

### Apagar

En reposo o pausa, mantén **Reproducir/Pausa** durante aproximadamente un
segundo. También puede apagarse automáticamente mediante el temporizador de
espera o una tarjeta de temporizador.

## 4. Guía de los seis botones

Una pulsación larga dura aproximadamente un segundo.

| Botón/acción | En reproducción | En reposo o pausa | En menús |
| --- | --- | --- | --- |
| Reproducir/Pausa | Pausar o continuar | Continuar el audio pausado | Confirmar |
| Reproducir/Pausa, larga | Anunciar pista actual | Apagar | Cancelar/salir |
| Siguiente | Pista siguiente | — | Opción siguiente |
| Siguiente, larga | Saltar 10 pistas | Acceso directo 2 | Avanzar 10 opciones |
| Anterior | Pista anterior | — | Opción anterior |
| Anterior, larga | Retroceder 10 pistas | Acceso directo 3 | Retroceder 10 opciones |
| Volumen + | Subir volumen | Subir volumen | Opción siguiente |
| Volumen − | Bajar volumen | Bajar volumen | Opción anterior |
| Idioma | Cambiar idioma | Cambiar idioma | Sin función en administración |
| Siguiente + Anterior, larga | Volver a la primera pista de la cola | Acceso directo 1 | — |

Mantener **Reproducir/Pausa + Siguiente + Anterior** o
**Reproducir/Pausa + Volumen + + Volumen −** abre el menú de administración
cuando su protección lo permite.

La opción «Invertir botones de volumen» del menú no altera esta versión de
cinco botones de reproducción más el botón de idioma.

## 5. Tarjetas RFID/NFC

### Reproducir

1. Coloca una tarjeta configurada sobre el lector.
2. TonUINO lee la carpeta, el modo y sus parámetros.
3. La reproducción empieza automáticamente.
4. Otra tarjeta válida cambia el contenido.

La misma tarjeta presentada durante su propia reproducción normalmente se
ignora. Se admiten MIFARE Mini, Classic 1K/4K y
Ultralight/NTAG213/215/216.

### Configurar una tarjeta vacía

Al detectar una tarjeta vacía, el asistente se inicia automáticamente:

1. Retira la tarjeta cuando se solicite.
2. Elige el modo con Siguiente/Anterior o Volumen +/−.
3. Confirma con **Reproducir/Pausa**.
4. Elige la carpeta `01`–`99` y los parámetros solicitados.
5. Vuelve a colocar la tarjeta cuando oigas «Pon la tarjeta».
6. No la muevas hasta la confirmación y después retírala.

Una pulsación larga en Reproducir/Pausa cancela el proceso. Si se anuncia un
error, vuelve a intentarlo manteniendo la tarjeta centrada y quieta.

### Pausa al retirar

La opción 13 de administración controla este comportamiento:

- **Sí:** retirar la tarjeta que inició el audio pone la caja en pausa. Solo se
  reanuda al volver a colocar esa tarjeta.
- **No:** el contenido sigue sonando después de retirarla.

### Tarjetas Disney compatibles

Esta compilación reconoce determinadas tarjetas Disney sin reescribirlas:

- Algunas tarjetas FUDAN usan las carpetas `97`, `98` o `99`, según el idioma
  activo.
- Las tarjetas Ultralight A reconocidas usan la carpeta fija `96`; el modelo
  de tarjeta determina la pista.

Estas carpetas deben contener los audios correspondientes. No todas las
tarjetas Disney son compatibles.

## 6. Modos de reproducción disponibles

Al crear una tarjeta o acceso directo, el asistente anuncia dieciséis modos.
En esta compilación deben usarse los siguientes:

| Nº | Modo | Funcionamiento |
| ---: | --- | --- |
| 1 | Aleatorio | Reproduce una pista al azar de la carpeta y termina. |
| 2 | Álbum | Reproduce toda la carpeta en orden. |
| 3 | Fiesta | Reproduce todas las pistas al azar y vuelve a barajarlas indefinidamente. |
| 4 | Individual | Reproduce una pista concreta de la carpeta. |
| 5 | Audiolibro | Reproduce en orden y recuerda la siguiente pista para otro día. |
| 6 | Administración | Crea una tarjeta que abre el menú de administración. |
| 7 | Aleatorio De–A | Reproduce una pista al azar entre la primera y la última elegidas. |
| 8 | Álbum De–A | Reproduce en orden el intervalo elegido. |
| 9 | Fiesta De–A | Reproduce al azar y en bucle el intervalo elegido. |
| 10 | Audiolibro individual | Continúa el progreso y reproduce una cantidad elegida de pistas, hasta 30 por uso. |
| 11 | Repetir última tarjeta | Vuelve a iniciar la última tarjeta o acceso directo válido. |
| 16 | Audiolibro De–A | Audiolibro con progreso limitado a un intervalo de pistas. |

Los modos 12–15 (Concurso, Memoria, Bluetooth y Palabras polisémicas) no están
habilitados en `TonUINO_Custom`.

### Progreso de audiolibros

Se memoriza la pista, no el segundo exacto dentro del archivo. Al terminar una
pista se guarda la siguiente; al saltar manualmente se guarda la elegida. Tras
la última pista, el siguiente uso empieza por la primera.

### Carpetas y rangos

- La carpeta debe estar entre `01` y `99`.
- El modo Individual pide una pista.
- Los modos De–A piden primera y última pista.
- Audiolibro y Audiolibro individual permiten seleccionar un intervalo de
  carpetas.
- Audiolibro individual también pide cuántas pistas reproducir.

## 7. Tarjetas de modificación disponibles

Una tarjeta de modificación cambia temporalmente el comportamiento. Presenta
de nuevo la tarjeta activa para desactivarla.

| Nº | Modificación | Efecto |
| ---: | --- | --- |
| 1 | Temporizador | Apaga tras 5, 15, 30 o 60 minutos. Puede hacerlo al vencer o esperar al final de la pista, con un máximo de diez minutos extra. |
| 2 | Baile congelado | Interrumpe la música al azar. Intervalos disponibles: 15–30, 25–40 o 35–50 segundos. |
| 3 | Fuego, agua y viento | Anuncia una acción al azar con los mismos intervalos. |
| 4 | Modo bebé | Bloquea los seis botones; las tarjetas siguen funcionando. |
| 5 | Modo guardería | Solo permite Pausa y deja una nueva tarjeta en espera hasta que termine la pista actual. |
| 6 | Repetir pista | Repite indefinidamente la pista actual. |
| 10 | Desactivar espera | Activa o desactiva temporalmente el temporizador general. |
| 11 | Modo infinito | Activa o desactiva la repetición de la cola actual. |

Las opciones 7–9 (Bluetooth, Jukebox y pausa después de cada pista) no están
habilitadas en esta compilación.

**Modo bebé:** como bloquea también el botón Idioma, vuelve a presentar su
tarjeta de modificación para salir.

## 8. Accesos directos

Los accesos directos ejecutan contenido sin tarjeta:

- **Acceso 1:** mantén Siguiente + Anterior.
- **Acceso 2:** mantén Siguiente en reposo o pausa.
- **Acceso 3:** mantén Anterior en reposo o pausa.

Se configuran en la opción 7 de administración. El cuarto destino «Al
arrancar» aparece en el menú, pero esta compilación no genera la orden necesaria
para ejecutarlo; utiliza los accesos 1–3.

## 9. Menú de administración

### Acceso y navegación

Para solicitar acceso:

- mantén **Reproducir/Pausa + Siguiente + Anterior**; o
- mantén **Reproducir/Pausa + Volumen + + Volumen −**; o
- presenta una tarjeta de administración.

Retira cualquier tarjeta del lector antes de navegar.

- Siguiente o Volumen +: opción siguiente.
- Anterior o Volumen −: opción anterior.
- Pulsación larga en Siguiente/Anterior o Volumen +/−: salto de diez.
- Reproducir/Pausa: confirmar.
- Reproducir/Pausa larga: cancelar o salir.

### Protección

1. **Sin protección:** se permiten las combinaciones de botones.
2. **Solo tarjeta:** únicamente una tarjeta de administración abre el menú.
3. **PIN:** introduce cuatro pulsaciones usando Reproducir/Pausa = 1,
   Siguiente = 2 y Anterior = 3.

### Opciones útiles en esta versión

| Nº | Opción | Uso |
| ---: | --- | --- |
| 1 | Configurar tarjeta | Crear o reconfigurar una tarjeta. |
| 2 | Volumen máximo | Fijar el límite superior. |
| 3 | Volumen mínimo | Fijar el límite inferior. |
| 4 | Volumen inicial | Fijar el volumen al encender. |
| 5 | Ecualizador | Normal, Pop, Rock, Jazz, Clásica o Graves. |
| 6 | Tarjeta de modificación | Crear una de las modificaciones disponibles. |
| 7 | Acceso directo | Configurar los accesos 1–3. |
| 8 | Temporizador de espera | Apagar tras 5, 15, 30 o 60 minutos en reposo/pausa, o no apagar. |
| 9 | Tarjetas por carpeta | Crear consecutivamente una tarjeta Individual por cada pista del intervalo. |
| 11 | Borrar ajustes | Borrar ajustes, accesos y progreso de audiolibros, y restaurar valores iniciales. |
| 12 | Proteger administración | Elegir sin protección, solo tarjeta o PIN. |
| 13 | Pausa al retirar | Activar o desactivar esta conducta. |
| 15 | Idioma inicial | Elegir Español, Italiano o Inglés para cada arranque. |

Las opciones 10 (invertir botones) y 14 (tarjetas de Memoria) aparecen en el
menú común, pero no aportan una función utilizable en esta compilación: hay
botones de volumen separados y el juego Memoria está deshabilitado.

### Escritura por lotes

En la opción 9, selecciona carpeta, primera y última pista. TonUINO anuncia cada
número antes de pedir una tarjeta. Retira cada tarjeta tras la confirmación y
presenta la siguiente. Mantén Reproducir/Pausa para cancelar.

## 10. Solución de problemas

| Problema | Qué comprobar |
| --- | --- |
| No se oye nada | microSD insertada, paquete `sd-card-multilang`, carpetas `mp3` y `advert`, volumen, altavoz y alimentación. |
| Solo funciona un idioma | Usa el contenido completo de `sd-card-multilang`; los mensajes de los tres idiomas deben estar en la misma microSD. |
| El idioma cambia tras reiniciar | El botón Idioma es temporal; guarda el idioma inicial con la opción 15. |
| Una carpeta no reproduce | Debe ser `01`–`99`, contener pistas numéricas consecutivas y coincidir con la tarjeta. |
| No se lee o escribe una tarjeta | Céntrala, mantenla quieta, sepárala de metal y prueba otra tarjeta compatible. |
| No continúa después de pausar | Si está activa la pausa al retirar, vuelve a colocar la tarjeta original. |
| No abre administración | Usa la tarjeta o el PIN configurados. En «solo tarjeta», las combinaciones están bloqueadas. |
| Un modo anunciado no funciona | No uses los modos 12–15 ni los modificadores 7–9 en esta compilación. |
| Se apaga solo | Revisa el temporizador de espera y la tarjeta de temporizador activa. |

---

# User manual in English

## 1. Overview

TonUINO plays audio from a microSD card. RFID/NFC cards select the folder or
track and determine how it is played. Spoken prompts make the box usable and
configurable without a screen.

This version has exactly six buttons:

1. **Play/Pause**
2. **Next**
3. **Previous**
4. **Volume +**
5. **Volume −**
6. **Language**

It does not include the Quiz, Memory, or Teapot games, Bluetooth, Jukebox,
3 × 3 keypad, NeoPixel ring, or ESP32 web interface.

## 2. Preparing the microSD card

To use all three languages, copy `sd-card-multilang` to the root of the
microSD card. Keep:

- `mp3/`: prompts, numbers, and system sounds in all three languages.
- `advert/`: system announcements in all three languages.
- Content folders `01` through `99`.

Store user content in two-digit folders (`01`, `02`, etc.) and use three-digit
numeric track names:

```text
01/
├── 001.mp3
├── 002.mp3
└── 003.mp3
```

Do not rename system files. Always insert the microSD card before power-on.

## 3. Power, language, and shutdown

### Power on

1. Insert the microSD card.
2. Switch TonUINO on.
3. Wait for the greeting.
4. Present a configured card to begin.

**Warning:** holding **Play/Pause + Next + Previous** together during startup
erases all saved settings.

### Changing language

Press **Language** to cycle:

**Spanish → Italian → English → Spanish**

TonUINO announces the selected language. The change immediately applies to
menus, numbers, and announcements while idle, playing, or paused. The Language
button has no effect inside the admin menu.

The button changes language temporarily. After a restart, TonUINO restores the
**startup language** saved with admin option 15.

Compatible language-dependent Disney cards also use the language active when
they are read.

### Shutdown

While idle or paused, hold **Play/Pause** for about one second. The standby
timer or a sleep-timer card can also shut TonUINO down.

## 4. Six-button reference

A long press takes about one second.

| Button/action | While playing | Idle or paused | In menus |
| --- | --- | --- | --- |
| Play/Pause | Pause or resume | Resume paused audio | Confirm |
| Long Play/Pause | Announce current track | Shut down | Cancel/exit |
| Next | Next track | — | Next option |
| Long Next | Skip 10 tracks | Shortcut 2 | Move 10 options forward |
| Previous | Previous track | — | Previous option |
| Long Previous | Go back 10 tracks | Shortcut 3 | Move 10 options back |
| Volume + | Increase volume | Increase volume | Next option |
| Volume − | Decrease volume | Decrease volume | Previous option |
| Language | Change language | Change language | No function in admin |
| Long Next + Previous | Return to first queue track | Shortcut 1 | — |

Hold **Play/Pause + Next + Previous** or
**Play/Pause + Volume + + Volume −** to open the admin menu when its protection
allows button access.

The “Invert volume buttons” setting does not change this five playback-button
plus language-button version.

## 5. RFID/NFC cards

### Playback

1. Place a configured card on the reader.
2. TonUINO reads its folder, mode, and parameters.
3. Playback starts automatically.
4. Another valid card changes the content.

Presenting the same card during its own playback is normally ignored. Supported
tags include MIFARE Mini, Classic 1K/4K, and
Ultralight/NTAG213/215/216.

### Configuring a blank card

A blank card starts the setup assistant automatically:

1. Remove the card when asked.
2. Select a mode with Next/Previous or Volume +/−.
3. Confirm with **Play/Pause**.
4. Select folder `01`–`99` and any requested parameters.
5. Replace the card when prompted.
6. Keep it still until confirmation, then remove it.

Long Play/Pause cancels. If an error is announced, retry with the card centered
and held still.

### Pause on removal

Admin option 13 controls this behavior:

- **Yes:** removing the card that started the audio pauses the box. It resumes
  only when that card is replaced.
- **No:** playback continues after removing the card.

### Compatible Disney cards

This build recognizes selected Disney cards without rewriting them:

- Some FUDAN cards use folder `97`, `98`, or `99` according to the active
  language.
- Recognized Ultralight A cards use fixed folder `96`; the card model selects
  the track.

Those folders must contain the matching audio. Not every Disney card is
supported.

## 6. Available playback modes

The setup assistant announces sixteen modes. Use these in this build:

| No. | Mode | Behavior |
| ---: | --- | --- |
| 1 | Random | Plays one random folder track and stops. |
| 2 | Album | Plays the complete folder in order. |
| 3 | Party | Plays all tracks randomly and reshuffles forever. |
| 4 | Single | Plays one selected folder track. |
| 5 | Audiobook | Plays in order and remembers the next track for later. |
| 6 | Admin | Creates a card that opens the admin menu. |
| 7 | Random from–to | Plays one random track between selected limits. |
| 8 | Album from–to | Plays the selected range in order. |
| 9 | Party from–to | Randomly loops the selected range. |
| 10 | Single audiobook | Resumes progress and plays a selected count, up to 30 tracks per use. |
| 11 | Repeat last card | Restarts the last valid card or shortcut. |
| 16 | Audiobook from–to | Audiobook progress within a selected track range. |

Modes 12–15 (Quiz, Memory, Bluetooth, and Teapot) are not enabled in
`TonUINO_Custom`.

### Audiobook progress

TonUINO stores the track number, not the exact position within the file.
Finishing a track stores the next one; manually skipping stores the selected
one. After the final track, the next session starts from the first.

### Folders and ranges

- Folders must be `01`–`99`.
- Single mode asks for one track.
- From–to modes ask for first and last tracks.
- Audiobook and Single audiobook allow a folder range.
- Single audiobook also asks how many tracks to play.

## 7. Available modifier cards

A modifier card temporarily changes TonUINO behavior. Present the active
modifier card again to disable it.

| No. | Modifier | Effect |
| ---: | --- | --- |
| 1 | Sleep timer | Shuts down after 5, 15, 30, or 60 minutes, either immediately or after the track finishes, with at most ten extra minutes. |
| 2 | Freeze dance | Randomly interrupts music. Intervals: 15–30, 25–40, or 35–50 seconds. |
| 3 | Fire, water, air | Calls a random action using the same intervals. |
| 4 | Toddler mode | Locks all six buttons; cards continue to work. |
| 5 | Kindergarten mode | Allows only Pause and queues one new card until the current track ends. |
| 6 | Repeat track | Repeats the current track forever. |
| 10 | Disable standby | Temporarily toggles the general standby timer. |
| 11 | Endless switch | Toggles repetition of the current queue. |

Options 7–9 (Bluetooth, Jukebox, and pause after each track) are not enabled in
this build.

**Toddler mode:** because it also locks Language, present its modifier card
again to leave the mode.

## 8. Shortcuts

Shortcuts play configured content without a card:

- **Shortcut 1:** hold Next + Previous.
- **Shortcut 2:** hold Next while idle or paused.
- **Shortcut 3:** hold Previous while idle or paused.

Configure them with admin option 7. The fourth “At startup” target is announced,
but this build does not generate the command required to run it; use shortcuts
1–3.

## 9. Admin menu

### Access and navigation

To request access:

- hold **Play/Pause + Next + Previous**; or
- hold **Play/Pause + Volume + + Volume −**; or
- present an admin card.

Remove any card from the reader before navigating.

- Next or Volume +: next option.
- Previous or Volume −: previous option.
- Long Next/Previous or Volume +/−: move ten options.
- Play/Pause: confirm.
- Long Play/Pause: cancel or exit.

### Protection

1. **No protection:** button combinations are allowed.
2. **Card only:** only an admin card opens the menu.
3. **PIN:** enter four presses using Play/Pause = 1, Next = 2, Previous = 3.

### Useful options in this build

| No. | Option | Purpose |
| ---: | --- | --- |
| 1 | Configure card | Create or reconfigure a card. |
| 2 | Maximum volume | Set the upper limit. |
| 3 | Minimum volume | Set the lower limit. |
| 4 | Startup volume | Set the power-on volume. |
| 5 | Equalizer | Normal, Pop, Rock, Jazz, Classic, or Bass. |
| 6 | Modifier card | Create one of the available modifiers. |
| 7 | Shortcut | Configure shortcuts 1–3. |
| 8 | Standby timer | Shut down after 5, 15, 30, or 60 idle/paused minutes, or never. |
| 9 | Folder cards | Sequentially create one Single card per track in a selected range. |
| 11 | Delete settings | Clear settings, shortcuts, and audiobook progress and restore defaults. |
| 12 | Protect admin | Choose no protection, card only, or PIN. |
| 13 | Pause on removal | Enable or disable this behavior. |
| 15 | Startup language | Select Spanish, Italian, or English for every startup. |

Options 10 (invert buttons) and 14 (Memory cards) remain in the common menu but
provide no useful function in this build: it has separate volume buttons and
the Memory game is disabled.

### Batch writing

In option 9, select the folder and first/last tracks. TonUINO announces each
number before requesting a card. Remove each card after confirmation and
present the next one. Hold Play/Pause to cancel.

## 10. Troubleshooting

| Problem | Check |
| --- | --- |
| No sound | Inserted microSD, complete `sd-card-multilang` package, `mp3` and `advert` folders, volume, speaker, and power. |
| Only one language works | The same microSD must contain all three language sets from `sd-card-multilang`. |
| Language changes after restart | The Language button is temporary; save startup language with option 15. |
| A folder will not play | It must be `01`–`99`, contain consecutively numbered tracks, and match the card. |
| A card will not read or write | Center it, hold it still, keep it away from metal, and try another supported card. |
| Playback will not resume | If pause-on-removal is enabled, replace the original card. |
| Admin will not open | Use the configured card or PIN. Button combinations are blocked in card-only mode. |
| An announced mode does not work | Do not use modes 12–15 or modifiers 7–9 in this build. |
| Unexpected shutdown | Check the standby timer and active sleep-timer card. |
