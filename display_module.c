/*
 * Monitor de Hidratação - EmbarcaTech Expansão
 * Arquivo: display_module.c
 */

#include "display_module.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "config.h"
#include <stdio.h>
#include <string.h>

static ssd1306_t s_display;

void display_init(void) {
    i2c_init(DISPLAY_I2C_PORT, 400 * 1000);
    gpio_set_function(DISPLAY_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(DISPLAY_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(DISPLAY_SDA_PIN);
    gpio_pull_up(DISPLAY_SCL_PIN);
    ssd1306_init(&s_display, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                 DISPLAY_ADDR, DISPLAY_I2C_PORT);
    ssd1306_clear(&s_display);
    ssd1306_show(&s_display);
}

void display_atualizar(uint8_t copos, uint32_t tempo_restante_s, bool alerta) {
    char linha[32];
    uint32_t min = tempo_restante_s / 60;
    uint32_t seg = tempo_restante_s % 60;
    uint32_t volume_ml = (uint32_t)copos * VOLUME_COPO_ML;

    ssd1306_clear(&s_display);
    ssd1306_draw_string(&s_display, 0, 0,  1, "Monitor de Agua");

    snprintf(linha, sizeof(linha), "Copos: %d / %d", copos, META_COPOS_DIA);
    ssd1306_draw_string(&s_display, 0, 16, 1, linha);

    if (alerta) {
        ssd1306_draw_string(&s_display, 0, 32, 1, "!! BEBA AGUA !!");
    } else {
        snprintf(linha, sizeof(linha), "Proximo: %02lu:%02lu", min, seg);
        ssd1306_draw_string(&s_display, 0, 32, 1, linha);
    }

    snprintf(linha, sizeof(linha), "Volume: %lu mL", volume_ml);
    ssd1306_draw_string(&s_display, 0, 48, 1, linha);
    ssd1306_show(&s_display);
}

void display_mostrar_alerta(void) {
    ssd1306_clear(&s_display);
    ssd1306_draw_string(&s_display, 10, 10, 2, "BEBA AGUA");
    ssd1306_draw_string(&s_display, 0,  40, 1, "Pressione A p/ confirmar");
    ssd1306_show(&s_display);
}

void display_boas_vindas(void) {
    ssd1306_clear(&s_display);
    ssd1306_draw_string(&s_display, 0,  0,  1, "EmbarcaTech 2026");
    ssd1306_draw_string(&s_display, 0,  20, 1, "Monitor de");
    ssd1306_draw_string(&s_display, 0,  32, 2, "Hidratacao");
    ssd1306_draw_string(&s_display, 0,  52, 1, "Iniciando...");
    ssd1306_show(&s_display);
}

void display_show_erro(const char *msg) {
    ssd1306_clear(&s_display);
    ssd1306_draw_string(&s_display, 0, 20, 1, "ERRO:");
    ssd1306_draw_string(&s_display, 0, 36, 1, msg);
    ssd1306_show(&s_display);
}

/*
 * display_parabens()
 * Exibe tela animada de parabéns ao atingir a meta diária de 2 litros.
 * Pisca 3 vezes para chamar atenção antes de mostrar a mensagem final.
 */
void display_parabens(void) {
    /* Pisca 3 vezes para chamar atenção */
    for (int i = 0; i < 3; i++) {
        ssd1306_clear(&s_display);
        ssd1306_draw_string(&s_display, 5,  10, 2, "PARABENS!");
        ssd1306_draw_string(&s_display, 0,  40, 1, "Meta atingida!");
        ssd1306_draw_string(&s_display, 0,  52, 1, "2 litros hoje!");
        ssd1306_show(&s_display);
        sleep_ms(400);

        ssd1306_clear(&s_display);
        ssd1306_show(&s_display);
        sleep_ms(200);
    }

    /* Mensagem final permanente */
    ssd1306_clear(&s_display);
    ssd1306_draw_string(&s_display, 5,  0,  2, "PARABENS!");
    ssd1306_draw_string(&s_display, 0,  22, 1, "Voce bebeu 2 litros!");
    ssd1306_draw_string(&s_display, 0,  36, 1, "Meta do dia: OK  :)");
    ssd1306_draw_string(&s_display, 0,  52, 1, "Continue amanha!");
    ssd1306_show(&s_display);
}
