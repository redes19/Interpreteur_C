cmake_minimum_required(VERSION 3.27)
project(Interpreteur_C C)
set(CMAKE_C_STANDARD 11)
include_directories(src)

# Liste des fichiers source du projet
set(SOURCES
        src/main.c
        src/lexer.c
        src/parser.c
        src/ast.c
        src/repl.c
)

# Liste des fichiers d'en-tête du projet
set(HEADERS
        src/lexer.h
        src/parser.h
        src/ast.h
        src/repl.h
)

add_executable(Interpreteur_C ${SOURCES} ${HEADERS})
