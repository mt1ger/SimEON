CC=g++ 

EXEC=Simulator

SOURCES=Network.cpp\
		Dijkstra.cpp\
		RoutingTable.cpp\
		TrafficGenerator.cpp\
		Event.cpp\
		EventQueue.cpp\
		ResourceAssignment.cpp\
		RandomVariable.cpp\
		Topology.cpp


OBJS=$(SOURCES:.cpp=.o)
# INCLUDES=-I.
CLEANFILES=*.o


all: $(SOURCES) $(EXEC)
$(EXEC): $(OBJS) 
	$(CC) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $@

main.o: main.cpp
	$(CC) $(INCLUDES) $(CFLAGS) main.cpp $(WHICH)
.cpp.o: 
	$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm ${CLEANFILES}


# main.cpp TrafficGenerator.cpp Event.cpp EventQueue.cpp ResourceAssignment.cpp Network.cpp RoutingTable.cpp Topology.cpp Dijkstra.cpp RandomVariable.cpp -o test

