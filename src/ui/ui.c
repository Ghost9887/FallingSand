#include "ui.h"


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
    default:
      break;
  }

  //draw FPS
  DrawText(TextFormat("%d", fps), 20, 20, 20, BLUE);
}
