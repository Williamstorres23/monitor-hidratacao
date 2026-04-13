# 💧 Monitor de Hidratação — BitDogLab (RP2040)

Projeto final do programa **EmbarcaTech Expansão**. Sistema embarcado que monitora a hidratação do usuário, emitindo lembretes sonoros e visuais em intervalos regulares e publicando dados em tempo real via MQTT.

---

## Objetivo

Desenvolver um sistema embarcado de baixo custo que auxilie pessoas a manterem hábitos saudáveis de hidratação ao longo do dia, utilizando a placa de desenvolvimento **BitDogLab (RP2040)** com comunicação IoT via WiFi e protocolo MQTT.

---

## Funcionalidades

* Lembrete sonoro (buzzer) e visual (display OLED) a cada 30 minutos
* Confirmação de copo d'água via botão com debounce por interrupção GPIO
* Contagem de copos bebidos e volume total ingerido no dia
* Countdown no display até o próximo lembrete
* Publicação de dados em JSON via MQTT para dashboard externo
* Meta diária configurável (padrão: 8 copos de 200 mL)

---

## Hardware

| Componente               | Descrição                      |
| ------------------------ | ------------------------------ |
| BitDogLab (RP2040)       | Microcontrolador principal     |
| Display SSD1306 (128x64) | Interface visual via I2C       |
| Buzzer passivo           | Alertas e confirmações via PWM |
| Botão A (GPIO 5)         | Confirmar copo de água bebido  |
| Botão B (GPIO 6)         | Pausar/retomar timer           |
| WiFi CYW43 (integrado)   | Comunicação IoT via MQTT       |

---

## Estrutura do Repositório

monitor_hidratacao/
├── firmware/
│   ├── main.c
│   ├── config.h
│   └── modules/
│       ├── timer_module.h/c
│       ├── display_module.h/c
│       ├── input_module.h/c
│       ├── buzzer_module.h/c
│       └── mqtt_module.h/c
├── libs/
│   └── ssd1306/
├── CMakeLists.txt
└── README.md

---

## Como Compilar e Gravar

### Pré-requisitos

* Pico SDK
* CMake >= 3.13
* GCC ARM (`arm-none-eabi-gcc`)
* Biblioteca SSD1306

---

### Configurar WiFi e MQTT

#define WIFI_SSID   "SUA_REDE_WIFI"
#define WIFI_PASS   "SUA_SENHA_WIFI"
#define MQTT_SERVER "broker.hivemq.com"
#define MQTT_TOPICO "embarcatech/hidratacao"

---

### Compilar

mkdir build
cd build
cmake .. -DPICO_SDK_PATH=/caminho/para/pico-sdk
cmake --build .

---

### Gravar na BitDogLab

1. Segure BOOTSEL
2. Conecte via USB
3. Copie monitor_hidratacao.uf2
4. Pronto 🚀

---

## Dados MQTT

{
"copos": 3,
"volume_ml": 600,
"tempo_restante_s": 1247
}

---

## Protocolo de Uso

1. Ligue o sistema
2. Aguarde o alerta
3. Pressione botão A após beber água
4. Acompanhe no display
5. Visualize no dashboard MQTT

---

## Dependências

https://github.com/raspberrypi/pico-sdk
https://github.com/daschr/pico-ssd1306

---

## Licença

MIT License

---

## Autor

Williams Torres Garcia da Silva
Projeto Final — EmbarcaTech Expansão (2026)
