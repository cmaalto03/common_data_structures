CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o priority_queue.o  

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

priority_queue.o: priority_queue.c  
	$(CC) $(CFLAGS) -c priority_queue.c -o priority_queue.o

clean:
	rm -f main $(OBJECTS)
