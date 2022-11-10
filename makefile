all: test

usecase: main.cpp
	g++ -std=c++11 main.cpp -o

test: test_graph.cpp
	g++ -std=c++11 test_graph.cpp -o test

clean:
	rm -rf *.o test