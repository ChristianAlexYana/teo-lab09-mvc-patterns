cmake_minimum_required(VERSION 3.21)
project(SeguimientoAcademico VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# --- Núcleo (Modelo + Controlador): C++ estándar, sin dependencia de Qt ---
file(GLOB_RECURSE NUCLEO_SRC CONFIGURE_DEPENDS
     src/model/*.cpp src/controller/*.cpp)
if(NUCLEO_SRC)
    add_library(nucleo STATIC ${NUCLEO_SRC})
    target_include_directories(nucleo PUBLIC src)
endif()

# --- Pruebas: se ejecutan sin iniciar la GUI ---
enable_testing()
file(GLOB TEST_SRC CONFIGURE_DEPENDS tests/test_*.cpp)
foreach(ts IN LISTS TEST_SRC)
    get_filename_component(nombre ${ts} NAME_WE)
    add_executable(${nombre} ${ts})
    target_link_libraries(${nombre} PRIVATE nucleo)
    target_include_directories(${nombre} PRIVATE tests)
    add_test(NAME ${nombre} COMMAND ${nombre})
endforeach()

# --- Vista (Qt 6 Widgets): solo si Qt está disponible ---
find_package(Qt6 COMPONENTS Widgets QUIET)
if(Qt6_FOUND AND TARGET nucleo AND EXISTS ${CMAKE_SOURCE_DIR}/src/main.cpp)
    set(CMAKE_AUTOMOC ON)
    add_executable(seguimiento src/main.cpp
                   src/view/MainWindow.cpp src/view/MainWindow.h)
    target_link_libraries(seguimiento PRIVATE nucleo Qt6::Widgets)
else()
    message(STATUS "Qt6 Widgets no encontrado o sin vista: se compilan solo núcleo y pruebas")
endif()
