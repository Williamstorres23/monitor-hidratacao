cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(monitor_hidratacao C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(monitor_hidratacao
    main.c
    timer_module.c
    display_module.c
    input_module.c
    buzzer_module.c
    mqtt_module.c
    libs/ssd1306/ssd1306.c
)

target_include_directories(monitor_hidratacao PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/ssd1306
)

target_link_libraries(monitor_hidratacao
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    hardware_i2c
    hardware_pwm
    hardware_gpio
    hardware_timer
    hardware_clocks
    pico_lwip_mqtt
)

pico_enable_stdio_usb(monitor_hidratacao 1)
pico_enable_stdio_uart(monitor_hidratacao 0)

pico_add_extra_outputs(monitor_hidratacao)
