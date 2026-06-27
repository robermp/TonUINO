#include "card_latency.hpp"

namespace {

bool active = false;
unsigned long t0 = 0;
constexpr bool emitSerial = false;

void emit(uint8_t id) {
  if (!emitSerial)
    return;
  const unsigned long total = millis() - t0;
  Serial.write('C');
  Serial.write(':');
  Serial.print(id);
  Serial.write(',');
  Serial.println(total);
}

}

namespace CardLatency {

void start(uint8_t id) {
  t0 = millis();
  active = true;
  emit(id);
}

void mark(uint8_t id) {
  if (!active)
    return;
  emit(id);
}

void stop(uint8_t id) {
  if (!active)
    return;
  emit(id);
  active = false;
}

bool isActive() {
  return active;
}

}
