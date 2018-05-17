main: main.o	file.o	
	gcc main.o	file.o -lm	-o exe
	rm *.o
main.o:	main.c
	gcc -c main.c
file.o:	file.h	file.c
	gcc	-c	file.c
