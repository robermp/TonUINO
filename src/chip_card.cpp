#include "chip_card.hpp"

#include <Arduino.h>
#include <SPI.h>

#include "mp3.hpp"
#include "constants.hpp"
#include "tonuino.hpp"
#include "logger.hpp"

// select whether StatusCode and PiccType are printed as names
// that uses about 690 bytes or 2.2% of flash
constexpr bool verbosePrintStatusCode = false;
constexpr bool verbosePrintPiccType   = true;

namespace {

constexpr size_t buffferSizeRead  = 18; // buffer size for read and write
constexpr size_t buffferSizeWrite = 16; // buffer size for read and write

const __FlashStringHelper *str_failed      () { return F(" failed: "    ); }
const __FlashStringHelper *str_MIFARE_Read () { return F("MIFARE_Read " ); }
const __FlashStringHelper *str_MIFARE_Write() { return F("MIFARE_Write "); }

/**
  Helper routine to dump a byte array as hex values to Serial.
*/
constexpr size_t maxBuffferLogSize  = 10;
char n16_hex(uint8_t number) {
  if (number >=16)
    return '?';
  return (number > 9) ? (number - 10) + 'a' : number + '0';
}
void u8toa_hex(uint8_t number, char *arr) {
  arr[0] = n16_hex(number/16);
  arr[1] = n16_hex(number%16);
}
const char* dump_byte_array(byte * buffer, uint8_t bufferSize) {
  static char ret[3*maxBuffferLogSize+1];
  if (bufferSize > maxBuffferLogSize)
    bufferSize = maxBuffferLogSize;
  uint8_t pos = 0;
  for (uint8_t i = 0; i < bufferSize; ++i) {
    u8toa_hex(buffer[i], &ret[pos]);
    pos +=2;
    ret[pos++] = ' ';
  }
  ret[pos] = '\0';
  return ret;
}

auto printStatusCode(MFRC522& mfrc522, MFRC522::StatusCode status) {
  if constexpr (verbosePrintStatusCode)
    return mfrc522.GetStatusCodeName(status);
  else
    return static_cast<byte>(status);
}

auto printPiccType(MFRC522& mfrc522, MFRC522::PICC_Type piccType) {
  if constexpr (verbosePrintPiccType)
    return mfrc522.PICC_GetTypeName(piccType);
  else
    return static_cast<byte>(piccType);
}

MFRC522::MIFARE_Key key{ 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
const byte sector       = 1;
const byte trailerBlock = 7;

#ifdef DISNEY_CARDS
bool readDisneyFudanBlock(MFRC522 &mfrc522, byte block, byte *buffer) {
  byte size = buffferSizeRead;
  return static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(block, buffer, &size)) == MFRC522::STATUS_OK;
}

bool selectDisneyFudan(MFRC522 &mfrc522) {
  byte buffer[buffferSizeRead] = {};

  if (!readDisneyFudanBlock(mfrc522, 0, buffer)) {
    byte atqa[2];
    byte atqaSize = sizeof(atqa);
    mfrc522.PICC_WakeupA(atqa, &atqaSize);
    if (!readDisneyFudanBlock(mfrc522, 0, buffer))
      return false;
  }

  if (buffer[0] != 0x05 || buffer[1] != 0x00)
    return false;

  if (!readDisneyFudanBlock(mfrc522, 1, buffer))
    return false;

  mfrc522.uid.size = 4;
  for (byte i = 0; i < mfrc522.uid.size; ++i)
    mfrc522.uid.uidByte[i] = buffer[i];
  mfrc522.uid.sak = 0x0A;
  return true;
}
#endif
} // namespace

Chip_card::Chip_card(Mp3 &mp3)
: mfrc522(mfrc522_SSPin, mfrc522_RSTPin)
, mp3(mp3)
, cardRemovedSwitch(cardRemoveDelay)
{}

