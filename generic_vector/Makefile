CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o generic_vector.o  

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

generic_vector.o: generic_vector.c  
	$(CC) $(CFLAGS) -c generic_vector.c -o generic_vector.o

clean:
	rm -f main $(OBJECTS)
