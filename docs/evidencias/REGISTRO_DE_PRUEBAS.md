# Registro de pruebas y evidencias — casco inteligente

**Estado inicial:** las pruebas físicas y la compilación en Arduino IDE deben ser realizadas por el equipo. No se deben marcar como exitosas sin evidencia.

## 1. Compilación

- Fecha:
- Integrante:
- Sistema operativo:
- Versión de Arduino IDE:
- Placa seleccionada (modelo exacto):
- Versión del core ESP32:
- Resultado: [ ] Correcto [ ] Error
- Mensaje de salida relevante:
- Archivo/captura: `compilacion-arduino-ide.png`

## 2. Prueba física del botón y buzzer

- Fecha:
- Integrante:
- Placa ESP32:
- Buzzer (activo/pasivo y modelo):
- Cableado confirmado: buzzer GPIO 32; botón GPIO 25 a GND con INPUT_PULLUP, salvo que el montaje real difiera.
- Al presionar el botón: [ ] Sonó [ ] No sonó
- Al soltar el botón: [ ] Se detuvo [ ] Siguió sonando
- Observaciones:
- Archivo/captura o video: `prueba-boton-buzzer.png`

## 3. Sensor de impacto

- Modelo exacto del sensor:
- Pin de señal:
- Método de lectura (digital/analógica):
- Resultado de prueba controlada:
- Falsas activaciones observadas:
- Evidencia:
- **No probar impactos peligrosos sobre una persona ni afirmar que el prototipo protege contra accidentes.**

## 4. GPS/GSM (solo si se dispone de los módulos)

- Modelo GPS:
- Modelo GSM:
- Alimentación y antenas verificadas:
- GPS obtuvo coordenadas válidas: [ ] Sí [ ] No [ ] No disponible
- GSM registró red: [ ] Sí [ ] No [ ] No disponible
- Mensaje/llamada de prueba autorizada completada: [ ] Sí [ ] No [ ] No disponible
- Evidencia (ocultar números personales, claves y datos sensibles):
- Limitaciones:

## 5. Pull Requests y revisión

| PR | Revisor | Revisión completada | Compilación comprobada | Resultado |
|---|---|---|---|---|
| #1 Documentación Git | | [ ] | N/A | |
| #2 Sensores | | [ ] | [ ] | |
| #3 Botón/buzzer | | [ ] | [ ] | |
| #4 GPS/GSM | | [ ] | [ ] | |

## 6. Evidencias finales requeridas

- [ ] Git instalado y configuración de nombre/correo (ocultar información privada que no sea necesaria).
- [ ] Rama y commits de cada integrante.
- [ ] Pull Request y comentarios de revisión.
- [ ] Resultado del workflow de compilación automática de GitHub Actions.
- [ ] Captura de compilación correcta en Arduino IDE.
- [ ] Evidencia de prueba física del botón/buzzer.
- [ ] Evidencias de sensor/GPS/GSM solo si los módulos existen y se probaron.
- [ ] Captura de la protección de la rama `main`.
- [ ] Repositorio final integrado y lista de limitaciones conocidas.

No adjuntar credenciales reales, contraseñas, tokens, ni información personal innecesaria.
