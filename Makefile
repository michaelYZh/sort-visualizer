CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=graphicalSorting.o data.o functions.o hitbox.o allegro.o apstring.o apvector.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=graphicalSorting

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}