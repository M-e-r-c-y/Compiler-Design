the project contains 3 needed files :
Scanner.hpp
Scanner.cpp
Tester.cpp	// contains the main method



************************* 1st method *************************************

To compile the program you can use the makefile file :
simply run 'make' from the command line in the directory 
where the makefile is located. 

When you run 'make', the test program reads input data from 'test-in.txt' file 
and writes output in 'test-out.txt' file.

To clean up the directory, run 'make clean'.

************************* 2nd method *************************************

An alternative method to compile the program is to type this command line :
g++ Tester.cpp Scanner.cpp -o tester

that will build an exe file : tester.exe

to run the exe file you can use this command line :

./tester

