#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "hardware/pio.h"
#include "led_5x5.h"

// ARQUIVO .pio
#include "build/ohmimetro_bitdoglab.pio.h"

// NÚMERO DE LEDS
#define NUM_PIXELS 25

// PINO DA MATRIZ DE LED
#define OUT_PIN 7

PIO pio;
uint sm; 

// INICIALIZAÇÃO E CONFIGURAÇÃO DO PIO
void setup_PIO() {
    pio = pio0;
    uint offset = pio_add_program(pio, &ohmimetro_bitdoglab_program);
    sm = pio_claim_unused_sm(pio, true);
    ohmimetro_bitdoglab_program_init(pio, sm, offset, OUT_PIN);
    matrix_rgb(0.0, 0.0, 0.0); // Inicializa a matriz com todos os LEDs apagados
}

// FUNÇÃO PARA ENVIAR O VALOR RGB PARA A MATRIZ
uint32_t matrix_rgb(double b, double r, double g) {
    unsigned char R, G, B;
    R = r * 255;
    G = g * 255;
    B = b * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// ACENDE TODOS OS LEDS COM UMA COR ESPECÍFICA
void drawMatrix(uint cor) {
    uint32_t valor_led;

    /*
    "0. Verde", 
    "1. Vermelho", 
    "2. Azul", 
    "3. Amarelo", 
    "4. Roxo,    
    "5. Desligado"
    */

    switch (cor)
    {
    case 0:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.0, 0.2);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    case 1:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.2, 0.0);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    case 2:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.2, 0.0, 0.0);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    case 3:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.6, 0.2);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    case 4:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.2, 0.2, 0.0);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    case 5:
        for (int16_t i = 0; i < NUM_PIXELS; i++) {
            valor_led = matrix_rgb(0.0, 0.0, 0.0);
            pio_sm_put_blocking(pio0, 0, valor_led);
        }
        break;
    }
    
    

}

void apagarMatriz() {
    for (int i = 0; i < NUM_PIXELS; i++) {
        uint32_t valor_led = matrix_rgb(0.0, 0.0, 0.0);
        pio_sm_put_blocking(pio0, 0, valor_led);
    }
}

void drawLinha(int cor, int linhaDesejada) {
    double r = 0.0, g = 0.0, b = 0.0;

    switch (cor) {
        case 0: r = 0.0; g = 0.0; b = 0.0; break;      // Preto
        case 1: r = 0.004; g = 0.0; b = 0.0; break;      // Marrom
        case 2: r = 0.1; g = 0.0; b = 0.0; break;      // Vermelho
        case 3: r = 0.2; g = 0.1; b = 0.0; break;      // Laranja
        case 4: r = 0.6; g = 0.6; b = 0.0; break;      // Amarelo
        case 5: r = 0.0; g = 0.1; b = 0.0; break;      // Verde
        case 6: r = 0.0; g = 0.0; b = 0.1; break;      // Azul
        case 7: r = 0.4; g = 0.0; b = 0.4; break;      // Violeta
        case 8: r = 0.004; g = 0.004; b = 0.004; break;      // Cinza
        case 9: r = 0.1; g = 0.1; b = 0.1; break;      // Branco
    }

    uint32_t cor_led = matrix_rgb(b, r, g);
    uint32_t apagado = matrix_rgb(0.0, 0.0, 0.0);

    for (int i = 0; i < NUM_PIXELS; i++) {

        if (i / 5 == linhaDesejada) {
            pio_sm_put_blocking(pio0, 0, cor_led);
        } 
    }
}
