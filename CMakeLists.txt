# Shoot'em up en C++ moderne avec SDL3
cmake_minimum_required(VERSION 3.29)

# macOS : le SDK 27 est incompatible avec libc++ 22 (<cfloat> cassé) ;
# on force le SDK 26 par défaut (doit être défini avant project()).
# Surchargeable avec -DCMAKE_OSX_SYSROOT=...
set(_MACOS_SDK_26 "/Library/Developer/CommandLineTools/SDKs/MacOSX26.sdk")
if(NOT CMAKE_OSX_SYSROOT AND EXISTS "${_MACOS_SDK_26}")
    set(CMAKE_OSX_SYSROOT "${_MACOS_SDK_26}" CACHE PATH "macOS SDK" FORCE)
endif()

project(shootemup CXX)

# C++ 23, avertissements traités comme des erreurs, sans extensions
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TESTS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests)

# Pour "import std"
include(cmake/std.cmake)
include(cmake/compile_options.cmake)

# Bibliothèque graphique
find_package(SDL3 REQUIRED CONFIG)

#######################################################
# Modules (.ixx), fichiers d'implémentation (.cpp hors main.cpp) et tests
file(GLOB PROJECT_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.ixx")
file(GLOB PROJECT_IMPLEMENTATION_FILES CONFIGURE_DEPENDS "${SRC_DIR}/*.cpp")
list(REMOVE_ITEM PROJECT_IMPLEMENTATION_FILES "${SRC_DIR}/main.cpp")
file(GLOB TEST_FILES CONFIGURE_DEPENDS "${TESTS_DIR}/*.cpp")

# Exécutable du jeu
add_executable(${PROJECT_NAME}
        ${SRC_DIR}/main.cpp
        ${PROJECT_IMPLEMENTATION_FILES}
)
target_sources(${PROJECT_NAME}
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        ${PROJECT_FILES}
)
compile_options(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} SDL3::SDL3)

#######################################################
# Tests unitaires
include(cmake/catch2.cmake)

add_executable(tests ${TEST_FILES} ${PROJECT_IMPLEMENTATION_FILES})
target_sources(tests
        PUBLIC
        FILE_SET CXX_MODULES
        FILES
        ${PROJECT_FILES}
)
compile_options(tests)
target_link_libraries(tests Catch2::Catch2WithMain SDL3::SDL3)

# Configuration automatique pour CTest
include(CTest)
include(Catch)
catch_discover_tests(tests)
