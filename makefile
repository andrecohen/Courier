CC=g++
CFLAGS=-c -Wall -I/opt/local/include/SDL2/
LDFLAGS=-framework GLUT -framework OpenGL -lsdl2 -L/opt/local/lib/ -lSDLmain -framework Cocoa
SOURCES=main.cpp game.cpp world.cpp target.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=courier

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@
