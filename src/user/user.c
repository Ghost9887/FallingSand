#include "user.h"

extern float worldTemp;

User createUser(){
  User user;
  user.equippedType = SAND;
  return user;
}

void switchTypes(User *user){
  if(IsKeyPressed(KEY_ZERO)){
    user->equippedType = EMPTY;
  }
  else if(IsKeyPressed(KEY_ONE)){
    user->equippedType = SAND;
  }
  else if(IsKeyPressed(KEY_TWO)){
    user->equippedType = WATER; 
  }
  else if(IsKeyPressed(KEY_THREE)){
    user->equippedType = STONE;
  }
  else if(IsKeyPressed(KEY_FOUR)){
    user->equippedType = SMOKE;
  }
  else if(IsKeyPressed(KEY_FIVE)){
    user->equippedType = DIRT;
  }
  else if(IsKeyPressed(KEY_SIX)){
    user->equippedType = WATER_VAPOR;
  }
  else if(IsKeyPressed(KEY_SEVEN)){
    user->equippedType = WOOD;
  }
  else if(IsKeyPressed(KEY_EIGHT)){
    user->equippedType = LAVA;
  }
}

void placeCell(User *user, Cell *cellArr){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 mousePos = GetMousePosition();
    int centerX = (int)mousePos.x / CELL_SIZE;
    int centerY = (int)mousePos.y / CELL_SIZE;
    for(int offsetY = -BRUSH_RADIUS; offsetY <= BRUSH_RADIUS; offsetY++){
      for(int offsetX = -BRUSH_RADIUS; offsetX <= BRUSH_RADIUS; offsetX++){
        int gridX = centerX + offsetX;
        int gridY = centerY + offsetY;
        if(gridX < 0 || gridX >= GRID_WIDTH || gridY < 0 || gridY >= GRID_HEIGHT) continue;
        int indexOfCell = gridY * GRID_WIDTH + gridX;
        if(!cellArr[indexOfCell].active && user->equippedType != EMPTY){
          switch(user->equippedType){
            case SAND:
              createSand(&cellArr[indexOfCell]);
              break;
            case WATER:
              createWater(&cellArr[indexOfCell]);
              break;
            case STONE:
              createStone(&cellArr[indexOfCell]);
              break;
            case SMOKE:
              createSmoke(&cellArr[indexOfCell]);
              break;
            case WATER_VAPOR:
              createWaterVapor(&cellArr[indexOfCell]);
              break;
            case DIRT:
              createDirt(&cellArr[indexOfCell]);
              break;
            case WOOD:
              createWood(&cellArr[indexOfCell]);
              break;
            case LAVA:
              createLava(&cellArr[indexOfCell]);
              break;
              default:
              break;
          }
        }
      }
    }
  }
}

void updateUser(User *user, Cell *cellArr){
  placeCell(user, cellArr);
  switchTypes(user);
}
