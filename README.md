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
- Meta diária configurável (padrão: 8 copos de 200 mL)

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
├── firmware/
│   ├── main.c                   # Loop principal e inicialização
│   ├── config.h                 # Configurações centralizadas (WiFi, pinos, MQTT)
│   └── modules/
│       ├── timer_module.h/c     # Temporização com repeating_timer
│       ├── display_module.h/c   # Interface SSD1306 via I2C
│       ├── input_module.h/c     # Leitura de botões via interrupção GPIO
│       ├── buzzer_module.h/c    # Tons PWM para alertas e confirmações
│       └── mqtt_module.h/c      # Publicação MQTT via lwIP
├── libs/
│   └── ssd1306/                 # Biblioteca do display (pico-ssd1306)
├── CMakeLists.txt               # Build system
└── README.md
```

---

## Como Compilar e Gravar

### Pré-requisitos

- [Raspberry Pi Pico SDK](https://github.com/raspberrypi/pico-sdk) instalado
- CMake >= 3.13
- GCC ARM toolchain (`arm-none-eabi-gcc`)
- Biblioteca [pico-ssd1306](https://github.com/daschr/pico-ssd1306) em `libs/ssd1306/`

### Configurar WiFi e MQTT

Edite o arquivo `firmware/config.h` com suas credenciais:

```c
#define WIFI_SSID   "SUA_REDE_WIFI"
#define WIFI_PASS   "SUA_SENHA_WIFI"
#define MQTT_SERVER "broker.hivemq.com"  // Ou seu broker
#define MQTT_TOPICO "embarcatech/hidratacao"
```

### Compilar

```bash
mkdir build && cd build
cmake .. -DPICO_SDK_PATH=/caminho/para/pico-sdk
make -j4
```

### Gravar na BitDogLab

1. Mantenha o botão **BOOTSEL** pressionado e conecte via USB
2. Copie o arquivo `build/monitor_hidratacao.uf2` para o drive **RPI-RP2**
3. A placa reiniciará automaticamente com o firmware

---

## Dados Publicados via MQTT

Payload JSON publicado no tópico `embarcatech/hidratacao` a cada 60 segundos e a cada confirmação de copo:

```json
{
  "copos": 3,
  "volume_ml": 600,
  "tempo_restante_s": 1247
}
```

Para visualizar os dados, use qualquer cliente MQTT como [MQTT Explorer](http://mqtt-explorer.com/) ou Node-RED.

---

## Protocolo de Uso

1. **Ligue a BitDogLab** — tela de boas-vindas por 2 segundos
2. **Aguarde o timer** — a cada 30 minutos, o buzzer soa e o display pisca
3. **Beba água e pressione o Botão A** — o copo é registrado e o timer é resetado
4. **Acompanhe no display** — copos bebidos, volume total e tempo até o próximo lembrete
5. **Dashboard externo** — visualize os dados publicados via MQTT

---

## Dependências

| Biblioteca | Finalidade | Fonte |
|---|---|---|
| pico-sdk | SDK oficial do RP2040 | raspberrypi/pico-sdk |
| pico-ssd1306 | Driver do display OLED | daschr/pico-ssd1306 |
| lwIP + MQTT | Pilha TCP/IP e cliente MQTT | Incluído no pico-sdk |
| CYW43 driver | WiFi da BitDogLab | Incluído no pico-sdk |

---

## Licença

MIT License — livre para uso, modificação e distribuição com atribuição.

---

## Autor

Desenvolvido como Projeto Final do EmbarcaTech Expansão — 2025.

Uso de IA: Claude (Anthropic) foi utilizado como assistente no desenvolvimento da arquitetura do sistema, estruturação do código em C, elaboração deste README e do relatório técnico.
