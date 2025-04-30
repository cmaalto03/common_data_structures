CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o queue.o  

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

queue.o: queue.c  
	$(CC) $(CFLAGS) -c queue.c -o queue.o

clean:
	rm -f main $(OBJECTS)