bool Chip_card::auth(MFRC522::PICC_Type piccType) {
  MFRC522::StatusCode status = MFRC522::STATUS_ERROR;

  // Authenticate using key A
  if ((piccType == MFRC522::PICC_TYPE_MIFARE_MINI) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_1K  ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_4K  ) )
  {
    LOG(card_log, s_debug, F("Auth Classic"));
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  }
  else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL ) {
    byte buffer[buffferSizeRead];

    byte size = sizeof(buffer);
    status = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(3, buffer, &size));
    if (status != MFRC522::STATUS_OK) {
      LOG(card_log, s_info, str_MIFARE_Read(), F("3"), str_failed(), printStatusCode(mfrc522, status));
      // Retry once after reselecting the card, useful for transient RF collisions/noise.
      stopCrypto1();
      stopCard();
      byte atqa[2];
      byte atqaSize = sizeof(atqa);
      mfrc522.PICC_WakeupA(atqa, &atqaSize);
      mfrc522.PICC_Select(&mfrc522.uid);
      size = sizeof(buffer);
      status = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(3, buffer, &size));
      if (status != MFRC522::STATUS_OK)
        LOG(card_log, s_info, str_MIFARE_Read(), F("3 retry"), str_failed(), printStatusCode(mfrc522, status));
    }
    else {
      switch (buffer[2]) {
      case 0x12: LOG(card_log, s_info, F("NTAG213")); break;
      case 0x3e: LOG(card_log, s_info, F("NTAG215")); break;
      case 0x6d: LOG(card_log, s_info, F("NTAG216")); break;
      default  : LOG(card_log, s_info, F("NTAG?-"), buffer[2]); break;
      }
    }

//    byte pACK[] = {0, 0}; //16 bit PassWord ACK returned by the tempCard
//
//    // Authenticate using key A
//    LOG(card_log, s_debug, F("Auth UL"));
//    status = mfrc522.PCD_NTAG216_AUTH(key.keyByte, pACK);
  }

  if (status != MFRC522::STATUS_OK) {
    LOG(card_log, s_error, F("Auth "), str_failed(), printStatusCode(mfrc522, status));
    return false;
  }

  return true;
}

