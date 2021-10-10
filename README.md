# AEDS3

Algoritmos e Estruturas de Dados 3 - Trabalhos Práticos (UFMG)

## Quickstart

## Example

### Code

```c
// main.c
#include <stdio.h>

int main(void)
{
  printf("Hello World!\n");
}
```
### Makefile

```Makefile
C_OBJS = main.o
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic
LDFLAGS = -lm
EXEC = example

${EXEC}: ${C_OBJS}
	${CC} -o $@ ${C_OBJS} ${LDFLAGS}

main.o: main.c
	${CC} -c $? ${CFLAGS}

run:
	./${EXEC}

clean:
	rm -f *.o ${EXEC}
```

### Compile
```sh
$ make
```
### Run
```sh
$ make run
./example
Hello World!
```

## License

The contents of this repository are covered under the [MIT License](https://github.com/urbanogilson/AEDS3/blob/master/LICENSE.md).
