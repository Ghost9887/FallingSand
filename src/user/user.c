#include "user.h"

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
}

//TODO: issue when placing tiles doesnt work sometimes
void placeCell(User *user, Cell *cellArr){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){

    Vector2 mousePos = GetMousePosition();
    int posX = ((int)mousePos.x / CELL_SIZE) * CELL_SIZE;
    int posY = ((int)mousePos.y / CELL_SIZE) * CELL_SIZE;

    int indexOfCell = (posY / CELL_SIZE) * GRID_WIDTH + (posX / CELL_SIZE);

    if(!cellArr[indexOfCell].active && user->equippedType != EMPTY){
      if(user->equippedType == SAND){
        cellArr[indexOfCell].element = SOLID;
        cellArr[indexOfCell].density = 1.5f;
      }
      else if(user->equippedType == WATER){
        cellArr[indexOfCell].element = LIQUID;
        cellArr[indexOfCell].density = 1.0f;
      }
      else if(user->equippedType == STONE){
        cellArr[indexOfCell].isSolid = true;
        cellArr[indexOfCell].element = SOLID;
        cellArr[indexOfCell].density = 3.0f;
      }
      else if(user->equippedType == SMOKE){
        cellArr[indexOfCell].element = GAS;
        cellArr[indexOfCell].density = 0.0f;
      }
      cellArr[indexOfCell].direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
      cellArr[indexOfCell].type = user->equippedType;
      cellArr[indexOfCell].active = true;
    }
  }
}

void updateUser(User *user, Cell *cellArr){
  placeCell(user, cellArr);
  switchTypes(user);
}
