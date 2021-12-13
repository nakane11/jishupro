#MAKEFILE

CC=gcc
RM=rm -f

CFLAGS=-Wall
LDFLAGS=-lglut -lGLU -lGL -lm

TARGET=main
OBJS=main.o draw_function.o cat_matrix.o tex.o action.o

sanitizer=-g -fsanitize=address

.c.o:
	${CC} ${sanitizer} -c ${CFLAGS} $<

TARGET: ${OBJS}
	${CC} ${sanitizer} -o ${TARGET} ${OBJS} ${LDFLAGS}

clean:
	${RM} ${TARGET} *.o *~

