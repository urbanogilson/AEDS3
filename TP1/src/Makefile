all:	TP1

TP1:	main.o TP1.o
	gcc main.o TP1.o -o TP1

main.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pedantic -g main.c

TP1.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pedantic -g TP1.c

clean:
	rm -rf *o TP1
