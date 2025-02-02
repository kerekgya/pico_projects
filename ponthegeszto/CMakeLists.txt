# cmake version
cmake_minimum_required(VERSION 3.13)

# include the sdk.cmake file
include(pico_sdk_import.cmake)

# give the project a name (anything you want)
project(ponthegeszto)

# initialize the sdk
pico_sdk_init()

#######

# name anything you want
add_executable(ponthegeszto)

# must match with pio filename and executable name from above
# pico_generate_pio_header(conway ${CMAKE_CURRENT_LIST_DIR}/hsync.pio)
# pico_generate_pio_header(conway ${CMAKE_CURRENT_LIST_DIR}/vsync.pio)
# pico_generate_pio_header(conway ${CMAKE_CURRENT_LIST_DIR}/rgb.pio)

# must match with executable name and source file names
target_sources(ponthegeszto PRIVATE main.c)

# must match with executable name
target_link_libraries(ponthegeszto PRIVATE pico_stdlib hardware_pio hardware_dma hardware_adc)

# enable usb output, disable uart output
pico_enable_stdio_usb(ponthegeszto 1)
pico_enable_stdio_uart(ponthegeszto 0)

# must match with executable name
pico_add_extra_outputs(ponthegeszto)