#ifdef DISNEY_CARDS
// Detecta y resuelve tarjetas de audiocuentos Disney (NFC ajenas, sin cookie
// TonUINO) fabricando un folderSettings de reproduccion de una sola pista.
// Hay DOS familias compatibles:
//   - Audiocuentos Disney:
//       * FUDAN (SAK 0x0A): la pista se guarda en el byte 0 del bloque 2.
//       * UL_A  (SAK 0x00 + CC E1 10 12 00 sin pagina 4): el byte 0 del bloque 2
//               se mapea a una pista fija (clones Disney conocidos).
//   - Cuentos de Mickey y sus amigos (SAK 0x00 sin CC NDEF, Ultralight "pequeno"
//     con solo paginas 0..3): se tratan como FUDAN; la pista es el byte 0 de la
//     pagina 0 (1er byte de UID).
Chip_card::readCardEvent Chip_card::readDisneyCard(folderSettings &nfcTag) {
  const byte sak = mfrc522.uid.sak & 0x7F;
  byte buffer[buffferSizeRead];
  byte size;

  // FUDAN: la pista es directamente el byte 0 del bloque 2.
  if (sak == 0x0A) {
    size = sizeof(buffer);
    if (mfrc522.MIFARE_Read(2, buffer, &size) != MFRC522::STATUS_OK)
      return readCardEvent::none;
    nfcTag.folder   = disneyFudanFolder;
#ifdef LANGUAGE_SELECT
    nfcTag.folder  += Tonuino::getTonuino().getSettings().language; // 97/98/99
#endif
    nfcTag.mode     = pmode_t::single_track;
    nfcTag.special  = buffer[0];
    nfcTag.special2 = 0;
    LOG(card_log, s_info, F("Disney FUDAN trk "), nfcTag.special);
    return readCardEvent::known;
  }

  // SAK 0x00: dos tipos de tarjeta Disney, ambos Ultralight "pequenos" (solo
  // paginas 0..3). Se distinguen por el CC NDEF de la pagina 3:
  //   - UL_A (audiocuentos): CC E1 10 12 00 y pagina 4 ausente.
  //   - Mickey: sin CC NDEF; se confirma porque la pagina 8 no existe.
  if (sak == 0x00) {
    size = sizeof(buffer);
    if (mfrc522.MIFARE_Read(0, buffer, &size) != MFRC522::STATUS_OK)
      return readCardEvent::none;
    const bool hasNdefCC = (buffer[12] == 0xE1 && buffer[13] == 0x10 && buffer[14] == 0x12 && buffer[15] == 0x00);
    const uint8_t mickeyTrack = buffer[0]; // 1er byte de UID (pista en Mickey)

    // Confirma "Ultralight pequeno": la pagina 4 (UL_A) o la pagina 8 (Mickey)
    // deben devolver NACK/TIMEOUT (no existen). Si existen, es UL/NTAG normal.
    const byte probePage = hasNdefCC ? 4 : 8;
    size = sizeof(buffer);
    const MFRC522::StatusCode st = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(probePage, buffer, &size));
    if (st != MFRC522::STATUS_MIFARE_NACK && st != MFRC522::STATUS_TIMEOUT)
      return readCardEvent::none; // tiene esa pagina -> no es Disney

    // la lectura fallida deja la comunicacion en mal estado: reiniciar
    mfrc522.PICC_HaltA();
    byte atqa[2];
    byte atqaSize = sizeof(atqa);
    mfrc522.PICC_WakeupA(atqa, &atqaSize);
    mfrc522.PICC_Select(&mfrc522.uid);

    if (hasNdefCC) {
      // Audiocuentos Disney UL_A: byte 0 del bloque 2 mapeado a pista fija.
      size = sizeof(buffer);
      if (mfrc522.MIFARE_Read(2, buffer, &size) != MFRC522::STATUS_OK)
        return readCardEvent::none;
      uint8_t id = 0;
      switch (buffer[0]) {
        case 0x7E: id =  1; break;
        case 0x6C: id =  2; break;
        case 0x5F: id =  3; break;
        case 0x34: id = 19; break;
        default  : id =  0; break;
      }
      nfcTag.folder   = disneyUlAFolder;
      nfcTag.mode     = pmode_t::single_track;
      nfcTag.special  = id;
      nfcTag.special2 = 0;
      LOG(card_log, s_info, F("Disney UL_A trk "), nfcTag.special);
      return readCardEvent::known;
    }

    // Cuentos de Mickey y sus amigos: tratada como la familia FUDAN.
    nfcTag.folder   = disneyFudanFolder;
#ifdef LANGUAGE_SELECT
    nfcTag.folder  += Tonuino::getTonuino().getSettings().language; // 97/98/99
#endif
    nfcTag.mode     = pmode_t::single_track;
    nfcTag.special  = mickeyTrack;
    nfcTag.special2 = 0;
    LOG(card_log, s_info, F("Disney Mickey trk "), nfcTag.special);
    return readCardEvent::known;
  }

  return readCardEvent::none;
}
#endif

Chip_card::readCardEvent Chip_card::readCard(folderSettings &nfcTag) {
  // Show some details of the PICC (that is: the tag/card)
  LOG(card_log, s_debug, F("Card UID: "), dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size));
  const MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  LOG(card_log, s_debug, F("PICC type: "), printPiccType(mfrc522, piccType));

#ifdef DISNEY_CARDS
  // Tarjetas Disney (NFC ajenas): se detectan por SAK antes del flujo estandar.
  if (const readCardEvent disney = readDisneyCard(nfcTag); disney == readCardEvent::known) {
    return disney;
  }
