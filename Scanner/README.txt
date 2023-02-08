the project contains 3 needed files :
Scanner.hpp
Scanner.cpp
Tester.cpp	// contains the main method



************************* 1st method *************************************

to compile the program you can use the makefile file :
simply run 'make' from the command line in the directory 
where the makefile is located. 
Then enter from the test input file called test-in.txt, containing at least 20 and no more than 50 
tokens, to see output produced by the program in response to the 
test input. 
To clean up the directory, run make clean.

************************* 2nd method *************************************

An alternative method to compile the program is to type this command line :
>g++ Tester.cpp Scanner.cpp -o tester

that will build an exe file : tester.exe

to run the exe file you can use this command line :

>tester
