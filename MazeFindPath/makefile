maze:maze.o SeqStack.o
	gcc maze.o SeqStack.o -o maze
maze.o:maze.c
	gcc -c maze.c
SeqStack.o:SeqStack.c
	gcc -c SeqStack.c
clean:
	rm *.o