#include <iostream>
#include <fstream>

#include "Parser.hpp"


using namespace std;



int main()
{
    
    ifstream infile("test-in.txt");
    
    string input, file_contents;

    if (infile.is_open())
    {
        while (getline(infile, input)) {
            file_contents += input + "\n";
        }
        infile.close();
        
    } else {
        cout << "Unable to open input file" << endl;
    }
    
    Parser parser = Parser(file_contents);
    Node* root = parser.parseProgram(); 
    parser.outputTree(root);
    parser.outputTreeToFile(root, "test-out.txt");

    parser.outputSymbolTable();
    parser.outputSymbolTableToFile("test-out.txt");
    
    
    return 0;
}