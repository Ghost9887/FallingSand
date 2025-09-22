#include "ui.h"

extern float worldTemp;

void drawUI(User *user, int fps){
  //print the user mode
  switch(user->equippedType){
    case EMPTY:
      DrawText("Empty", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case SAND: 
      DrawText("Sand", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case WATER:
      DrawText("Water", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case STONE:
      DrawText("Stone", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case SMOKE:
      DrawText("Smoke", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case DIRT:
      DrawText("Dirt", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case WATER_VAPOR:
      DrawText("Water Vapor", SCREEN_WIDTH - 220, 20, 30,PURPLE);
      break;
    case WOOD:
      DrawText("Wood", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    case LAVA:  
      DrawText("Lava", SCREEN_WIDTH - 120, 20, 30,PURPLE);
      break;
    default:
      break;
  }

  //draw FPS
  DrawText(TextFormat("%d", fps), 20, 20, 20, BLUE);

  //draw the world temp
  DrawText(TextFormat("Temp: %.2f", worldTemp), 20, 50, 20, GREEN);
}

void drawCellInfo(Cell *cellArr){
  Vector2 mousePos = GetMousePosition();
  int posX = (int)mousePos.x / CELL_SIZE;
  int posY = (int)mousePos.y / CELL_SIZE;
  int index = posY * GRID_WIDTH + posX;
  switch(cellArr[index].type){
    case EMPTY:
      DrawText("Type: Empty", 20, 80, 20, PURPLE);
     break;
    case SAND: 
      DrawText("Type: Sand", 20, 80, 20, PURPLE);
      break;
    case WET_SAND:  
      DrawText("Type: Wet Sand", 20, 80, 20, PURPLE);
      break;
    case WATER:
      DrawText("Type: Water", 20, 80, 20, PURPLE);
      break;
    case STONE:
      DrawText("Type: Stone", 20, 80, 20, PURPLE);
      break;
    case SMOKE:
      DrawText("Type: Smoke", 20, 80, 20, PURPLE);
      break;
    case DIRT:
      DrawText("Type: Dirt", 20, 80, 20, PURPLE);
      break;
    case WET_DIRT:
      DrawText("Type: Wet Dirt", 20, 80, 20, PURPLE);
      break;
    case WATER_VAPOR:
      DrawText("Type: Water Vapor", 20, 80, 20, PURPLE);
      break;
    case WOOD:
      DrawText("Type: Wood", 20, 80, 20, PURPLE);
      break;
    case LAVA:
      DrawText("Type: Lava", 20, 80, 20, PURPLE);
      break;
    default:
      break;
  }
  DrawText(TextFormat("Density: %.2f", cellArr[index].density), 20, 100, 20, WHITE);
  DrawText(TextFormat("Direction: %d", cellArr[index].direction), 20, 120, 20, WHITE);
  DrawText(TextFormat("Temp: %.2f", cellArr[index].temp), 20, 140, 20, WHITE);
}
