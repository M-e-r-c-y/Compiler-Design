#include "Node.h"
#include <iostream>

Node::Node() {
    this->level = 0; 
    this->line = 0; 
    this->indent = 0; 
}

Node::Node(NodeType type) {
    this->type = type;
    this->line = 0; 
    this->indent = 0; 
    this->level = 0;
    if (type == NodeType::NOT) 
   	this->level = 1;
    else if (type == NodeType::MULTIPLY || type == NodeType::DIVIDE || 
	type == NodeType::DIV || type == NodeType::MOD || 
	type == NodeType::AND) 
	this->level = 2;
    else if (type == NodeType::ADD || type == NodeType::SUBTRACT || 
	type == NodeType::OR) 
	this->level = 3; 
    else if (type == NodeType::LT || type == NodeType::GT || 
	type == NodeType::EQ || type == NodeType::NE || 
	type == NodeType::LTEQ || type == NodeType::GTEQ) 
	this->level = 4;
}

Node::~Node() {
    for (auto child : children) {
        delete child;
    }
}

void Node::adopt(Node* otherNode) {
    if (otherNode == nullptr) {
        return;
    }
    this->children.push_back(otherNode);
    
}

NodeType Node::getType() const {
    return type;
}

std::string Node::toString() const {
    std::string result = std::string(this->indent, '\t') + "<" + typeToString(this->type);
    if (this->type == NodeType::VARIABLE) {
        result += " id=\"" + this->name + "\"" 
	+ " level=\"" + std::to_string(this->level) + "\" />\n";
    } else if (this->type == NodeType::INTEGER_CONSTANT ||
        this->type == NodeType::REAL_CONSTANT ||
        this->type == NodeType::STRING_CONSTANT) {
        result += " value=\"" + this->value + "\" />\n";
    } else if (this->type == NodeType::COMPOUND ||
        this->type == NodeType::ASSIGN ||
        this->type == NodeType::LOOP ||
        this->type == NodeType::TEST ||
        this->type == NodeType::WRITE) {
        result += " line=\"" + std::to_string(this->line) + "\">\n"; 
        for (auto child : this->children) {
            result += child->toString();
        }
  	result += std::string(this->indent, '\t') + "</" + typeToString(this->type) + ">\n" ;
    } else if (this->type == NodeType::PROGRAM) {
	result += " id=\"" + this->name + "\">\n"; 
        for (auto child : this->children) {
            result += child->toString();
        }
  	result += std::string(this->indent, '\t') + "</" + typeToString(this->type) + ">\n" ;
    } else if (this->level > 0) {
    	result += " level=\"" + std::to_string(this->level) + "\" />\n"; 
        for (auto child : this->children) {
            result += child->toString();
        }
  	result += std::string(this->indent, '\t') + "</" + typeToString(this->type) + ">\n" ;
    } else {
    	result += ">\n"; 
        for (auto child : this->children) {
            result += child->toString();
        }
  	result += std::string(this->indent, '\t') + "</" + typeToString(this->type) + ">\n" ;
    }
    
    return result;
}

std::string Node::typeToString(NodeType type) const{
    switch (type) {
        case NodeType::PROGRAM:
            return "PROGRAM";
        case NodeType::COMPOUND:
            return "COMPOUND";
        case NodeType::ASSIGN:
            return "ASSIGN";
        case NodeType::LOOP:
            return "LOOP";
        case NodeType::TEST:
            return "TEST";
        case NodeType::WRITE:
            return "WRITE";
        case NodeType::WRITELN:
            return "WRITELN";
        case NodeType::ADD:
            return "ADD";
        case NodeType::SUBTRACT:
            return "SUBTRACT";
        case NodeType::MULTIPLY:
            return "MULTIPLY";
        case NodeType::DIVIDE:
            return "DIVIDE";
        case NodeType::EQ:
            return "EQ";
        case NodeType::LT:
            return "LT";
        case NodeType::VARIABLE:
            return "VARIABLE";
        case NodeType::INTEGER_CONSTANT:
            return "INTEGER_CONSTANT";
        case NodeType::REAL_CONSTANT:
            return "REAL_CONSTANT";
        case NodeType::STRING_CONSTANT:
            return "STRING_CONSTANT";
        case NodeType::OR:
            return "OR";
        case NodeType::DIV:
            return "DIV";
        case NodeType::MOD:
            return "MOD";
        case NodeType::AND:
            return "AND";
        case NodeType::GT:
            return "GT";
        case NodeType::NE:
            return "NE";
        case NodeType::LTEQ:
            return "LTEQ";
        case NodeType::GTEQ:
            return "GTEQ";
        case NodeType::NOT:
            return "NOT";
        default:
            return "UNKNOWN";
    }
}

void Node::setName(std::string name) {
    this->name = name;
}

void Node::setValue(std::string value) {
    this->value = value;
}

void Node::setLevel(int level) {

    this->level = level;
    
}

void Node::setLine(int line) {
    this->line = line;
}

void Node::setIndent(int indent) {
    this->indent = indent;
    for (auto child : this->children) {
        child->setIndent(indent+1);
    }
}

std::string Node::getName() {
    return name;
}

std::string Node::getValue() {
    return value;
}

int Node::getLevel() {
    return level;
}

int Node::getIndent() {
    return indent;
}

std::vector<Node*> Node::getChildren() const {
    return children;
}

