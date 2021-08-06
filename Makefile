LD = g++
LFLAGS = -Wall

INCLUDES = main.cpp Date.cpp Estadual.cpp Nacional.cpp UserInterface.cpp

EXECUTABLE = covid

all:
	$(LD) $(LFLAGS) -g -o $(EXECUTABLE) $(INCLUDES)

clean:
	rm -rf *.o $(EXECUTABLE)
