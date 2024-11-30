# Укажите минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.10)

# Переменные окружения
message(STATUS "Environment Variables:")
execute_process(COMMAND printenv
                OUTPUT_VARIABLE ENV_OUTPUT
                OUTPUT_STRIP_TRAILING_WHITESPACE)
message(STATUS "${ENV_OUTPUT}")

# Название проекта
project(Test VERSION 1.0 LANGUAGES CXX)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Укажите путь к исходным файлам
set(SRC_DIR src)
set(INCLUDE_DIR src)

# Найдите все исходные файлы в каталоге src
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Укажите путь к заголовочным файлам
include_directories(${INCLUDE_DIR})

# Добавьте основной исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${SRC_DIR})

# Опционально: подключите библиотеки, если они есть
# target_link_libraries(${PROJECT_NAME} <library_name>)

# Опционально: добавьте тесты
# enable_testing()