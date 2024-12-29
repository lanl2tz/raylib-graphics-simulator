// Graph.hpp
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "graph/Node.hpp"
#include "graph/Edge.hpp"

class Graph
{
public:
    std::vector<Node> nodes;
    std::vector<Edge> edges;

    // Create a node with a label and position
    void addNode(const std::string &label, float x, float y)
    {
        nodes.emplace_back(label, x, y);
    }

    // Add an edge between two existing nodes by index (or you can do it by pointer)
    void addEdge(int srcIndex, int dstIndex, float weight = 1.0f)
    {
        if (srcIndex < nodes.size() && dstIndex < nodes.size())
        {
            edges.emplace_back(&nodes[srcIndex], &nodes[dstIndex], weight);
        }
    }

    // BFS as an example of an algorithm
    std::vector<int> bfs(int startIndex)
    {
        std::vector<int> visitedOrder;
        if (startIndex >= nodes.size())
            return visitedOrder;

        std::vector<bool> visited(nodes.size(), false);
        std::queue<int> queue;

        visited[startIndex] = true;
        queue.push(startIndex);

        while (!queue.empty())
        {
            int current = queue.front();
            queue.pop();
            visitedOrder.push_back(current);

            // Get neighbors
            for (auto &edge : edges)
            {
                if (edge.source == &nodes[current])
                {
                    int neighborIndex = edge.destination - &nodes[0];
                    if (!visited[neighborIndex])
                    {
                        visited[neighborIndex] = true;
                        queue.push(neighborIndex);
                    }
                }
                // If undirected, also check if edge.destination == &nodes[current]
            }
        }
        return visitedOrder;
    }
};

#endif // GRAPH_HPP