the project contains 7 needed files :
Scanner.hpp
Scanner.cpp
Node.h
Node.cpp
Parser.hpp
Parser.cpp
Tester.cpp	// contains the main method



************************* 1st method *************************************

to compile the program you can use the makefile file :
simply run 'make' from the command line in the directory 
where the makefile is located. 
To clean up the directory, run make clean.

************************* 2nd method *************************************

An alternative method to compile the program is to type this command line :
>g++ Tester.cpp Parser.cpp Scanner.cpp Node.cpp -o tester

that will build an exe file : tester.exe

to run the exe file you can use this command line :

>tester

if you want to redirect the output to a text file use > like this :

>tester > test-out.txt