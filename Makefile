CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=graphicalSorting.o data.o functions.o hitbox.o allegro.o apstring.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=graphicalSorting

${EXEC}: ${OBJECTS}
	${CXX} -o ${EXEC} ${OBJECTS} -lstdc++ -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_dialog -lallegro_font -lallegro_image -lallegro_main -lallegro_memfile -lallegro_physfs -lallegro_primitives -lallegro_ttf -lallegro_video

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}