# Evidencia previa de pruebas del prototipo

Esta página reúne las entradas de la bitácora de Notion que documentan pruebas previas relacionadas con el ESP32, el sensor de impacto y el GPS. Se enlazan como evidencia de trabajo por subsistema; **no demuestran por sí solas que la integración completa del firmware actual haya sido probada físicamente**.

## Registros de la bitácora

- **15 de septiembre de 2026 — Revisé nuevamente el sensor de impacto.**  
  [Abrir registro de Notion](https://app.notion.com/p/3f0d68807ac0805eaad1f125c4274f5e)

- **28 de septiembre de 2026 — Voy a pasar el prototipo con el ESP32 y comprobar hoy.**  
  [Abrir registro de Notion](https://app.notion.com/p/3f0d68807ac080908249c6e82e281c2d)  
  La descripción de la bitácora indica una prueba de código para detectar accidentes y que todavía faltaban el sensor y el módulo en ese momento.

- **30 de septiembre de 2026 — Conectar el ESP32 con el sensor en protoboard.**  
  [Abrir registro de Notion](https://app.notion.com/p/3f0d68807ac080dabde7dd175d7d0ba3)

- **2 de octubre de 2026 — Revisar la recepción de señal del GPS.**  
  [Abrir registro de Notion](https://app.notion.com/p/3f0d68807ac0804aac57ceecf4f2afcc)

- **5 de octubre de 2026 — Práctica con ESP32 y módulo 2G.**  
  [Abrir página de Notion](https://app.notion.com/p/3f0d68807ac0808f8f66d092d4ebd2fb)

## Cómo se relaciona con el firmware actual

Los registros respaldan que se ha trabajado previamente con los subsistemas de impacto, ESP32, GPS y módulo 2G. El firmware de esta rama integra esos elementos a nivel de código, pero las siguientes comprobaciones siguen pendientes hasta documentarlas con resultados reproducibles:

1. Compilar el firmware en CI y revisar el resultado de la ejecución más reciente.
2. Confirmar el modelo exacto de cada módulo y validar el cableado real.
3. Probar por separado el botón y el buzzer, la lectura del MPU6050, la recepción de coordenadas GPS y la comunicación AT del SIM800L.
4. Realizar una prueba integrada controlada y registrar sus resultados.
5. Mantener los SMS desactivados por defecto; activarlos solo para una prueba autorizada con número verificado.

## Limitaciones

Las referencias anteriores llevan a los registros originales de Notion. Esta documentación no afirma haber inspeccionado visualmente los archivos adjuntos ni que las pruebas completas hayan pasado. El umbral de impacto del código es experimental: este proyecto es un prototipo educativo y no debe considerarse un dispositivo certificado de seguridad o detección de accidentes.
