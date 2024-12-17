#include <string>
#include <raylib.h>

#include "grid/grid.hpp"

int main()
{
  grid::Grid g;

  SetConfigFlags(FLAG_MSAA_4X_HINT);

  // Enable Multi-Sample Anti-Aliasing (MSAA) before window creation
  InitWindow(300, 300, "Simulator");

  SetTargetFPS(60);

  while (WindowShouldClose() == false)
  {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawCircle(150, 150, 50, BLUE);
    DrawText(std::to_string(g.getGridSize()).c_str(), 40, 40, 10, BLACK);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
