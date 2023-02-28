#include "Scanner.hpp"
#include <iostream>

std::map<TokenLabel, std::string> labelToString = {
  {AND, "AND"}, {ARRAY, "ARRAY"}, {ASM, "ASM"}, {BEGIN, "BEGIN"},
  {BREAK, "BREAK"}, {CASE, "CASE"}, {CONST, "CONST"},
  {CONSTRUCTOR, "CONSTRUCTOR"}, {CONTINUE, "CONTINUE"},
  {DESTRUCTOR, "DESTRUCTOR"}, {DIV, "DIV"}, {DO, "DO"}, {DOWNTO, "DOWNTO"},
  {ELSE, "ELSE"}, {END, "END"}, {FALSE, "FALSE"}, {FILE_T, "FILE"},
  {FOR, "FOR"}, {FUNCTION, "FUNCTION"}, {GOTO, "GOTO"}, {IF, "IF"},
  {IMPLEMENTATION, "IMPLEMENTATION"}, {IN, "IN"}, {INLINE, "INLINE"},
  {INTERFACE, "INTERFACE"}, {LABEL, "LABEL"}, {MOD, "MOD"}, {NIL, "NIL"},
  {NOT, "NOT"}, {OBJECT, "OBJECT"}, {OF, "OF"}, {ON, "ON"},
  {OPERATOR, "OPERATOR"}, {OR, "OR"}, {PACKED, "PACKED"},
  {PROCEDURE, "PROCEDURE"}, {PROGRAM, "PROGRAM"}, {RECORD, "RECORD"},
  {REPEAT, "REPEAT"}, {SET, "SET"}, {SHL, "SHL"}, {SHR, "SHR"},
  {STRING, "STRING"}, {THEN, "THEN"}, {TO, "TO"}, {TRUE, "TRUE"},
  {TYPE, "TYPE"}, {UNIT, "UNIT"}, {UNTIL, "UNTIL"}, {USES, "USES"},
  {VAR, "VAR"}, {WHILE, "WHILE"}, {WITH, "WITH"}, {XOR, "XOR"},
  {INTEGER, "INTEGER"}, {REAL,"REAL"}, {IDENTIFIER,"IDENTIFIER"}, 
  {PLUSOP,"PLUSOP"}, {MINUSOP,"MINUSOP"}, {MULTOP,"MULTOP"}, {DIVOP,"DIVOP"},
  {ASSIGN,"ASSIGN"}, {EQUAL,"EQUAL"}, {NE,"NE"}, {LTEQ,"LTEQ"}, {GTEQ,"GTEQ"},
  {LT,"LT"}, {GT,"GT"}, {PLUSEQUAL,"PLUSEQUAL"}, {MINUSEQUAL,"MINUSEQUAL"},
  {MULTEQUAL,"MULTEQUAL"}, {DIVEQUAL,"DIVEQUAL"}, {CARAT,"CARAT"}, 
  {SEMICOLON,"SEMICOLON"}, {COMMA,"COMMA"}, {LPAREN,"LPAREN"}, {RPAREN,"RPAREN"}, 
  {LBRACKET,"LBRACKET"}, {RBRACKET,"RBRACKET"}, {LBRACE,"LBRACE"}, {RBRACE,"RBRACE"}, 
  {LCOMMENT,"LCOMMENT"}, {RCOMMENT,"RCOMMENT"}, {WRITE, "WRITE"} 
};

//default Constructor
Scanner::Scanner() 
{
    this->currentIndex=0;
    this->input="";
    this->keywords = {};
    this->currentLine = 1;
}
    
