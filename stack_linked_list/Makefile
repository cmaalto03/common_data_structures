CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o stack.o  

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c -o stack.o

clean:
	rm -f main $(OBJECTS)
