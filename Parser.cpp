#include <iostream>
#include <fstream>

#include "Parser.hpp"

using namespace std;

Parser::Parser() 
{
    this->program = "";
    this->sc = Scanner(this->program);
}

Parser::Parser(std::string program) 
{
    this->program = program;
    this->sc = Scanner(program);
}

Parser::~Parser() {
    
}

Node* Parser::parseProgram() {
    Node* rootNode = new Node(NodeType::PROGRAM);
    if (sc.nextToken() == PROGRAM) {
        
	if (sc.nextToken() == IDENTIFIER) {
	    rootNode->setName(sc.getCurrentWord());
	    if (sc.nextToken() == SEMICOLON) {	
	    	if (sc.nextToken() == BEGIN) {
		    Node* comNode = parseCompoundStatement();
        	    rootNode->adopt(comNode);    
	    	} else {
	    	    // syntax error
        	    std::cerr << "Expected BEGIN at the begin of program!\n";
        	    delete rootNode;
        	    return nullptr;
	    	}
	    } else {
	   	// syntax error
            	std::cerr << "Expected ; after the program IDENTIFIER!\n";
            	delete rootNode;
            	return nullptr;
	    }
	} else {
	    // syntax error
            std::cerr << "Expected IDENTIFIER after BEGIN of program!\n";
            delete rootNode;
            return nullptr;
	}
            
    } else {
        // syntax error
        std::cerr << "Expected PROGRAM at the begin of code!\n";
        delete rootNode;
        return nullptr;
    }
    rootNode->setIndent(0);
    return rootNode;
}

Node* Parser::parseStatement() {
    Node* stmtNode = nullptr;
    TokenLabel token = sc.afterNextToken();
    if (token == BEGIN) {
        sc.nextToken();
        stmtNode = parseCompoundStatement();
    } else if (token == REPEAT) {
        sc.nextToken();
        stmtNode = parseRepeatStatement();
    } else if (token == WHILE) {
        sc.nextToken();
        stmtNode = parseWhileStatement();
    } else if (token == FOR) {
        sc.nextToken();
        stmtNode = parseForStatement();
    } else if (token == IF) {
        sc.nextToken();
        stmtNode = parseIfStatement();
    } else {
        
        stmtNode = parseAssignmentStatement();
    }
    return stmtNode;
}

Node* Parser::parseAssignmentStatement() {
    Node* assignNode = new Node(NodeType::ASSIGN);
    Node* varNode = parseVariable();
    assignNode->setLine(sc.getCurrentLine());
    TokenLabel token = sc.nextToken();
    if (token == ASSIGN) {
        Node* exprNode = parseExpression();
        assignNode->adopt(varNode);
        assignNode->adopt(exprNode);
    } else {
        // syntax error
        std::cerr << "Expected := after variable in assignment statement\n";
        delete assignNode;
        return nullptr;
    }
    return assignNode;
}

Node* Parser::parseCompoundStatement() {
    Node* compNode = new Node(NodeType::COMPOUND);
    compNode->setLine(sc.getCurrentLine());
    TokenLabel token; 
    do {
        Node* stmtNode = parseStatement();
        compNode->adopt(stmtNode);
        token = sc.nextToken();
    } while (token == SEMICOLON);
        
    if (token != END) {
        // syntax error
        std::cerr << "Expected end after compound statement\n";
        delete compNode;
        return nullptr;
    }
    return compNode;
}

Node* Parser::parseRepeatStatement() {
    Node* repeatNode = new Node(NodeType::LOOP);
    repeatNode->setLine(sc.getCurrentLine());
    TokenLabel token = sc.nextToken();
    do {
        Node* stmtNode = parseStatement();
        repeatNode->adopt(stmtNode);
        token = sc.nextToken();
    } while (token == SEMICOLON);
    
    if (sc.nextToken() == UNTIL) {
        Node* exprNode = parseExpression();
        repeatNode->adopt(exprNode);
    } else {
        // syntax error
        std::cerr << "Expected until after repeat statement\n";
        delete repeatNode;
        return nullptr;
    }
    return repeatNode;
}

