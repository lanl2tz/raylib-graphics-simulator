#include <raylib.h>

int main() {
  SetConfigFlags(FLAG_MSAA_4X_HINT);

  // Enable Multi-Sample Anti-Aliasing (MSAA) before window creation
  InitWindow(300, 300, "Simulator");

  SetTargetFPS(60);

  while (WindowShouldClose() == false) {
    BeginDrawing();
      ClearBackground(RAYWHITE);
      DrawCircle(150, 150, 50, BLUE); 
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
