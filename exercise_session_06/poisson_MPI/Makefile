# this is just example Makefile, write your own or modify

CFLAGS=-O3 -ffast-math -mavx2
CC = CC

all: mpi_module.o init.o io.o jacobi.o main.o main 
init.o: init.cpp init.h
	${CC} ${CFLAGS} -c -o init.o init.cpp 
io.o: io.cpp io.h
	${CC} ${CFLAGS} -c -o io.o io.cpp
jacobi.o: jacobi.cpp jacobi.h
	${CC} ${CFLAGS} -c -o jacobi.o jacobi.cpp
mpi_module.o: mpi_module.cpp mpi_module.h
	${CC} ${CFLAGS} -c -o mpi_module.o mpi_module.cpp
main.o: main.cpp
	${CC} ${CFLAGS} -c -o main.o main.cpp 
main: mpi_module.o jacobi.o io.o init.o main.o
	${CC} -o main main.o init.o io.o jacobi.o mpi_module.o

clean: 
	rm -f main main.o init.o io.o jacobi.o mpi_module.o
