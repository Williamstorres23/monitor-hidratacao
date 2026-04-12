/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: display_module.h
 */

#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H

#include "pico/stdlib.h"

void display_init(void);
void display_atualizar(uint8_t copos, uint32_t tempo_restante_s, bool alerta);
void display_mostrar_alerta(void);
void display_boas_vindas(void);
void display_show_erro(const char *msg);
void display_parabens(void);   /* Tela de meta atingida! */

#endif
