#include "potentiometer.hpp"

#include "constants.hpp"

#ifdef POTENTIOMETER
#include "logger.hpp"
#include "mp3.hpp"

#if defined(ALLinONE) or defined(TonUINO_Esp32)
  static constexpr int16_t maxLevel = 4064;
#else
  static constexpr int16_t maxLevel = 1023;
#endif


Potentiometer::Potentiometer(Mp3& mp3)
: CommandSource()
, mp3(mp3)
{
  pinMode(potentiometerPin, INPUT);
}

commandRaw Potentiometer::getCommandRaw() {
  const uint8_t volume = map( analogRead(potentiometerPin), 0, maxLevel, mp3.getMinVolume(), mp3.getMaxVolume());

  if (volume < mp3.getVolume()) {
    LOG(button_log, s_debug, F("potentiometer volume: "), volume);
    mp3.setVolume(volume);
  }
  else if (volume > mp3.getVolume()+1) {
    LOG(button_log, s_debug, F("potentiometer volume: "), volume-1);
    mp3.setVolume(volume-1);
  }

  return commandRaw::none;
}

#endif // POTENTIOMETER
