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
    default:
      break;
  }

  //draw FPS
  DrawText(TextFormat("%d", fps), 20, 20, 20, BLUE);

  //draw the world temp
  DrawText(TextFormat("Temp: %.2f", worldTemp), 20, 50, 20, GREEN);
}
