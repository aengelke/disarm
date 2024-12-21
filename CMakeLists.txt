cmake_minimum_required(VERSION 3.23)

project(disarm64)
enable_testing()

set(DISARM_FEATURES "all" CACHE STRING "Comma-separated list of ISA extensions, or all.")

set(CMAKE_C_STANDARD 11)

if (MSVC)
    # NB: Building with MSVC is not (yet) supported.
    add_compile_options(/W4 -D_CRT_SECURE_NO_WARNINGS /wd4018 /wd4146 /wd4244 /wd4245 /wd4267 /wd4310)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Wno-overlength-strings)
endif()

find_package(Python3 3.10 REQUIRED)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include")
set(PRIV_INC ${CMAKE_CURRENT_BINARY_DIR}/include/disarm64-private.inc)
set(PUB_INC ${CMAKE_CURRENT_BINARY_DIR}/include/disarm64-public.inc)
add_custom_command(
    OUTPUT ${PRIV_INC} ${PUB_INC}
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/parse.py ${PUB_INC} ${PRIV_INC} ${CMAKE_CURRENT_SOURCE_DIR}/desc.txt --features ${DISARM_FEATURES} --feature-desc ${CMAKE_CURRENT_SOURCE_DIR}/feat.txt --encode-in-header
    DEPENDS desc.txt feat.txt parse.py
    COMMENT "Building table for disarm64"
)

add_library(disarm64 STATIC)
add_library(disarm64::disarm64 ALIAS disarm64)
set_target_properties(disarm64 PROPERTIES LINKER_LANGUAGE C)
target_sources(disarm64 PRIVATE
    classify.c
    decode.c
    encode.c
    format.c

    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS .
    FILES
        disarm64.h

    PUBLIC
    FILE_SET generated_public TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
    FILES
        ${PUB_INC}

    PRIVATE
    FILE_SET generated_private TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/include
    FILES
        ${PRIV_INC}
)

add_executable(decode-test test/decode-test.c)
target_link_libraries(decode-test disarm64)
add_test(NAME decode-test COMMAND decode-test)

add_executable(encode-test test/encode-test.c)
# Disabling optimization substantially reduces compile time.
target_compile_options(encode-test PRIVATE -O0)
target_link_libraries(encode-test disarm64)
add_test(NAME encode-test COMMAND encode-test)

install(TARGETS disarm64 EXPORT disarm64
    LIBRARY
    ARCHIVE
    FILE_SET HEADERS FILE_SET generated_public)
