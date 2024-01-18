
#include "node.hpp"


int Node::getDepth() const 
{
    return depth;
}

int Node::getEval() const 
{
    return eval;
}

TYPE Node::getType() const 
{
    return type;
}

void Node::setDepth(int newDepth) 
{
    depth = newDepth;
}

void Node::setEval(int newEval) 
{
    eval = newEval;
}

void Node::setType(TYPE newType) 
{
    eval = newType;
}

namespace std 
{
    template <>
    struct hash<Node> {
        size_t operator()(const Node& n) const 
        {
            return hash<int>()(n.getDepth()) ^
             hash<int>()(n.getEval()) ^
              hash<TYPE>()(n.getType());
        }
    };
}

bool operator==(const Node& lhs, const Node& rhs) 
{
    return lhs.getDepth() == rhs.getDepth() &&
     lhs.getEval() == rhs.getEval() &&
      lhs.getType() == rhs.getType();
}