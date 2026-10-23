#pragma once
#include <Arduino.h>

// MPU6050 en I2C. Se usa aceleración en m/s^2 y un umbral configurable.
// Este detector es experimental; no certifica que el casco detecte todos los accidentes.
bool iniciarSensorImpacto();
bool actualizarSensorImpacto();
float obtenerMagnitudAceleracionG();
