# Los Vengadores — Casco inteligente

Proyecto escolar de un prototipo de casco inteligente basado en ESP32 para detectar impactos y activar una alerta sonora. La comunicación GPS/GSM se documentará como funcional únicamente después de probar el hardware real.

## Estado actual

- [ ] Integrar y probar sensor de impacto.
- [ ] Confirmar el diseño del botón de alerta/cancelación.
- [ ] Compilar el sketch en Arduino IDE para la placa ESP32 exacta.
- [ ] Probar físicamente botón y buzzer.
- [ ] Integrar y probar GPS/GSM si los módulos están disponibles.
- [ ] Adjuntar evidencias de pruebas, revisión y compilación.

## Estructura

- `casco_inteligente/casco_inteligente.ino`: programa principal.
- `casco_inteligente/alerta.h` y `casco_inteligente/alerta.cpp`: módulo inicial para buzzer.
- `arduino_secrets.h.example`: plantilla de configuración sin credenciales reales.
- `docs/`: evidencias y documentación del proyecto.

## Abrir y compilar

1. Instala Arduino IDE y el soporte de placas ESP32 correspondiente a tu placa.
2. Descarga o clona el repositorio.
3. Abre la carpeta `casco_inteligente` en Arduino IDE (debe contener el archivo `.ino` y los archivos `.h/.cpp` del módulo).
4. Selecciona la placa ESP32 correcta y compila.
5. Si la compilación termina sin errores, guarda una captura como evidencia. La compilación aún debe ser confirmada por el equipo.

## Configuración privada

Si más adelante el firmware requiere credenciales, copia `arduino_secrets.h.example` como `arduino_secrets.h` en tu equipo local y reemplaza los valores de ejemplo. **Nunca subas `arduino_secrets.h` ni claves reales a GitHub.** El archivo real está excluido por `.gitignore`. Actualmente la plantilla es solo un ejemplo y el sketch no la utiliza.

## Flujo de trabajo GitHub

1. Trabaja en una rama por tarea o módulo.
2. Haz commits pequeños con mensajes descriptivos.
3. Abre un Pull Request hacia `main` y solicita revisión.
4. Revisa los cambios y comprueba la compilación antes de fusionar.
5. Después del merge, actualiza tu copia local con `git checkout main` y `git pull origin main`.

## Limitaciones importantes

El código actual solo demuestra el control del buzzer con un botón: GPIO 32 para el buzzer y GPIO 25 para el botón, cableado provisional entre GPIO 25 y GND con `INPUT_PULLUP`. No implementa detección de impacto ni comunicación GPS/GSM. No declarar el prototipo terminado hasta realizar las pruebas físicas y guardar evidencias.
