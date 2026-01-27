cmake_minimum_required(VERSION 4.1)
project(ggj2k26_v3)

set(CMAKE_C_STANDARD 11)

add_executable(ggj2k26_v3 ${SRC_FILES}
        src/game.c
        src/draw.c
        src/error.c
        src/events.c
        src/main.c
        src/update.c
        src/utils.c
        inc/user_data.h
        src/user_data.c
        inc/module.h
        inc/action.h
        src/module.c
        inc/mod_convey.h
        src/mod_convey.c
        inc/mod_junction.h
        src/mod_junction.c
)

target_include_directories(ggj2k26_v3 PRIVATE inc)
