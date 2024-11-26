idf_component_register(SRCS main.c status.c screen.c action.c
                       INCLUDE_DIRS .
                       PRIV_REQUIRES lcd pin esp_timer config joy)
# PRIV_REQUIRES ...
# target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
