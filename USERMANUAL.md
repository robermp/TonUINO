# TonUINO — Manual de usuario / User manual

- [Español](#manual-de-usuario-en-español)
- [English](#user-manual-in-english)

> TonUINO is a DIY project. The available controls and functions depend on the
> board, button layout, connected accessories, and firmware options selected by
> the person who built it.

---

# Manual de usuario en español

## 1. Qué es TonUINO

TonUINO es un reproductor de audio manejado principalmente mediante tarjetas
RFID/NFC. Cada tarjeta puede iniciar una carpeta, una pista, un audiolibro, un
juego o una función especial. Los mensajes de voz guían la configuración, por
lo que no es necesaria una pantalla.

Este manual describe todas las funciones disponibles en el software. Es
posible que algunas no estén activadas en tu unidad. Consulta a quien instaló
el firmware si un menú o accesorio descrito aquí no aparece.

## 2. Antes del primer uso

### Tarjeta microSD

La microSD debe contener:

- `mp3/`: mensajes de voz, números y sonidos del sistema.
- `advert/`: avisos que se reproducen sobre el audio actual.
- Carpetas de contenido numeradas de `01` a `99`, con las pistas en el orden
  deseado. Usa nombres numéricos de tres cifras, por ejemplo `001.mp3`,
  `002.mp3`, etc.

Puedes usar el paquete de idioma correspondiente incluido en este repositorio
(`sd-card-spanish`, `sd-card-english`, etc.) o el paquete
`sd-card-multilang`. No cambies los nombres de los archivos del sistema.

### Encendido

1. Inserta la microSD antes de encender.
2. Enciende la caja.
3. Espera el saludo y el sonido de inicio.
4. Acerca una tarjeta configurada al lector para reproducirla.

**Atención:** mantener pulsados simultáneamente los tres botones principales
durante el arranque borra los ajustes guardados.

### Apagado

Con la caja en reposo o en pausa, mantén pulsado **Reproducir/Pausa** durante
aproximadamente un segundo. También puede apagarse por el temporizador de
espera, una tarjeta de temporizador, batería agotada o la interfaz web ESP32.
Algunas instalaciones desactivan el apagado mediante botón.

## 3. Botones y controles

Una pulsación larga dura aproximadamente un segundo.

### Funciones comunes

| Acción | En reproducción | En reposo o pausa | En un menú |
| --- | --- | --- | --- |
| Reproducir/Pausa | Pausar o continuar | Continuar, si hay contenido pausado | Confirmar |
| Reproducir/Pausa, pulsación larga | Anunciar el número de pista | Apagar | Cancelar/salir |
| Siguiente + Anterior, pulsación larga | Ir al principio de la cola | Acceso directo 1 | — |
| Los tres botones principales, pulsación larga | Solicitar acceso al menú de administración | Solicitar acceso al menú de administración | — |

Al pausar retirando una tarjeta, no se puede continuar hasta volver a colocarla
si está activada la opción **Pausa al retirar la tarjeta**.

### Versión de tres botones

Los botones laterales tienen dos configuraciones posibles:

| Configuración | Pulsación corta Arriba/Abajo | Pulsación larga Arriba/Abajo |
| --- | --- | --- |
| Invertida (ajuste inicial del firmware) | Subir/bajar volumen | Siguiente/anterior |
| No invertida | Siguiente/anterior | Subir/bajar volumen continuamente |

En reposo o pausa:

- Pulsación larga en **Arriba**: acceso directo 2.
- Pulsación larga en **Abajo**: acceso directo 3.

### Versión de cinco botones

- **Siguiente/Anterior**: cambia una pista; una pulsación larga salta diez.
- **Volumen +/−**: cambia el volumen; mantenlo pulsado para repetir el cambio.
- La inversión de botones no afecta a la versión de cinco botones.
- En reposo, Siguiente/Anterior puede ajustar el brillo del aro NeoPixel.
- En reposo o pausa, una pulsación larga en Siguiente o Anterior inicia los
  accesos directos 2 o 3.

### Menús de voz

- **Siguiente/Anterior**: avanzar o retroceder una opción.
- **Pulsación larga**: avanzar o retroceder diez opciones cuando proceda.
- **Reproducir/Pausa**: confirmar.
- **Reproducir/Pausa, pulsación larga**: cancelar.

La caja anuncia cada valor. Al elegir una carpeta o pista también puede
reproducir una vista previa.

### Controles opcionales

- **Placa 3 × 3:** ofrece 18 botones adicionales configurables como accesos
  directos.
- **Encoder giratorio:** normalmente controla el volumen; una configuración
  alternativa permite cambiar de pista.
- **Potenciómetro:** fija el volumen dentro de los límites configurados.
- **Botón de idioma:** en el firmware personalizado multilingüe cambia en
  tiempo real entre español, italiano e inglés.

## 4. Uso de tarjetas RFID/NFC

### Reproducir una tarjeta

1. Acerca una tarjeta configurada.
2. TonUINO lee de ella la carpeta, el modo y sus parámetros.
3. La reproducción empieza automáticamente.
4. Acercar otra tarjeta válida cambia el contenido. Presentar de nuevo la misma
   tarjeta durante su reproducción normalmente no reinicia el audio.

Se admiten tarjetas MIFARE Mini, Classic 1K/4K y
Ultralight/NTAG213/215/216. La compatibilidad puede depender del lector.

### Configurar una tarjeta vacía

Al detectar una tarjeta vacía, TonUINO inicia automáticamente el asistente:

1. Retira la tarjeta cuando se solicite.
2. Elige el modo de reproducción.
3. Elige la carpeta y los parámetros adicionales solicitados.
4. Confirma cada paso con **Reproducir/Pausa**.
5. Vuelve a colocar la tarjeta cuando oigas «Pon la tarjeta».
6. Retírala después de la confirmación.

La tarjeta debe permanecer quieta mientras se escribe. Un mensaje de error
indica que la escritura falló; vuelve a intentarlo con la tarjeta centrada.

### Pausa al retirar la tarjeta

Si está habilitada en administración, retirar la tarjeta que inició el audio
pone la caja en pausa y volver a colocar la misma tarjeta continúa la
reproducción. Si está deshabilitada, el audio continúa aunque se retire.

### Tarjetas Disney opcionales

Un firmware compilado con esta función puede reconocer determinadas tarjetas
Disney sin reescribirlas. Las tarjetas FUDAN usan carpetas dependientes del
idioma (`97`–`99`) y las Ultralight compatibles usan la carpeta `96`. Solo se
admiten los modelos y códigos configurados en el firmware.

## 5. Modos de reproducción

| Modo | Funcionamiento | Datos que se eligen |
| --- | --- | --- |
| Aleatorio | Reproduce una pista al azar de la carpeta y termina. | Carpeta |
| Álbum | Reproduce toda la carpeta en orden. | Carpeta |
| Fiesta | Reproduce todas las pistas en orden aleatorio y vuelve a barajarlas indefinidamente. | Carpeta |
| Individual | Reproduce una pista concreta. | Carpeta y pista |
| Audiolibro | Reproduce en orden y recuerda la siguiente pista para la próxima vez. Guarda la pista, no la posición dentro del archivo. | Primera y última carpeta |
| Aleatorio De–A | Reproduce una pista al azar dentro de un intervalo. | Carpeta, primera y última pista |
| Álbum De–A | Reproduce en orden solo un intervalo. | Carpeta, primera y última pista |
| Fiesta De–A | Reproduce aleatoriamente y en bucle solo un intervalo. | Carpeta, primera y última pista |
| Audiolibro individual | Continúa el progreso y reproduce una cantidad configurada de pistas (hasta 30 por activación). | Intervalo de carpetas y cantidad |
| Repetir última tarjeta | Vuelve a iniciar la última tarjeta o acceso directo válido. | Ninguno |
| Audiolibro De–A | Como Audiolibro, limitado a un intervalo de pistas. | Carpeta, primera y última pista |
| Concurso | Inicia el juego de preguntas. | Carpeta y formato de respuestas |
| Memoria | Inicia el juego de parejas. | Carpeta |
| Palabras polisémicas | Inicia el juego de adivinanzas. | Carpeta |
| Cambiar Bluetooth | Activa o desactiva el módulo Bluetooth opcional. | Ninguno |
| Administración | Convierte la tarjeta en llave del menú de administración. | Ninguno |

Una carpeta vacía o con nombres que el reproductor no pueda reconocer vuelve al
reposo sin reproducir contenido.

### Progreso de audiolibros

El progreso se guarda por carpeta. Al finalizar una pista se memoriza la
siguiente; al saltar manualmente se memoriza la pista elegida. Al terminar la
última, la siguiente sesión comienza de nuevo por la primera. Las variantes con
varias carpetas eligen una carpeta pendiente dentro del intervalo configurado.

## 6. Juegos opcionales

Los juegos solo aparecen si fueron activados al compilar el firmware.

### Concurso

Cada bloque de archivos de la carpeta debe contener:

1. una pregunta;
2. cero, dos o cuatro respuestas;
3. opcionalmente, una explicación/solución.

Durante el juego:

- Pulsa **Reproducir/Pausa** para obtener una pregunta aleatoria. No se repite
  hasta completar la ronda.
- Usa Siguiente, Anterior y, si están disponibles, Volumen +/− para escuchar
  respuestas.
- Pulsa **Reproducir/Pausa** para comprobar la respuesta elegida.
- En el modo pulsador, esos cuatro botones identifican al jugador más rápido y
  **Reproducir/Pausa** reproduce después la solución.
- Mantén Siguiente + Anterior para salir.

El juego termina tras unos cinco minutos sin interacción, salvo que esté
desactivado temporalmente el temporizador de espera.

### Memoria

Primero crea las tarjetas de memoria desde el menú de administración.

1. Inicia una tarjeta configurada en modo Memoria.
2. Presenta la primera tarjeta de pareja y después la segunda.
3. Pulsa **Reproducir/Pausa** para comprobar si coinciden.
4. El sistema considera pareja las pistas consecutivas `1–2`, `3–4`, etc.
5. Mantén Siguiente + Anterior para terminar.

Una pulsación larga en Reproducir/Pausa vuelve a escuchar la última tarjeta.

### Palabras polisémicas

Cada concepto usa seis pistas: palabra, cuatro descripciones y solución.

- Mantén **Reproducir/Pausa** para iniciar un concepto o revelar la solución.
- Usa los cinco controles para volver a escuchar las descripciones disponibles.
- Mantén Siguiente + Anterior para salir.

## 7. Tarjetas de modificación

Estas tarjetas cambian temporalmente el comportamiento de la caja. Acercar de
nuevo la tarjeta de modificación activa la desactiva.

| Modificación | Efecto |
| --- | --- |
| Temporizador de apagado | Apaga después de 5, 15, 30 o 60 minutos. Puede apagar inmediatamente al vencer o esperar a que termine la pista (máximo diez minutos adicionales). |
| Baile congelado | Interrumpe aleatoriamente la música para jugar. Intervalos: 15–30, 25–40 o 35–50 segundos. |
| Fuego, agua y viento | Anuncia al azar una de las tres acciones usando los mismos intervalos. |
| Modo bebé | Bloquea todos los botones; las tarjetas siguen funcionando. |
| Modo guardería | Solo permite Pausa y deja una nueva tarjeta en espera hasta que termine la pista actual. |
| Repetir pista | Repite indefinidamente la pista actual. |
| Jukebox | Encola hasta diez tarjetas o accesos directos; anuncia su posición. Un sonido avisa si la cola está llena. |
| Pausa tras cada pista | Pone la reproducción en pausa después de cada pista. |
| Desactivar espera | Activa o desactiva temporalmente el temporizador de apagado general. |
| Modo infinito | Activa o desactiva la repetición infinita de la cola actual. |
| Bluetooth | Activa o desactiva el módulo Bluetooth. |

Jukebox, pausa tras cada pista y Bluetooth son funciones opcionales del
firmware.

## 8. Accesos directos

Los accesos directos reproducen contenido sin tarjeta y se configuran en
administración con el mismo asistente de modos.

- **Acceso 1:** pulsación larga simultánea en Siguiente + Anterior.
- **Acceso 2:** pulsación larga en Siguiente estando en reposo o pausa.
- **Acceso 3:** pulsación larga en Anterior estando en reposo o pausa.
- **Placa 3 × 3:** hasta 18 accesos adicionales.

Los accesos directos normales se inician cuando no se está reproduciendo nada.
Con Jukebox activo, un acceso puede añadirse a la cola.

## 9. Menú de administración

### Entrar y salir

Para entrar:

- mantén pulsados los tres botones principales; o
- acerca una tarjeta de administración.

Para salir o cancelar en cualquier nivel, mantén pulsado
**Reproducir/Pausa**. Retira cualquier tarjeta del lector antes de navegar; si
no, TonUINO pedirá retirarla.

### Protección

Hay tres opciones reales:

1. **Sin protección:** se permite la combinación de botones.
2. **Solo tarjeta:** solo una tarjeta de administración permite entrar.
3. **PIN:** introduce cuatro pulsaciones; Reproducir/Pausa = 1, Siguiente = 2 y
   Anterior = 3.

### Opciones

| Nº | Opción | Uso |
| ---: | --- | --- |
| 1 | Configurar tarjeta | Crea o reconfigura una tarjeta de contenido o administración. |
| 2 | Volumen máximo | Fija el límite superior. |
| 3 | Volumen mínimo | Fija el límite inferior. |
| 4 | Volumen inicial | Fija el volumen usado al encender. |
| 5 | Ecualizador | Normal, Pop, Rock, Jazz, Clásica o Graves. |
| 6 | Tarjeta de modificación | Elige una modificación y escribe la tarjeta. |
| 7 | Acceso directo | Elige el acceso y configura su contenido. |
| 8 | Temporizador de espera | Apagado tras 5, 15, 30 o 60 minutos en reposo/pausa, o desactivado. |
| 9 | Tarjetas individuales por carpeta | Escribe consecutivamente una tarjeta por pista dentro del intervalo elegido. |
| 10 | Invertir botones | Intercambia volumen y cambio de pista en la versión de tres botones. |
| 11 | Borrar ajustes | Borra de inmediato ajustes, accesos y progreso de audiolibros, y restaura valores iniciales. |
| 12 | Proteger administración | Selecciona sin protección, solo tarjeta o PIN. |
| 13 | Pausa al retirar tarjeta | Activa o desactiva esta conducta. |
| 14 | Crear tarjetas de memoria | Escribe tarjetas numeradas para el juego; una pulsación corta en Pausa finaliza. |
| 15 | Idioma inicial | Solo en firmware multilingüe; elige español, italiano o inglés. |

Después de guardar una opción, TonUINO vuelve al menú principal de
administración.

### Escritura por lotes

Retira cada tarjeta después de la confirmación y presenta la siguiente cuando
TonUINO anuncie su número. En tarjetas por carpeta, una pulsación larga en
Reproducir/Pausa cancela. En tarjetas de Memoria, una pulsación corta termina
el proceso; Siguiente/Anterior cambia el número que se va a escribir.

## 10. Indicadores y accesorios opcionales

- **Aro NeoPixel:** indica arranque, reposo, reproducción, pausa,
  administración, temporizador y apagado mediante colores/animaciones; en
  reposo se puede cambiar el brillo con Siguiente/Anterior.
- **LED de botones:** secuencia al arrancar, parpadeo conjunto en reposo, todos
  encendidos al reproducir, solo Pausa parpadeando durante la pausa y apagados
  al desconectar.
- **Auriculares:** las placas compatibles apagan el altavoz automáticamente y
  usan límites de volumen independientes.
- **Medición de batería:** un sonido periódico avisa de nivel bajo; un nivel
  crítico mantenido provoca el apagado.
- **Bluetooth:** una pulsación larga en Reproducir/Pausa durante la reproducción
  solicita reconexión/emparejamiento cuando Bluetooth está activo.

## 11. Interfaz web ESP32

Las versiones ESP32 incluyen una interfaz web.

### Conexión

1. Si no hay una red guardada o la conexión falla, busca la red Wi-Fi
   **TonUINO**.
2. Conéctate y abre una dirección con al menos un punto, por ejemplo
   `http://tonuino.t`.
3. Si el dispositivo con el que navegas también tiene Internet, usa
   `http://192.168.4.1`.
4. Si TonUINO se conectó a tu red doméstica, abre su dirección IP o su nombre
   de host.

Mantener **Siguiente** al arrancar fuerza un punto de acceso abierto para
recuperar la configuración Wi-Fi.

### Funciones web

La página principal muestra el estado y permite:

- usar botones virtuales;
- iniciar una carpeta/modo y escribir su configuración en una tarjeta;
- activar o escribir modificadores;
- apagar la caja.

La página de ajustes permite modificar volúmenes de altavoz y auriculares,
ecualizador, temporizador, inversión de botones, protección de administración,
PIN, pausa al retirar y accesos directos. También hay páginas de Wi-Fi, sistema,
registro y actualización de firmware. Reinicia después de cambiar la red si no
se seleccionó el reinicio automático.

Protege la red de acceso y cambia las credenciales de actualización
predeterminadas antes de exponer el dispositivo a una red que no sea de
confianza.

## 12. Solución de problemas

| Problema | Qué comprobar |
| --- | --- |
| No se oye nada | microSD insertada, carpetas `mp3` y `advert`, nombres numéricos, volumen, altavoz/auriculares y alimentación. |
| Una carpeta no reproduce | Debe estar entre `01` y `99`, contener pistas numéricas consecutivas y coincidir con la carpeta grabada en la tarjeta. |
| No lee una tarjeta | Céntrala, mantenla quieta, prueba otra tarjeta compatible y separa el lector de metal o fuentes de interferencia. |
| No escribe una tarjeta | Retírala cuando se pida, vuelve a colocarla centrada y no la muevas hasta la confirmación. |
| No continúa tras una pausa | Si está activa la pausa al retirar, vuelve a colocar la tarjeta original. |
| No puedo abrir administración | Prueba la tarjeta de administración o el PIN configurado. En modo «solo tarjeta», la combinación de botones está bloqueada. |
| Un modo/juego/modificador no aparece | Esa función probablemente no fue incluida en la compilación instalada. |
| Se apaga solo | Revisa el temporizador general, una modificación de apagado y el nivel de batería. |
| ESP32 no aparece en la red | Mantén Siguiente durante el arranque, conéctate al AP `TonUINO` y revisa la configuración Wi-Fi. |
| La tarjeta da error o se ignora | Puede ser incompatible, estar dañada, contener datos de otra versión o haber fallado la lectura. |

---

# User manual in English

## 1. What TonUINO is

TonUINO is an audio player controlled mainly with RFID/NFC cards. Each card can
start a folder, track, audiobook, game, or special function. Spoken prompts
guide configuration, so no screen is required.

This manual describes every feature available in the software. Some may not be
enabled on your unit. Ask the firmware installer if a menu or accessory
described here is missing.

## 2. Before first use

### microSD card

The microSD card must contain:

- `mp3/`: spoken prompts, numbers, and system sounds.
- `advert/`: announcements played over current audio.
- Content folders numbered `01` through `99`, with tracks in the desired
  order. Use three-digit numeric names such as `001.mp3`, `002.mp3`, and so on.

Use the matching language package in this repository (`sd-card-english`,
`sd-card-spanish`, etc.) or `sd-card-multilang`. Do not rename system files.

### Power on

1. Insert the microSD card before switching on.
2. Switch the box on.
3. Wait for the greeting and startup sound.
4. Place a configured card on the reader.

**Warning:** holding all three main buttons together during startup erases the
saved settings.

### Power off

While idle or paused, hold **Play/Pause** for about one second. TonUINO may also
shut down because of the standby timer, a sleep modifier, an empty battery, or
the ESP32 web interface. Some installations disable button shutdown.

## 3. Buttons and controls

A long press takes about one second.

### Common functions

| Action | While playing | Idle or paused | In a menu |
| --- | --- | --- | --- |
| Play/Pause | Pause or resume | Resume paused content | Confirm |
| Long Play/Pause | Announce track number | Shut down | Cancel/exit |
| Long Next + Previous | Jump to the start of the queue | Shortcut 1 | — |
| Long press all three main buttons | Request admin access | Request admin access | — |

If **Pause when card is removed** caused the pause, playback cannot resume
until the card is placed back on the reader.

### Three-button version

The side buttons have two possible configurations:

| Configuration | Short Up/Down | Long Up/Down |
| --- | --- | --- |
| Inverted (firmware default) | Volume up/down | Next/previous track |
| Not inverted | Next/previous track | Continuous volume up/down |

While idle or paused:

- Long **Up**: shortcut 2.
- Long **Down**: shortcut 3.

### Five-button version

- **Next/Previous:** move one track; hold to skip ten.
- **Volume +/−:** change volume; hold for repeated changes.
- Button inversion does not affect the five-button version.
- While idle, Next/Previous may adjust optional NeoPixel brightness.
- While idle or paused, long Next or Previous starts shortcut 2 or 3.

### Voice menus

- **Next/Previous:** move one option.
- **Long press:** move ten options where applicable.
- **Play/Pause:** confirm.
- **Long Play/Pause:** cancel.

TonUINO announces every value. Folder and track selection may also play a
preview.

### Optional controls

- **3 × 3 board:** provides 18 additional configurable shortcut buttons.
- **Rotary encoder:** normally controls volume; an alternate setup changes
  tracks.
- **Potentiometer:** sets volume within the configured limits.
- **Language button:** the custom multilingual firmware cycles between Spanish,
  Italian, and English at runtime.

## 4. Using RFID/NFC cards

### Playing a card

1. Place a configured card on the reader.
2. TonUINO reads its folder, mode, and parameters.
3. Playback starts automatically.
4. Another valid card changes the content. Presenting the same card again
   during playback normally does not restart it.

Supported tags include MIFARE Mini, Classic 1K/4K, and
Ultralight/NTAG213/215/216. Compatibility can depend on the reader.

### Configuring a blank card

A blank card starts the setup assistant automatically:

1. Remove the card when asked.
2. Choose the playback mode.
3. Choose the folder and requested extra parameters.
4. Confirm each step with **Play/Pause**.
5. Place the card back when prompted.
6. Remove it after confirmation.

Keep the card still while it is written. If the generic error prompt plays,
retry with the card centered on the reader.

### Pause when card is removed

When enabled in the admin menu, removing the card that started playback pauses
the box, and placing that same card back resumes it. When disabled, playback
continues after card removal.

### Optional Disney cards

Firmware compiled with this feature can recognize selected Disney cards
without rewriting them. FUDAN cards use language-specific folders `97`–`99`;
compatible Ultralight cards use folder `96`. Only models and codes configured
in the firmware are supported.

## 5. Playback modes

| Mode | Behavior | Selected data |
| --- | --- | --- |
| Random episode | Plays one random track and stops. | Folder |
| Album | Plays the entire folder in order. | Folder |
| Party | Plays all tracks in random order and reshuffles forever. | Folder |
| Single | Plays one selected track. | Folder and track |
| Audiobook | Plays in order and remembers the next track. It saves the track, not a position within the file. | First and last folder |
| Random from–to | Plays one random track within a selected range. | Folder, first and last track |
| Album from–to | Plays only a selected range in order. | Folder, first and last track |
| Party from–to | Shuffles and loops only a selected range. | Folder, first and last track |
| Single audiobook | Resumes progress and plays a configured number of tracks, up to 30 per activation. | Folder range and count |
| Repeat last card | Restarts the last valid card or shortcut. | None |
| Audiobook from–to | Audiobook behavior limited to a track range. | Folder, first and last track |
| Quiz | Starts the question game. | Folder and answer format |
| Memory | Starts the matching game. | Folder |
| Teapot/polysemy | Starts the word guessing game. | Folder |
| Switch Bluetooth | Toggles the optional Bluetooth module. | None |
| Admin | Makes the card an admin-menu key. | None |

An empty folder, or files the player cannot recognize, returns to idle without
playing content.

### Audiobook progress

Progress is saved per folder. Finishing a track stores the next one; skipping
manually stores the selected track. After the final track, the next session
starts from the first. Multi-folder variants select unfinished content within
the configured range.

## 6. Optional games

Games are available only when enabled in the installed firmware.

### Quiz

Each group of files in the folder contains:

1. one question;
2. zero, two, or four answers;
3. optionally, one explanation/solution.

During play:

- Press **Play/Pause** for a random question. Questions do not repeat until the
  round is complete.
- Use Next, Previous, and Volume +/− when available to hear answers.
- Press **Play/Pause** to check the selected answer.
- In buzzer mode, those four buttons identify the fastest player;
  **Play/Pause** then plays the solution.
- Hold Next + Previous to exit.

The game exits after about five minutes without input unless standby
suppression is active.

### Memory

First create the memory cards through the admin menu.

1. Start a card configured in Memory mode.
2. Present the first matching card and then the second.
3. Press **Play/Pause** to check the pair.
4. Consecutive tracks `1–2`, `3–4`, etc. are treated as pairs.
5. Hold Next + Previous to exit.

Long Play/Pause replays the most recently presented card.

### Teapot/polysemy

Each term uses six tracks: term, four descriptions, and solution.

- Hold **Play/Pause** to start a term or reveal its solution.
- Use the five controls to replay the available descriptions.
- Hold Next + Previous to exit.

## 7. Modifier cards

Modifier cards temporarily change the box behavior. Present the active modifier
card again to disable it.

| Modifier | Effect |
| --- | --- |
| Sleep timer | Shuts down after 5, 15, 30, or 60 minutes. It can stop immediately or finish the current track first, with a maximum ten-minute grace period. |
| Freeze dance | Interrupts music at random for the game. Intervals: 15–30, 25–40, or 35–50 seconds. |
| Fire, water, air | Calls one of the three actions at random using the same interval choices. |
| Toddler mode | Locks every button; cards still work. |
| Kindergarten mode | Allows only Pause and queues one newly presented card until the current track ends. |
| Repeat track | Repeats the current track forever. |
| Jukebox | Queues up to ten cards or shortcuts and announces their positions. A chime indicates a full queue. |
| Pause after each track | Pauses playback after every track. |
| Disable standby | Temporarily toggles the general standby timer. |
| Endless switch | Toggles endless repetition of the current queue. |
| Bluetooth | Toggles the Bluetooth module. |

Jukebox, pause-after-track, and Bluetooth depend on firmware options.

## 8. Shortcuts

Shortcuts play configured content without a card and use the same mode setup
assistant as RFID cards.

- **Shortcut 1:** hold Next + Previous together.
- **Shortcut 2:** long Next while idle or paused.
- **Shortcut 3:** long Previous while idle or paused.
- **3 × 3 board:** up to 18 additional shortcuts.

Normal shortcuts start when nothing is playing. With Jukebox active, a shortcut
can be added to the queue.

## 9. Admin menu

### Entering and leaving

To enter:

- hold all three main buttons; or
- present an admin card.

Long-press **Play/Pause** to cancel or leave at any level. Remove any card from
the reader before navigating; otherwise TonUINO asks you to remove it.

### Protection

Three protection choices are operational:

1. **No protection:** the button combination is allowed.
2. **Card only:** only an admin card grants access.
3. **PIN:** enter four button presses; Play/Pause = 1, Next = 2, Previous = 3.

### Options

| No. | Option | Purpose |
| ---: | --- | --- |
| 1 | Configure card | Creates or reconfigures a content or admin card. |
| 2 | Maximum volume | Sets the upper limit. |
| 3 | Minimum volume | Sets the lower limit. |
| 4 | Startup volume | Sets the power-on volume. |
| 5 | Equalizer | Normal, Pop, Rock, Jazz, Classic, or Bass. |
| 6 | Modifier card | Selects a modifier and writes its card. |
| 7 | Shortcut | Selects a shortcut and configures its content. |
| 8 | Standby timer | Shut down after 5, 15, 30, or 60 idle/paused minutes, or disable it. |
| 9 | Single cards for folder | Writes one single-track card for each track in the selected range. |
| 10 | Invert buttons | Swaps volume and track functions on the three-button version. |
| 11 | Delete settings | Immediately clears settings, shortcuts, and audiobook progress and restores defaults. |
| 12 | Protect admin menu | Selects no protection, card only, or PIN. |
| 13 | Pause when card removed | Enables or disables this behavior. |
| 14 | Create memory cards | Writes numbered game cards; short Play/Pause finishes. |
| 15 | Startup language | Multilingual firmware only; selects Spanish, Italian, or English. |

After saving an option, TonUINO returns to the main admin menu.

### Batch writing

Remove each card after confirmation and present the next when TonUINO announces
its number. For folder cards, long Play/Pause cancels. For Memory cards, short
Play/Pause ends the process; Next/Previous changes the number to write.

## 10. Optional indicators and accessories

- **NeoPixel ring:** uses colors/animations for startup, idle, playback, pause,
  admin, sleep countdown, and shutdown; Next/Previous changes brightness while
  idle.
- **Button LEDs:** run in sequence at startup, blink together while idle, stay
  on during playback, blink only Play while paused, and turn off at shutdown.
- **Headphones:** compatible boards turn the speaker off automatically and use
  separate volume limits.
- **Battery measurement:** a periodic chime warns of low voltage; sustained
  critical voltage shuts down the box.
- **Bluetooth:** long Play/Pause during playback requests reconnection/pairing
  while Bluetooth is active.

## 11. ESP32 web interface

ESP32 variants include a web interface.

### Connecting

1. If there is no saved network or connection fails, join the Wi-Fi network
   **TonUINO**.
2. Open an address containing at least one dot, such as
   `http://tonuino.t`.
3. If the browsing device also has Internet access, use
   `http://192.168.4.1`.
4. If TonUINO joined your home network, open its IP address or hostname.

Holding **Next** during startup forces an open access point for Wi-Fi recovery.

### Web features

The home page shows status and can:

- operate virtual buttons;
- start a folder/mode and write that setup to a card;
- activate or write modifiers;
- shut the box down.

The settings page controls speaker/headphone volumes, equalizer, standby
timer, button inversion, admin protection, PIN, pause-on-removal, and
shortcuts. Wi-Fi, system, log, and firmware-upgrade pages are also available.
Restart after changing the network unless automatic restart was selected.

Protect the access-point network and change default firmware-update
credentials before exposing the device to an untrusted network.

## 12. Troubleshooting

| Problem | Check |
| --- | --- |
| No sound | Inserted microSD, `mp3` and `advert` folders, numeric filenames, volume, speaker/headphones, and power. |
| A folder will not play | It must be `01`–`99`, contain consecutively numbered tracks, and match the folder stored on the card. |
| A card is not read | Center it, hold it still, try another supported card, and keep the reader away from metal/interference. |
| A card is not written | Remove it when prompted, replace it centrally, and do not move it before confirmation. |
| Playback will not resume | If pause-on-removal is enabled, replace the original card. |
| Cannot open the admin menu | Use the configured admin card or PIN. The button combination is disabled in card-only mode. |
| A mode/game/modifier is missing | The feature was probably not included in the installed firmware. |
| Unexpected shutdown | Check the standby timer, sleep modifier, and battery level. |
| ESP32 is not reachable | Hold Next during startup, join the `TonUINO` AP, and review Wi-Fi settings. |
| A card errors or is ignored | It may be incompatible, damaged, contain data from another version, or have failed to read. |
