#ifndef SRC_CARD_LATENCY_HPP_
#define SRC_CARD_LATENCY_HPP_

#include <Arduino.h>

namespace CardLatency {

void start(uint8_t id);
void mark(uint8_t id);
void stop(uint8_t id);
bool isActive();

}

#endif /* SRC_CARD_LATENCY_HPP_ */
