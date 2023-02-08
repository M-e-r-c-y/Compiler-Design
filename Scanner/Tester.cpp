#include <iostream>
#include "Scanner.hpp"


using namespace std;



int main()
{
    string input;
    getline(cin,input);
    
    Scanner sc(input);
    TokenLabel token;
    while ((token = sc.nexttoken()) != EOF_T) {
        cout << token << endl;  
    }
    return 0;
}