CFLAGS=-O3 -ffast-math -mavx2 -fopenmp
CC=CC
all: init.o io.o jacobi.o main.o main main_argv.o main_argv
init.o: init.cpp init.h
	${CC} ${CFLAGS} -c -o init.o init.cpp
io.o: io.cpp io.h
	${CC} ${CFLAGS} -c -o io.o io.cpp
jacobi.o: jacobi.cpp jacobi.h
	${CC} ${CFLAGS} -c -o jacobi.o jacobi.cpp
main.o: main.cpp jacobi.o io.o init.o
	${CC} ${CFLAGS} -c -o main.o main.cpp
main:
	${CC} ${CFLAGS} -o main main.o init.o io.o jacobi.o

main_argv.o: main_argv.cpp jacobi.o io.o init.o
	${CC} ${CFLAGS} -c -o main_argv.o main_argv.cpp
main_argv:
	${CC} ${CFLAGS} -o main_argv main_argv.o init.o io.o jacobi.o
clean:
	rm -f main main.o init.o io.o jacobi.o main_argv main_argv.o
