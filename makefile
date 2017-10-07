CC = gpp 
# CFLAGS = -c -g -Wall 
# LDFLAGS = 
EXEC = test

SOURCES = Network.cpp \
		  Dijkstra.cpp \
		  RoutingTable.cpp \

OBJS = $(SOURCES:.cpp=.o)
# INCLUDES = -I.
CLEANFILES = *.o 

all: $(SOURCES) $(EXEC)
$(EXEC): $(OBJS) 
	# $(CC) $(INCLUDES) $(LDFLAGS) $(OBJS) -o $@
	$(CC) $(OBJS) -o $@

main.o: main.cpp
	# $(CC) $(INCLUDES) $(CFLAGS) main.cpp $(WHICH)
	$(CC) main.cpp $(WHICH)
.cpp.o: 
	# $(CC) $(INCLUDES) $(CFLAGS) $< -o $@
	$(CC) $< -o $@

.PHONY: clean
clean:
	rm ${CLEANFILES}

