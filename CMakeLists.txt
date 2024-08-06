cmake_minimum_required(VERSION 3.10)

# Название проекта
project(Tetris)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Путь к SFML, установленной через Homebrew
set(SFML_DIR "/usr/local/Cellar/sfml/2.5.1/lib/cmake/SFML")

# Указать директорию заголовочных файлов
include_directories(include)

# Добавление исполняемого файла
add_executable(Tetris
    src/main.cpp
    src/Game.cpp
    src/Tetromino.cpp
    src/Interface.cpp
)

# Поиск пакетов SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Подключение библиотек SFML
target_link_libraries(Tetris sfml-system sfml-window sfml-graphics)