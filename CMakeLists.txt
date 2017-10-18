cmake_minimum_required(VERSION 3.8)
project(Go_Compiler)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c analizadorLexico.c analizadorLexico.h analizadorSintactico.c analizadorSintactico.h definiciones.h gestorErrores.c gestorErrores.h sistemaEntrada.c sistemaEntrada.h tablaSimbolos.c tablaSimbolos.h)
add_executable(Go_Compiler ${SOURCE_FILES})