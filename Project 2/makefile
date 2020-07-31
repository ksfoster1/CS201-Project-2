OBJS = BST.o trees.o node.o queue.o scanner.o
OPTS = -Wall -g -std=c99

trees : $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees -lm

trees.o : trees.c trees.h BST.h scanner.h
	gcc $(OPTS) -c trees.c

scanner.o : scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

node.o : node.c node.h BST.h
	gcc $(OPTS) -c node.c

BST.o : BST.c queue.h BST.h
	gcc $(OPTS) -c BST.c

queue.o : queue.c queue.h BST.h
	gcc $(OPTS) -c queue.c

test : trees
	trees -a test.txt commands.txt 
	trees -b test.txt commands.txt

clean :
	rm -f $(OBJS) trees