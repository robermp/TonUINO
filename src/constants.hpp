#ifndef SRC_CONSTANTS_HPP_
#define SRC_CONSTANTS_HPP_

#include <Arduino.h>

// ######################################################################
// ####### default pins #################################################
// ######################################################################

/* #### Classic/Every/Esp32-Nano ###########################################################
 *                         | A0| A1| A2| A3| A4| A5| A6| A7| D0| D1| D2| D3| D5| D6| D7| D8|
 * ------------------------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * Com to DF Player        |   |   |   |   |   |   |   |   |RX*|TX*| RX| TX|   |   |   |   |
 * 3 Button                | P | U | D |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * 5 Button                | P | V+| V-| U | D |   |   |   |   |   |   |   |   |   |   |   |
 * 3x3 Button Board        | P | U | D | A |   |   |   |   |   |   |   |   |   |   |   |   |
 * Open pin for random     |   |   |   |   |   |   |   | x |   |   |   |   |   |   |   |   |
 * Rotary encoder          |   |   |   |CLK| DT|   |   |   |   |   |   |   |   |   |   |   |
 * Potentiometer                    |   |   |   | x |   |   |   |   |   |   |   |   |   |   |   |   |
 * Neo Ring/LED animat.    |   |   |   |   |   |   |   |   |   |   |(x)|   | x |   |   |   |
 * Speaker off             |   |   |   |   |   |   |   |   |   |   |   |   |   | x |   |   |
 * Shutdown                |   |   |   |   |   |   |   |   |   |   |   |   |   |   | x |   |
 * headphone jack detection|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | x |
 * special start shortcut  |   |   |   |   |   |   | x |   |   |   |   |   |   |   |   |   |
 * bat voltage measurement |   |   |   |   |   | x |   |   |   |   |   |   |   |   |   |   |
 * Bluetooth ON/OFF        |   |   |   |   |   |   |   |   |   |   | x*|   |   | x |   |   |
 * Bluetooth Pairing       |   |   |   |   |   |   |   |   |   |   |   | x*|   |   |   | x |
 * Button LED Pins         |   |   |   |   |   | P |   |   |   |   |   |   | D | U |   |   |
 * #########################################################################################
 *
 * (*) Hardware Serial on Every/Esp32-Nano
 */

/* ### AiOplus #########################################################################################
 *                         | A0| A1| A2| A3| A4| A5| A6| A7|D10|D14|D19|D21|D27|D31|D32|D33|D36|D37|A14|
 *                         |   |   |   |   |   |   |   |   |PB2|PC0|PC5|PC7|PD5|PE1|PE2|PE3|PF2|PF3|PF4|
 * ------------------------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * 3 Button                | P | D | U |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * 5 Button                | P | D | U | V-| V+|   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * 3x3 Button Board        | P |   | A | D | U |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
 * Open pin for random     |   |   |   |   |   |   |   | x |   |   |   |   |   |   |   |   |   |   |   |
 * Rotary encoder          |   |   |   |   |   |   |   |   |   |   |   |   |   |CLK| DT|   |CLK| DT|   |
 * Potentiometer                    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | x |
 * Neo Ring/LED animat.    |   |   |   |   |   |   |   |   | x |(x)|   |   |   |   |   |   |   |   |   |
 * Speaker off             |   |   |   |   |   |   |   |   |   |   | x |   |   |   |   |   |   |   |   |
 * Shutdown                |   |   |   |   |   |   |   |   |   |   |   |   | x |   |   |   |   |   |   |
 * headphone jack detection|   |   |   |   |   |   |   |   |   |   |   | x |   |   |   |   |   |   |   |
 * special start shortcut  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | x |   |   |   |
 * bat voltage measurement |   |   |   |   |   |   | x |   |   |   |   |   |   |   |   |   |   |   |   |
 * #####################################################################################################
 */

/* ### AiO #################################################################
 *                         | A0| A1| A2| A3| A4| A5| A6| A7| D5| D6| D7| D8|
 * ------------------------+---+---+---+---+---+---+---+---+---+---+---+---+
 * 3 Button                | P | D | U |   |   |   |   |   |   |   |   |   |
 * 5 Button                | P | D | U | V-| V+|   |   |   |   |   |   |   |
 * 3x3 Button Board        | P |   | A | D | U |   |   |   |   |   |   |   |
 * Open pin for random     |   |   |   |   |   |   |   | x |   |   |   |   |
 * Rotary encoder          |   |   |   |CLK| DT|   |   |   |   |   |   |   |
 * Potentiometer                    |   |   |   | x |   |   |   |   |   |   |   |   |
 * Neo Ring/LED animat.    |   |   |   |   |   |   |   |   | x |   |   |   |
 * Speaker off             |   |   |   |   |   |   |   |   |   |   |   | x |
 * Shutdown                |   |   |   |   |   |   |   |   |   |   | x |   |
 * special start shortcut  |   |   |   |   |   |   | x |   |   |   |   |   |
 * #########################################################################
 */

