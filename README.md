# TonUINO
La caja de música DIY (no solo) para niños

Este es el software oficial para la caja de música que se describe [aquí](https://www.tonuino.de/TNG). 

Si te interesa contribuir al desarrollo del proyecto TonUINO, estás cordialmente invitado a participar. Para las discusiones utiliza por favor el [foro](https://discourse.voss.earth). Allí encontrarás también más guías y obtendrás ayuda con los problemas. 

# Instrucciones para compilar

## Arduino IDE
Guías generales para configurar el IDE se encuentran aquí [www.tonuino.de/TNG](https://www.tonuino.de/TNG) y aquí [www.leiterkartenpiraten.de](https://www.leiterkartenpiraten.de)

- Es imprescindible asegurarse de que el directorio en el que se clona o descarga el repositorio (es decir, el directorio en el que finalmente se encuentra también el TonUINO-TNG.ino) se llame exactamente igual que el archivo ino, en este caso "TonUINO-TNG".

- En la variante de HW classic (Nano, Every, Every4808 y Esp32) así como AiO, el archivo 'platform.local.txt' debe copiarse en la carpeta de HW avr. Esta carpeta suele ser la siguiente:  

```
    Windows:  
      Classic:  C:\Users\<Benutzer>\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.6
      Every:    C:\Users\<Benutzer>\AppData\Local\Arduino15\packages\arduino\hardware\megaavr\1.8.8
      AiO:      C:\Users\<Benutzer>\AppData\Local\Arduino15\packages\LGT8fx Boards\hardware\avr\1.0.7
      Esp32:    C:\Users\<Benutzer>\AppData\Local\Arduino15\packages\arduino\hardware\esp32\2.0.18-arduino.5

    Linux:  
      Classic:  ~/.arduino15/packages/arduino/hardware/avr/1.8.6
      Every:    ~/.arduino15/packages/arduino/hardware/megaavr/1.8.8
      Aio:      ~/.arduino15/packages/LGT8fx Boards/hardware/avr/1.0.7
      Esp32:    ~/.arduino15/packages/arduino/hardware/esp32/2.0.18-arduino.5/

    MacOS 13.x:  
      Classic:  ~/Library/Arduino15/packages/arduino/hardware/avr/1.8.6
      Every:    ~/Library/Arduino15/packages/arduino/hardware/megaavr/1.8.8
      AiO:      ~/Library/Arduino15/packages/LGT8fx Boards/hardware/avr/1.0.7
      Esp32:    ~/Library/Arduino15/packages/arduino/hardware/esp32/2.0.18-arduino.5/
```

- También se encuentra la carpeta buscando el archivo platform.txt.  

- Para la variante de HW AiOplus no son necesarios cambios  

- La variante de HW (TonUINO_*, ALLinONE o ALLinONE_Plus) así como la configuración de botones (THREEBUTTONS, FIVEBUTTONS o BUTTONS3X3) deben indicarse en el archivo constants.hpp eliminando el comentario correspondiente. (solo si se utiliza el Arduino IDE) 

**Librerías**
- Deben utilizarse las siguientes versiones de las librerías:  
    - jchristensen/JC_Button: 2.1.2  
    - boerge1/MFRC522_fix: 1.4.12  
    - makuna/DFPlayer Mini Mp3 by Makuna: 1.2.3
    - adafruit/Adafruit NeoPixel: 1.11.0 (opcional, solo necesario con la función NEO_RING)

- Para la variante de HW Esp32 adicionalmente:
    - plerup/espsoftwareserial: 8.1.0
    - esp32async/AsyncTCP: 3.3.6
    - esp32async/ESPAsyncWebServer: 3.7.2
    - bblanchon/ArduinoJson: 7.3.0

**ESP32 Nano**
En el Arduino IDE debe configurarse obligatoriamente en "Herramientas/Tools" --> "Pin Numbering" la opción "By GPIO number (legacy)". 

## platform.io

- Se ofrecen las mismas variantes de HW que en la subida online, sin necesidad de editar el archivo constants.hpp

```
  Classic, Every, Every4808, AiO, AiOplus y Esp32
    3 Buttons
    5 Buttons
    3x3 Button Board
    5 Buttons con todas las funciones (solo Every, Esp32 y AiOplus)
```

**Uso junto con Visual Code**

Una guía para ello se encuentra [aquí](https://discourse.voss.earth/t/tonuino-software-mit-platformio-aufspielen/13468)

**Solo platform.io (CLI)**
- instalar platform.io

```
  pip install platformio
```

- Build (elige la [variante específica](platformio.ini) con el flag `-e <environment>`)

```
  pio run
```

- Upload (el puerto se puede encontrar con `pio device list`)

```
  pio run -e <environment> -t upload --upload-port <port>
```

- Monitor

```
  pio device monitor -p <port>
```

# Instalación

La tarjeta SD (carpetas mp3 y advert) ha cambiado respecto a la versión 3.3.2. Aquí se pueden descargar los archivos: [tonuino.github.io/TonUINO-TNG/sd-card.zip](https://tonuino.github.io/TonUINO-TNG/sd-card.zip)

# Conversión de tarjetas Disney Ultralight

Cuando se compila con `DISNEY_CARDS`, las tarjetas Ultralight A de "Cuentos de Mickey y sus amigos" se detectan por SAK `0x00`, ATQA `0x0044` y la Capability Container `E1:10:12:00` en la página `03`. La conversión usa el primer byte de la página `02` para seleccionar la pista de la carpeta fija `96`.

| Tarjeta | Pista | UID | Página 02 | Clave de conversión |
| --- | ---: | --- | --- | --- |
| A | 1 | `53:CF:9A:2D:52:00:01` | `7E:48:00:00` | `0x7E` |
| B | 2 | `53:0E:9B:5F:32:00:01` | `6C:48:00:00` | `0x6C` |
| C | 3 | `53:D6:BD:05:2D:73:00:01` | `5F:48:00:00` | `0x5F` |
| D | 4 | `53:A0:D8:09:98:A1:00:01` | `38:48:00:00` | `0x38` |
| R | 19 | `53:87:30:C6:06:33:00:01` | `34:48:00:00` | `0x34` |

# Notas sobre la configuración WLAN del ESP32

Si se está conectado exclusivamente al AP de TonUINO con el SSID "TonUINO", se accede a la página web con 
cualquier dirección (con al menos un punto), por ejemplo "http://tonuino.t". 
Si además se está conectado a Internet, hay que usar la dirección IP: "http://192.168.4.1". 

# Change Log

## Version 3.3.3 (11.06.2026)
- [Issue 328](https://github.com/tonuino/TonUINO-TNG/issues/328): New modifier card "endless"
- [Issue 319](https://github.com/tonuino/TonUINO-TNG/issues/319): Hoerbuch mode "random folder"
- [Issue 330](https://github.com/tonuino/TonUINO-TNG/issues/330): Compiler error when defining "BOUTTONS3X3"
- [Issue 324](https://github.com/tonuino/TonUINO-TNG/issues/324): Rotary Encoder doesn't work stable for ESP32
- [Issue 322](https://github.com/tonuino/TonUINO-TNG/issues/322): ESP32: add a possibility to indicate that the power hold pin is ready.
- [Issue 321](https://github.com/tonuino/TonUINO-TNG/issues/321): LKP Player with HW serial doesn't not work

## Version 3.3.3 (25.02.2026)
- [Issue 301](https://github.com/tonuino/TonUINO-TNG/issues/301): Support ESP32 Wroom 32
- [Issue 317](https://github.com/tonuino/TonUINO-TNG/issues/317): New play mode: hoerbuch von bis
- [Issue 312](https://github.com/tonuino/TonUINO-TNG/issues/312): Add password protection to wifi AP
- [Issue 313](https://github.com/tonuino/TonUINO-TNG/issues/313): Fix some bugs in the LED Manager
- [Issue 309](https://github.com/tonuino/TonUINO-TNG/issues/309): Improve GPIO handling
- [Issue 303](https://github.com/tonuino/TonUINO-TNG/issues/303): New game: Teekesselchen
- [Issue 302](https://github.com/tonuino/TonUINO-TNG/issues/302): Memory game: ignore second card if it is the same
- [Issue 300](https://github.com/tonuino/TonUINO-TNG/issues/300): Error message when no PCB define was specified

## Version 3.3.2 (19.12.2025)
- [Issue 297](https://github.com/tonuino/TonUINO-TNG/issues/297): Update french translation and add audio files
- [Issue 294](https://github.com/tonuino/TonUINO-TNG/issues/294): Esp32 webinterface: missing mutex on mp3 track queue
- [Issue 292](https://github.com/tonuino/TonUINO-TNG/issues/292): Some improvements for settings and shutdown pin
- [Issue 290](https://github.com/tonuino/TonUINO-TNG/issues/290): Compiler error if HPJACKDETECT is enabled but not SPKONOFF
- [Issue 288](https://github.com/tonuino/TonUINO-TNG/issues/288): Mod card "Disable standby timer": disable also timeouts for quiz and memory game

## Version 3.3.2 (15.11.2025)
- [Issue 284](https://github.com/tonuino/TonUINO-TNG/issues/284): New Modification Card: Disable standby timer
- [Issue 282](https://github.com/tonuino/TonUINO-TNG/issues/282): Allow to jump to a track in the queue via mfc card

## Version 3.3.1 (11.11.2025)
- [Issue 285](https://github.com/tonuino/TonUINO-TNG/issues/285): ESP32: Crash in pages Info and FwUpgrade while getting version
- [Issue 274](https://github.com/tonuino/TonUINO-TNG/issues/278): Proposal - Add Language-Specific Voice Packs (Beginning with English)
- [Issue 278](https://github.com/tonuino/TonUINO-TNG/issues/278): Version string not shown in Log
- [Issue 276](https://github.com/tonuino/TonUINO-TNG/issues/276): Deploy also binary for Esp32

## Version 3.3.0 (26.07.2025)
- [Issue 270](https://github.com/tonuino/TonUINO-TNG/issues/270): Add LedManager to control button LEDs with animated states
- [Issue 272](https://github.com/tonuino/TonUINO-TNG/issues/272): Refactor constants.hpp - Avoid unnecessary global definitions
- [Issue 268](https://github.com/tonuino/TonUINO-TNG/issues/268): Compile Error when using Rotary-Encoder and Classic HW

## Version 3.3.0 (09.07.2025)
- [Issue 259](https://github.com/tonuino/TonUINO-TNG/issues/259): New Hardware Type ESP32 Nano

## Version 3.2.1 (25.03.2025)
- [Issue 265](https://github.com/tonuino/TonUINO-TNG/issues/265): Optonal Feature: Jukebox modifier card

## Version 3.2.1 (16.01.2025)
- [Issue 261](https://github.com/tonuino/TonUINO-TNG/issues/261): Increase the number of addidional Tracks for Mode "Hoerbuch einzeln" to 30
- [Issue 263](https://github.com/tonuino/TonUINO-TNG/issues/263): Initialization: increase delay between the tries of setting volume

## Version 3.2.1 (13.01.2025)
- [Issue 135](https://github.com/tonuino/TonUINO-TNG/issues/135): Make new variants available for online uploads II
- [Issue 254](https://github.com/tonuino/TonUINO-TNG/issues/254): Enhance configuration in constants.hpp
- [Issue 245](https://github.com/tonuino/TonUINO-TNG/issues/245): Support NFC 215 Tags

## Version 3.2.1 (23.11.2024)
- [Issue 251](https://github.com/tonuino/TonUINO-TNG/issues/251): Changes to enable configuration of showdown behavior
- [Issue 250](https://github.com/tonuino/TonUINO-TNG/issues/250): Update the non-German texts for advert and mp3 tracks
- [Issue 248](https://github.com/tonuino/TonUINO-TNG/issues/248): Add the possibility to change the antenna gain of the RFRC522 module

## Version 3.2.1 (14.11.2024)
- [Issue 246](https://github.com/tonuino/TonUINO-TNG/issues/246): With LKP Player there is no pling on startup

## Version 3.2.1 (13.10.2024)
- [Issue 238](https://github.com/tonuino/TonUINO-TNG/issues/238): Pololu sometimes does not switch off in sleep mode
- [Issue 240](https://github.com/tonuino/TonUINO-TNG/issues/240): Some code restructuring
- [Issue 239](https://github.com/tonuino/TonUINO-TNG/issues/239): Starting Quiz or Memory game the "pling" is missing
- [Issue 236](https://github.com/tonuino/TonUINO-TNG/issues/236): Improve hardware diagnostic on startup

## Version 3.2.0 (05.09.2024)
- [Issue 231](https://github.com/tonuino/TonUINO-TNG/issues/231): Fix logging of card data (bad order)
- [Issue 229](https://github.com/tonuino/TonUINO-TNG/issues/229): playAdvertisement does not work for some DF Player
- [Issue 228](https://github.com/tonuino/TonUINO-TNG/issues/228): NeoPixel for two Rings with Sleep modification card: no update on one ring
- [Issue 226](https://github.com/tonuino/TonUINO-TNG/issues/226): Use MegaCoreX as Board package for Nano Every instead of Arduino megaAVR Boards
- [Issue 225](https://github.com/tonuino/TonUINO-TNG/issues/225): Support Nano Every with Atmega4808

## Version 3.1.12 (22.08.2024)
- [Issue 222](https://github.com/tonuino/TonUINO-TNG/issues/222): Fix bug: TB modification card ends active game modification card
- [Issue 220](https://github.com/tonuino/TonUINO-TNG/issues/220): New shortcut for switching BT on/off
- [Issue 219](https://github.com/tonuino/TonUINO-TNG/issues/219): Disable modification cards during quiz and memory game

## Version 3.1.11 (31.07.2024)
- [Issue 212](https://github.com/tonuino/TonUINO-TNG/issues/212): Sleep Timer Modification card doesn't work properly with NeoPixel Ring
- [Issue 215](https://github.com/tonuino/TonUINO-TNG/issues/215): New optional Feature: Support BT Modul
- [Issue 217](https://github.com/tonuino/TonUINO-TNG/issues/217): Improve and fix handling of some DF Player

## Version 3.1.10 (27.06.2024)
- [Issue 210](https://github.com/tonuino/TonUINO-TNG/issues/210): Make text in the admin menu for switching volume button more clearer

## Version 3.1.9 (05.06.2024)
- [Issue 207](https://github.com/tonuino/TonUINO-TNG/issues/207): Use poti for setting the volume: add threshold to prevent continuously switching volume
- [Issue 205](https://github.com/tonuino/TonUINO-TNG/issues/205): Implement the game "Feuer, Wasser, Luft" as modification card

## Version 3.1.8 (26.04.2024)
- [Issue 202](https://github.com/tonuino/TonUINO-TNG/issues/202): Enhance modifier card SleepTimer to stop only after the track finished
- [Issue 200](https://github.com/tonuino/TonUINO-TNG/issues/200): Add possibility to use Pololu-Powerswitch for shutdown
- [Issue 196](https://github.com/tonuino/TonUINO-TNG/issues/196): Enhance Hoerbuch_1 mode to play more tracks
- [Issue 197](https://github.com/tonuino/TonUINO-TNG/issues/197): SPECIAL_START_SHORTCUT: pin A6 cannot be read digital on Nano

## Version 3.1.7 (11.04.2024)
- [Issue 193](https://github.com/tonuino/TonUINO-TNG/issues/193): Hoerbuch mode: after playing last track it does not change to first track on next start
- [Issue 190](https://github.com/tonuino/TonUINO-TNG/issues/190): Neo Pixel Ring: Add the possibility to have 2 rings remains
- [Issue 188](https://github.com/tonuino/TonUINO-TNG/issues/188): Pause when card removed modus: do not go to Play via button if card is not present

## Version 3.1.7 (29.03.2024)
- [Issue 184](https://github.com/tonuino/TonUINO-TNG/issues/184): #define DONT_ACCEPT_SAME_RFID_TWICE makes the error: 'class Tonuino' has no member named 'getCard'
- [Issue 181](https://github.com/tonuino/TonUINO-TNG/issues/181): Implement battery voltage measurement
- [Issue 180](https://github.com/tonuino/TonUINO-TNG/issues/180): Play special shortcut on startup if a GPIO is set
- [Issue 056](https://github.com/tonuino/TonUINO-TNG/issues/56): Implement headphone jack detection
- [Issue 178](https://github.com/tonuino/TonUINO-TNG/issues/178): Use Nano Every optional with HW Serial connection to the DfPlayer

## Version 3.1.7 (25.03.2024)
- [Issue 182](https://github.com/tonuino/TonUINO-TNG/issues/182): Quiz game: do not repeat a question until no question remains
- [Issue 176](https://github.com/tonuino/TonUINO-TNG/issues/176): Implement the memory game

## Version 3.1.6 (18.02.2024)
- [Issue 173](https://github.com/tonuino/TonUINO-TNG/issues/173): Improve Rorary Encoder implementation (also for NANO and optional for next/previous)
- [Issue 135](https://github.com/tonuino/TonUINO-TNG/issues/135): Make new variants available for online upload (3 butonn variants)
- [Issue 167](https://github.com/tonuino/TonUINO-TNG/issues/167): Save the last played card in EEPROM and restore it at startup
- [Issue 155](https://github.com/tonuino/TonUINO-TNG/issues/155): Implement a Quiz Game

## Version 3.1.5 (30.01.2024)
- [Issue 166](https://github.com/tonuino/TonUINO-TNG/issues/166): Issue_166: generateRamdomSeed() does not generate a random value
- [Issue 165](https://github.com/tonuino/TonUINO-TNG/issues/165): 'Play last card' does not work as ShortCut
- [Issue 162](https://github.com/tonuino/TonUINO-TNG/issues/162): Prepare optional feature ROTARY_ENCODER for Nano Every
- [Issue 160](https://github.com/tonuino/TonUINO-TNG/issues/160): Improve the description for platform.io in the Readme
- [Issue 153](https://github.com/tonuino/TonUINO-TNG/issues/153): Some improvements of the DF Player handling
- [Issue 149](https://github.com/tonuino/TonUINO-TNG/issues/149): Add possibility to reset the current track on hoerbuch mode
- [Issue 148](https://github.com/tonuino/TonUINO-TNG/issues/148): New handling of prev and next button on first and last track
- [Issue 147](https://github.com/tonuino/TonUINO-TNG/issues/147): No or bad saving of current track in hoerbuch mode when using prev, prev10 or next10 button
- [Issue 143](https://github.com/tonuino/TonUINO-TNG/issues/143): With some players the start of a track stutters or goes into pause
- [Issue 142](https://github.com/tonuino/TonUINO-TNG/issues/142): Restart last playback if Play/Pause pressed
- [Issue 141](https://github.com/tonuino/TonUINO-TNG/issues/141): Enhance Features for Neo Pixel Ring
- [Issue 132](https://github.com/tonuino/TonUINO-TNG/issues/132): Support DF Player MP3-TF-16P V3.0 with the chip MH2024K-24SS

## Version 3.1.4 (20.11.2023)
- [Issue 138](https://github.com/tonuino/TonUINO-TNG/issues/138): Two new options for when the same RFID card is inserted
- [Issue 130](https://github.com/tonuino/TonUINO-TNG/issues/130): Add circuit diagram
- [Issue 133](https://github.com/tonuino/TonUINO-TNG/issues/133): Cards with version 1 don't work
- [Issue 125](https://github.com/tonuino/TonUINO-TNG/issues/125): platform.local.txt on MacOS
- [Issue 126](https://github.com/tonuino/TonUINO-TNG/issues/126): Support Speaker on/off for Classic Variant to suppress Noise on startup and shutdown 
- [Issue 123](https://github.com/tonuino/TonUINO-TNG/issues/123): Setting of pauseWhenCardRemoved not disabled when upgraded from Version 2.x 
- [Issue 117](https://github.com/tonuino/TonUINO-TNG/issues/117): Support potentiometer for setting the 
- [Issue 120](https://github.com/tonuino/TonUINO-TNG/issues/120): Change to version 1.2.2 of the DFMiniMp3 library
- [Issue 118](https://github.com/tonuino/TonUINO-TNG/issues/118): In modus pause_if_card_removed no shortcut is played
- [Issue 115](https://github.com/tonuino/TonUINO-TNG/issues/115): Sometimes initial SetVolume does not come to an end
- [Issue 103](https://github.com/tonuino/TonUINO-TNG/issues/103): Deploy pages for online upload
- [Issue 111](https://github.com/tonuino/TonUINO-TNG/issues/111): TonUINO crashes if if the player gives a track count >255
- [Issue 108](https://github.com/tonuino/TonUINO-TNG/issues/108): Missing OnPlayFinished: the progress is not saved for Hoerbuch mode
- [Issue 106](https://github.com/tonuino/TonUINO-TNG/issues/106): Support LISP3 DF Player
- [Issue 100](https://github.com/tonuino/TonUINO-TNG/issues/100): Support Nano Every with classic HW
- [Issue 104](https://github.com/tonuino/TonUINO-TNG/issues/104): Use bad framework-lgt8fx
- [Issue 099](https://github.com/tonuino/TonUINO-TNG/issues/99): Use new DFPlayer Mini Mp3 v1.2.1 Library

## Version 3.1.3 (03.08.2023)
- [Issue 073](https://github.com/tonuino/TonUINO-TNG/issues/73): Support LED or NeoPixel Ring
- [Issue 095](https://github.com/tonuino/TonUINO-TNG/issues/95): React on 3x3 Button Board also in Play State
- [Issue 088](https://github.com/tonuino/TonUINO-TNG/issues/88): Flash reset during startup should not open the admin menu
- [Issue 039](https://github.com/tonuino/TonUINO-TNG/issues/39): No pause if card is removed too early
- [Issue 091](https://github.com/tonuino/TonUINO-TNG/issues/91): Revise configuration part of the file constants.hpp
- [Issue 093](https://github.com/tonuino/TonUINO-TNG/issues/93): location for platfrom.txt on macOS does not exist
- [Issue 079](https://github.com/tonuino/TonUINO-TNG/issues/79): Support DF Player GD3200B
- [Issue 085](https://github.com/tonuino/TonUINO-TNG/issues/85): Bad audio message on writing card if card is already present
- [Issue 069](https://github.com/tonuino/TonUINO-TNG/issues/69): Enhance serial input as command source to jump into menu entries
- [Issue 075](https://github.com/tonuino/TonUINO-TNG/issues/75): Optimize Memory (RAM and FLASH) usage
- [Issue 082](https://github.com/tonuino/TonUINO-TNG/issues/82): Speed up VolumeUp/Down when using longpress
- [Issue 070](https://github.com/tonuino/TonUINO-TNG/issues/70): Revise modification cards
- [Issue 076](https://github.com/tonuino/TonUINO-TNG/issues/76): \<\<Phopp\>\> sound at poweroff
- [Issue 072](https://github.com/tonuino/TonUINO-TNG/issues/72): Support Rotary Encoder KY-040 for setting the volume
- Muchas correcciones de errores y mejoras
- [Issue 019](https://github.com/tonuino/TonUINO-TNG/issues/19): Implement support for the 3x3 Button board

## Version 3.1.2 (03.03.2023)
- [Issue 062](https://github.com/tonuino/TonUINO-TNG/issues/62): Add offline TTS coqui to text_to_speach
- [Issue 067](https://github.com/tonuino/TonUINO-TNG/issues/67): Add a hint in the admin menu that the card has to be removed
- [Issue 065](https://github.com/tonuino/TonUINO-TNG/issues/65): Increase dfPlayer_timeUntilStarts
- [Issue 061](https://github.com/tonuino/TonUINO-TNG/issues/61): Fix pin assignment for classic with 5 buttons
- [Issue 054](https://github.com/tonuino/TonUINO-TNG/issues/54): For classic variant: the shutdownPin should be HIGH on shutdown for the POLOLU switch
- [Issue 050](https://github.com/tonuino/TonUINO-TNG/issues/50): Cards with bad version handled as modification cards
- [Issue 038](https://github.com/tonuino/TonUINO-TNG/issues/38): Bad initialization of setting 'pause when card removed'
- [Issue 039](https://github.com/tonuino/TonUINO-TNG/issues/39): No pause if card is removed too early
- [Issue 028](https://github.com/tonuino/TonUINO-TNG/issues/28): Revise Button behavior

## Version 3.1.1 (15.01.2023)
- [Issue 045](https://github.com/tonuino/TonUINO-TNG/issues/45): audio_messages_de.txt isn't up to date.
- [Issue 044](https://github.com/tonuino/TonUINO-TNG/issues/44): Statemachine remains in StartPlay forever is mp3 files missing
- [Issue 034](https://github.com/tonuino/TonUINO-TNG/issues/34): Unit Test Framework and example Tests
- [Issue 026](https://github.com/tonuino/TonUINO-TNG/issues/26): DFMiniMp3 lib support T_CHIP_VARIANT
- Remove strange noise during startup
- [Issue 015](https://github.com/tonuino/TonUINO-TNG/issues/15): Implement command sources
- [Issue 016](https://github.com/tonuino/TonUINO-TNG/issues/16): Shortcut at startup doesn't work
- Bug Fix: Cannot enter Admin Menue with buttons
- [Issue 003](https://github.com/tonuino/TonUINO-TNG/issues/3): Shortcut does not work after power-up
- Bug Fix: Hoerbuch mode: Bad handling of start track
- [Issue 004](https://github.com/tonuino/TonUINO-TNG/issues/4): Implement reaction to empty card
- [Issue 005](https://github.com/tonuino/TonUINO-TNG/issues/5): Update to use new mp3 library version 1.1.0

## Version 3.1 (13.10.2022)
- Añadido soporte para todas las placas de Leiterkartenpiraten (configurable mediante un sencillo #define en `src/constants.hpp`)
  - TonUINO Classic
  - All-in-One
  - All-in-One Plus
  - fix for NTAG213

## Version 3.0 (xx.xx.xxxx) - by Boerge1
- refactorización completa con máquina de estados
- El bucle principal ahora funciona de forma estable con 50 ms
- Nueva función: nuevo modo: Audiolibro individual (solo se reproduce un título y se guarda el progreso)
- Nueva función: Pausa cuando se retira la tarjeta (se puede controlar mediante los ajustes)
- El menú de administración no se abandona después de un ajuste (se puede cambiar fácilmente en el software)
- El menú de administración se puede cancelar en cualquier punto
- Muchas otras mejoras y correcciones de errores

## Version 2.1 (xx.xx.xxxx) noch WIP
- El modo fiesta ahora tiene una cola -> cada canción aparece exactamente 1 vez
- Nuevos modos de reproducción "Modo especial De-Hasta" - Audiocuento, Álbum y Fiesta -> permite, por ejemplo, tener varios álbumes en una carpeta y vincular cada uno con una tarjeta
- Menú de administración
- Volumen máximo, mínimo e inicial
- Las tarjetas ahora se reconfiguran a través del menú de administración
- la función de los botones de volumen (subir/bajar o avanzar/retroceder) se puede intercambiar en el menú de administración
- ¡Los accesos directos (shortcuts) se pueden configurar!
- Añadido soporte para 5 botones
- Restablecimiento de los ajustes movido al menú de administración
- Tarjetas de modificación (temporizador de apagado, bloqueo de botones, baile de la silla, modo guardería)
- El menú de administración se puede proteger

## Version 2.01 (01.11.2018)
- pequeña corrección para reducir los problemas al asociar tarjetas

## Version 2.0 (26.08.2018)

- El volumen ahora se cambia mediante una pulsación larga de botón
- con una pulsación corta se reproduce la pista siguiente / anterior (no disponible según el modo de reproducción)
- Durante la reproducción, con una pulsación larga en Play/Pause se anuncia el número de la pista actual
- Nuevo modo de reproducción: **Modo individual**
  Una tarjeta se puede vincular con un único archivo de una carpeta. Con ello son posibles teóricamente 25000 tarjetas distintas, cada una para un archivo
- Nuevo modo de reproducción: **Modo audiolibro**
  Funciona exactamente como el modo álbum. Además, el progreso se guarda en la EEPROM del Arduino y la próxima vez se reinicia en el último archivo correspondiente. Lamentablemente solo se puede guardar la pista, no la posición dentro de la pista
- Para admitir más de 100 tarjetas, la configuración de las tarjetas ya no se guarda en la EEPROM, sino directamente en las tarjetas; ¡por eso la tarjeta debe permanecer colocada durante la asociación!
- Mediante una pulsación larga en Play/Pause se puede **reconfigurar una tarjeta**
- En los diálogos de selección se puede saltar 10 carpetas o archivos hacia adelante y hacia atrás mediante una pulsación larga de los botones de volumen
- Eliminado el reinicio del módulo MP3 al arrancar; no era necesario y hacía "ruido"

# Open Source 

- jchristensen/JC_Button - GPL 2007
- boerge1/MFRC522_fix - free PD
- makuna/DFPlayer Mini Mp3 by Makuna - LGPL 2007
- adafruit/Adafruit NeoPixel - LGPL 2007
- plerup/espsoftwareserial - LGPL 1999
- esp32async/AsyncTCP - LGPL 2007 
- esp32async/ESPAsyncWebServer - LGPL 2007
- bblanchon/ArduinoJson - MIT
- digint.ch/tinyfsm - free PD (código modificado)
- circuitcode/AsyncWebSerial - MIT (código modificado)
- tuniii/LogRingBuffer - GPL V3+ (código modificado)


