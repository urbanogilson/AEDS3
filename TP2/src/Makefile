all:	TP2

TP2:	main.o TP2.o
	gcc main.o TP2.o -o TP2

main.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pedantic -g main.c

TP2.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pedantic -g TP2.c

clean:
	rm -rf *o TP2