/* #### Esp32-Wroom32 ##############################################################
 * GPIO                    | 33| 25| 26| 27| 44| 35| 12| 39| 16| 17|  2| 15| 13| 34|
 * Pin                     |D33|D25|D26|D27|D14|D35|D12| VN|RX2|TX2| D2|D15|D13|D34|
 * ------------------------+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
 * Com to DF Player        |   |   |   |   |   |   |   |   | RX| TX|   |   |   |   |
 * 3 Button                | P | U | D |   |   |   |   |   |   |   |   |   |   |   |
 * 5 Button                | P | V+| V-| U | D |   |   |   |   |   |   |   |   |   |
 * 3x3 Button Board        | P | U | D | A |   |   |   |   |   |   |   |   |   |   |
 * Open pin for random     |   |   |   |   |   |   |   | x |   |   |   |   |   |   |
 * Rotary encoder          |   |   |   |CLK| DT|   |   |   |   |   |   |   |   |   |
 * Potentiometer                    |   |   |   | x |   |   |   |   |   |   |   |   |   |   |
 * Neo Ring/LED animat.    |   |   |   |   |   |   |   |   |   |   | x |   |   |   |
 * Speaker off             |   |   |   |   |   |   |   |   |   |   |   | x |   |   |
 * Shutdown                |   |   |   |   |   |   |   |   |   |   |   |   | x |   |
 * headphone jack detection|   |   |   |   |   |   |   |   |   |   |   |   |   | x |
 * special start shortcut  |   |   |   |   |   |   | x |   |   |   |   |   |   |   |
 * bat voltage measurement |   |   |   |   |   | x |   |   |   |   |   |   |   |   |
 * #################################################################################
 */

// ######################################################################
// ####### variant and feature configuration ############################
// ######################################################################

/* Select the right PCB by uncommenting one of the following lines */
//#define TonUINO_Classic
//#define TonUINO_Every
//#define TonUINO_Every_4808
//#define ALLinONE
//#define ALLinONE_Plus
//#define TonUINO_Esp32 100 // Esp32 Nano
//#define TonUINO_Esp32 200 // Esp32 Wroom 32

#include "gpioHelper.hpp"

#if defined(TonUINO_Classic)
DECL_PCB(1)
#endif
#if defined(TonUINO_Every)
DECL_PCB(2)
#endif
#if defined(TonUINO_Every_4808)
DECL_PCB(3)
#endif
#if defined(ALLinONE)
DECL_PCB(4)
#endif
#if defined(ALLinONE_Plus)
DECL_PCB(5)
#endif
#if defined(TonUINO_Esp32)
DECL_PCB(6)
#endif
static_assert(SUM_PCB == 1 , "Please uncomment exactly one of the PCB lines (TonUINO_Classic, TonUINO_Every, etc.).");

// ######################################################################

/* uncomment one of the below lines to enable special button support
 * default: THREEBUTTONS for classic/every
 *          FIVEBUTTONS  for AiO and AiO+
 */
//#define THREEBUTTONS
//#define FIVEBUTTONS
//#define BUTTONS3X3

// ######################################################################

/* If using Nano Every with connected DfPlayer Rx/Tx to D0/D1 uncomment the following line */
//#define DFPlayerUsesHardwareSerial

// ######################################################################

/* uncomment the below line to enable serial input as additional command source
 * -7:             -8: up         -9: upLong
 * -4: allLong     -5: pause      -6: pauseLong
 * -1: up/downLong -2: down       -3: downLong
 * number n > 0: Jump to the nth voice menu entry and select it
 */
//#define SerialInputAsCommand

// ######################################################################

/* uncomment one of the below lines to support a special chip on the DfMiniMp3 player
 *
 * GD3200B:     bad behavior of getFolderTrackCount() - ignores the parameter folder
 *              bad behavior of callback OnPlayFinished - it is also called on advertise tracks
 * MH2024K16SS: no checksums
 * LISP3:       bad behavior of callback OnPlayFinished - it is also called on advertise tracks
 * MP3-TF-16P V3.0 with MH2024K24SS:
 *              very slow
 *              bad behavior of callback OnPlayFinished - it is also called on advertise tracks
 * LKP Player:  no ACK for requests (use Mp3ChipIncongruousNoAck for them)
 */
//#define DFMiniMp3_T_CHIP_GD3200B
//#define DFMiniMp3_T_CHIP_MH2024K16SS
//#define DFMiniMp3_T_CHIP_LISP3
//#define DFMiniMp3_T_CHIP_MH2024K24SS_MP3_TF_16P_V3_0
#define DFMiniMp3_T_CHIP_Mp3ChipIncongruousNoAck

