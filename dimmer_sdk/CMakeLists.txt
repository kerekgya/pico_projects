# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "/mnt/d/tmp/pico/pico-sdk")

# set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(dimmer_sdk C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(dimmer_sdk dimmer_sdk.cpp )

pico_generate_pio_header(dimmer_sdk ${CMAKE_CURRENT_LIST_DIR}/dimmer.pio)

pico_set_program_name(dimmer_sdk "dimmer_sdk")
pico_set_program_version(dimmer_sdk "0.1")


# Add the standard library to the build
target_link_libraries(dimmer_sdk
pico_stdlib)

# Add the standard include files to the build
target_include_directories(dimmer_sdk PRIVATE
${CMAKE_CURRENT_LIST_DIR}
${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(dimmer_sdk
        hardware_spi
        hardware_i2c
        hardware_dma
        hardware_pio
        hardware_interp
        hardware_timer
        hardware_watchdog
        hardware_clocks
)

pico_enable_stdio_uart(dimmer_sdk 0)
pico_enable_stdio_usb(dimmer_sdk 1)

pico_add_extra_outputs(dimmer_sdk)