Node* Parser::parseWhileStatement() {
    Node* whileNode = new Node(NodeType::LOOP);
    whileNode->setLine(sc.getCurrentLine());
    Node* exprNode = parseExpression();
    whileNode->adopt(exprNode);
    if (sc.nextToken() == DO) {
        Node* stmtNode = parseStatement();
        whileNode->adopt(stmtNode);
    } else {
        // syntax error
        std::cerr << "Expected do after while statement\n";
        delete whileNode;
        return nullptr;
    }
    return whileNode;
}

// for
Node* Parser::parseForStatement() {
    Node* forNode = new Node(NodeType::LOOP);
    forNode->setLine(sc.getCurrentLine()); 
    Node* assignNode = parseAssignmentStatement();
    TokenLabel token = sc.nextToken();
    if (token == TO || token == DOWNTO) {
        Node* exprNode = parseExpression();
        if (sc.nextToken() == DO) {
            Node* stmtNode = parseStatement();
            forNode->adopt(assignNode);
            forNode->adopt(exprNode);
            forNode->adopt(stmtNode);
        } else {
            // syntax error
            std::cerr << "Expected to after for statement\n";
            delete forNode;
            return nullptr;
        }
    } else {
        // syntax error
        std::cerr << "Expected do after for statement\n";
        delete forNode;
        return nullptr;
    }
    return forNode;
}

// if
Node* Parser::parseIfStatement() {
    Node* ifNode = new Node(NodeType::TEST);
    ifNode->setLine(sc.getCurrentLine()); 
    Node* exprNode = parseExpression();
    if (sc.nextToken() == THEN) {
        Node* trueStmtNode = parseStatement();
        ifNode->adopt(exprNode);
        ifNode->adopt(trueStmtNode);
        if (sc.afterNextToken() == ELSE) {
            sc.nextToken();
            Node* falseStmtNode = parseStatement();
            ifNode->adopt(falseStmtNode);
        }
    } else {
        // syntax error
        std::cerr << "Expected then after if statement\n";
        delete ifNode;
        return nullptr;
    }
    return ifNode;
}

Node* Parser::parseVariable() {
    Node* varNode = new Node(NodeType::VARIABLE);
    sc.nextToken();
    varNode->setName(sc.getCurrentWord());
    if (!existSymbol(varNode->getName())) {
     	symbolTable.insert(pair<std::string, std::string>(varNode->getName(), "INTEGER"));
    }
    return varNode;
}

// write
Node* Parser::parseWriteStatement() {
    Node* writeNode = new Node(NodeType::WRITE);
    writeNode->setLine(sc.getCurrentLine()); 
    if (sc.nextToken() == LPAREN) {
        Node* exprNode = parseExpression();
        writeNode->adopt(exprNode);
        while (sc.afterNextToken() == COMMA) {
            sc.nextToken();
            Node* exprNode = parseExpression();
            writeNode->adopt(exprNode);
        }
        if (sc.nextToken() == RPAREN) {
            // success
            writeNode->setLine(sc.getCurrentLine());
            return writeNode;
        } else {
            // syntax error
            std::cerr << "Expected ) after write statement\n";
            delete writeNode;
            return nullptr;
        }
    } else {
        // syntax error
        std::cerr << "Expected ( after write statement\n";
        delete writeNode;
        return nullptr;
    }
    
}