// ######################################################################

/* uncomment the below line to disable shutdown via button (long press play/pause) */
//#define DISABLE_SHUTDOWN_VIA_BUTTON

// ######################################################################

/* uncomment the below line to enable the rotary encoder for volume setting */
//#define ROTARY_ENCODER
/* uncomment the below line to enable the rotary encoder also for next and previous (only one click in one second) */
//#define ROTARY_ENCODER_LONGPRESS

#ifdef ROTARY_ENCODER
#ifdef ALLinONE_Plus
// if using rotary encoder socket
//inline constexpr uint8_t   rotaryEncoderClkPin    = 31; // PE1
//inline constexpr uint8_t   rotaryEncoderDtPin     = 32; // PE2

// if using optional male header
inline constexpr uint8_t   rotaryEncoderClkPin    = 36; // PF2
inline constexpr uint8_t   rotaryEncoderDtPin     = 37; // PF3

#elif TonUINO_Esp32 == 200
inline constexpr uint8_t   rotaryEncoderClkPin    = 27; // (D27)
inline constexpr uint8_t   rotaryEncoderDtPin     = 14; // (D14)

#else
inline constexpr uint8_t   rotaryEncoderClkPin    = A3; // A3
inline constexpr uint8_t   rotaryEncoderDtPin     = A4; // A4
#endif // ALLinONE_Plus

inline constexpr uint8_t   rotaryEncoderDebounce  = 75; // ms
inline constexpr bool      rotaryEncoderPullUp    = false;
#endif // ROTARY_ENCODER

// ######################################################################

/* uncomment the below line to enable the potentiometer for volume setting */
//#define POTENTIOMETER

#ifdef POTENTIOMETER
#ifdef ALLinONE_Plus
inline constexpr uint8_t   potentiometerPin    = A14; // AiO+ PF4

#elif TonUINO_Esp32 == 200
inline constexpr uint8_t   potentiometerPin    = 27 ; // (D27)

#else
inline constexpr uint8_t   potentiometerPin    = A3 ; // AiO/Classic A3
#endif // ALLinONE_Plus
#endif // POTENTIOMETER

// ######################################################################

/* uncomment the below line to enable the NeoPixel ring
 * To have more features (show volume setting) uncomment also NEO_RING_EXT
 */
//#define NEO_RING
//#define NEO_RING_EXT
//#define NEO_RING_2

#ifdef NEO_RING
#ifdef ALLinONE_Plus
inline constexpr uint8_t neoPixelRingPin = 10; // PB2 on AiOplus (extension header, female)

#elif TonUINO_Esp32 == 200
inline constexpr uint8_t neoPixelRingPin =  2; // GPIO02 (D2) on ESP32 Wroom 32

#else
inline constexpr uint8_t neoPixelRingPin = D5; // D5 on AiO/Classic
#endif // ALLinONE_Plus

inline constexpr uint8_t neoPixelNumber  = 24; // Total Number of Pixels

#ifdef NEO_RING_2
#ifdef ALLinONE_Plus
inline constexpr uint8_t neoPixelRingPin2= 14; // PC0 on AiOplus (extension header, female)

#else
inline constexpr uint8_t neoPixelRingPin2= D2; // D2 on AiO/Classic (only Every)
#endif // ALLinONE_Plus
inline constexpr uint8_t neoPixelNumber2 = 24; // Total Number of Pixels
#endif // NEO_RING_2

#endif // NEO_RING

// ######################################################################

/* uncomment the below line to enable the speaker on/off switch for Classic to suppress noise
 * on startup and shutdown (automatically enabled on AiO and AiOplus)
 */
//#define SPKONOFF

#ifdef SPKONOFF
#if not defined(ALLinONE_Plus) and not defined(ALLinONE) and not (TonUINO_Esp32 == 200)
inline constexpr uint8_t       ampEnablePin     = D6;
inline constexpr levelType     ampEnablePinType = levelType::activeHigh;

#elif (TonUINO_Esp32 == 200)
inline constexpr uint8_t       ampEnablePin     = 15; // (D15)
inline constexpr levelType     ampEnablePinType = levelType::activeLow;
#endif
#endif // SPKONOFF

// ######################################################################

/* uncomment the below line to enable the headphone jack detection (automatically enabled on AiOplus) */
//#define HPJACKDETECT

#ifdef HPJACKDETECT
#if not defined(ALLinONE_Plus)  and not (TonUINO_Esp32 == 200)
inline constexpr uint8_t       dfPlayer_noHeadphoneJackDetect     = D8;
inline constexpr levelType     dfPlayer_noHeadphoneJackDetectType = levelType::activeLow;

