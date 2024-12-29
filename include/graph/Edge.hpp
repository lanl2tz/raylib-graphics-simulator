// Edge.hpp
#ifndef EDGE_HPP
#define EDGE_HPP

#include "Node.hpp"

class Edge
{
public:
    Node *source;
    Node *destination;
    float weight; // optional

    Edge(Node *src, Node *dst, float w = 0.0f)
        : source(src), destination(dst), weight(w) {}
};

#endif // EDGE_HPP