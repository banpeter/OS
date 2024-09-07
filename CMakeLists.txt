cmake_minimum_required(VERSION 3.27.1)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(OS C CXX ASM)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()
# rest of your project

include_directories(include)

add_executable(main src/main.c
        src/context_switch.s
        include/process.h
        include/motor_control.h
        src/motor_control.c
        include/ultrasonic_sensor.h
        src/ultrasonic_sensor.c
        src/ipc.c
        include/ipc.h
)



# Add pico_stdlib library which aggregates commonly used features
target_link_libraries( main pico_stdlib pico_cyw43_arch_none hardware_pwm hardware_gpio)

# Enable USB stdio communication
pico_enable_stdio_usb(main 1)
pico_enable_stdio_uart(main 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(main)