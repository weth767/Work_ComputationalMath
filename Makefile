main: main.o	file.o	gauss_pivoting.o
	gcc main.o	file.o	gauss_pivoting.o -lm -o exe
	rm *.o
main.o:	main.c
	gcc -c main.c
file.o:	file.h	file.c
	gcc	-c	file.c
gauss_pivoting.o:	gauss_pivoting.h	gauss_pivoting.c
	gcc -c gauss_pivoting.c
