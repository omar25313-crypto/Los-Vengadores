# Los Vengadores — Casco inteligente

Prototipo educativo basado en ESP32. El firmware de esta rama integra una lectura experimental del MPU6050, el botón/buzzer y una interfaz inicial para GPS separado + SIM800L. El hardware aún debe validarse físicamente.

## Estado real

- [x] Módulo de buzzer y botón.
- [x] Código inicial de lectura del MPU6050 (I2C) con umbral experimental.
- [x] Lector básico de sentencias GPS NMEA RMC.
- [x] Interfaz SIM800L para SMS; **envío desactivado por defecto**.
- [x] Workflow de compilación automática para PRs de firmware.
- [ ] Confirmar compilación local en Arduino IDE con la placa exacta.
- [ ] Probar el MPU6050 y calibrar umbral de forma controlada.
- [ ] Probar GPS en exterior y validar coordenadas.
- [ ] Probar SIM800L con fuente adecuada, SIM, antena y cobertura.
- [ ] Realizar prueba integral y guardar evidencias.

## Archivos principales

- `casco_inteligente/casco_inteligente.ino`: programa principal.
- `casco_inteligente/alerta.h/.cpp`: botón/buzzer.
- `casco_inteligente/impacto.h/.cpp`: MPU6050 y umbral experimental.
- `casco_inteligente/gps_gsm.h/.cpp`: lectura GPS y SMS por SIM800L.
- `casco_inteligente/configuracion.h.example`: ejemplo para configurar el teléfono sin publicar datos privados.
- `docs/modulos/integracion-mpu6050-gps-sim800l.md`: cableado provisional, alimentación y pasos de validación.
- `docs/evidencia/pruebas-previas-notion.md`: enlaces a registros previos de la bitácora de Notion y alcance de lo que respaldan.
- `docs/evidencias/REGISTRO_DE_PRUEBAS.md`: plantilla de evidencias.

## Pines provisionales

| Función | GPIO ESP32 |
|---|---|
| MPU6050 SDA/SCL | 21 / 22 |
| Botón | 25 a GND, INPUT_PULLUP |
| Buzzer | 32 |
| GPS RX/TX del ESP32 | 16 / 17 |
| SIM800L RX/TX del ESP32 | 26 / 27 |

Verifica el modelo de cada módulo y su pinout antes de conectar. En UART, TX de un módulo va a RX del ESP32 y viceversa. Algunos módulos requieren adaptación de nivel lógico.

## SMS: desactivado por defecto

El código no envía mensajes por defecto. Si el equipo tiene autorización para probar SMS, copia `casco_inteligente/configuracion.h.example` como `casco_inteligente/configuracion.h` en tu equipo local, cambia el número de prueba autorizado y activa `ENABLE_SMS_ALERTS 1`. El archivo `configuracion.h` está excluido por `.gitignore`; nunca lo subas ni compartas números o credenciales reales.

**Alimentación SIM800L:** no alimentarlo desde el pin 3V3 del ESP32. Verifica la hoja de datos de la placa concreta; el SIM800L normalmente requiere una fuente estable en torno a 3.4–4.4 V con picos de corriente elevados, frecuentemente hasta ~2 A.

## Compilar

1. Instala Arduino IDE y soporte de placas ESP32.
2. Abre la carpeta `casco_inteligente`.
3. Selecciona el modelo exacto de placa y compila.
4. Observa el Monitor Serie a 115200 baudios para comprobar si se detecta el MPU6050.
5. Guarda capturas de compilación y pruebas reales.

GitHub Actions compila el sketch en Pull Requests que cambien el firmware, usando `ESP32 Dev Module`. Una CI exitosa no sustituye la compilación en la placa real ni la prueba física.

## Limitaciones de seguridad

El umbral MPU6050 de 2.5 g es experimental y puede producir falsas activaciones o no detectar eventos. GPS puede no obtener posición en interiores y SMS depende de cobertura, SIM, antena y alimentación. No es un sistema certificado ni debe considerarse dispositivo de protección o reemplazo de un casco homologado.
