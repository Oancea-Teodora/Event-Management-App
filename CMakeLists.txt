cmake_minimum_required(VERSION 3.22)
project(oop_a10_915_Oancea_Teodora)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.7.1\\mingw_64")
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Charts Graphs)
qt_standard_project_setup()

include_directories(.)
#include_directories(. GUI)

qt_add_executable(oop_a10_915_Oancea_Teodora
        Event.h
        Event.cpp
        main.cpp
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        UI.cpp
        UI.h
        Utils.h
        Utils.cpp
        HTML_Repo.h
        HTML_Repo.cpp
        CSV_Repo.h
        CSV_Repo.cpp
        Exceptions.h
        Exceptions.cpp
        Validations.h
        Validations.cpp
        HTML_Repo.cpp
        GUI/GUI.h
        GUI/GUI.cpp
        Action.cpp
        Action.h
        Action.h
        Action.cpp
        TableMode.cpp
        TableMode.h
        TableMode.h
        TableMode.cpp

)

target_link_libraries(oop_a10_915_Oancea_Teodora PRIVATE Qt6::Widgets Qt6::Charts Qt6::Graphs)

set_target_properties(oop_a10_915_Oancea_Teodora PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

