main: main.o	file.o	gauss_pivoting.o	horner.o	interpolation.o	trapezium_rule.o
	gcc main.o	file.o	gauss_pivoting.o	horner.o	interpolation.o	trapezium_rule.o	-lm -o exe
	rm *.o
main.o:	main.c
	gcc -c main.c
file.o:	file.h	file.c
	gcc	-c	file.c
gauss_pivoting.o:	gauss_pivoting.h	gauss_pivoting.c
	gcc -c gauss_pivoting.c
horner.o:	horner.h	horner.c
	gcc -c horner.c
interpolation.o:	interpolation.h	interpolation.c
	gcc -c interpolation.c
trapezium_rule.o:
	gcc -c trapezium_rule.c