#elif (TonUINO_Esp32 == 200)
inline constexpr uint8_t        dfPlayer_noHeadphoneJackDetect     = 34; // (D34)
inline constexpr levelType      dfPlayer_noHeadphoneJackDetectType = levelType::activeLow;
#endif
#endif // HPJACKDETECT

// ######################################################################

/* uncomment the below line to ignore the RFID if it is already playing */
//#define DONT_ACCEPT_SAME_RFID_TWICE

/* uncomment the below line to resume playback if the RFID that started the
 * playback is detected again
 */
//#define RESUME_ON_SAME_RFID

/* uncomment the below line to replay the last card or short cut if pressed play/pause
 * in Idle state
 */
//#define REPLAY_ON_PLAY_BUTTON

// ######################################################################

/* uncomment the below line(s) to enable the quiz, memory or teapot game */
//#define QUIZ_GAME
//#define MEMORY_GAME
//#define TEAPOT_GAME

// ######################################################################

/* uncomment the below line to store the last played card in EEPROM */
//#define STORE_LAST_CARD

// ######################################################################

/* uncomment the below line to enable special shortcut on startup via GPIO */
//#define SPECIAL_START_SHORTCUT

#ifdef SPECIAL_START_SHORTCUT
#ifdef ALLinONE_Plus
inline constexpr uint8_t   specialStartShortcutPin     = 33; // PE3

#elif (TonUINO_Esp32 == 200)
inline constexpr uint8_t   specialStartShortcutPin     = 12; // D12

#else
inline constexpr uint8_t   specialStartShortcutPin     = A6; // A6 on AiO/Classic
#endif // ALLinONE_Plus

inline constexpr levelType specialStartShortcutPinType = levelType::activeHigh;
inline constexpr uint8_t   specialStartShortcutFolder  = 1;
inline constexpr uint8_t   specialStartShortcutTrack   = 1;
#endif // SPECIAL_START_SHORTCUT

// ######################################################################

/* uncomment the below line to enable support for BT module */
//#define BT_MODULE

#ifdef BT_MODULE
#ifdef DFPlayerUsesHardwareSerial
inline constexpr uint8_t   btModuleOnPin               =  D2; // D2
inline constexpr uint8_t   btModulePairingPin          =  D3; // D3

#else
inline constexpr uint8_t   btModuleOnPin               =  D6; // D6
inline constexpr uint8_t   btModulePairingPin          =  D8; // D8
#endif

inline constexpr levelType btModuleOnPinType           = levelType::activeHigh;
inline constexpr levelType btModulePairingPinType      = levelType::activeHigh;
inline constexpr unsigned long btModulePairingPulse    = 500;
#endif // BT_MODULE

// ######################################################################

/* uncomment the below line to enable battery voltage measurement (not for ALLinONE, not recommended for TonUINO_Classic) */
//#define BAT_VOLTAGE_MEASUREMENT

#ifdef BAT_VOLTAGE_MEASUREMENT
#if not defined(ALLinONE_Plus) and not defined(ALLinONE) and not (TonUINO_Esp32 == 200)
inline constexpr uint8_t voltageMeasurementPin         = A5;

#elif (TonUINO_Esp32 == 200)
inline constexpr uint8_t voltageMeasurementPin         = 35; // (D35)
#endif // ALLinONE_Plus

#ifdef ALLinONE_Plus
inline constexpr float   voltageMeasurementCorrection  = 2.075; // voltage divider 100k/100k
#endif
#ifdef TonUINO_Classic
inline constexpr float   voltageMeasurementCorrection  = 1.960; // voltage divider 100k/100k
#endif
#ifdef TonUINO_Every
inline constexpr float   voltageMeasurementCorrection  = 2.007; // voltage divider 100k/100k
#endif
#ifdef TonUINO_Every_4808
inline constexpr float   voltageMeasurementCorrection  = 2.007; // voltage divider 100k/100k
#endif
#ifdef TonUINO_Esp32
inline constexpr float   voltageMeasurementCorrection  = 0.710; // voltage divider 100k/100k
#endif

// for Li-Ion
inline constexpr float   batVoltageLow                 = 2.95;
inline constexpr float   batVoltageEmpty               = 2.90;
// for Li-PO
//inline constexpr float   batVoltageLow                 = 3.40;
//inline constexpr float   batVoltageEmpty               = 3.20;
#endif // BAT_VOLTAGE_MEASUREMENT

// ######################################################################

/* uncomment the below lines if you use Pololu Powerswitch or carrier board for shutdown */
//#define USE_POLOLU_SHUTDOWN
//#define USE_CARRIER_BOARD_SHUTDOWN

// ######################################################################

