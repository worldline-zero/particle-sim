CC = gcc

CFLAGS = -Wall -Wimplicit-fallthrough -g -msse

SRC = ./src/* ./lib/src/gl.c

OBJNAME = particle-sim

LDFLAGS = -lglfw -lGL -ldl

INCFLAGS = -I ./lib/include/glad/

build:
	$(CC) $(INCFLAGS) $(CFLAGS) $(SRC) $(LDFLAGS) -o $(OBJNAME)
