SOURCES = main.c

INCLUDE = -I/usr/include/SDL2

LINK = -lSDL2

NAME = toz

all : $(SOURCES)
	g++ $(SOURCES) $(INCLUDE) $(LINK) -o $(NAME)