/* uncomment one of the below lines if you want to change the antenna gain of the MFRC522 module */
//#define MRFC522_RX_GAIN RxGain_18dB
//#define MRFC522_RX_GAIN RxGain_23dB
//#define MRFC522_RX_GAIN RxGain_33dB // default
//#define MRFC522_RX_GAIN RxGain_38dB
//#define MRFC522_RX_GAIN RxGain_43dB
//#define MRFC522_RX_GAIN RxGain_48dB
//#define MRFC522_RX_GAIN RxGain_min  // 18dB
//#define MRFC522_RX_GAIN RxGain_avg  // 33dB
#define MRFC522_RX_GAIN RxGain_max  // 48dB - mejora fiabilidad de lectura (tarjetas Disney/UL)

// ######################################################################

/* Soporte de audiocuentos Disney (tarjetas NFC ajenas, no TonUINO).
 * Las tarjetas FUDAN (SAK 0x0A) usan la carpeta base + idioma; las
 * Ultralight A (SAK 0x00) usan una carpeta fija con mapeo de UID a pista.
 */
#ifdef DISNEY_CARDS
inline constexpr uint8_t  disneyFudanFolder = 97; // +idioma (97/98/99)
inline constexpr uint8_t  disneyUlAFolder   = 96;
#endif

// ######################################################################

/* Seleccion de idioma en runtime (ES/IT/EN). Los prompts y numeros se
 * reproducen desde /mp3/ con el prefijo (idioma+1)*1000, de modo que:
 *   idioma 0 (ES) -> 1xxx, idioma 1 (IT) -> 2xxx, idioma 2 (EN) -> 3xxx.
 */
#ifdef LANGUAGE_SELECT
inline constexpr uint8_t  numLanguages    = 3;     // ES, IT, EN
inline constexpr uint16_t languageMp3Step = 1000;  // offset por idioma
inline constexpr uint16_t languageNameMp3 = 309;   // pista que dice el nombre del idioma (en cada pack)
#endif

// ######################################################################

/* uncomment the below lines if you want to have the Jukebox modification card */
//#define MODIFICATION_CARD_JUKEBOX

#ifdef MODIFICATION_CARD_JUKEBOX
inline constexpr uint8_t jukebox_max_cards  = 10;
#endif

// ######################################################################

/* uncomment the below lines if you want to have the Pause after Track modification card */
//#define MODIFICATION_CARD_PAUSE_AFTER_TRACK

// ######################################################################

/* Enable this definition to activate animated LED button support via the LedManager.
 *
 * LED behavior:
 * - Startup:        All LEDs blink one after another.
 * - Awaiting input: All LEDs blink synchronously.
 * - Playing:        All LEDs stay on continuously.
 * - Paused:         Only the Play/Pause LED blinks.
 * - Shutdown:       All LEDs are turned off.
 * - On a valid button press, all LEDs blink once by toggling their current state.
 *
 * Use a series resistor (e.g. 1KΩ) per LED to limit current.
 *
 */

//#define USE_LED_BUTTONS

#ifdef USE_LED_BUTTONS
inline constexpr uint8_t led_play_pin = A5;
inline constexpr uint8_t led_up_pin   = D6;
inline constexpr uint8_t led_down_pin = D5;

inline constexpr unsigned long led_update_interval = 800; // ms
inline constexpr unsigned long led_short_blink     = 400; // ms
#endif // USE_LED_BUTTONS

//#define POWER_HOLD_READY

#ifdef POWER_HOLD_READY
inline constexpr uint8_t power_hold_ready_pin        = D2;
inline constexpr levelType power_hold_ready_pin_type = levelType::activeHigh;
#endif

//#define FOLDER_QUEUE_AUDIOBOOK

/* #################################################################################################
 * ##### normally, the following lines do not have to be edited             ############################
 * #################################################################################################
 */

// ####### rules for buttons ############################

inline constexpr uint8_t lastSortCut         =  24;
#ifdef BUTTONS3X3
#ifdef FIVEBUTTONS
static_assert(false, "The 3x3 Button board doesn't have 5 Buttons");
#endif
inline constexpr uint8_t buttonExtSC_begin   = 101;
inline constexpr uint8_t buttonExtSC_buttons =  18; // <= lastSortCut
#endif // BUTTONS3X3

inline constexpr uint32_t  buttonLongPress       = 1000; // timeout for long press button in ms
inline constexpr uint32_t  buttonLongPressRepeat =  200; // timeout for long press button repeat in ms

/***************************************************************************
 ** Classic ****************************************************************
 ***************************************************************************/

#if defined(TonUINO_Classic) or defined(TonUINO_Every) or defined(TonUINO_Every_4808)
// ####### buttons #####################################

