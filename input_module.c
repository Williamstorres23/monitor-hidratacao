/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: input_module.c
 */

#include "input_module.h"
#include "hardware/gpio.h"
#include "pico/time.h"

#define DEBOUNCE_MS 200

static void (*s_callback_a)(void)   = NULL;
static absolute_time_t s_ultimo_botao_a;
static uint s_pino_botao_a          = 0;

static void gpio_irq_handler(uint gpio, uint32_t eventos) {
    absolute_time_t agora = get_absolute_time();
    if (gpio == s_pino_botao_a) {
        if (absolute_time_diff_us(s_ultimo_botao_a, agora) > (DEBOUNCE_MS * 1000)) {
            s_ultimo_botao_a = agora;
            if (s_callback_a) s_callback_a();
        }
    }
}

void input_init(uint pino_botao_a, void (*callback_a)(void)) {
    s_pino_botao_a   = pino_botao_a;
    s_callback_a     = callback_a;
    s_ultimo_botao_a = get_absolute_time();

    gpio_init(pino_botao_a);
    gpio_set_dir(pino_botao_a, GPIO_IN);
    gpio_pull_up(pino_botao_a);

    gpio_set_irq_enabled_with_callback(pino_botao_a,
                                       GPIO_IRQ_EDGE_FALL,
                                       true,
                                       &gpio_irq_handler);
}
