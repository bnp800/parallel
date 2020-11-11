num = 1 2 4 8 16
begin = 1
end = 100000
dst = primes.txt
all: prime run

report: test draw

test: prime 
	for n in $(num); do \
	    mpirun -np $$n ./prime $(begin) $(end) $(dst); \
	done

draw: plot.p
	gnuplot plot.p

run: prime
	mpirun -np 16 ./prime 1 100000 primes.txt
prime: prime.c
	mpicc prime.c -o prime -lm
clean:
	rm primes.txt
	rm time.dat
	rm prime
	rm time.svg

