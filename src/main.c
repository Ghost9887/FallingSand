#include "common.h"
#include "grid.h"
#include "cell.h"
#include "user.h"
#include "ui.h"

void updateGameState(Cell *cellArr, User *user);

float worldTemp = 23.0f;

int main(){

  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Falling Sand");
  SetTargetFPS(FPS);
  //ToggleFullscreen();

  Cell *cellArr = (Cell*)malloc(sizeof(Cell) * AMOUNT_OF_CELLS);
  initCellArr(cellArr);

  User user = createUser();

  while(!WindowShouldClose()){

    BeginDrawing();
      
      ClearBackground(BLACK);

      updateGameState(cellArr, &user);

    EndDrawing();
  }

  CloseWindow();

  return 0;
}

void updateGameState(Cell *cellArr, User *user){
 
  //updateGrid();

  updateUser(user, cellArr);

  updateCells(cellArr);

  drawUI(user, GetFPS());

  drawCellInfo(cellArr);

}
