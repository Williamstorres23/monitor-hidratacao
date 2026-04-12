/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: mqtt_module.c
 */

#include "mqtt_module.h"
#include "lwip/apps/mqtt.h"
#include "pico/cyw43_arch.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

static mqtt_client_t *s_cliente_mqtt = NULL;
static const char    *s_topico       = NULL;

static void mqtt_conn_callback(mqtt_client_t *cliente,
                                void *arg,
                                mqtt_connection_status_t status) {
    (void)cliente;
    (void)arg;
    (void)status;
}

void mqtt_init(const char *servidor, uint16_t porta, const char *topico) {
    s_topico       = topico;
    s_cliente_mqtt = mqtt_client_new();
    if (!s_cliente_mqtt) return;

    struct mqtt_connect_client_info_t info;
    memset(&info, 0, sizeof(info));
    info.client_id  = MQTT_CLIENT_ID;
    info.keep_alive = 60;

    ip_addr_t ip_broker;
    if (ipaddr_aton(servidor, &ip_broker)) {
        mqtt_client_connect(s_cliente_mqtt, &ip_broker, porta,
                            mqtt_conn_callback, NULL, &info);
    }
}

void mqtt_publicar_dados(uint8_t copos, uint32_t tempo_restante_s) {
    if (!s_cliente_mqtt || !mqtt_client_is_connected(s_cliente_mqtt)) return;

    char payload[128];
    uint32_t volume_ml = (uint32_t)copos * VOLUME_COPO_ML;

    snprintf(payload, sizeof(payload),
             "{\"copos\":%d,\"volume_ml\":%lu,\"tempo_restante_s\":%lu}",
             copos, volume_ml, tempo_restante_s);

    mqtt_publish(s_cliente_mqtt, s_topico,
                 payload, strlen(payload),
                 0, 0, NULL, NULL);
}
