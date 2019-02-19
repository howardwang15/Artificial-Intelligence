#include <vector>

#ifndef NODE_H
#define NODE_H

class Node {
    public:
        Node(int);
    private:
        int value_;
        std::vector<Node*> children_;
};

#endif