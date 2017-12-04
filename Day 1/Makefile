all: solution execution solution2 execution2

execution: solution
	./solution < input.txt

solution:
	g++ solution.cpp -o solution -std=c++17 -O2

execution2: solution
	./solution2 < input.txt

solution2:
	g++ solution2.cpp -o solution2 -std=c++17 -O2

clean:
	rm solution solution2
