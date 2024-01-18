
#include <functional>

enum TYPE
{
    EXACT,
    LOWER,
    UPPER
};

class Node 
{
    private:
        int depth;
        int eval;
        TYPE type;

    public:

        Node() : depth(0), eval(0), type(EXACT) {}

        Node(int depth, int eval, TYPE type)
            : depth(depth), eval(eval), type(type) {}

        int getDepth() const;
        int getEval() const;
        TYPE getType() const;


        void setDepth(int newDepth);
        void setEval(int newEval);
        void setType(TYPE newType);

        friend struct std::hash<Node>;

        friend bool operator==(const Node& lhs, const Node& rhs);

};