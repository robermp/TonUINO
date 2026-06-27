#ifndef SRC_POTENTIOMETER_HPP_
#define SRC_POTENTIOMETER_HPP_

#include <Arduino.h>

#include "commands.hpp"

class Mp3;

class Potentiometer: public CommandSource {
public:

  Potentiometer(Mp3& mp3);
  commandRaw getCommandRaw() override;

private:
  Mp3&            mp3;
};

#endif /* SRC_POTENTIOMETER_HPP_ */
