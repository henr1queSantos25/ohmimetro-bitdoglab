#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "pico/bootrom.h"
#include <math.h> // Para fabs()

// Bibliotecas externas
#include "lib/ssd1306.h"
#include "lib/font.h"

// Definições de Hardware
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define ADC_PIN 28 // GPIO para o voltímetro
#define Botao_A 5  // GPIO para botão A
#define botaoB 6   // GPIO para botão B (modo BOOTSEL)

// Constantes
#define R_CONHECIDO 10000 // Resistor de 10k ohm
#define ADC_RESOLUTION 4095 // Resolução do ADC (12 bits)

// Variáveis globais
ssd1306_t ssd;
float R_x = 0.0; 


// Função para modo BOOTSEL
void gpio_irq_handler(uint gpio, uint32_t events) {
  reset_usb_boot(0, 0);
}

// Vetor de valores E24
float e24_series[] = {
    1.0, 1.1, 1.2, 1.3, 1.5, 1.6, 1.8,
    2.0, 2.2, 2.4, 2.7, 3.0, 3.3, 3.6,
    3.9, 4.3, 4.7, 5.1, 5.6, 6.2, 6.8,
    7.5, 8.2, 9.1};

// Prototipos de funções
void setup();
float medir_resistor();
float encontrar_valor_E24_tolerancia(float resistencia);
void obter_cores(int resistencia, char *cor1, char *cor2, char *multiplicador);

int main() {
  // Inicialização
  setup(); // Chama a função de setup

  gpio_init(botaoB);
  gpio_set_dir(botaoB, GPIO_IN);
  gpio_pull_up(botaoB);
  gpio_set_irq_enabled_with_callback(botaoB, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);

  gpio_init(Botao_A);
  gpio_set_dir(Botao_A, GPIO_IN);
  gpio_pull_up(Botao_A);


  char valor_ohms[10], cor1[20], cor2[20], mult[20];

  bool cor = true;
  while (true) {
    R_x = medir_resistor(); // Chama a função para medir o resistor desconhecido
    printf("Valor do resistor: %1.0f Ohms\n", R_x); // Imprime o valor real do resistor no console
    R_x = encontrar_valor_E24_tolerancia(R_x); // Encontra o valor E24 mais próximo

    sprintf(valor_ohms, "%1.0f Ohms", R_x); // Formata o valor do resistor em string

    obter_cores((int)R_x, cor1, cor2, mult); // Obtém as cores do resistor


    // Atualiza o display
    ssd1306_fill(&ssd, false);

    ssd1306_rect(&ssd, 0, 0, 128, 64, cor, !cor); // Desenha um retângulo
    ssd1306_line(&ssd, 0, 18, 128, 18, cor);      // Desenha uma linha
    ssd1306_draw_string(&ssd, valor_ohms, 18, 8);
    ssd1306_draw_string(&ssd, cor1, 3, 24);
    ssd1306_draw_string(&ssd, cor2, 3, 38);
    ssd1306_draw_string(&ssd, mult, 3, 52);

    ssd1306_send_data(&ssd);
    sleep_ms(300);
  }
}

/* ==========================================================
   FUNÇÃO DE SETUP
   ========================================================== */
void setup() {
  stdio_init_all();
  setup_I2C(I2C_PORT, I2C_SDA, I2C_SCL);
  setup_ssd1306(&ssd, endereco, I2C_PORT);
  adc_init();
  adc_gpio_init(ADC_PIN); // GPIO 28 como entrada analógica
}

/* ==========================================================
   FUNÇÃO PARA MEDIR O RESISTOR DESCONHECIDO
   ========================================================== */
float medir_resistor() {
  adc_select_input(2); // Pino 28 analógico
  float soma = 0.0f;

  for (int i = 0; i < 500; i++) {
    soma += adc_read();
    sleep_ms(1);
  }

  float media = soma / 500.0f;
  float resistencia = (R_CONHECIDO * media) / (ADC_RESOLUTION - media);

  return resistencia;
}

/* ==========================================================
   FUNÇÃO PARA ENCONTAR O VALOR E24 MAIS PRÓXIMO
   ========================================================== */
float encontrar_valor_E24_tolerancia(float resistencia) {
  float melhor_match = 0;
  float menor_erro = 1e9;
  int potencia = 0;
  float valor_normalizado = resistencia;

  while (valor_normalizado >= 10.0f) {
    valor_normalizado /= 10.0f;
    potencia++;
  }
  while (valor_normalizado < 1.0f) {
    valor_normalizado *= 10.0f;
    potencia--;
  }

  for (int i = 0; i < 24; i++) {
    float base = e24_series[i];
    if (valor_normalizado >= base * 0.95f && valor_normalizado <= base * 1.05f) {
      float erro = fabs(valor_normalizado - base);
      if (erro < menor_erro) {
        menor_erro = erro;
        melhor_match = base;
      }
    }
  }

  if (melhor_match == 0) {
    for (int i = 0; i < 24; i++) {
      float erro = fabs(valor_normalizado - e24_series[i]);
      if (erro < menor_erro) {
        menor_erro = erro;
        melhor_match = e24_series[i];
      }
    }
  }

  while (potencia > 0) {
    melhor_match *= 10.0f;
    potencia--;
  }
  while (potencia < 0) {
    melhor_match /= 10.0f;
    potencia++;
  }

  return melhor_match;
}

/* ==========================================================
   FUNÇÃO PARA OBTER AS CORES DO RESISTOR
   ========================================================== */
void obter_cores(int resistencia, char *cor1, char *cor2, char *multiplicador) {
  static const char *cores[] = {"Preto", "Marrom", "Vermelho", "Laranja", "Amarelo", "Verde", "Azul", "Violeta", "Cinza", "Branco"};

  int valor = resistencia;
  int expoente = 0;

  while (valor >= 100) {
    valor /= 10;
    expoente++;
  }

  int digito1 = valor / 10;
  int digito2 = valor % 10;

  sprintf(cor1, "1: %s", cores[digito1]);
  sprintf(cor2, "2: %s", cores[digito2]);

  if (expoente >= 0 && expoente <= 9)
    sprintf(multiplicador, "Mul: %s", cores[expoente]);
  else
    sprintf(multiplicador, "Mul: Erro");
}