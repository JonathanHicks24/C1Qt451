cmake_minimum_required(VERSION 3.10)

project(rewritten_code)

# Append the custom path for Qt
list(APPEND CMAKE_PREFIX_PATH "C:/Qt/6.5.3/mingw_64/lib/cmake/Qt6")

# Specify the required Qt modules
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# List your source and header files
set(SOURCES
        main.cpp
        mainwindow.cpp
        dungeon.cpp
)

set(HEADERS
        mainwindow.h
        dungeon.h
)

set(FORMS
        mainwindow.ui
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${FORMS})

# Link the required Qt modules
target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)
set_target_properties(rewritten_code PROPERTIES WIN32_EXECUTABLE ON)

