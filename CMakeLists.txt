# Минимальная версия CMake
cmake_minimum_required(VERSION 3.14)

# Название проекта
project(NavalBattle)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка компилятора C++ и компилятора ресурсов для MinGW
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

# Добавление флагов компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")

# Установка директорий
set(FILES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/files")
set(RESOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/resources")

# Добавление исходных файлов для каждого модуля
set(SOURCES
        # Основные файлы
        ${FILES_DIR}/core/src/main.cpp
        ${FILES_DIR}/core/src/Console.cpp
        ${FILES_DIR}/core/src/Game.cpp
        ${FILES_DIR}/core/src/GameLogic.cpp
        ${FILES_DIR}/core/src/ManagerShips.cpp

        # Файлы для меню
        ${FILES_DIR}/menu/src/MenuState.cpp
        ${FILES_DIR}/menu/src/MenuDisplay.cpp
        ${FILES_DIR}/menu/src/MenuInput.cpp

        # Файлы для настроек поля
        ${FILES_DIR}/field_settings/src/FieldSettingsState.cpp
        ${FILES_DIR}/field_settings/src/FieldSettingsDisplay.cpp
        ${FILES_DIR}/field_settings/src/FieldSettingsInput.cpp

        # Файлы для поля
        ${FILES_DIR}/game_field/src/GameField.cpp
        ${FILES_DIR}/game_field/src/GameFieldDisplay.cpp
        ${FILES_DIR}/game_field/src/GameFieldInput.cpp

        # Файлы для сущностей
        ${FILES_DIR}/entities/src/Ship.cpp
        ${FILES_DIR}/entities/src/ShipPoint.cpp
        ${FILES_DIR}/entities/src/Cell.cpp
        ${FILES_DIR}/entities/src/Player.cpp

        # Ресурсы
        ${RESOURCES_DIR}/resources.rc
)

# Создание исполняемого файла
add_executable(${PROJECT_NAME} ${SOURCES})

# Подключение заголовочных файлов для каждого модуля
target_include_directories(${PROJECT_NAME} PRIVATE
        ${FILES_DIR}/core/include
        ${FILES_DIR}/menu/include
        ${FILES_DIR}/field_settings/include
        ${FILES_DIR}/entities/include
)

# Связывание с библиотекой winmm (для поддержки PlaySoundA)
target_link_libraries(${PROJECT_NAME} PRIVATE winmm)
