C_OBJS = main.o TP0.o
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
LDFLAGS = -lm
EXEC = TP0

${EXEC}: ${C_OBJS}
	${CC} -o $@ ${C_OBJS} ${LDFLAGS}

main.o: main.c
	${CC} -c $? ${CFLAGS}

TP0.o: TP0.c
	${CC} -c $? ${CFLAGS}

run:
	./${EXEC}

clean:
	rm -f *.o ${EXEC}