#endif

  byte buffer[buffferSizeRead];
  MFRC522::StatusCode status = MFRC522::STATUS_ERROR;

  auto recoverAndSelect = [this]() {
    // Recover from transient RF errors without forcing the user to reinsert.
    stopCrypto1();
    stopCard();
    byte atqa[2];
    byte atqaSize = sizeof(atqa);
    mfrc522.PICC_WakeupA(atqa, &atqaSize);
    mfrc522.PICC_Select(&mfrc522.uid);
  };

  if (not auth(piccType)) {
    recoverAndSelect();
    if (not auth(piccType))
      return readCardEvent::none;
  }
  // Read data from the block
  if ((piccType == MFRC522::PICC_TYPE_MIFARE_MINI) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_1K  ) ||
      (piccType == MFRC522::PICC_TYPE_MIFARE_4K  ) )
  {
    for (uint8_t attempt = 0; attempt < 3; ++attempt) {
      byte size = sizeof(buffer);
      status = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(4, buffer, &size));
      if (status == MFRC522::STATUS_OK)
        break;

      LOG(card_log, s_debug, str_MIFARE_Read(), F("4"), attempt == 0 ? F("") : F(" retry"), str_failed(), printStatusCode(mfrc522, status));
      recoverAndSelect();
      if (auth(piccType))
        continue;
      else
        break;
    }
  }
  else if (piccType == MFRC522::PICC_TYPE_MIFARE_UL ) {
    byte buffer2[buffferSizeRead];

    for (byte block = 8, bufpos = 0; block <= 11; ++block, bufpos += 4) {
      for (uint8_t attempt = 0; attempt < 3; ++attempt) {
        byte size2 = sizeof(buffer2);
        status = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Read(block, buffer2, &size2));
        if (status == MFRC522::STATUS_OK)
          break;

        LOG(card_log, s_debug, str_MIFARE_Read(), block, attempt == 0 ? F("") : F(" retry"), str_failed(), printStatusCode(mfrc522, status));
        recoverAndSelect();
      }

      if (status != MFRC522::STATUS_OK) {
        break;
      }
      memcpy(buffer+bufpos, buffer2, 4);
    }
  }
  stopCrypto1();

  if (status != MFRC522::STATUS_OK) {
    LOG(card_log, s_error, str_MIFARE_Read(), str_failed(), printStatusCode(mfrc522, status));
    return readCardEvent::none;
  }

  LOG(card_log, s_info, F("CardData: "), dump_byte_array(buffer, 9));

  uint32_t tempCookie = 0;
  for (byte i = 0, shift = 24; i < 4; ++i, shift -= 8)
    tempCookie  += static_cast<uint32_t>(buffer[i]) << shift;

  if (tempCookie != cardCookie) {
    if (tempCookie == 0)
      return readCardEvent::empty;
    else
      return readCardEvent::none;
  }
  const uint32_t version              = buffer[4];
  if ((version != 0) && (version <= cardVersion)) {
    nfcTag.folder   = buffer[5];
    nfcTag.mode     = static_cast<pmode_t>(buffer[6]);
    nfcTag.special  = buffer[7];
    nfcTag.special2 = buffer[8];
    if (version == 1) {
      switch (buffer[6]) {
      case 6: nfcTag.mode = pmode_t::audio_play_from_to; break;
      case 7: nfcTag.mode = pmode_t::album_from_to;     break;
      case 8: nfcTag.mode = pmode_t::party_from_to;     break;
      case 9:
#ifdef LANGUAGE_SELECT
        nfcTag.folder += Tonuino::getTonuino().getSettings().language;
#endif
        nfcTag.mode = pmode_t::single_track;
        break;
      default:
        break;
      }
    }
  }
  else {
    LOG(card_log, s_warning, F("bad ver "), version);
    nfcTag.folder   = 0;
    nfcTag.mode     = pmode_t::none;
    return readCardEvent::none;
  }
  return readCardEvent::known;
}

bool Chip_card::writeCard(const folderSettings &nfcTag) {

  constexpr byte coockie_4 = (cardCookie & 0x000000ff) >>  0;
  constexpr byte coockie_3 = (cardCookie & 0x0000ff00) >>  8;
  constexpr byte coockie_2 = (cardCookie & 0x00ff0000) >> 16;
  constexpr byte coockie_1 = (cardCookie & 0xff000000) >> 24;
  byte buffer[buffferSizeWrite] = {coockie_1, coockie_2, coockie_3, coockie_4,          // 0x1337 0xb347 magic cookie to
                                                                                        // identify our nfc tags
                                   cardVersion,                                         // version 1
                                   nfcTag.folder,                     // the folder picked by the user
                                   static_cast<uint8_t>(nfcTag.mode), // the playback mode picked by the user
                                   nfcTag.special,                    // track or function for admin cards
                                   nfcTag.special2,
                                   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
                                  };

  const MFRC522::PICC_Type mifareType = mfrc522.PICC_GetType(mfrc522.uid.sak);

  if (not auth(mifareType))
    return false;

  MFRC522::StatusCode status = MFRC522::STATUS_ERROR;

  // Write data to the block
  LOG(card_log, s_info, F("Writing: "), dump_byte_array(buffer, 9));

  if ((mifareType == MFRC522::PICC_TYPE_MIFARE_MINI) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_1K  ) ||
      (mifareType == MFRC522::PICC_TYPE_MIFARE_4K  ) ) {
    status = (MFRC522::StatusCode)mfrc522.MIFARE_Write(4, buffer, sizeof(buffer));
    if (status != MFRC522::STATUS_OK)
      LOG(card_log, s_debug, str_MIFARE_Write(), F("4"), str_failed(), printStatusCode(mfrc522, status));
  }
  else if (mifareType == MFRC522::PICC_TYPE_MIFARE_UL ) {
    byte buffer2[4];

    for (byte block = 8, bufpos = 0; block <= 11; ++block, bufpos += 4) {
      memcpy(buffer2, buffer+bufpos, 4);
      status = static_cast<MFRC522::StatusCode>(mfrc522.MIFARE_Ultralight_Write(block, buffer2, sizeof(buffer2)));
      if (status != MFRC522::STATUS_OK) {
        LOG(card_log, s_debug, str_MIFARE_Write(), block, str_failed(), printStatusCode(mfrc522, status));
        break;
      }
    }
  }
  stopCrypto1();

  if (status != MFRC522::STATUS_OK) {
    LOG(card_log, s_error, str_MIFARE_Write(), str_failed(), printStatusCode(mfrc522, status));
    return false;
  }
  return true;
}

