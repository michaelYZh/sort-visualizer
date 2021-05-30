#!/bin/bash
# 20180506 chen.s.g <chensg@imohe.com> 编译助手

# 编译之前需要安装mingw-w64-x86_64-allegro、mingw-w64-x86_64-freeimage 这两个库，msys2 参考命令：
# pacman -S mingw-w64-x86_64-allegro
# pacman -S mingw-w64-x86_64-freeimage

gcc -Wall allegro.cpp data.cpp apstring.cpp functions.cpp hitbox.cpp main.cpp \
    -lstdc++ -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf -lallegro_video \
    -o main.exe
