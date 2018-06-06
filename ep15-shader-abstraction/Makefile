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

default: debug

app: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(FRAMEWORKS) -o $@ $(OBJECTS)

# Define debug and -g enables debug symbols
debug: CFLAGS+=-DDEBUG -g
debug: app

release: app

.PHONY: clean
clean:
	rm -f *.o app

.PHONY: debugger
debugger: debug
	PATH=/usr/bin /usr/bin/lldb ./app

