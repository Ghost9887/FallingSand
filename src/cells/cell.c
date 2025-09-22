#include "cell.h"

const float updateTime = 0.001f;
float updateTimer = 0.0f;

Cell createCell(int x, int y){
  Cell cell;
  cell.pos = (Vector2){ x, y };
  cell.direction = 0;
  cell.type = EMPTY;
  cell.element = NOTHING;
  cell.isSolid = false; // immovable
  cell.moved = false;
  cell.active = false;
  return cell;
}

void initCellArr(Cell *cellArr){
  int index = 0;
  for(int y = 0; y < GRID_HEIGHT; y++){
    for(int x = 0; x < GRID_WIDTH; x++){
      int posX = x * CELL_SIZE;
      int posY = y * CELL_SIZE;
      cellArr[index] = createCell(posX, posY);
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
            consume(i, belowIndex, cellArr);
            consume(i, aboveIndex, cellArr);
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
            break;
          case WET_SAND:
            tempChange(i, cellArr);
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
           break;
          case DIRT:
            consume(i, belowIndex, cellArr);
            consume(i, aboveIndex, cellArr);
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
            break;
          case WET_DIRT:
            tempChange(i, cellArr);
            moveDown(i, belowIndex, cellArr);
            moveDownRight(i, belowIndex + 1, cellArr);
            moveDownLeft(i, belowIndex - 1, cellArr);
           break;
          case WATER:
            tempChange(i, cellArr);
            moveDown(i, belowIndex, cellArr);
            moveRight(i, i + 1, cellArr);
            moveLeft(i, i - 1, cellArr);
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
            tempChange(i, cellArr);
            if(aboveIndex >= 0 && cellArr[i].type == WATER_VAPOR){ //checks if a temp change happend
              changeDirectionRandomly(&cellArr[i]);
              moveUp(i, aboveIndex, cellArr);
              moveLeft(i, i - 1, cellArr);
              moveRight(i, i + 1, cellArr);
            }
            break;
          default:
            break;
        }
      }
    }
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
