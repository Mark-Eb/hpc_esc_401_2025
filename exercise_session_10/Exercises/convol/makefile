all : main.o convol.o
	nvcc main.o convol.o

main.o : main.c
	cc -c main.c

convol.o : convol.cu
	nvcc -c convol.cu

.PHONY: clean
clean:
	rm -f a.out main.o convol.o
