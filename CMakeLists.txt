cmake_minimum_required(VERSION 3.27)
project(Interpreteur_C C)

# Spécifier le standard C
set(CMAKE_C_STANDARD 11)

# Spécifier les répertoires d'inclusion
include_directories(src)

# Regrouper les fichiers sources
set(SOURCE_FILES
        src/lexer.c
        src/main.c
        src/AST.c
)

# Regrouper les fichiers d'en-tête
set(HEADER_FILES
        src/lexer.h
        src/AST.h
)

# Créer l'exécutable
add_executable(Interpreteur_C ${SOURCE_FILES} ${HEADER_FILES})