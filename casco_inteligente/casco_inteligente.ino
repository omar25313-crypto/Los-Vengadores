/*
  Casco inteligente - prototipo inicial ESP32
  Estado: demostración básica del botón y buzzer.
  No representa todavía una detección de impacto ni una alerta GPS/GSM validada.

  Cableado provisional:
  - Buzzer: GPIO 32
  - Botón: GPIO 25 conectado entre el pin y GND (INPUT_PULLUP)

  Abrir la carpeta casco_inteligente en Arduino IDE y compilar para la placa ESP32
  correspondiente. La compilación y las pruebas físicas aún deben confirmarse.
*/

#include "alerta.h"

constexpr uint8_t BUTTON_PIN = 25;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  iniciarAlerta();

  Serial.begin(115200);
  Serial.println("Casco inteligente: prueba inicial de boton y buzzer");
}

void loop() {
  const bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);
  actualizarAlerta(buttonPressed);
  delay(10);
}
