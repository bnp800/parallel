


all: generate run

main: main.cpp
	mpic++ main.cpp ../test1/matrix.cpp -o main

run: main
	mpirun -np 4 ./main a.bin b.bin c.bin

generator: 
	g++ generateMatrix.cpp -o generator

generate: generator
	./generator a.bin b.bin d

clean:
	rm *.bin
	rm generator
	rm main
