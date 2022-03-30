CC = g++
CFLAGS = -Wall -Werror -pedantic --std=c++14
LIBS = -lsfml-graphics -lsfml-audio -lsfml-system -lsfml-window
DEPS = CircularBuffer.h StringSound.h

all: KSGuitarSim.o StringSound.o CircularBuffer.o KSGuitarSim

KSGuitarSim: KSGuitarSim.o StringSound.o CircularBuffer.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

lint: KSGuitarSim.cpp CircularBuffer.cpp CircularBuffer.h StringSound.cpp StringSound.h
	cpplint KSGuitarSim.cpp CircularBuffer.cpp CircularBuffer.h StringSound.cpp StringSound.h

clean:
	rm *.o KSGuitarSim
