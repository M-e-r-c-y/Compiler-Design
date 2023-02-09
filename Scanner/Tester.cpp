#include <iostream>
#include <fstream>

#include "Scanner.hpp"


using namespace std;



int main()
{
    string input;
    Scanner sc;
    TokenLabel token;
    ifstream infile("test-in.txt");
    ofstream outfile("test-out.txt");
    if (infile.is_open())
    {
        while (getline(infile, input))
        {
            sc = Scanner(input);
            while ((token = sc.nexttoken()) != EOF_T) {
                outfile << token << endl;
            }
        }
        infile.close();
        outfile.close();
    }
    else
    {
        cout << "Unable to open input file" << endl;
    }

    return 0;
}
