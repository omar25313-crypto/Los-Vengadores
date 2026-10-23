/*
  Casco inteligente ESP32 — prototipo educativo integrado.

  Entradas/salidas provisionales (ver docs/modulos/):
  - MPU6050: I2C SDA=21, SCL=22, dirección 0x68
  - Botón: GPIO 25 a GND (INPUT_PULLUP)
  - Buzzer: GPIO 32
  - GPS UART2: RX=16, TX=17
  - SIM800L UART1: RX=26, TX=27

  IMPORTANTE:
  - Confirmar los pines y alimentación según los módulos físicos.
  - El umbral de impacto es experimental, no detecta todos los accidentes ni certifica seguridad.
  - SMS está desactivado por defecto. Requiere configurar y autorizar pruebas.
*/

#include "alerta.h"
#include "impacto.h"
#include "gps_gsm.h"

constexpr uint8_t BUTTON_PIN = 25;
constexpr uint32_t DURACION_ALERTA_IMPACTO_MS = 10000;

bool sensorImpactoDisponible = false;
bool alertaImpactoActiva = false;
bool botonAnterior = false;
uint32_t finAlertaImpactoMs = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  iniciarAlerta();
  iniciarGPSGSM();

  sensorImpactoDisponible = iniciarSensorImpacto();
  if (sensorImpactoDisponible) {
    Serial.println("MPU6050 detectado; lectura de aceleracion habilitada.");
  } else {
    Serial.println("ERROR: MPU6050 no detectado en I2C 0x68. Revisar SDA/SCL y alimentacion.");
  }
  Serial.println("GPS/GSM inicializados. SMS desactivado por defecto.");
  Serial.println("No usar este prototipo como equipo de proteccion o sistema de emergencia certificado.");
}

void loop() {
  actualizarGPS();

  const bool botonPresionado = (digitalRead(BUTTON_PIN) == LOW);
  const bool nuevoEventoBoton = botonPresionado && !botonAnterior;
  botonAnterior = botonPresionado;

  bool eventoImpacto = false;
  if (sensorImpactoDisponible) {
    eventoImpacto = actualizarSensorImpacto();
    if (eventoImpacto) {
      alertaImpactoActiva = true;
      finAlertaImpactoMs = millis() + DURACION_ALERTA_IMPACTO_MS;
      Serial.print("Umbral experimental de impacto alcanzado. Magnitud g = ");
      Serial.println(obtenerMagnitudAceleracionG(), 2);
    }
  }

  if (nuevoEventoBoton) {
    Serial.println("Boton de alerta presionado.");
  }

  const bool alarmaActiva = botonPresionado ||
    (alertaImpactoActiva && (int32_t)(finAlertaImpactoMs - millis()) > 0);
  if (alertaImpactoActiva && (int32_t)(finAlertaImpactoMs - millis()) <= 0) {
    alertaImpactoActiva = false;
  }
  actualizarAlerta(alarmaActiva);

  // Enviar un SMS por cada nuevo evento; la función no hace nada si sigue desactivada.
  if (eventoImpacto) {
    const bool enviado = enviarSMSAlerta("posible impacto detectado");
    Serial.println(enviado ? "SMS de impacto enviado." : "SMS no enviado (desactivado o modem/GPS sin validar).");
  } else if (nuevoEventoBoton) {
    const bool enviado = enviarSMSAlerta("boton de alerta activado");
    Serial.println(enviado ? "SMS manual enviado." : "SMS no enviado (desactivado o modem no validado).");
  }

  delay(10);
}
