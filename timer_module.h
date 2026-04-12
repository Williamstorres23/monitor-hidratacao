/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: timer_module.h
 */

#ifndef TIMER_MODULE_H
#define TIMER_MODULE_H

#include "pico/stdlib.h"

void     timer_init(uint8_t intervalo_min, void (*callback)(void));
void     timer_resetar(void);
uint32_t timer_tempo_restante_s(void);
void     timer_pausar(void);
void     timer_retomar(void);

#endif