void Chip_card::sleepCard() {
  mfrc522.PCD_AntennaOff   ();
  mfrc522.PCD_SoftPowerDown();
}

void Chip_card::initCard() {
  SPI.begin();                                                    // Init SPI bus
  mfrc522.PCD_Init();                                             // Init MFRC522
  LOG_CODE(card_log, s_debug, {
      if (not mfrc522.PCD_PerformSelfTest())
        LOG(card_log, s_debug, F("mfrc522 self test not successful"));
  });
  byte ver = mfrc522.PCD_ReadRegister(MFRC522::VersionReg);
  LOG(card_log, s_info, F("MFRC522:"), ver);
  // Show MFRC522 Card Reader version
  // 0 or 255: communication  error)
  //      136: (clone)
  //      144: v0.0
  //      145: v1.0
  //      146: v2.0
  //       18: counterfeit chip
  //     else: unknown
  if ((ver == 0) || (ver == 255)) {
    LOG(card_log, s_error, F("com to mfrc broken"));
    return;
  }
#ifdef MRFC522_RX_GAIN
  mfrc522.PCD_SetAntennaGain(mfrc522.MRFC522_RX_GAIN);
#endif
}

void Chip_card::stopCard() {
  mfrc522.PICC_HaltA();
}

void Chip_card::stopCrypto1() {
  mfrc522.PCD_StopCrypto1();
}

cardEvent Chip_card::getCardEvent() {
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);
  MFRC522::StatusCode result = mfrc522.PICC_RequestA(bufferATQA, &bufferSize);

  // Fiabilidad: una sola REQA puede no ver una tarjeta recien colocada con
  // acoplamiento debil (tipico en tarjetas Disney / Ultralight). Mientras no
  // haya tarjeta presente reintentamos con WUPA, que ademas despierta tarjetas
  // en estado HALT. Solo se reintenta sin tarjeta para no retrasar la deteccion
  // de retirada.
  if (result != mfrc522.STATUS_OK && cardRemoved) {
    bufferSize = sizeof(bufferATQA);
    result = mfrc522.PICC_WakeupA(bufferATQA, &bufferSize);
  }

  if(result != mfrc522.STATUS_OK) {
    ++cardRemovedSwitch;
  } else {
    bool selected = mfrc522.PICC_ReadCardSerial();
#ifdef DISNEY_CARDS
    if (!selected)
      selected = selectDisneyFudan(mfrc522);
#endif
    if (selected)
      cardRemovedSwitch.reset();
    else
      ++cardRemovedSwitch;
  }

  if (cardRemovedSwitch.on()) {
    if (not cardRemoved) {
      LOG(card_log, s_info, F("Card Rem"));
      cardRemoved = true;
      stopCard();
      return cardEvent::removed;
    }
  }
  else {
    if (cardRemoved) {
      LOG(card_log, s_info, F("Card Ins"));
      cardRemoved = false;
      return cardEvent::inserted;
    }
  }
  return cardEvent::none;
}

