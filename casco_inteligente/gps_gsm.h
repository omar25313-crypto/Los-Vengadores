#pragma once
#include <Arduino.h>

void iniciarGPSGSM();
void actualizarGPS();
bool hayPosicionGPS();
String obtenerLatitudGPS();
String obtenerLongitudGPS();

// Envía un SMS solo si ENABLE_SMS_ALERTS está activado y hay teléfono configurado.
// Por seguridad, los SMS permanecen desactivados por defecto.
bool enviarSMSAlerta(const String &motivo);
