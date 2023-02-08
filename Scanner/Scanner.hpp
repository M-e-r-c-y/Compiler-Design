
#ifndef scanner_hpp
#define scanner_hpp

#include <string>
#include <map>

enum TokenLabel {
  AND,
  ARRAY,
  ASM,
  BEGIN,
  BREAK,
  CASE,
  CONST,
  CONSTRUCTOR,
  CONTINUE,
  DESTRUCTOR,
  DIV,
  DO,
  DOWNTO,
  ELSE,
  END,
  FALSE,
  FILE_T,
  FOR,
  FUNCTION,
  GOTO,
  IF,
  IMPLEMENTATION,
  IN,
  INLINE,
  INTERFACE,
  LABEL,
  MOD,
  NIL,
  NOT,
  OBJECT,
  OF,
  ON,
  OPERATOR,
  OR,
  PACKED,
  PROCEDURE,
  PROGRAM,
  RECORD,
  REPEAT,
  SET,
  SHL,
  SHR,
  STRING,
  THEN,
  TO,
  TRUE,
  TYPE,
  UNIT,
  UNTIL,
  USES,
  VAR,
  WHILE,
  WITH,
  XOR,
  INTEGER,
  REAL,
  IDENTIFIER,
  PLUSOP,
  MINUSOP,
  MULTOP,
  DIVOP,
  ASSIGN,
  EQUAL,
  NE,
  LTEQ,
  GTEQ,
  LT,
  GT,
  PLUSEQUAL,
  MINUSEQUAL,
  MULTEQUAL,
  DIVEQUAL,
  CARAT,
  SEMICOLON,
  COMMA,
  LPAREN,
  RPAREN,
  LBRACKET,
  RBRACKET,
  LBRACE,
  RBRACE,
  LCOMMENT,
  RCOMMENT,
  EOF_T
};

class Scanner 
{

    private:

    std::map<std::string, TokenLabel> keywords;
    std::string input;
    int currentIndex;
    
    void skip_whitespace();

    public:
    
    Scanner();
    ~Scanner();
    
    Scanner(std::string input);
    
    TokenLabel nexttoken();

    
    
};

std::ostream& operator<<(std::ostream& os, const TokenLabel& label);

bool is_letter(char c);

bool is_digit(char c);

bool is_SpecialChar(char c);


#endif /* scanner_hpp */