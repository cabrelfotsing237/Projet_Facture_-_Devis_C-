cmake_minimum_required(VERSION 3.16)
project(FacturesDevis VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Type de build" FORCE)
endif()

# Options de qualité communes à toutes les cibles (EOO-10, CT-07).
option(ISTILE_SANITIZERS "Active AddressSanitizer et UBSan" OFF)

add_library(istile_options INTERFACE)
if(MSVC)
  target_compile_options(istile_options INTERFACE /W4)
else()
  target_compile_options(istile_options INTERFACE -Wall -Wextra -pedantic)
  if(ISTILE_SANITIZERS)
    target_compile_options(istile_options INTERFACE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(istile_options INTERFACE -fsanitize=address,undefined)
  endif()
endif()

# Couche métier : aucune dépendance vers présentation ni persistance (EOO-01).
add_library(metier STATIC
  src/metier/montant_en_lettres.cpp
  src/metier/arrondi.cpp
  src/metier/taux.cpp
  src/metier/montant.cpp
)
target_include_directories(metier PUBLIC src)
target_link_libraries(metier PUBLIC istile_options)

# Tests unitaires (EOO-09).
enable_testing()
add_executable(tests_unitaires
  tests/test_main.cpp
  tests/test_montant_en_lettres.cpp
  tests/test_arrondi.cpp
  tests/test_montant.cpp
)
target_include_directories(tests_unitaires SYSTEM PRIVATE tests/third_party)
target_link_libraries(tests_unitaires PRIVATE metier istile_options)
add_test(NAME tests_unitaires COMMAND tests_unitaires)