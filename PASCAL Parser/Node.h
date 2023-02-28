
#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>


enum class NodeType
{
PROGRAM, COMPOUND, ASSIGN, LOOP, TEST, WRITE, WRITELN,
ADD, SUBTRACT, OR, MULTIPLY, DIVIDE, DIV, MOD, AND,
EQ, LT, GT, NE, LTEQ, GTEQ, NOT,
VARIABLE, INTEGER_CONSTANT, REAL_CONSTANT, STRING_CONSTANT
};

class Node {
public:
    Node();
    ~Node();
    Node(NodeType type);
    void adopt(Node* child);
    NodeType getType() const;
    std::string toString() const;
    std::string typeToString(NodeType type) const;
    void setName(std::string name);
    void setValue(std::string value);
    void setLevel(int level);
    void setLine(int line);
    void setIndent(int indet);
    std::string getName();
    std::string getValue();
    int getLevel();
    int getLine();
    int getIndent();
    std::vector<Node*> getChildren() const;
private:
    NodeType type;
    std::string name;
    std::string value;
    int level;
    int line;
    int indent;
    std::vector<Node*> children;
};

#endif

