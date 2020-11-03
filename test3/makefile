all: prime run


run: prime
	mpirun -np 4 ./prime 1 10000 primes.txt
prime: prime.c
	mpicc prime.c -o prime -lm
clean:
	rm primes.txt
	rm time.dat
	rm prime

