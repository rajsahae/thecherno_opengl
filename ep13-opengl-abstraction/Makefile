CC=clang++
current_directory=$(shell pwd)

FRAMEWORKS=-framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo

CFLAGS=-std=c++11
CFLAGS+=-I$(current_directory)
CFLAGS+=-I$(current_directory)/../external

LDFLAGS=-L$(current_directory)/../lib
LDFLAGS+=-lglfw3
LDFLAGS+=-lGLEW

SOURCES=$(wildcard *.cpp)
OBJECTS=$(patsubst %.cpp, %.o, $(SOURCES))


%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

app: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(FRAMEWORKS) -o app $(OBJECTS)

all: app

.PHONY: clean
clean:
	rm -f *.o app
