num = 1 2 4 6 8 10 12 14 16
begin = 1
end = 100000000
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
	mpirun -np 4 ./prime $(begin) $(end) primes.txt
prime: prime.c
	mpicc prime.c -o prime -lm -g -fsanitize=address

report_pthread: run_pthread draw

pthread: prime_p.cpp
	g++ prime_p.cpp -o pthread -lpthread 

run_pthread: pthread
	for n in $(num); do \
	    ./pthread $$n $(begin) $(end); \
	done

	
clean:
	rm primes.txt
	rm time.dat
	rm prime
	rm time.svg
clean_pthread:
	rm pthread*

