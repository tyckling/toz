SOURCES = main.c 

INCLUDE = -I/usr/include/SDL2 -I/usr/include/GL

LINK = -lSDL2 -lGL -lGLEW

NAME = toz

all : $(SOURCES)
	g++ $(SOURCES) $(INCLUDE) $(LINK) -o $(NAME)
