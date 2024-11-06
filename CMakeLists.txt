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
        src/parser.c
)

# Regrouper les fichiers d'en-tête
set(HEADER_FILES
        src/lexer.h
        src/AST.h
        src/parser.h
)

# Créer l'exécutable
add_executable(Interpreteur_C ${SOURCE_FILES} ${HEADER_FILES})

# Optionnel: Si tu as un sous-dossier avec des fichiers C, tu peux les ajouter de manière dynamique :
# aux_source_directory(src SOURCES)
# add_executable(Interpreteur_C ${SOURCES})
