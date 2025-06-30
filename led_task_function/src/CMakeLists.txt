add_executable(led_task_function
    led_task_function.c
)

set_target_properties(led_task_function PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_sources(led_task_function
    PRIVATE
    ${FREERTOS_KERNEL_PATH}/portable/MemMang/heap_4.c
)

target_include_directories(led_task_function PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../config
    ${CMAKE_CURRENT_LIST_DIR}/../tasks
    ${CMAKE_CURRENT_LIST_DIR}/../drivers
)

target_link_libraries(led_task_function 
    pico_stdlib 
    hardware_adc
    FreeRTOS-Kernel
)

pico_add_extra_outputs(led_task_function)
