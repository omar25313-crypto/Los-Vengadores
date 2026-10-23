#pragma once

#include <Arduino.h>

// Inicializa el buzzer del prototipo (GPIO 32).
void iniciarAlerta();

// Activa el tono mientras buttonPressed sea true.
void actualizarAlerta(bool buttonPressed);
