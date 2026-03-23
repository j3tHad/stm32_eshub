cmake_minimum_required(VERSION 3.22)
project(gpio_button_led C ASM)

# --- 1. MCU Specific Flags (UPDATE THESE FOR YOUR CHIP) ---
# currently Cortex-M4 with floating point
set(MCU_FLAGS -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16)

# --- 2. Compiler and Linker Options ---
# --specs=nano.specs uses a smaller C library optimized for embedded
add_compile_options(
    ${MCU_FLAGS}
    -O0 -g3 -Wall -Wextra 
    -ffunction-sections -fdata-sections
)

# --- 3. Linker Script (UPDATE THIS TO MATCH YOUR .ld FILE) ---
# Look in your project folder for a file ending in .ld
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/STM32F411RETX_FLASH.ld)

add_link_options(
    ${MCU_FLAGS}
    -T${LINKER_SCRIPT}
    --specs=nano.specs
    -Wl,-Map=${PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--print-memory-usage
)

# --- 4. Include Directories ---
include_directories(
    Inc
    # Add any other folders with .h files here
    Drivers/CMSIS/Device/ST/STM32F4xx/Include
    Drivers/CMSIS/Include
)

# --- 5. Source Files ---
# Find all C and Assembly files in the respective directories
file(GLOB_RECURSE SOURCES "Src/*.c")
file(GLOB_RECURSE ASM_SOURCES "Startup/*.s") # Sometimes it's .S (capital)

# --- 6. Build the Executable ---
add_executable(${PROJECT_NAME} ${SOURCES} ${ASM_SOURCES})

# --- 7. Generate .bin and .hex files for flashing ---
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMENT "Generating .hex and .bin files"
)

add_compile_options(
    ${MCU_FLAGS}
    -O0 -g3 -Wall -Wextra
    -ffunction-sections -fdata-sections
    -fno-exceptions -fno-unwind-tables
)