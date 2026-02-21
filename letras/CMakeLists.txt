cmake_minimum_required(VERSION 3.13)
project(Practica_final_Juego_letras)

set(CMAKE_CXX_STANDARD 14)

set(BASE_FOLDER .)

include_directories(${BASE_FOLDER}/include)

# ==============================================================
# Crear carpeta bin si no existe y definir salida del ejecutable
# ==============================================================
file(MAKE_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# ==============================================================
# Ejecutables
# ==============================================================


if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/letras.cpp)
    add_executable(letras
            ${BASE_FOLDER}/src/letras.cpp
            ${BASE_FOLDER}/src/letters_set.cpp
            ${BASE_FOLDER}/src/dictionary.cpp
            ${BASE_FOLDER}/src/letters_bag.cpp
    )
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/conjunto_letras.cpp)
  add_executable(conjunto_letras
    ${BASE_FOLDER}/src/conjunto_letras.cpp
    ${BASE_FOLDER}/src/letters_set.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/bolsa.cpp)
  add_executable(bolsa
    ${BASE_FOLDER}/src/bolsa.cpp
    ${BASE_FOLDER}/src/letters_bag.cpp
    ${BASE_FOLDER}/src/letters_set.cpp
    ${BASE_FOLDER}/src/dictionary.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/bolsa_letras.cpp)
  add_executable(bolsa_letras
    ${BASE_FOLDER}/src/bolsa_letras.cpp
    ${BASE_FOLDER}/src/letters_bag.cpp
    ${BASE_FOLDER}/src/letters_set.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/generador_letras.cpp)
    add_executable(generador_letras
        ${BASE_FOLDER}/src/generador_letras.cpp
        ${BASE_FOLDER}/src/dictionary.cpp
        ${BASE_FOLDER}/src/letters_set.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/cantidad_letras.cpp)
  add_executable(cantidad_letras
    ${BASE_FOLDER}/src/cantidad_letras.cpp
    ${BASE_FOLDER}/src/dictionary.cpp
    ${BASE_FOLDER}/src/letters_set.cpp)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/palabras_longitud.cpp)
  add_executable(palabras_longitud
    ${BASE_FOLDER}/src/palabras_longitud.cpp
    ${BASE_FOLDER}/src/dictionary.cpp)
endif()

# ==============================================================
# Doxygen (documentación)
# ==============================================================

find_package(Doxygen)
if (DOXYGEN_FOUND)
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)
else()
    message("Doxygen needs to be installed to generate documentation")
endif()

