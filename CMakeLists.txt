cmake_minimum_required(VERSION 3.16)
project(GraphComponents LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Включаем предупреждения (для GCC / Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Пути к заголовочным файлам
include_directories(${CMAKE_SOURCE_DIR}/include)

# Собираем все .cpp файлы из src/
file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/common/*.cpp)

# Создаем исполняемые файлы
add_executable(${PROJECT_NAME}_play ${CMAKE_SOURCE_DIR}/src/main_play.cpp ${SRC_FILES})
add_executable(${PROJECT_NAME}_tests ${CMAKE_SOURCE_DIR}/src/main_tests.cpp ${SRC_FILES})

# (необязательно) Указываем папку для сборки бинарников
set_target_properties(${PROJECT_NAME}_play PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/
)

set_target_properties(${PROJECT_NAME}_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
