CPPXX := g++ -std=c++11

INCLUDE_DIR := include
SRC_DIR := src
OUT_DIR := out

LINKER_FLAGS := -L${INCLUDE_DIR}/SDL2 -lmingw32 -lSDL2main -lSDL2
INCLUDE_FLAGS := -I${INCLUDE_DIR}/
CPP_FLAGS := -Wall -Werror

EXE_FILE :=	particle-fire-explosion.exe

main: main.o
	${CPPXX} ${OUT_DIR}/main.o ${OUT_DIR}/screen.o ${OUT_DIR}/swarm.o ${OUT_DIR}/particle.o ${INCLUDE_FLAGS} ${LINKER_FLAGS} -o ${EXE_FILE} ${CPP_FLAGS}

main.o: screen.o swarm.o particle.o
	${CPPXX} ${INCLUDE_FLAGS} ${LINKER_FLAGS} -c ${SRC_DIR}/main.cpp -o ${OUT_DIR}/main.o ${CPP_FLAGS}

screen.o: ${SRC_DIR}/screen.cpp ${INCLUDE_DIR}/screen.h
	${CPPXX} ${INCLUDE_FLAGS} ${LINKER_FLAGS} -c ${SRC_DIR}/screen.cpp -o ${OUT_DIR}/screen.o ${CPP_FLAGS}

swarm.o: ${SRC_DIR}/swarm.cpp ${INCLUDE_DIR}/swarm.h
	${CPPXX} ${INCLUDE_FLAGS} ${LINKER_FLAGS} -c ${SRC_DIR}/swarm.cpp -o ${OUT_DIR}/swarm.o ${CPP_FLAGS}

particle.o:	${SRC_DIR}/particle.cpp ${INCLUDE_DIR}/particle.h
	${CPPXX} ${INCLUDE_FLAGS} ${LINKER_FLAGS} -c ${SRC_DIR}/particle.cpp -o ${OUT_DIR}/particle.o ${CPP_FLAGS}

.PHONY: clean
clean:
	del /F out/*
	del /F ${EXE_FILE}

