num = 1 2 4 8 16 32 48 64 96
begin = 99900000
end = 100000000
dst = primes.txt
dst2 = primes_p.txt

all: prime run

report: test draw

test: prime 
	for n in $(num); do \
	    mpirun -np $$n ./prime $(begin) $(end) $(dst); \
	done
test_p: pthread
	     ./pthread 1 $(begin) $(end) $(dst2); 
	     ./pthread 2 $(begin) $(end) $(dst2); 
	     ./pthread 4 $(begin) $(end) $(dst2); 
	     ./pthread 8 $(begin) $(end) $(dst2); 
	     ./pthread 16 $(begin) $(end) $(dst2);
	     ./pthread 32 $(begin) $(end) $(dst2);
	     ./pthread 48 $(begin) $(end) $(dst2); 
	     ./pthread 64 $(begin) $(end) $(dst2); 
	     ./pthread 96 $(begin) $(end) $(dst2); 
	
draw: plot.p
	gnuplot plot.p

run: prime
	mpirun -np $(num) ./prime $(begin) $(end) primes.txt
prime: prime.c
	mpicc prime.c -o prime -lm -g 

report_pthread: run_pthread draw

pthread: prime_p.cpp
	g++ prime_p.cpp -o pthread -lpthread 

run_pthread: pthread
	for n in $(num); do \
	    ./pthread $$n $(begin) $(end); \
	done

	
clean:
	rm prime
	rm time.svg
	rm *.txt
	rm *.dat
	rm pthread*

