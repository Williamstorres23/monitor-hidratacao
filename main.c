/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: main.c
 * Hardware: BitDogLab (RP2040W)
 * Autor: Williams Torres Garcia da Silva
 * Data: 2026
 */

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "timer_module.h"
#include "display_module.h"
#include "input_module.h"
#include "mqtt_module.h"
#include "buzzer_module.h"
#include "config.h"

/* ── Estado global do sistema ── */
volatile uint8_t  g_copos_bebidos   = 0;
volatile bool     g_alerta_ativo    = false;
volatile bool     g_copo_confirmado = false;
static   bool     g_meta_atingida   = false;  /* Evita repetir a celebração */

void callback_timer_hidratacao(void) {
    g_alerta_ativo = true;
}

void callback_botao_copo(void) {
    g_copo_confirmado = true;
}

int main(void) {
    stdio_init_all();
    sleep_ms(1000);

    display_init();
    buzzer_init(BUZZER_PIN);
    input_init(BOTAO_A_PIN, callback_botao_copo);
    timer_init(INTERVALO_ALERTA_MIN, callback_timer_hidratacao);

    if (cyw43_arch_init()) {
        display_show_erro("Falha WiFi");
        while (true) tight_loop_contents();
    }
    cyw43_arch_enable_sta_mode();
    cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASS,
                                       CYW43_AUTH_WPA2_AES_PSK, 10000);
    mqtt_init(MQTT_SERVER, MQTT_PORT, MQTT_TOPICO);

    display_boas_vindas();
    sleep_ms(TEMPO_BOAS_VINDAS_MS);

    while (true) {

        /* ── 1. Usuário confirmou um copo ── */
        if (g_copo_confirmado) {
            g_copo_confirmado = false;
            g_alerta_ativo    = false;

            /* Só incrementa se ainda não atingiu a meta */
            if (g_copos_bebidos < META_COPOS_DIA) {
                g_copos_bebidos++;
                buzzer_toque_confirmacao(BUZZER_PIN);
                timer_resetar();
                mqtt_publicar_dados(g_copos_bebidos, timer_tempo_restante_s());

                /* ── Verifica se acabou de atingir a meta ── */
                if (g_copos_bebidos >= META_COPOS_DIA && !g_meta_atingida) {
                    g_meta_atingida = true;

                    /* Para o timer — meta do dia concluída! */
                    timer_pausar();

                    /* Celebra: melodia + tela piscante */
                    buzzer_musica_parabens(BUZZER_PIN);
                    display_parabens();

                    /* Publica meta atingida no MQTT */
                    mqtt_publicar_dados(g_copos_bebidos, 0);

                    /* Fica na tela de parabéns — aguarda reinício */
                    while (true) {
                        cyw43_arch_poll();
                        sleep_ms(100);
                    }
                }
            }
        }

        /* ── 2. Alerta de hidratação disparado ── */
        if (g_alerta_ativo && !g_meta_atingida) {
            buzzer_toque_alerta(BUZZER_PIN);
            display_mostrar_alerta();
        }

        /* ── 3. Atualiza display normal ── */
        if (!g_meta_atingida) {
            display_atualizar(g_copos_bebidos,
                              timer_tempo_restante_s(),
                              g_alerta_ativo);
        }

        /* ── 4. Publica MQTT periodicamente ── */
        static absolute_time_t ultima_publicacao;
        if (!g_meta_atingida &&
            absolute_time_diff_us(ultima_publicacao, get_absolute_time()) >
            MQTT_INTERVALO_US) {
            mqtt_publicar_dados(g_copos_bebidos, timer_tempo_restante_s());
            ultima_publicacao = get_absolute_time();
        }

        cyw43_arch_poll();
        sleep_ms(100);
    }

    return 0;
}
