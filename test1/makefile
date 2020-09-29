type = d
mode = 0
test: generateMatrix main
	./generateMatrix a.txt b.txt $(type)
	./main a.txt b.txt c.txt $(mode)

generateMatrix: generateMatrix.cpp
	g++ generateMatrix.cpp -o generateMatrix

main: matrix.cpp 
	g++ matrix.cpp -o main

clean:
	rm generateMatrix
	rm main
