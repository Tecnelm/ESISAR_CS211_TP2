cmake_minimum_required(VERSION 3.15)
project(ESISAR_CS211_TP2 C)

set(CMAKE_C_STANDARD 90)
set(HEADER
        src/utility_fonction.h
        src/fonction_decode_question_I1.h)
set(SRCS
        src/utility_fonction.c
        src/fonction_decode_question_I1.c)

add_executable(ESISAR_CS211_TP2 main.c ${SRCS} ${HEADER})