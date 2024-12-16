#include <raylib.h>

int main() {
  InitWindow(300, 600, "Simulator");
  SetTargetFPS(60);
  while (WindowShouldClose() == false) {
    BeginDrawing();
    
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}
