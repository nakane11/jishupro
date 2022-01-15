#MAKEFILE

CC=gcc
RM=rm -f

CFLAGS=-Wall
LDFLAGS=-lglut -lGLU -lGL -lm

TARGET=main
OBJS=main.o draw_function.o tex.o matrix_function.o action.o line.o ball.o

sanitizer=-g -fsanitize=address

.c.o:
	${CC} ${sanitizer} -c ${CFLAGS} $<

TARGET: ${OBJS}
	${CC} ${sanitizer} -o ${TARGET} ${OBJS} ${LDFLAGS}

clean:
	${RM} ${TARGET} *.o *~

main.o: main.c draw_function.h tex.h matrix_function.h action.h line.h ball.h
draw_function.o: draw_function.c tex.h matrix_function.h draw_function.h line.h
tex.o: tex.c
matrix_function.o: matrix_function.c tex.h matrix_function.h action.h
action.o: action.c tex.h matrix_function.h action.h
line.o: line.c line.h
ball.o: ball.c ball.h

