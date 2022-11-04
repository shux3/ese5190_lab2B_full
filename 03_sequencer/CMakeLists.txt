# Set minimum required CMake version -- 3.12
cmake_minimum_required(VERSION 3.13)
# Pull in (SDK before the project)
include(pico_sdk_import.cmake)

# Set project name and C/C++ standards
project(sequencer C CXX ASM)
# Set the version of C/C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Tell CMake where to find executable source file
add_executable(${PROJECT_NAME}
   sequencer.c
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio) #OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(${PROJECT_NAME} PRIVATE sequencer.c)

# Links to find python.h
find_package(Python COMPONENTS Development REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
target_link_libraries(<Python.h> ${PYTHON_LIBRARIES})

# Link to libs
target_link_libraries(${PROJECT_NAME}
    PRIVATE pico_stdlib 
    PRIVATE hardware_pio
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})