Node* Parser::parseExpression() {
    Node* exprNode = nullptr;
    Node* leftNode = parseSimpleExpression();
    TokenLabel token = sc.afterNextToken();
    Node* rightNode = nullptr;
    switch (token) {
        case LT : { 
            sc.nextToken();
            exprNode = new Node(NodeType::LT);
            rightNode = parseSimpleExpression();
            break;
        }
        case LTEQ : {
            sc.nextToken();
            exprNode = new Node(NodeType::LTEQ);
            rightNode = parseSimpleExpression();
            break;
        }
        case EQUAL : {
            sc.nextToken();
            exprNode = new Node(NodeType::EQ);
            rightNode = parseSimpleExpression();
            break;
        }
        case GTEQ : {
            sc.nextToken();
            exprNode = new Node(NodeType::GTEQ);
            rightNode = parseSimpleExpression();
            break;
        }
        case GT : {
            sc.nextToken();
            exprNode = new Node(NodeType::GT);
            rightNode = parseSimpleExpression();
            break;
        }
        case NE : {
            sc.nextToken();
            exprNode = new Node(NodeType::NE);
            rightNode = parseSimpleExpression();
            break;
        }         
    }
    
    
    if (rightNode != nullptr) {
   	exprNode->adopt(leftNode);
	exprNode->adopt(rightNode);
        return exprNode;
    }
    return leftNode;
}

Node* Parser::parseSimpleExpression() {
    Node* simpleExprNode = nullptr;
    Node* signNode = nullptr;
    TokenLabel token = sc.afterNextToken();
    if (token == PLUSOP) {
        sc.nextToken();
        signNode = new Node(NodeType::ADD);
    } else if (token == MINUSOP) {
        sc.nextToken();
        signNode = new Node(NodeType::SUBTRACT);
    } 
    Node* term1 = parseTerm();
    if (signNode != nullptr)
	signNode->adopt(term1);
    token = sc.afterNextToken();
    
    while (token == PLUSOP || token == MINUSOP || token == OR) {
        Node* opNode = nullptr;
        switch (token) {
            case PLUSOP : 
                sc.nextToken();
                opNode = new Node(NodeType::ADD);
                break;
            case MINUSOP : 
                sc.nextToken();
                opNode = new Node(NodeType::SUBTRACT);
                break;
            case OR : 
                sc.nextToken();
                opNode = new Node(NodeType::OR);
                break;
        }
        if (simpleExprNode != nullptr) {
            Node* term2 = parseTerm();
            simpleExprNode->adopt(opNode);
	    simpleExprNode->adopt(term2);
 	    token = sc.afterNextToken();
        } else {
            simpleExprNode = new Node(opNode->getType());
 	    Node* term2 = parseTerm();
            simpleExprNode->adopt(term1);
	    simpleExprNode->adopt(term2);
 	    token = sc.afterNextToken();
        }
    }
    if (simpleExprNode == nullptr) 
        return term1;
    return simpleExprNode;
}

// parseTerm()
Node* Parser::parseTerm() {
    Node* termNode = nullptr;
    Node* factorNode1 = parseFactor();
    TokenLabel token = sc.afterNextToken();
    while (token == MULTOP || token == DIVOP || token == DIV
        || token == MOD || token == AND) {
        Node* opNode = nullptr;
        switch (token) {
            case MULTOP : 
                sc.nextToken();
                opNode = new Node(NodeType::MULTIPLY);
                break;
            case DIVOP : 
                sc.nextToken();
                opNode = new Node(NodeType::DIVIDE);
                break;
            case DIV : 
                sc.nextToken();
                opNode = new Node(NodeType::DIV);
                break;
            case MOD : 
                sc.nextToken();
                opNode = new Node(NodeType::MOD);
                break;
            case AND : 
                sc.nextToken();
                opNode = new Node(NodeType::AND);
                break;
        }
        
        if (termNode != nullptr) {
            Node* factorNode2 = parseFactor();
            termNode->adopt(opNode);
            termNode->adopt(factorNode2);
            token = sc.afterNextToken();
        } else {
	    Node* factorNode2 = parseFactor();
            termNode = new Node(opNode->getType());
            termNode->adopt(factorNode1);
 	    termNode->adopt(factorNode2); 
            token = sc.afterNextToken();
	}  
    }
    if (termNode == nullptr) 
	return factorNode1; 

    return termNode;
}

