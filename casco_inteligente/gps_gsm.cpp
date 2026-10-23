#include "gps_gsm.h"
#include <stdlib.h>
#include <string.h>

// UART GPS: ESP32 RX=16, TX=17. UART SIM800L: ESP32 RX=26, TX=27.
// Cablear TX del módulo al RX del ESP32 y RX del módulo al TX del ESP32.
// Confirmar pines con el montaje real antes de energizar.

#ifndef ENABLE_SMS_ALERTS
#define ENABLE_SMS_ALERTS 0
#endif
#ifndef EMERGENCY_PHONE
#define EMERGENCY_PHONE ""
#endif

namespace {
HardwareSerial gpsSerial(2);
HardwareSerial gsmSerial(1);
constexpr int GPS_RX_PIN = 16;
constexpr int GPS_TX_PIN = 17;
constexpr int GSM_RX_PIN = 26;
constexpr int GSM_TX_PIN = 27;
constexpr uint32_t GPS_BAUD = 9600;
constexpr uint32_t GSM_BAUD = 9600;
char nmeaLine[120];
size_t nmeaIndex = 0;
bool gpsFix = false;
String latitude = "";
String longitude = "";

String coordenadaDecimal(const char *raw, const char *hemisferio) {
  if (!raw || !raw[0] || !hemisferio || !hemisferio[0]) return "";
  const double n = atof(raw);
  const int grados = (int)(n / 100.0);
  const double minutos = n - (grados * 100.0);
  double decimal = grados + minutos / 60.0;
  if (hemisferio[0] == 'S' || hemisferio[0] == 'W') decimal = -decimal;
  return String(decimal, 6);
}

bool procesarRMC(char *linea) {
  if (strncmp(linea, "$GPRMC,", 7) != 0 &&
      strncmp(linea, "$GNRMC,", 7) != 0) return false;
  char *campos[12] = {};
  size_t cantidad = 0;
  char *token = strtok(linea, ",");
  while (token && cantidad < 12) {
    campos[cantidad++] = token;
    token = strtok(nullptr, ",");
  }
  // RMC: 0 sentencia, 1 hora, 2 estado, 3 lat, 4 N/S, 5 lon, 6 E/W
  if (cantidad < 7 || strcmp(campos[2], "A") != 0) {
    gpsFix = false;
    return true;
  }
  String lat = coordenadaDecimal(campos[3], campos[4]);
  String lon = coordenadaDecimal(campos[5], campos[6]);
  if (lat.length() && lon.length()) {
    latitude = lat;
    longitude = lon;
    gpsFix = true;
  }
  return true;
}

bool esperarRespuesta(const char *esperado, uint32_t timeoutMs) {
  const uint32_t inicio = millis();
  String respuesta;
  while (millis() - inicio < timeoutMs) {
    while (gsmSerial.available()) {
      const char c = (char)gsmSerial.read();
      respuesta += c;
      if (respuesta.indexOf(esperado) >= 0) return true;
      if (respuesta.length() > 250) respuesta.remove(0, 120);
    }
    delay(5);
  }
  return false;
}

bool comandoAT(const String &comando, const char *esperado, uint32_t timeoutMs=2500) {
  while (gsmSerial.available()) gsmSerial.read();
  gsmSerial.println(comando);
  return esperarRespuesta(esperado, timeoutMs);
}
}

void iniciarGPSGSM() {
  gpsSerial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
  gsmSerial.begin(GSM_BAUD, SERIAL_8N1, GSM_RX_PIN, GSM_TX_PIN);
}

void actualizarGPS() {
  while (gpsSerial.available()) {
    const char c = (char)gpsSerial.read();
    if (c == '\r') continue;
    if (c == '\n') {
      nmeaLine[nmeaIndex] = '\0';
      if (nmeaIndex > 6) procesarRMC(nmeaLine);
      nmeaIndex = 0;
    } else if (nmeaIndex < sizeof(nmeaLine) - 1) {
      nmeaLine[nmeaIndex++] = c;
    } else {
      nmeaIndex = 0; // descartar línea demasiado larga
    }
  }
}

bool hayPosicionGPS() { return gpsFix; }
String obtenerLatitudGPS() { return latitude; }
String obtenerLongitudGPS() { return longitude; }

bool enviarSMSAlerta(const String &motivo) {
#if ENABLE_SMS_ALERTS
  if (String(EMERGENCY_PHONE).length() < 8) return false;
  if (!comandoAT("AT", "OK")) return false;
  if (!comandoAT("AT+CMGF=1", "OK")) return false;
  gsmSerial.print("AT+CMGS=\"");
  gsmSerial.print(EMERGENCY_PHONE);
  gsmSerial.println("\"");
  if (!esperarRespuesta(">", 5000)) return false;

  gsmSerial.print("Alerta del prototipo de casco inteligente: ");
  gsmSerial.print(motivo);
  if (hayPosicionGPS()) {
    gsmSerial.print(". Ubicacion: ");
    gsmSerial.print(obtenerLatitudGPS());
    gsmSerial.print(",");
    gsmSerial.print(obtenerLongitudGPS());
  } else {
    gsmSerial.print(". GPS sin posicion valida.");
  }
  gsmSerial.write((uint8_t)26); // Ctrl+Z para enviar el SMS
  return esperarRespuesta("OK", 15000);
#else
  (void)motivo;
  return false; // SMS desactivado hasta configurar y autorizar pruebas
#endif
}
