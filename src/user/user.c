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
          Cell *cell = &cellArr[indexOfCell];
          switch(user->equippedType){
            case SAND:
              cell->element = SOLID;
              cell->density = 1.5f;
              cell->temp = worldTemp; 
              break;
            case WATER:
              cell->element = LIQUID;
              cell->density = 1.0f;
              cell->temp = worldTemp;
              break;
            case STONE:
              cell->isSolid = true;
              cell->element = SOLID;
              cell->density = 3.0f;
              cell->temp = worldTemp;
              break;
            case SMOKE:
              cell->element = GAS;
              cell->density = 0.0f;
              cell->temp = worldTemp;
              break;
            case WATER_VAPOR:
              cell->element = GAS;
              cell->density = 0.0f;
              cell->temp = MAX_WATER_TEMP - 1;
              break;
            case DIRT:
              cell->element = SOLID;
              cell->density = 1.5f;
              cell->temp = worldTemp;
              break;
            default:
              break;
          }
          cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
          cell->type = user->equippedType;
          cell->active = true;
        }
      }
    }
  }
}

void updateUser(User *user, Cell *cellArr){
  placeCell(user, cellArr);
  switchTypes(user);
}
