/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: buzzer_module.c
 */

#include "buzzer_module.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h"
#include "config.h"

/* ── Frequências das notas musicais (Hz) ── */
#define NOTA_C4   262
#define NOTA_D4   294
#define NOTA_E4   330
#define NOTA_F4   349
#define NOTA_G4   392
#define NOTA_A4   440
#define NOTA_B4   494
#define NOTA_C5   523
#define NOTA_D5   587
#define NOTA_E5   659
#define NOTA_G5   784
#define SILENCIO  0

static void buzzer_set_frequencia(uint pino, uint freq_hz) {
    uint slice = pwm_gpio_to_slice_num(pino);
    uint chan  = pwm_gpio_to_channel(pino);
    uint32_t clock_sys = clock_get_hz(clk_sys);
    uint32_t divisor   = clock_sys / (freq_hz * 4096);
    if (divisor < 1) divisor = 1;
    pwm_set_clkdiv(slice, (float)divisor);
    pwm_set_wrap(slice, 4095);
    pwm_set_chan_level(slice, chan, 2048);
    pwm_set_enabled(slice, true);
}

void buzzer_init(uint pino) {
    gpio_set_function(pino, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(pino);
    pwm_set_enabled(slice, false);
}

void buzzer_toque_alerta(uint pino) {
    buzzer_set_frequencia(pino, BUZZER_FREQ_ALERTA);
    sleep_ms(BUZZER_DURACAO_ALERTA_MS);
    buzzer_parar(pino);
    sleep_ms(200);
    buzzer_set_frequencia(pino, BUZZER_FREQ_ALERTA);
    sleep_ms(BUZZER_DURACAO_ALERTA_MS);
    buzzer_parar(pino);
}

void buzzer_toque_confirmacao(uint pino) {
    buzzer_set_frequencia(pino, BUZZER_FREQ_CONFIRMACAO);
    sleep_ms(BUZZER_DURACAO_CONF_MS);
    buzzer_parar(pino);
    sleep_ms(80);
    buzzer_set_frequencia(pino, BUZZER_FREQ_CONFIRMACAO + 200);
    sleep_ms(BUZZER_DURACAO_CONF_MS);
    buzzer_parar(pino);
}

void buzzer_parar(uint pino) {
    uint slice = pwm_gpio_to_slice_num(pino);
    pwm_set_enabled(slice, false);
}

/*
 * buzzer_musica_parabens()
 * Toca uma melodia comemorativa ao atingir a meta de 2 litros.
 * Melodia: trecho de "Ode à Alegria" (Beethoven) — simples e reconhecível.
 */
void buzzer_musica_parabens(uint pino) {
    /* Pares: {frequência Hz, duração ms} */
    uint notas[][2] = {
        {NOTA_E4, 200}, {NOTA_E4, 200}, {NOTA_F4, 200}, {NOTA_G4, 200},
        {NOTA_G4, 200}, {NOTA_F4, 200}, {NOTA_E4, 200}, {NOTA_D4, 200},
        {NOTA_C4, 200}, {NOTA_C4, 200}, {NOTA_D4, 200}, {NOTA_E4, 200},
        {NOTA_E4, 300}, {NOTA_D4, 100}, {NOTA_D4, 400},
        {SILENCIO, 100},
        /* Subida final comemorativa */
        {NOTA_C5, 150}, {NOTA_D5, 150}, {NOTA_E5, 150}, {NOTA_G5, 400},
    };

    uint total = sizeof(notas) / sizeof(notas[0]);

    for (uint i = 0; i < total; i++) {
        if (notas[i][0] == SILENCIO) {
            buzzer_parar(pino);
        } else {
            buzzer_set_frequencia(pino, notas[i][0]);
        }
        sleep_ms(notas[i][1]);
        buzzer_parar(pino);
        sleep_ms(30); /* Pequena pausa entre notas para separar os sons */
    }
}
