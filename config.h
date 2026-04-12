/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: config.h
 * Descrição: Centraliza todas as configurações e constantes do projeto.
 *            Edite este arquivo para ajustar pinos, WiFi, MQTT e timers.
 *
 * Hardware: BitDogLab (RP2040W)
 * Autor: Williams Torres Garcia da Silva
 */

#ifndef CONFIG_H
#define CONFIG_H

/* ================================================================
 * PINOS DA BITDOGLAB
 * ================================================================ */
#define BUZZER_PIN          21   /* Buzzer passivo da BitDogLab       */
#define BOTAO_A_PIN         5    /* Botão A (confirmar copo)          */
#define BOTAO_B_PIN         6    /* Botão B (pausar/retomar timer)    */
#define JOYSTICK_BTN_PIN    22   /* Botão central do joystick         */

/* Display SSD1306 via I2C */
#define DISPLAY_SDA_PIN     14
#define DISPLAY_SCL_PIN     15
#define DISPLAY_I2C_PORT    i2c1
#define DISPLAY_ADDR        0x3C
#define DISPLAY_WIDTH       128
#define DISPLAY_HEIGHT      64

/* ================================================================
 * CONFIGURAÇÕES DE HIDRATAÇÃO
 * ================================================================ */
#define INTERVALO_ALERTA_MIN    30   /* Minutos entre lembretes de beber água */
#define META_COPOS_DIA          10   /* Meta: 10 copos x 200ml = 2 litros/dia */
#define VOLUME_COPO_ML          200  /* Volume em mL por copo confirmado      */

/* Tempo da tela de boas-vindas em milissegundos */
#define TEMPO_BOAS_VINDAS_MS    5000  /* 5 segundos na tela inicial */

/* ================================================================
 * CONFIGURAÇÕES WIFI
 * ================================================================ */
#define WIFI_SSID    "SUA_REDE_WIFI"
#define WIFI_PASS    "SUA_SENHA_WIFI"

/* ================================================================
 * CONFIGURAÇÕES MQTT
 * ================================================================ */
#define MQTT_SERVER      "broker.hivemq.com"
#define MQTT_PORT        1883
#define MQTT_TOPICO      "embarcatech/hidratacao"
#define MQTT_CLIENT_ID   "bitdoglab_hidratacao"
#define MQTT_INTERVALO_US (60 * 1000000)

/* ================================================================
 * CONFIGURAÇÕES DO BUZZER
 * ================================================================ */
#define BUZZER_FREQ_ALERTA        1000  /* Hz - tom de alerta               */
#define BUZZER_FREQ_CONFIRMACAO   1500  /* Hz - tom de confirmação de copo  */
#define BUZZER_DURACAO_ALERTA_MS   500  /* ms - duração do alerta sonoro    */
#define BUZZER_DURACAO_CONF_MS     150  /* ms - duração do bipe de confirmação */

#endif /* CONFIG_H */