#if defined(FIVEBUTTONS) && defined(LANGUAGE_SELECT)
// Mapeo de pines compatible con el firmware 2.x del fork (con botón de idioma dedicado)
//   play/pause = A4   siguiente = A0   anterior = A3   vol+ = A2   vol- = A1   idioma = A5
inline constexpr uint8_t   buttonPausePin  = A4;
inline constexpr uint8_t   buttonUpPin     = A0;
inline constexpr uint8_t   buttonDownPin   = A3;
inline constexpr uint8_t   buttonFourPin   = A2;
inline constexpr uint8_t   buttonFivePin   = A1;
inline constexpr uint8_t   buttonLangPin   = A5;
#else
inline constexpr uint8_t   buttonPausePin  = A0;

#if defined(BUTTONS3X3)
inline constexpr uint8_t   button3x3Pin    = A3;
inline constexpr uint8_t   buttonUpPin     = A1;
inline constexpr uint8_t   buttonDownPin   = A2;
inline constexpr uint32_t  button3x3DbTime = 50; // Debounce time in milliseconds (default 50ms)
#elif defined(FIVEBUTTONS)
inline constexpr uint8_t   buttonUpPin     = A3;
inline constexpr uint8_t   buttonDownPin   = A4;
inline constexpr uint8_t   buttonFourPin   = A1;
inline constexpr uint8_t   buttonFivePin   = A2;
#else
inline constexpr uint8_t   buttonUpPin     = A1;
inline constexpr uint8_t   buttonDownPin   = A2;
#endif

#endif // FIVEBUTTONS && LANGUAGE_SELECT

inline constexpr levelType buttonPinType   = levelType::activeLow;
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  =  9;
inline constexpr byte     mfrc522_SSPin   = 10;
inline constexpr uint8_t  cardRemoveDelay =  3;

// ####### mp3 #########################################

#ifdef DFPlayerUsesHardwareSerial
inline constexpr HardwareSerial &dfPlayer_serial         = Serial1; // D0 RX, D1 TX (Every)
#else
inline constexpr uint8_t       dfPlayer_receivePin      = 2;
inline constexpr uint8_t       dfPlayer_transmitPin     = 3;
#endif

inline constexpr uint8_t       maxTracksInFolder        = 255;
inline constexpr uint8_t       dfPlayer_busyPin         = 4;
inline constexpr levelType     dfPlayer_busyPinType     = levelType::activeLow;
#if defined(DFMiniMp3_T_CHIP_MH2024K24SS_MP3_TF_16P_V3_0)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#elif defined(DFMiniMp3_T_CHIP_GD3200B)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#else
inline constexpr unsigned long dfPlayer_timeUntilStarts = 1200;
#endif

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin      = 7;
#ifdef USE_CARRIER_BOARD_SHUTDOWN
inline constexpr levelType     shutdownPinType  = levelType::activeLow;
#else
inline constexpr levelType     shutdownPinType  = levelType::activeHigh;
#endif
inline constexpr uint8_t       openAnalogPin    = A7;
inline constexpr unsigned long cycleTime        = 50;
#endif /* TonUINO_Classic or TonUINO_Every or TonUINO_Every_4808 */

/***************************************************************************
 ** AiO plus ***************************************************************
 ***************************************************************************/

#ifdef ALLinONE_Plus
// ####### buttons #####################################

#if not defined(THREEBUTTONS) and not defined(BUTTONS3X3)
#define FIVEBUTTONS
#endif

#define SPKONOFF
#define HPJACKDETECT

inline constexpr uint8_t   buttonPausePin  = A0;

#ifdef BUTTONS3X3
inline constexpr uint8_t   button3x3Pin    = A2;
inline constexpr uint8_t   buttonUpPin     = A4;
inline constexpr uint8_t   buttonDownPin   = A3;
inline constexpr uint32_t  button3x3DbTime = 50; // Debounce time in milliseconds (default 50ms)
#else
inline constexpr uint8_t   buttonUpPin     = A2;
inline constexpr uint8_t   buttonDownPin   = A1;
#endif

#ifdef FIVEBUTTONS
inline constexpr uint8_t   buttonFourPin   = A4;
inline constexpr uint8_t   buttonFivePin   = A3;
#endif

inline constexpr levelType buttonPinType   = levelType::activeLow;
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  = 11;
inline constexpr byte     mfrc522_SSPin   =  7;
inline constexpr uint8_t  cardRemoveDelay =  3;

// ####### mp3 #########################################

#define DFPlayerUsesHardwareSerial
inline constexpr HardwareSerial &dfPlayer_serial         = Serial3;

