CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = core.o allocations.o getFile.o useData.o
EXECUTABLE = key

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXECUTABLE)

core.o: core.c allocations.h getFile.h
	$(CC) $(CFLAGS) -c core.c -o core.o

allocations.o: allocations.c allocations.h
	$(CC) $(CFLAGS) -c allocations.c -o allocations.o

getFile.o: getFile.c getFile.h allocations.h
	$(CC) $(CFLAGS) -c getFile.c -o getFile.o
useData.o: useData.c useData.h allocations.h
	$(CC) $(CFLAGS) -c useData.c -o useData.o
clean:
	rm -f $(EXECUTABLE) $(OBJS)
