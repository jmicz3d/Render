CC = gcc
CFLAGS = -g
LDLIBS=-lglut -lGLEW -lGL -lm
all: main
clean:
	rm -f *.o main

main: shader_utilities.o model_loader.o jdmath.o
.PHONY: all clean
