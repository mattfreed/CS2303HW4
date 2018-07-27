CFLAGS= -g -Wall

all: qSim

qSim: qSim.o Simulator.o Event.o Clock.o EventQueue.o TellerQueue.o
	g++ $(CFLAGS) qSim.o Simulator.o TellerQueue.o EventQueue.o Event.o Clock.o -o qSim

qSim.o: qSim.cpp
	g++ $(CFLAGS) -c qSim.cpp
	
Simulator.o: Simulator.cpp Simulator.h
	g++ $(CFLAGS) -c Simulator.cpp


Event.o: Event.cpp Event.h
	g++ $(CFLAGS) -c Event.cpp

Clock.o: Clock.cpp Clock.h
	g++ $(CFLAGS) -c Clock.cpp

EventQueue.o: EventQueue.cpp EventQueue.h
	g++ $(CFLAGS) -c EventQueue.cpp
	
TellerQueue.o: TellerQueue.cpp TellerQueue.h
	g++ $(CFLAGS) -c TellerQueue.cpp

clean:
	rm -f *.o qSim
	
docs:
	doxygen -g Doxyfile