// parseFactor()
Node* Parser::parseFactor() {
    TokenLabel token = sc.afterNextToken();
    if (token == LPAREN ) {
        sc.nextToken();
        Node* exprNode = parseExpression();
        if (sc.nextToken() == RPAREN) {
            return exprNode;
        } else {
            // syntax error
            std::cerr << "Expected ) after expression\n";
            delete exprNode;
            return nullptr;
        }
    } else if (token == NOT) {
        Node* notNode = new Node(NodeType::NOT);
        sc.nextToken();
        Node* factNode = parseFactor();
        notNode->adopt(factNode);
        return notNode;
    } else if (token == STRING) {
        sc.nextToken();
        Node* strNode = parseStringConstant();
        return strNode;
    } else if (token == INTEGER) {
        sc.nextToken();
        Node* intNode = parseIntegerConstant();
        return intNode;
    } else if (token == REAL) {
        sc.nextToken();
        Node* realNode = parseRealConstant();
        return realNode;
    } else if (token == IDENTIFIER) {
        Node* varNode = parseVariable();
        return varNode;
    } else { 
        // syntax error
        std::cerr << "Expected ( , NOT, string, number or variable\n";
        return nullptr;
    } 
}

Node* Parser::parseIntegerConstant() {
            
    Node* intNode = new Node(NodeType::INTEGER_CONSTANT);
    intNode->setValue(sc.getCurrentWord());
    return intNode;
}

Node* Parser::parseRealConstant() {
    Node* realNode = new Node(NodeType::REAL_CONSTANT);
    realNode->setValue(sc.getCurrentWord());
    return realNode;
}

Node* Parser::parseStringConstant() {
    Node* strNode = new Node(NodeType::STRING_CONSTANT);
    strNode->setValue(sc.getCurrentWord());
    return strNode;
}

bool Parser::existSymbol(std::string symb) {
    for (auto it = symbolTable.begin(); it != symbolTable.end(); ++it) {
        auto const& key = it->first;
        if (key == symb) {
            return true;
        }
    }
    return false;
}

void Parser::outputTree(Node* node) {

    cout << "Parse Tree in XML format : " << endl ;
 
    cout << node->toString() << endl;
}

void Parser::outputTreeToFile(Node* node, std::string fileName) {

    ofstream outfile(fileName);

    if (outfile.is_open()) {
	outfile << "Parse Tree in XML format : " << endl ;
    	outfile << node->toString() << endl;
    	outfile.close();
    } else {
        cerr << "Error: Could not create file." << endl;
    }
}

void Parser::outputSymbolTable() {
     
    cout << "Symbols in the Table-Symbol : " << endl ;
 
    for (auto const& entry : symbolTable) {
        cout << "name: " << entry.first << " type: " << entry.second << endl;
    }
}

void Parser::outputSymbolTableToFile(std::string fileName) {

    ifstream infile(fileName);
    if (infile.good()) {

        infile.close(); 
        ofstream outfile(fileName, ios::app);
	if (outfile.is_open()) {
    	    for (auto const& entry : symbolTable) {
 		outfile << "Symbols in the Table-Symbol : " << endl ;
        	outfile << "name: " << entry.first << " type: " << entry.second << endl;
    	    }
            outfile.close();
	} else {
	    std::cerr << "Error: Could not open file for append." << endl;
	    return;
	}

    } else {

	infile.close(); 
        ofstream outfile(fileName); 
        
        if (outfile.is_open()) {
	    for (auto const& entry : symbolTable) {
		outfile << "Symbols in the Table-Symbol : " << endl ;
        	outfile << "name: " << entry.first << " type: " << entry.second << endl;
    	    }
	    outfile.close();
	} else {
            cerr << "Error: Could not create file." << endl;
            return;
        }
    }
}
