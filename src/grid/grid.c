#include "grid.h"

void drawGrid(){
  for(int i = 0; i <= GRID_WIDTH; i++){
    DrawLine(i * CELL_SIZE, 0, i * CELL_SIZE, GRID_HEIGHT * CELL_SIZE, BLACK);
  }
  for(int i = 0; i <= GRID_HEIGHT; i++){
    DrawLine(0, i * CELL_SIZE, GRID_WIDTH * CELL_SIZE, i * CELL_SIZE, BLACK);
  }
}

void updateGrid(){
  drawGrid();
}
