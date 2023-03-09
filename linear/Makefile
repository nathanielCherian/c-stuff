linear: operations.o matrix.o vector.o
	gcc operations.o matrix.o vector.o -o linear -lm

operations.o: operations.c
	gcc operations.c -c -o operations.o

matrix.o: matrix.c
	gcc matrix.c -c -o matrix.o 

#vector.o: vector.c
#	gcc vector.c -c -o vector.o

clean:
	rm *.o linear
