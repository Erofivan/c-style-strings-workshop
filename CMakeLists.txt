cmake_minimum_required(VERSION 3.16)
project(c_style_strings_workshop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# По умолчанию собирается ваш код (cstring/my_cstring.cpp).
# -DUSE_SOLUTIONS=ON подменяет его эталонным решением (solutions/my_cstring.cpp):
# так преподаватель может проверить, что сами тесты корректны.
option(USE_SOLUTIONS "Собрать тесты против эталонного решения" OFF)

if(USE_SOLUTIONS)
    set(MY_CSTRING_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/solutions/my_cstring.cpp")
    message(STATUS "my_cstring: ЭТАЛОННОЕ РЕШЕНИЕ (solutions/my_cstring.cpp)")
else()
    set(MY_CSTRING_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/cstring/my_cstring.cpp")
    message(STATUS "my_cstring: ваш код (cstring/my_cstring.cpp)")
endif()

add_library(my_cstring STATIC "${MY_CSTRING_SOURCE}")
target_include_directories(my_cstring PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/cstring")

if(MSVC)
    target_compile_options(my_cstring PRIVATE /W4)
else()
    target_compile_options(my_cstring PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()

# Песочница для первой (объяснительной) части семинара: cmake --build build --target playground
add_executable(playground main.cpp)
target_link_libraries(playground PRIVATE my_cstring)

enable_testing()
add_subdirectory(tests)
