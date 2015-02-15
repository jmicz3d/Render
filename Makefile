CC = gcc
CFLAGS = -g
LDLIBS=-lglut -lGLEW -lGL -lm
all: main
clean:
	rm -f *.o main

main: shader_utilities.o
.PHONY: all clean