#include <raylib.h>
#include <iostream>
#include "Graph.hpp"

int main()
{
  // Window initialization
  InitWindow(800, 600, "Graph Visualization");
  SetTargetFPS(60);

  Graph graph;

  // Example: Add some nodes
  graph.addNode("A", 100.0f, 200.0f);
  graph.addNode("B", 300.0f, 100.0f);
  graph.addNode("C", 500.0f, 300.0f);

  // Add edges
  graph.addEdge(0, 1);
  graph.addEdge(1, 2);
  graph.addEdge(0, 2);

  // Optional: BFS result, we’ll animate this later
  std::vector<int> bfsOrder = graph.bfs(0);
  // for debugging
  for (auto idx : bfsOrder)
  {
    std::cout << "Visited: " << graph.nodes[idx].label << std::endl;
  }

  // We'll use this to highlight BFS progression
  int highlightIndex = -1;
  float highlightTimer = 0.0f;    // accumulates time
  float highlightInterval = 1.0f; // highlight each node every 1 second

  while (!WindowShouldClose())
  {
    // Update section
    highlightTimer += GetFrameTime();
    // If enough time passed, move to next BFS node
    if (highlightTimer >= highlightInterval)
    {
      highlightTimer = 0.0f;
      if (highlightIndex < (int)bfsOrder.size() - 1)
      {
        highlightIndex++;
      }
    }

    // Draw section
    BeginDrawing();
    ClearBackground(RAYWHITE);

    // Draw edges
    for (auto &edge : graph.edges)
    {
      DrawLine(
          (int)edge.source->x,
          (int)edge.source->y,
          (int)edge.destination->x,
          (int)edge.destination->y,
          DARKGRAY);
    }

    // Draw nodes
    for (int i = 0; i < graph.nodes.size(); i++)
    {
      auto &node = graph.nodes[i];

      // Determine color if highlighted
      Color color = BLUE;
      // If the BFS node up to highlightIndex is i, then highlight it
      if (highlightIndex >= 0)
      {
        // BFS up to highlightIndex
        for (int j = 0; j <= highlightIndex && j < bfsOrder.size(); j++)
        {
          if (bfsOrder[j] == i)
          {
            color = RED; // highlight color
            break;
          }
        }
      }

      DrawCircle((int)node.x, (int)node.y, 20, color);
      // Label
      DrawText(
          node.label.c_str(),
          (int)node.x - 6,
          (int)node.y - 10,
          20,
          WHITE);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}