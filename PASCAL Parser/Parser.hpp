
#ifndef parser_hpp
#define parser_hpp

#include <string>
#include <vector>

#include "Scanner.hpp"
#include "Node.h"

class Parser 
{

    private:

    std::map<std::string, std::string> symbolTable;
    Scanner sc;
    std::string program;
    
    Node* parseStatement();
    Node* parseAssignmentStatement();
    Node* parseCompoundStatement();
    Node* parseRepeatStatement();
    Node* parseWhileStatement();
    Node* parseForStatement();
    Node* parseIfStatement();
    Node* parseWriteStatement();
    Node* parseExpression();
    Node* parseSimpleExpression();
    Node* parseTerm();
    Node* parseFactor();
    Node* parseVariable();
    Node* parseIntegerConstant();
    Node* parseRealConstant();
    Node* parseStringConstant();

    bool existSymbol(std::string symb);
    
    public:
    
    Parser();
    ~Parser();
    
    Parser(std::string program);
    
    Node* parseProgram();
    void outputTree(Node* node);
    void outputTreeToFile(Node* node, std::string fileName);
    void outputSymbolTable();
    void outputSymbolTableToFile(std::string fileName);
    
};

#endif
