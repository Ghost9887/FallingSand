#include "cell.h"

const float updateTime = 0.01f;
float updateTimer = 0.0f;

Cell createCell(int x, int y){
  Cell cell;
  cell.pos = (Vector2){ x, y };
  cell.direction = 0;
  cell.type = EMPTY;
  cell.active = false;
  cell.moved = false;
  cell.isSolid = false;
  cell.colour = BLACK;
  cell.element = SOLID;
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
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, cell->colour);
      break;
   case WATER:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, cell->colour);
      break;
    case STONE:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, cell->colour);
      break;
    case SMOKE:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, cell->colour);
      break;
   default:
      break;
  }
}

void copyData(int originalIndex, int targetIndex, Cell *cellArr){
  cellArr[targetIndex].direction = cellArr[originalIndex].direction;
  cellArr[targetIndex].type = cellArr[originalIndex].type;
  cellArr[targetIndex].active = true;
  cellArr[targetIndex].colour = cellArr[originalIndex].colour;
  cellArr[targetIndex].element = cellArr[originalIndex].element;
}

void deactivateCell(int originalIndex, Cell *cellArr){
  cellArr[originalIndex].direction = 0;
  cellArr[originalIndex].type = EMPTY;
  cellArr[originalIndex].element = NOTHING;
  cellArr[originalIndex].active = false;
}

void moveDown(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY){
    copyData(originalIndex, targetIndex, cellArr);
    deactivateCell(originalIndex, cellArr);
  }
}

void moveDownRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY){
    copyData(originalIndex, targetIndex, cellArr);
    deactivateCell(originalIndex, cellArr);
  }
}

void moveDownLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY){
    copyData(originalIndex, targetIndex, cellArr);
    deactivateCell(originalIndex, cellArr);
  }
}

void moveRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction > 0){
    copyData(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
    deactivateCell(originalIndex, cellArr);
    cellArr[originalIndex].moved = false;
  }  
  //flipping the direction
  if(cellArr[targetIndex].type != EMPTY){
    cellArr[originalIndex].direction *= -1;
  }
}

void moveLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction < 0){
    copyData(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
    deactivateCell(originalIndex, cellArr);
    cellArr[originalIndex].moved = false;
  }  
  //flip the direction 
  if(cellArr[targetIndex].type != EMPTY){
    cellArr[originalIndex].direction *= -1;
  }
}

void moveUp(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction == 0){
    copyData(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
    deactivateCell(originalIndex, cellArr);
  }
}

void changeDirectionRandomly(Cell *cell){
  cell->direction = GetRandomValue(-1, 1);
}


void clearMoved(Cell *cellArr){
  for(int i = 0; i < AMOUNT_OF_CELLS; i++){
    cellArr[i].moved = false;
  }
}

//have to go up so we dont cycle already moved cells
void moveCells(Cell *cellArr){
  clearMoved(cellArr);
  for(int i = AMOUNT_OF_CELLS - 1; i >= 0; i--){
    if(cellArr[i].active && !cellArr[i].moved){
      int targetIndex = i + GRID_WIDTH; 
      if(targetIndex < AMOUNT_OF_CELLS){
        switch(cellArr[i].type){
          case SAND:
            moveDown(i, targetIndex, cellArr);
            moveDownRight(i, targetIndex + 1, cellArr);
            moveDownLeft(i, targetIndex - 1, cellArr);
            break;
          case WATER:
            moveDown(i, targetIndex, cellArr);
            moveRight(i, i + 1, cellArr);
            moveLeft(i, i - 1, cellArr);
            break;
          case STONE:
            break;
          case SMOKE:
            targetIndex = i - GRID_WIDTH;
            if(targetIndex >= 0){
              changeDirectionRandomly(&cellArr[i]);
              moveUp(i, targetIndex, cellArr);
              moveLeft(i, i - 1, cellArr);
              moveRight(i, i + 1, cellArr);
              break;
             }
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
    }
  }
  updateTimer += GetFrameTime();
  if(updateTimer >= updateTime){
    moveCells(cellArr);
    updateTimer = 0.00f;
  }
}
