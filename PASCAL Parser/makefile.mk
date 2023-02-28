all: tester

tester: Tester.cpp Parser.cpp Scanner.cpp Node.cpp
	g++ Tester.cpp Parser.cpp Scanner.cpp Node.cpp -o tester

clean:
	rm -f tester