//Parameterized Constructor
Scanner::Scanner(std::string input)
{
    this->currentIndex=0;
    this->input=input;
    this->currentLine = 1;
    keywords = {
        {"and", AND},                 
        {"array", ARRAY},           
        {"asm", ASM},       
        {"begin", BEGIN},
        {"break", BREAK},             
        {"case", CASE},             
        {"const", CONST},   
        {"constructor", CONSTRUCTOR},
        {"continue", CONTINUE},       
        {"destructor", DESTRUCTOR}, 
        {"div", DIV},       
        {"do", DO},
        {"downto", DOWNTO},           
        {"else", ELSE},             
        {"end", END},       
        {"false", FALSE},
        {"file", FILE_T},               
        {"for", FOR},
        {"function", FUNCTION},
        {"goto", GOTO},
        {"if", IF},
        {"implementation", IMPLEMENTATION},
        {"in", IN},
        {"inline", INLINE},
        {"interface", INTERFACE},
        {"label", LABEL},
        {"mod", MOD},
        {"nil", NIL},
        {"not", NOT}, 
        {"object", OBJECT}, 
        {"of", OF}, 
        {"on", ON},
        {"operator", OPERATOR}, 
        {"or", OR}, 
        {"packed", PACKED},
        {"procedure", PROCEDURE}, 
        {"program", PROGRAM}, 
        {"record", RECORD},
        {"repeat", REPEAT}, 
        {"set", SET}, 
        {"shl", SHL}, 
        {"shr", SHR},
        {"string", STRING}, 
        {"then", THEN}, 
        {"to", TO}, 
        {"true", TRUE},
        {"type", TYPE}, 
        {"unit", UNIT}, 
        {"until", UNTIL}, 
        {"uses", USES},
        {"var", VAR}, 
        {"while", WHILE}, 
        {"with", WITH}, 
        {"xor", XOR},
        {"(integer)", INTEGER},
        {"(real number)", REAL},
        {"(identifier)", IDENTIFIER},
        {"+", PLUSOP},
        {"-", MINUSOP},
        {"*", MULTOP},
        {"/", DIVOP},
        {":=", ASSIGN},
        {"=", EQUAL},
        {"<>", NE},
        {"<=", LTEQ},
        {">=", GTEQ},
        {"<", LT},
        {">", GT},
        {"+=", PLUSEQUAL},
        {"-=", MINUSEQUAL},
        {"*=", MULTEQUAL},
        {"/=", DIVEQUAL},
        {"^", CARAT},
        {";", SEMICOLON},
        {",", COMMA},
        {"(", LPAREN},
        {")", RPAREN},
        {"[", LBRACKET},
        {"]", RBRACKET},
        {"{", LBRACE},
        {"}", RBRACE},
        {"(*", LCOMMENT},
        {"*)", RCOMMENT},
        {"write", WRITE}
    };
}

//Destructor
Scanner::~Scanner() 
{
}
    
TokenLabel Scanner::nextToken() 
{
    while (true) {
        currentWord.clear();
        skip_whitespace();
        if (currentIndex >= input.length()) {
            return EOF_T;
        }
        char c = input[currentIndex];
        if (is_letter(c)) {
            while (currentIndex < input.length() && (is_letter(input[currentIndex]) || is_digit(input[currentIndex]))) {
                currentWord += (char)tolower(input[currentIndex]);
                currentIndex++;
            } 
        } else if (is_SpecialChar(c)){
            currentWord += input[currentIndex];
            currentIndex++;
            if (currentIndex < input.length()) {
                if (is_SpecialChar(input[currentIndex])) {
                    currentWord += input[currentIndex];
                    currentIndex++;
                }
            } 
        } else if (is_digit(c)) {
            while (currentIndex < input.length() && (is_digit(input[currentIndex]))) {
                currentWord += input[currentIndex];
                currentIndex++;
            }
            if (currentIndex < input.length()) {
                if (input[currentIndex] == '.') {
                    currentWord += input[currentIndex];
                    currentIndex++;
                    while (currentIndex < input.length() && (is_digit(input[currentIndex]))) {
                        currentWord += input[currentIndex];
                        currentIndex++;
                    }
                    return REAL;
                }
            }
            return INTEGER; 
        }
        auto it = keywords.find(currentWord);
        if (it != keywords.end()) {
            return it->second;
        } 
        else {
            return IDENTIFIER; 
        }
    }
}

TokenLabel Scanner::afterNextToken() 
{
    int index = currentIndex;
    int line_ = currentLine;
    TokenLabel tmpToken = nextToken();
    currentIndex = index;
    currentLine = line_;
    return tmpToken;
}

std::string Scanner::getCurrentWord() {
    return currentWord;
}
    
std::ostream& operator<<(std::ostream& os, const TokenLabel& label) {
    os << labelToString[label];
    return os;
}

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

bool is_SpecialChar(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == ':' || c == '=' || c == '<'
            || c == '>' || c == '^' || c == ';' || c == ',' || c == '(' || c == ')' 
            || c == '[' || c == ']' || c == '{' || c == '}');
}

void Scanner::skip_whitespace() {
    while (currentIndex < input.length() && (input[currentIndex] == ' ' || input[currentIndex] == '\t' || input[currentIndex] == '\n')) {
        if (input[currentIndex] == '\n')
	    this->currentLine++;
	currentIndex++;
    }
}

int Scanner::getCurrentLine() {
    return currentLine;
}