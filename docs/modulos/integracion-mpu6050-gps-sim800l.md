# Integración inicial: MPU6050 + GPS UART + SIM800L

Este documento describe una integración de prototipo para ESP32. Los pines indicados son valores iniciales de software, no una confirmación del cableado físico del equipo.

## Pines provisionales

| Componente | ESP32 | Notas |
|---|---|---|
| MPU6050 SDA | GPIO 21 | I2C SDA |
| MPU6050 SCL | GPIO 22 | I2C SCL |
| GPS TX | GPIO 16 (RX del ESP32) | UART2 RX |
| GPS RX | GPIO 17 (TX del ESP32) | UART2 TX; a veces no hace falta conectar si solo se leen datos |
| SIM800L TXD | GPIO 26 (RX del ESP32) | UART1 RX |
| SIM800L RXD | GPIO 27 (TX del ESP32) | UART1 TX; verificar nivel lógico |
| Botón | GPIO 25 y GND | Usa INPUT_PULLUP |
| Buzzer | GPIO 32 | Verificar si es activo/pasivo y su corriente |

## Alimentación y seguridad eléctrica

- No alimentar el SIM800L desde el pin 3V3 del ESP32. El SIM800L suele requerir una fuente propia estable alrededor de 3.4–4.4 V y puede demandar picos cercanos a 2 A; revisar la hoja de datos exacta de la placa/módulo adquirido.
- Unir GND de la fuente del SIM800L y GND del ESP32.
- Confirmar niveles lógicos del UART del SIM800L. No aplicar señales de 5 V al ESP32; utilizar adaptación de nivel adecuada cuando el módulo lo requiera.
- Alimentar el MPU6050 según el breakout concreto y verificar que SDA/SCL sean compatibles con 3.3 V.
- No conectar/desconectar cables con la alimentación encendida.

## Qué implementa el código actual

- Lee aceleración del MPU6050 por I2C en dirección 0x68 y calcula magnitud en g.
- Configura el acelerómetro en rango ±8 g y utiliza 2.5 g como umbral experimental inicial. Ese valor no está calibrado para detectar accidentes reales.
- Lee sentencias NMEA RMC del GPS a 9600 baudios y conserva coordenadas cuando la sentencia indica fix válido.
- Tiene un módulo SIM800L por UART a 9600 baudios para enviar un SMS de prueba con coordenadas si están disponibles.
- El envío de SMS está DESACTIVADO por defecto. Para configurarlo localmente, copia `configuracion.h.example` como `configuracion.h`, pon el número autorizado y cambia `ENABLE_SMS_ALERTS` a 1. `configuracion.h` está excluido por `.gitignore`; no lo subas a GitHub.

## Prueba por etapas

1. Con todo apagado, revisar conexiones y alimentación con la documentación del fabricante.
2. Compilar en Arduino IDE para la placa ESP32 exacta.
3. Encender solo ESP32 + MPU6050 y confirmar en Monitor Serie que detecta I2C.
4. Validar datos del GPS en exterior con vista despejada; un GPS puede tardar en obtener fix.
5. Validar el SIM800L por separado: SIM, cobertura, antena y alimentación estable. No mandar SMS hasta tener un destinatario de prueba autorizado.
6. Probar el botón/buzzer y registrar resultados. No provocar impactos peligrosos ni probar el casco sobre una persona.
7. Integrar todo y documentar falsas activaciones, pérdidas de señal y limitaciones.

## Limitaciones conocidas

- No se conoce el modelo exacto del GPS, el breakout MPU6050 ni la placa SIM800L; los pines, UART y alimentación deben confirmarse con los módulos reales.
- El umbral de 2.5 g es solo un punto de partida. Orientación, vibraciones, montaje y ruido pueden generar falsos positivos o no detectar un evento.
- El SMS puede fallar por cobertura, operador, SIM, alimentación o antena. La ubicación GPS puede no estar disponible en interiores.
- Este prototipo educativo no es un dispositivo de protección certificado ni sustituye a un casco homologado, los servicios de emergencia ni sistemas de seguridad profesionales.
