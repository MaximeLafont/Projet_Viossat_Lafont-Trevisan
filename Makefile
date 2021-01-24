CC=g++
CCFLAGS= -Wall -Werror -std=c++11 -g 
LIBFLAGS= -I/usr/include/SDL2 -lSDL2_image -lSDL2_ttf -lSDL2
SRC= $(wildcard *.cc)
OBJ= $(SRC:.cc=.o)
EXEC= Apocalypse


all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(LIBFLAGS) $^ -o $@  

%.o: %.cc
	$(CC) $(CCFLAGS) -o $@ -c $<

.depend:
	g++ $(CCFLAGS) -MM $(SRC) > .depends
-include .depends

clean:
	rm -f $(OBJ) $(EXEC)