inline constexpr uint8_t        maxTracksInFolder        = 255;
inline constexpr uint8_t        dfPlayer_busyPin         = 13;
inline constexpr levelType      dfPlayer_busyPinType     = levelType::activeLow;
inline constexpr unsigned long  dfPlayer_timeUntilStarts = 1200;
inline constexpr uint8_t        dfPlayer_noHeadphoneJackDetect     = 21;
inline constexpr levelType      dfPlayer_noHeadphoneJackDetectType = levelType::activeLow;

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin           = 27;
inline constexpr levelType     shutdownPinType       = levelType::activeLow;
inline constexpr uint8_t       ampEnablePin          = 19;
inline constexpr levelType     ampEnablePinType      = levelType::activeLow;
inline constexpr uint8_t       usbAccessPin          = 20;
inline constexpr levelType     usbAccessPinType      = levelType::activeHigh;
inline constexpr uint8_t       voltageMeasurementPin = A6;
inline constexpr uint8_t       openAnalogPin         = A7;
inline constexpr unsigned long cycleTime             = 50;
#endif /* ALLinONE_Plus */

/***************************************************************************
 ** AiO ********************************************************************
 ***************************************************************************/

#ifdef ALLinONE
// ####### buttons #####################################

#if not defined(THREEBUTTONS) and not defined(BUTTONS3X3)
#define FIVEBUTTONS
#endif

#define SPKONOFF

inline constexpr uint8_t   buttonPausePin  = A0;

#ifdef BUTTONS3X3
inline constexpr uint8_t   button3x3Pin    = A2;
inline constexpr uint8_t   buttonUpPin     = A4;
inline constexpr uint8_t   buttonDownPin   = A3;
inline constexpr uint32_t  button3x3DbTime = 50; // Debounce time in milliseconds (default 50ms)
#else
inline constexpr uint8_t   buttonUpPin     = A2;
inline constexpr uint8_t   buttonDownPin   = A1;
#endif

#ifdef FIVEBUTTONS
inline constexpr uint8_t   buttonFourPin   = A4;
inline constexpr uint8_t   buttonFivePin   = A3;
#endif

inline constexpr levelType buttonPinType   = levelType::activeLow;
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  =  9;
inline constexpr byte     mfrc522_SSPin   = 10;
inline constexpr uint8_t  cardRemoveDelay =  3;

// ####### mp3 #########################################

inline constexpr uint8_t       dfPlayer_receivePin      = 2;
inline constexpr uint8_t       dfPlayer_transmitPin     = 3;

inline constexpr uint8_t       maxTracksInFolder        = 255;
inline constexpr uint8_t       dfPlayer_busyPin         = 4;
inline constexpr levelType     dfPlayer_busyPinType     = levelType::activeLow;
inline constexpr unsigned long dfPlayer_timeUntilStarts = 1200;

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin      = 7;
inline constexpr levelType     shutdownPinType  = levelType::activeLow;
inline constexpr uint8_t       ampEnablePin     = 8;
inline constexpr levelType     ampEnablePinType = levelType::activeLow;
inline constexpr uint8_t       usbAccessPin     = A5;
inline constexpr levelType     usbAccessPinType = levelType::activeHigh;
inline constexpr uint8_t       openAnalogPin    = A7;
inline constexpr unsigned long cycleTime        = 50;
#endif /* ALLinONE */

/***************************************************************************
 ** Esp32 ******************************************************************
 ***************************************************************************/

#if defined(TonUINO_Esp32)

/***************************************************************************
 ** Esp32 Nano *************************************************************
 ***************************************************************************/

#if TonUINO_Esp32 == 100
// ####### buttons #####################################

inline constexpr uint8_t   buttonPausePin  = A0;

#if defined(BUTTONS3X3)
inline constexpr uint8_t   button3x3Pin    = A3;
inline constexpr uint8_t   buttonUpPin     = A1;
inline constexpr uint8_t   buttonDownPin   = A2;
inline constexpr uint32_t  button3x3DbTime = 50; // Debounce time in milliseconds (default 50ms)
#elif defined(FIVEBUTTONS)
inline constexpr uint8_t   buttonUpPin     = A3;
inline constexpr uint8_t   buttonDownPin   = A4;
inline constexpr uint8_t   buttonFourPin   = A1;
inline constexpr uint8_t   buttonFivePin   = A2;
#else
inline constexpr uint8_t   buttonUpPin     = A1;
inline constexpr uint8_t   buttonDownPin   = A2;
#endif

inline constexpr levelType buttonPinType   = levelType::activeLow;
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  =  D9;
inline constexpr byte     mfrc522_SSPin   = D10;
inline constexpr uint8_t  cardRemoveDelay =   3;

// ####### mp3 #########################################

