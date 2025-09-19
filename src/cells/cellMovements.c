#include "cellMovements.h"

//INCLUDES ALL OF THE WAYS DIFFERENT CELLS CAN MOVE AND HELPER FUNCTION AS WELL


void flipDirection(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type != EMPTY){
    cellArr[originalIndex].direction *= -1;
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
  flipDirection(originalIndex, targetIndex, cellArr);
}

void moveLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction < 0){
    copyData(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
    deactivateCell(originalIndex, cellArr);
    cellArr[originalIndex].moved = false;
  }  
  flipDirection(originalIndex, targetIndex, cellArr);
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




