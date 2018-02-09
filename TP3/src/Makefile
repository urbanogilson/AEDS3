all:	TP3

TP3:	main.o TP3.o
	gcc main.o TP3.o -pthread -o TP3

main.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pthread -pedantic -g main.c

TP3.o:
	gcc -c -Wall -Wextra -Werror -std=c99 -pthread -pedantic -g TP3.c

clean:
	rm -rf *o TP3
