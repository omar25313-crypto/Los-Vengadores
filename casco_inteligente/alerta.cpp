#include "alerta.h"

namespace {
constexpr uint8_t BUZZER_PIN = 32;
constexpr unsigned int FRECUENCIA_ALERTA_HZ = 2500;
}

void iniciarAlerta() {
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
}

void actualizarAlerta(bool buttonPressed) {
  if (buttonPressed) {
    tone(BUZZER_PIN, FRECUENCIA_ALERTA_HZ);
  } else {
    noTone(BUZZER_PIN);
  }
}
