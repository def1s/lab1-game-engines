cmake_minimum_required(VERSION 3.31)
project(Demo
    VERSION 1.0
    LANGUAGES CXX)

# Run clang-tidy during CMake builds when available.
option(ENABLE_CLANG_TIDY "Enable clang-tidy checks during build" ON)
if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (CLANG_TIDY_EXE)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}")
        message(STATUS "clang-tidy enabled: ${CLANG_TIDY_EXE}")
    else ()
        message(STATUS "clang-tidy not found; build-time linting is disabled")
    endif ()
endif ()

file(COPY
    fonts/futura.ttf
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/fonts)
#file(COPY
#    config.json
#    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(dependencies)
add_subdirectory(src)
