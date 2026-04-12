/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: input_module.h
 */

#ifndef INPUT_MODULE_H
#define INPUT_MODULE_H

#include "pico/stdlib.h"

void input_init(uint pino_botao_a, void (*callback_a)(void));

#endif
