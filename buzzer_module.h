/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: buzzer_module.h
 */

#ifndef BUZZER_MODULE_H
#define BUZZER_MODULE_H

#include "pico/stdlib.h"

void buzzer_init(uint pino);
void buzzer_toque_alerta(uint pino);
void buzzer_toque_confirmacao(uint pino);
void buzzer_parar(uint pino);
void buzzer_musica_parabens(uint pino);  /* Melodia ao atingir a meta! */

#endif
