// Node.hpp
#ifndef NODE_HPP
#define NODE_HPP

#include <string>
#include <vector>

class Node
{
public:
    // Maybe we store x, y for rendering
    float x, y;
    std::string label;

    // Constructor
    Node(const std::string &lbl, float xpos, float ypos)
        : label(lbl), x(xpos), y(ypos) {}
};

#endif // NODE_HPP