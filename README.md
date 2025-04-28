# Ohmímetro Digital - BitDogLab

O **Ohmímetro Digital** é um sistema embarcado desenvolvido para medir resistores de forma precisa e prática utilizando a plataforma **BitDogLab**. O sistema calcula o valor do resistor, aproxima o valor para a série comercial **E24** e apresenta o resultado tanto em um **display OLED** quanto de forma gráfica em uma **matriz de LEDs 5x5**.

---

## Funcionalidades Principais

- **Medição de Resistores**: Mede resistores conectados através de um divisor resistivo.
- **Ajuste para Série E24**: Aproxima automaticamente o valor lido para o resistor comercial mais próximo da série E24.
- **Identificação Visual**:
  - Exibe o valor numérico e a representação textual das cores no display OLED.
  - Representa graficamente o código de cores na matriz de LEDs 5x5.
- **Detecção de Erros**: Indica no display OLED a ausência de resistor quando detectada resistência elevada.

---

## Tecnologias Utilizadas

- **Linguagem de Programação**: C  
- **Microcontrolador**: Raspberry Pi Pico W  
- **Componentes Utilizados**:
  - Display OLED SSD1306 128x64 (I2C)
  - Matriz de LEDs 5x5 RGB (WS2812)
  - Protoboard para montagem do divisor resistivo
- **Bibliotecas e SDKs**:
  - `ssd1306` para controle do display OLED
  - `led_5x5` para controle da matriz de LEDs via PIO
  - Pico SDK para GPIO, ADC e comunicação I2C

---

## Como Funciona

### Medição do Resistor
- Realiza **500 leituras** consecutivas via ADC para calcular a média, reduzindo ruídos.
- Utiliza um divisor resistivo com resistência de **10kΩ conhecida** para calcular a resistência desconhecida.
- Aplica a fórmula adequada de divisores de tensão.

### Ajuste para Série E24
- Após a medição, o valor é **normalizado** e comparado com a série E24, com tolerância de 5%.
- O valor mais próximo é escolhido para melhor representar o resistor comercial padrão.

### Exibição de Resultados
- **Display OLED**:
  - Exibe o valor da resistência lida.
  - Mostra os textos correspondentes às faixas de cores.
- **Matriz de LEDs 5x5**:
  - Representa o código de cores dos resistores:
    - Primeira linha: primeiro dígito.
    - Segunda linha: segundo dígito.
    - Terceira linha: multiplicador.

### Tratamento de Erros
- Resistência superior a **200kΩ** é interpretada como ausência de resistor:
  - Mensagem de erro exibida no display OLED.
  - Matriz de LEDs é apagada.

---

## Configuração do Hardware

| Componente            | Pino do Pico | Função                                     |
|------------------------|--------------|-------------------------------------------|
| Display OLED (I2C)     | GP14 (SDA), GP15 (SCL) | Comunicação I2C                          |
| Matriz de LEDs 5x5     | GP7          | Controle de LEDs via PIO                  |
| Entrada Analógica (ADC)| GP28         | Medição da tensão do divisor resistivo    |

---

## Estrutura do Repositório

- **`ohmimetro-bitdoglab.c`**: Código-fonte principal do projeto.  
- **`lib/ssd1306.h` e `lib/ssd1306.c`**: Controle do display OLED.  
- **`lib/font.h`**: Fonte utilizada no display.  
- **`lib/led_5x5.h` e `lib/led_5x5.c`**: Controle gráfico da matriz de LEDs RGB.  
- **`README.md`**: Documentação do projeto.

---

## Demonstração do Projeto

_Link para o vídeo e demonstração prática:_  
[#]

---

## Conceitos Aplicados

- **Conversão Analógica-Digital (ADC)** para medição de tensão.  
- **Divisor de Tensão** para medir resistência desconhecida.  
- **Comunicação I2C** para controle do display OLED.  
- **Controle de LEDs via PIO** para a matriz RGB.  
- **Normalização e aproximação para série E24**.  
- **Exibição gráfica e textual simultânea** para melhor entendimento dos resultados.

---

## Objetivos Alcançados

- **Medição precisa** de resistores.
- **Identificação visual eficiente** através do OLED e matriz 5x5.
- **Código modularizado e organizado** para facilitar manutenção e expansão.
- **Tratamento de erros** de conexão do resistor.

---

## Desenvolvido por

Henrique Santos  
[LinkedIn](https://www.linkedin.com/in/dev-henriqueo-santos/)
