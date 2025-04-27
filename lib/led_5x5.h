#include "pico/stdlib.h"

// NÚMERO DE LEDS
#define NUM_PIXELS 25

// PINO DA MATRIZ DE LED
#define OUT_PIN 7

// FUNÇÕES
void setup_PIO();
static inline void put_pixel(uint32_t pixel_grb);
uint32_t matrix_rgb(double b, double r, double g);
void drawMatrix(uint cor);
void apagarMatriz();
void drawLinha(int cor, int linhaDesejada);
