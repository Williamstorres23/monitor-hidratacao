/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: timer_module.c
 */

#include "timer_module.h"
#include "hardware/timer.h"
#include "config.h"

static struct repeating_timer s_timer_hw;
static volatile uint32_t      s_segundos_decorridos = 0;
static uint32_t               s_intervalo_s         = 0;
static volatile bool          s_pausado             = false;
static void (*s_callback_usuario)(void)             = NULL;

static bool callback_interno(struct repeating_timer *t) {
    (void)t;
    if (s_pausado) return true;
    s_segundos_decorridos++;
    if (s_segundos_decorridos >= s_intervalo_s) {
        s_segundos_decorridos = 0;
        if (s_callback_usuario) s_callback_usuario();
    }
    return true;
}

void timer_init(uint8_t intervalo_min, void (*callback)(void)) {
    s_intervalo_s         = (uint32_t)intervalo_min * 60;
    s_callback_usuario    = callback;
    s_segundos_decorridos = 0;
    s_pausado             = false;
    add_repeating_timer_ms(1000, callback_interno, NULL, &s_timer_hw);
}

void timer_resetar(void) {
    s_segundos_decorridos = 0;
}

uint32_t timer_tempo_restante_s(void) {
    if (s_intervalo_s > s_segundos_decorridos)
        return s_intervalo_s - s_segundos_decorridos;
    return 0;
}

void timer_pausar(void)  { s_pausado = true;  }
void timer_retomar(void) { s_pausado = false; }
