#include "cell.h"

const float updateTime = 0.01f;
float updateTimer = 0.0f;
int updateCounter = 3;

void initCellArr(Cell *cellArr){
  int index = 0;
  for(int y = 0; y < GRID_HEIGHT; y++){
    for(int x = 0; x < GRID_WIDTH; x++){
      int posX = x * CELL_SIZE;
      int posY = y * CELL_SIZE;
      cellArr[index] = createEmptyCell(posX, posY);
      index++;
    }
  }
}

void drawCells(Cell *cell){
  switch (cell->type) {
    case SAND:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, YELLOW);
      break;
    case WET_SAND:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, GOLD);
      break;
    case WATER:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, BLUE);
      break;
    case STONE:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, GRAY);
      break;
    case SMOKE:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, DARKGRAY);
      break;
    case WATER_VAPOR:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, SKYBLUE);
      break;
    case DIRT:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, BROWN);
      break;
    case WET_DIRT:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, DARKBROWN);
      break;
    case WOOD:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, BEIGE);
      break;
    case LAVA:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, ORANGE); 
      break;
    case GLASS:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, WHITE); 
      break;
    case VOLCANIC_GLASS:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, PURPLE); 
      break;
   default:
      break;
  }
}

//have to go up so we dont cycle already moved cells
void moveCells(Cell *cellArr){
  for(int i = AMOUNT_OF_CELLS - 1; i >= 0; i--){
    if(cellArr[i].active && !cellArr[i].moved){
      int belowIndex = i + GRID_WIDTH; 
      int aboveIndex = i - GRID_WIDTH;
      if(belowIndex < AMOUNT_OF_CELLS){
        switch(cellArr[i].type){
          case SAND:
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
            break;
          case WET_SAND:
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
           break;
          case DIRT:
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
            break;
          case WET_DIRT:
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
           break;
          case WATER:
            if(updateCounter % cellArr[i].vescocity == 0){
              moveDown(i, belowIndex, cellArr);
              moveRight(i, i + 1, cellArr);
              moveLeft(i, i - 1, cellArr);
            }
            break;
          case LAVA:
            if(updateCounter % cellArr[i].vescocity == 0){
              moveDown(i, belowIndex, cellArr);
              moveRight(i, i + 1, cellArr);
              moveLeft(i, i - 1, cellArr);
            }
            break;
          case VOLCANIC_GLASS:
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex, cellArr);
            moveDownLeft(i, belowIndex, cellArr);
            break;
          case SMOKE:
            if(aboveIndex >= 0){
              changeDirectionRandomly(&cellArr[i]);
              moveUp(i, aboveIndex, cellArr);
              moveLeft(i, i - 1, cellArr);
              moveRight(i, i + 1, cellArr);
            }
            break;
          case WATER_VAPOR:
            if(aboveIndex >= 0){
              changeDirectionRandomly(&cellArr[i]);
              moveUp(i, aboveIndex, cellArr);
              moveLeft(i, i - 1, cellArr);
              moveRight(i, i + 1, cellArr);
            }
            break;
          case WOOD:
            break;
          case STONE:
            break;
          default:
            break;
        }
      }
    }
  }
  updateCounter++;
  if(updateCounter >= 10){
    updateCounter = 3;
  }
}

void updateCells(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    if(cellArr[i].active){
      drawCells(&cellArr[i]);
      cellArr[i].moved = false;
    }
  }
  updateTimer += GetFrameTime();
  if(updateTimer >= updateTime){
    moveCells(cellArr);
    updateTimer = 0.00f;
  }
}