#ifdef DFPlayerUsesHardwareSerial
inline constexpr HardwareSerial &dfPlayer_serial         = Serial0; // D0 RX, D1 TX (Esp32)
#else
inline constexpr uint8_t       dfPlayer_receivePin      = D2;
inline constexpr uint8_t       dfPlayer_transmitPin     = D3;
#endif

inline constexpr uint8_t       maxTracksInFolder        = 255;
inline constexpr uint8_t       dfPlayer_busyPin         = D4;
inline constexpr levelType     dfPlayer_busyPinType     = levelType::activeLow;
#if defined(DFMiniMp3_T_CHIP_MH2024K24SS_MP3_TF_16P_V3_0)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#elif defined(DFMiniMp3_T_CHIP_GD3200B)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#else
inline constexpr unsigned long dfPlayer_timeUntilStarts = 1200;
#endif

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin      = D7;
#ifdef USE_CARRIER_BOARD_SHUTDOWN
inline constexpr levelType     shutdownPinType  = levelType::activeLow;
#else
inline constexpr levelType     shutdownPinType  = levelType::activeHigh;
#endif
inline constexpr uint8_t       openAnalogPin    = A7;
inline constexpr unsigned long cycleTime        = 50;


/***************************************************************************
 ** Esp32-Core Development Board *******************************************
 ***************************************************************************/

#elif TonUINO_Esp32 == 200
// ####### buttons #####################################

inline constexpr uint8_t   buttonPausePin  = 33; // (D33)

#if defined(BUTTONS3X3)
inline constexpr uint8_t   button3x3Pin    = 27; // ADC2_7(D27)
inline constexpr uint8_t   buttonUpPin     = 25; // (D25)
inline constexpr uint8_t   buttonDownPin   = 26; // (D26)
inline constexpr uint32_t  button3x3DbTime = 50; // Debounce time in milliseconds (default 50ms)
#elif defined(FIVEBUTTONS)
inline constexpr uint8_t   buttonUpPin     = 27; // (D27)
inline constexpr uint8_t   buttonDownPin   = 14; // (D14)
inline constexpr uint8_t   buttonFourPin   = 25; // (D25)
inline constexpr uint8_t   buttonFivePin   = 26; // (D26)
#else
inline constexpr uint8_t   buttonUpPin     = 25; // (D25)
inline constexpr uint8_t   buttonDownPin   = 26; // (D26)
#endif

inline constexpr levelType buttonPinType   = levelType::activeLow;
inline constexpr uint32_t  buttonDbTime    = 25; // Debounce time in milliseconds (default 25ms)

// ####### chip_card ###################################

inline constexpr uint32_t cardCookie      = 0x1337b347;
inline constexpr uint8_t  cardVersion     = 0x02;
inline constexpr byte     mfrc522_RSTPin  =  22; // (D22)
inline constexpr byte     mfrc522_SSPin   =   5; // (D5)
inline constexpr uint8_t  cardRemoveDelay =   3;

// ####### mp3 #########################################

#ifdef DFPlayerUsesHardwareSerial
inline constexpr HardwareSerial &dfPlayer_serial         = Serial2; // GPIO16 (6) RX, GPIO17 (7) TX (Esp32 Wroom)
#else
inline constexpr uint8_t       dfPlayer_receivePin      =  16; // (RX2)
inline constexpr uint8_t       dfPlayer_transmitPin     =  17; // (TX2)
#endif

inline constexpr uint8_t       maxTracksInFolder        = 255;
inline constexpr uint8_t       dfPlayer_busyPin         =   4; // (D4)
inline constexpr levelType     dfPlayer_busyPinType     = levelType::activeLow;
#if defined(DFMiniMp3_T_CHIP_MH2024K24SS_MP3_TF_16P_V3_0)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#elif defined(DFMiniMp3_T_CHIP_GD3200B)
inline constexpr unsigned long dfPlayer_timeUntilStarts = 2500;
#else
inline constexpr unsigned long dfPlayer_timeUntilStarts = 1200;
#endif

// ####### tonuino #####################################

inline constexpr uint8_t       shutdownPin      = 13; // (D13)
#ifdef USE_POLOLU_SHUTDOWN
inline constexpr levelType     shutdownPinType  = levelType::activeHigh;
#else
inline constexpr levelType     shutdownPinType  = levelType::activeLow;
#endif
inline constexpr uint8_t       openAnalogPin    = 39; // (VN)
inline constexpr unsigned long cycleTime        = 50;

#else //  TonUINO_Esp32 == *
static_assert(false, "Not supported Esp32 HW type");
#endif  //  TonUINO_Esp32 == *

#endif /* TonUINO_Esp32 */


// ####### some helper fuctions #####################################

template <typename T> void PROGMEM_read(const T * sce, T& dest)
{
  memcpy_P (&dest, sce, sizeof (T));
}



#endif /* SRC_CONSTANTS_HPP_ */
