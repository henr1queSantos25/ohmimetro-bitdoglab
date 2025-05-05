# Semáforo Inteligente com Modo Noturno usando FreeRTOS

O **Semáforo Inteligente** é um sistema embarcado desenvolvido para simular o funcionamento de um semáforo tradicional com recursos multimídia e modo noturno utilizando o microcontrolador **RP2040** e o sistema operacional de tempo real **FreeRTOS**. O projeto integra múltiplas tarefas concorrentes que operam de forma coordenada para controlar diversos periféricos, incluindo **LEDs RGB**, **matriz de LED 5x5**, **display OLED** e um **buzzer**.

---

## Funcionalidades Principais

- **Modos de Operação**:
  - **Modo Normal**: Alterna entre as cores verde, amarelo e vermelho com tempos específicos.
  - **Modo Noturno**: Acionado por botão, opera com sinalização amarela intermitente.
- **Interface Multimídia**:
  - Exibe informações textuais no display OLED.
  - Representa visualmente o estado atual na matriz de LEDs 5x5.
  - Emite sinais sonoros distintos para cada estado via buzzer.
- **Multitarefa**: Utiliza FreeRTOS para gerenciar múltiplas tarefas concorrentes.
- **Sincronização**: Coordena tarefas por meio de variáveis globais voláteis sem uso de filas ou semáforos.

---

## Tecnologias Utilizadas

- **Linguagem de Programação**: C  
- **Microcontrolador**: Raspberry Pi Pico (RP2040)  
- **Sistema Operacional**: FreeRTOS  
- **Componentes Utilizados**:
  - Display OLED SSD1306 128x64 (I2C)
  - LEDs externos (verde e vermelho)
  - Matriz de LEDs 5x5 RGB (PIO)
  - Buzzer (PWM)
  - Botão físico para alternância de modo
- **Bibliotecas**:
  - Pico SDK para GPIO, ADC, PWM e comunicação I2C
  - Bibliotecas personalizadas para controle dos periféricos

---

## Como Funciona

### Ciclo do Semáforo (Modo Normal)
- **Verde** (5 segundos): Sinal aberto, permitindo passagem.
- **Amarelo** (3 segundos): Atenção, preparando para parar.
- **Vermelho** (6 segundos): Sinal fechado, parada obrigatória.

### Modo Noturno
- Ativado por botão físico.
- LED amarelo piscando com intervalo de 2 segundos.
- Matriz de LED 5x5 alterna entre amarelo aceso e desligado.
- Display OLED mostra a mensagem "MODO NOTURNO".
- Buzzer emite sinais sonoros suaves e intermitentes.

### Organização das Tarefas
- **vButtonTask**: Monitora o botão e alterna entre modos de operação.
- **vLedRGBTask**: Controla os LEDs físicos e gerencia o tempo de cada fase do semáforo.
- **vDisplayTask**: Atualiza o display OLED com informações sobre o estado atual.
- **vMatrizLedTask**: Controla a matriz de LEDs 5x5 para exibir a cor correspondente.
- **vBuzzerTask**: Emite sons diferentes para cada estado do semáforo.

---

## Configuração do Hardware

| Componente            | Pino do RP2040 | Função                          |
|-----------------------|----------------|----------------------------------|
| Display OLED (I2C)    | GP14 (SDA), GP15 (SCL) | Exibição de mensagens   |
| Botão                 | GP5            | Alternar entre modos             |
| LED Verde             | GP11           | Indicação visual          |
| LED Vermelho          | GP13           | Indicação visual           |
| Matriz de LEDs 5x5    | GP7       | Representação gráfica colorida   |
| Buzzer                | GP10            | Sinais sonoros                   |

---

## Estrutura do Repositório

- **`semaforo_inteligente_freertos.c`**: Código-fonte principal do projeto.
- **`lib/ssd1306.h` e `lib/ssd1306.c`**: Controle do display OLED.
- **`lib/led_5x5.h` e `lib/led_5x5.c`**: Controle da matriz de LEDs RGB.
- **`lib/button.h` e `lib/button.c`**: Gestão de entrada do botão com debounce.
- **`lib/ledRGB.h` e `lib/ledRGB.c`**: Controle dos LEDs físicos.
- **`lib/buzzer.h` e `lib/buzzer.c`**: Controle do buzzer via PWM.
- **`README.md`**: Documentação do projeto.

---

## Conceitos Aplicados

- **Programação Multitarefa**: Execução paralela de múltiplas funcionalidades.
- **Sincronização de Tarefas**: Coordenação via variáveis voláteis compartilhadas.
- **Interface I2C**: Comunicação com o display OLED.
- **Geração PWM**: Controle de frequência sonora no buzzer.
- **Programable IO (PIO)**: Controle eficiente da matriz de LEDs.
- **Debounce de Botão**: Eliminação de leituras falsas por ruído mecânico.
- **Esquemas de Prioridade**: Tarefas com diferentes níveis de importância.

---

## Objetivos Alcançados

- **Simulação Realista**: Reprodução fiel do comportamento de um semáforo real.
- **Integração Multimídia**: Informações visuais e sonoras sincronizadas.
- **Multitarefa Eficiente**: Tarefas concorrentes sem conflitos de recursos.
- **Economia de Energia**: Modo noturno com operação reduzida.
- **Código Modular**: Organização lógica e manutenível das funcionalidades.

---

## Demonstração do Projeto

[Link para o vídeo de demonstração]

---

## Desenvolvido por

Henrique Oliveira dos Santos  
[LinkedIn](https://www.linkedin.com/in/dev-henriqueo-santos/)
