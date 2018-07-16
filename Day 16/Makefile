all: solution execution solution2 execution2

execution: solution
	./solution < input.txt

solution:
	g++ solution.cpp -o solution -std=c++17 -O2

execution2: solution2
	valgrind --leak-check=full ./solution2

solution2:
	g++ solution2.cpp -o solution2 -std=c++17 -O2 -g

clean:
	rm solution solution2
