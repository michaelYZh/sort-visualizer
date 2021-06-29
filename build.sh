#!/bin/bash

# Need to install: mingw-w64-x86_64-allegro, mingw-w64-x86_64-freeimage
# msys2 command:
# pacman -S mingw-w64-x86_64-allegro
# pacman -S mingw-w64-x86_64-freeimage

gcc -Wall allegro.cpp data.cpp apstring.cpp functions.cpp hitbox.cpp graphicalSorting.cpp \
    -lstdc++ -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf -lallegro_video \
    -o graphicalSorting
