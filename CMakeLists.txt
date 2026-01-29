cmake_minimum_required(VERSION 4.1)
set(CMAKE_C_STANDARD 11)

project(ggj2k26_v3)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.c *.h)
list(FILTER SOURCES EXCLUDE REGEX "cmake-build-")
add_executable(ggj2k26_v3 ${SOURCES}
        code/product/inc/product.h
        code/product/src/product.c)
target_include_directories( ggj2k26_v3 PRIVATE
                            inc
                            code/modules/inc
                            code/actions/inc
                            code/product/inc)

