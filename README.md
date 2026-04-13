Aqui está:

---

# 💧 Monitor de Hidratação — BitDogLab (RP2040)

Projeto final do programa **EmbarcaTech Expansão**. Sistema embarcado que monitora a hidratação do usuário, emitindo lembretes sonoros e visuais em intervalos regulares e publicando dados em tempo real via MQTT.

---

## Objetivo

Desenvolver um sistema embarcado de baixo custo que auxilie pessoas a manterem hábitos saudáveis de hidratação ao longo do dia, utilizando a placa de desenvolvimento **BitDogLab (RP2040)** com comunicação IoT via WiFi e protocolo MQTT.

---

## Funcionalidades

- Lembrete sonoro (buzzer) e visual (display OLED) a cada 30 minutos
- Confirmação de copo d'água via botão com debounce por interrupção GPIO
- Contagem de copos bebidos e volume total ingerido no dia
- Countdown no display até o próximo lembrete
- Publicação de dados em JSON via MQTT para dashboard externo
- Meta diária: 10 copos de 200 mL (2 litros/dia)
- Melodia comemorativa e tela de parabéns ao atingir a meta

---

## Hardware

| Componente | Descrição |
|---|---|
| BitDogLab (RP2040) | Microcontrolador principal |
| Display SSD1306 (128x64) | Interface visual via I2C |
| Buzzer passivo | Alertas e confirmações via PWM |
| Botão A (GPIO 5) | Confirmar copo de água bebido |
| Botão B (GPIO 6) | Pausar/retomar timer |
| WiFi CYW43 (integrado) | Comunicação IoT via MQTT |

---

## Estrutura do Repositório

```
monitor_hidratacao/
├── main.c
├── config.h
├── timer_module.c / .h
├── display_module.c / .h
├── input_module.c / .h
├── buzzer_module.c / .h
├── mqtt_module.c / .h
├── lwipopts.h
├── libs/
│   └── ssd1306/
├── CMakeLists.txt
└── README.md
```

---

## Como Compilar e Gravar

### Pré-requisitos

- Raspberry Pi Pico SDK
- CMake >= 3.13
- GCC ARM (arm-none-eabi-gcc)
- Biblioteca pico-ssd1306 em libs/ssd1306/

### Configurar WiFi e MQTT

Edite o arquivo `config.h`:

```c
#define WIFI_SSID   "SUA_REDE_WIFI"
#define WIFI_PASS   "SUA_SENHA_WIFI"
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_TOPICO "embarcatech/hidratacao"
```

### Compilar

```bash
mkdir build
cd build
cmake .. -DPICO_SDK_PATH=/caminho/para/pico-sdk -DPICO_BOARD=pico_w
nmake
```

### Gravar na BitDogLab

1. Segure o botão BOOTSEL
2. Conecte via USB
3. Copie o arquivo monitor_hidratacao.uf2 para o drive RPI-RP2
4. Pronto 🚀

---

## Dados MQTT

Payload publicado no tópico `embarcatech/hidratacao`:

```json
{
  "copos": 3,
  "volume_ml": 600,
  "tempo_restante_s": 1247
}
```

---

## Protocolo de Uso

1. Ligue o sistema — tela de boas-vindas por 5 segundos
2. Aguarde o alerta (buzzer + display) a cada 30 minutos
3. Beba água e pressione o Botão A para confirmar
4. Acompanhe copos, volume e countdown no display
5. Ao atingir 10 copos — melodia comemorativa e tela de parabéns
6. Visualize os dados em tempo real via dashboard MQTT

---

## Dependências

| Biblioteca | Fonte |
|---|---|
| Raspberry Pi Pico SDK | https://github.com/raspberrypi/pico-sdk |
| pico-ssd1306 | https://github.com/daschr/pico-ssd1306 |
| lwIP + MQTT | Incluído no Pico SDK |
| CYW43 driver | Incluído no Pico SDK |

---

## Uso de Inteligência Artificial

O desenvolvimento contou com o auxílio da ferramenta **Claude (Anthropic)** nas seguintes etapas: definição da arquitetura do sistema, desenvolvimento do código-fonte em C, elaboração do relatório técnico e documentação do projeto. Todas as decisões técnicas foram validadas e o código revisado pelo autor.

---

## Licença

MIT License — livre para uso, modificação e distribuição com atribuição.

---

## Autor

**Williams Torres Garcia da Silva**
Projeto Final — EmbarcaTech Expansão (2026)
