/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: mqtt_module.h
 */

#ifndef MQTT_MODULE_H
#define MQTT_MODULE_H

#include "pico/stdlib.h"

void mqtt_init(const char *servidor, uint16_t porta, const char *topico);
void mqtt_publicar_dados(uint8_t copos, uint32_t tempo_restante_s);

#endif
