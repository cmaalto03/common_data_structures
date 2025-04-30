CC = gcc
CFLAGS = -Wall --std=c99
OBJECTS = main.o avl_tree.o  

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o main $(OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

avl_tree.o: avl_tree.c  
	$(CC) $(CFLAGS) -c avl_tree.c -o avl_tree.o

clean:
	rm -f main $(OBJECTS)
