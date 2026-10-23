/*
  Casco inteligente - prototipo inicial ESP32
  Estado: demostración básica del botón y buzzer.
  No representa todavía una detección de impacto ni una alerta GPS/GSM validada.

  Cableado provisional basado en los pines mencionados por el equipo:
  - Buzzer: GPIO 32
  - Botón: GPIO 25 conectado entre el pin y GND

  Si el botón está cableado de otra forma, ajustar INPUT_PULLUP y la lógica.
  Para buzzer pasivo se usa tone(); para buzzer activo puede ser necesario
  usar digitalWrite() según el módulo.
*/

const int BUZZER_PIN = 32;
const int BUTTON_PIN = 25;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  noTone(BUZZER_PIN);

  Serial.begin(115200);
  Serial.println("Casco inteligente: prueba inicial de boton y buzzer");
}

void loop() {
  const bool buttonPressed = (digitalRead(BUTTON_PIN) == LOW);

  if (buttonPressed) {
    // Tono continuo mientras se mantenga presionado el botón.
    tone(BUZZER_PIN, 2500);
  } else {
    noTone(BUZZER_PIN);
  }

  delay(10);
}
