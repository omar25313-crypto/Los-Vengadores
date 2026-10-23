#include "impacto.h"
#include <Wire.h>
#include <math.h>

namespace {
constexpr uint8_t MPU6050_ADDR = 0x68;
constexpr uint8_t REG_PWR_MGMT_1 = 0x6B;
constexpr uint8_t REG_ACCEL_XOUT_H = 0x3B;
constexpr uint8_t REG_ACCEL_CONFIG = 0x1C;
constexpr float ESCALA_ACCEL_G = 4096.0f; // rango ±8 g
constexpr float UMBRAL_IMPACTO_G = 2.5f;    // ajustar solo con pruebas controladas
constexpr uint32_t INTERVALO_MINIMO_MS = 1500;
float magnitudG = 1.0f;
uint32_t ultimoEventoMs = 0;

bool escribirRegistro(uint8_t reg, uint8_t valor) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(reg);
  Wire.write(valor);
  return Wire.endTransmission() == 0;
}

bool leerAcelerometro(int16_t &ax, int16_t &ay, int16_t &az) {
  Wire.beginTransmission(MPU6050_ADDR);
  Wire.write(REG_ACCEL_XOUT_H);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU6050_ADDR, (uint8_t)6) != 6) return false;
  ax = (int16_t)((Wire.read() << 8) | Wire.read());
  ay = (int16_t)((Wire.read() << 8) | Wire.read());
  az = (int16_t)((Wire.read() << 8) | Wire.read());
  return true;
}
}

bool iniciarSensorImpacto() {
  Wire.begin(21, 22); // SDA, SCL por defecto para ESP32 Dev Module
  delay(50);
  Wire.beginTransmission(MPU6050_ADDR);
  if (Wire.endTransmission() != 0) return false;
  if (!escribirRegistro(REG_PWR_MGMT_1, 0x00)) return false; // salir del modo sleep
  delay(100);
  return escribirRegistro(REG_ACCEL_CONFIG, 0x10); // rango de acelerómetro ±8 g
}

bool actualizarSensorImpacto() {
  int16_t ax, ay, az;
  if (!leerAcelerometro(ax, ay, az)) return false;
  const float x = ax / ESCALA_ACCEL_G;
  const float y = ay / ESCALA_ACCEL_G;
  const float z = az / ESCALA_ACCEL_G;
  magnitudG = sqrtf(x*x + y*y + z*z);
  const uint32_t ahora = millis();
  if (magnitudG >= UMBRAL_IMPACTO_G &&
      (ahora - ultimoEventoMs) >= INTERVALO_MINIMO_MS) {
    ultimoEventoMs = ahora;
    return true;
  }
  return false;
}

float obtenerMagnitudAceleracionG() {
  return magnitudG;
}
