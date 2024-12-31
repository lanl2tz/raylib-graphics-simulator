// main.cpp
#include <raylib.h>
#include <cmath>
#include <iostream>
#include "Graph.hpp"

int main()
{
  // Window setup
  InitWindow(800, 600, "Graph Visualization - Draggable Nodes + BFS");
  SetTargetFPS(60);

  // Create a Graph and populate
  Graph graph;
  // Add nodes (example positions)
  graph.addNode("A", 100.0f, 200.0f);
  graph.addNode("B", 300.0f, 100.0f);
  graph.addNode("C", 500.0f, 300.0f);
  graph.addNode("D", 600.0f, 150.0f);
  graph.addNode("E", 600.0f, 250.0f);

  // Add edges (example)
  graph.addEdge(0, 1);
  graph.addEdge(2, 4);
  graph.addEdge(1, 3);
  graph.addEdge(0, 2);
  graph.addEdge(1, 4);

  // -- Dragging variables --
  int draggedNodeIndex = -1; // which node is being dragged (-1 = none)
  Vector2 dragOffset = {0.0f, 0.0f};
  float nodeRadius = 20.0f; // node circle radius

  // -- BFS Animation variables --
  bool bfsRunning = false;    // is BFS animation active?
  std::vector<int> bfsOrder;  // BFS visiting order of node indices
  int bfsHighlightIndex = -1; // which BFS node is currently highlighted
  float bfsTimer = 0.0f;      // accumulates time for BFS steps
  float bfsInterval = 1.0f;   // highlight next BFS node every 1 second

  // Button rectangle for "Start BFS"
  // We'll place it top-right corner, say 100x40 px
  Rectangle startBtnRect = {800.0f - 110.0f, 10.0f, 100.0f, 40.0f};

  while (!WindowShouldClose())
  {
    Vector2 mousePos = GetMousePosition();

    //------------------------------------------------
    // 1) Handle Button Click for BFS
    //------------------------------------------------
    if (CheckCollisionPointRec(mousePos, startBtnRect))
    {
      // if hovering, and user clicks, start BFS
      if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        // Run BFS from node 0 (or any node you want)
        bfsOrder = graph.bfs(0);
        bfsRunning = true;
        bfsHighlightIndex = -1; // reset BFS index
        bfsTimer = 0.0f;        // reset timer
      }
    }

    //------------------------------------------------
    // 2) Handle Mouse Input for Dragging Nodes
    //------------------------------------------------
    // If user presses left mouse button (and isn't clicking the BFS button)
    // we attempt to pick up a node:
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
      // Only start dragging if we didn't click the BFS button
      // (One approach: check if we clicked outside startBtnRect)
      if (!CheckCollisionPointRec(mousePos, startBtnRect))
      {
        // Check if the click is on any node
        for (int i = 0; i < (int)graph.nodes.size(); i++)
        {
          float dx = mousePos.x - graph.nodes[i].x;
          float dy = mousePos.y - graph.nodes[i].y;
          float dist = std::sqrt(dx * dx + dy * dy);

          if (dist <= nodeRadius)
          {
            draggedNodeIndex = i;
            dragOffset = {dx, dy};
            break;
          }
        }
      }
    }

    // If user releases left mouse button, stop dragging
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
    {
      draggedNodeIndex = -1;
    }

    // If a node is being dragged, update its position
    if (draggedNodeIndex != -1)
    {
      graph.nodes[draggedNodeIndex].x = mousePos.x - dragOffset.x;
      graph.nodes[draggedNodeIndex].y = mousePos.y - dragOffset.y;
    }

    //------------------------------------------------
    // 3) Update BFS animation if active
    //------------------------------------------------
    if (bfsRunning && !bfsOrder.empty())
    {
      bfsTimer += GetFrameTime();
      // Move to the next BFS node if enough time has passed
      if (bfsTimer >= bfsInterval)
      {
        bfsTimer = 0.0f;
        if (bfsHighlightIndex < (int)bfsOrder.size() - 1)
        {
          bfsHighlightIndex++;
        }
        else
        {
          // Reached the end of BFS order, stop or loop as desired
          bfsRunning = false;
        }
      }
    }

    //------------------------------------------------
    // 4) Begin drawing
    //------------------------------------------------
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
    for (int i = 0; i < (int)graph.nodes.size(); i++)
    {
      auto &node = graph.nodes[i];
      Color color = BLUE;

      // If this node is currently being dragged, draw in ORANGE
      if (i == draggedNodeIndex)
      {
        color = ORANGE;
      }

      // If BFS is running or has run, check if the node is in BFS highlight range
      // bfsHighlightIndex tells us how many BFS nodes are "active"
      if (bfsHighlightIndex >= 0)
      {
        // For all BFS indices up to bfsHighlightIndex, highlight them
        for (int j = 0; j <= bfsHighlightIndex && j < (int)bfsOrder.size(); j++)
        {
          if (bfsOrder[j] == i)
          {
            color = RED;
            break; // once matched, color is RED
          }
        }
      }

      // Draw the circle for the node
      DrawCircle((int)node.x, (int)node.y, nodeRadius, color);

      // Node label in white
      int textWidth = MeasureText(node.label.c_str(), 20);
      DrawText(
          node.label.c_str(),
          (int)(node.x - textWidth * 0.5f),
          (int)(node.y - 10),
          20,
          WHITE);
    }

    // Draw "Start BFS" button
    DrawRectangleRec(startBtnRect, LIGHTGRAY);
    DrawText("START",
             (int)(startBtnRect.x + 10),
             (int)(startBtnRect.y + 10),
             20,
             BLACK);

    // Optionally, show a hover effect if mouse is over the button
    if (CheckCollisionPointRec(mousePos, startBtnRect))
    {
      DrawRectangleLinesEx(startBtnRect, 2, RED);
    }
    else
    {
      DrawRectangleLinesEx(startBtnRect, 2, BLACK);
    }

    EndDrawing();
  }

  CloseWindow();
  return 0;
}