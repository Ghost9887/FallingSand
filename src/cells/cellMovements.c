#include "cellMovements.h"

//INCLUDES ALL OF THE WAYS DIFFERENT CELLS CAN MOVE AND HELPER FUNCTION AS WELL


void flipDirection(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type != EMPTY){
    cellArr[originalIndex].direction *= -1;
  }
}

void switchType(int originalIndex, CellType type, Cell *cellArr){
  switch(type){
    case WET_SAND:
      cellArr[originalIndex].type = WET_SAND;
      cellArr[originalIndex].density = 2.0f;
      break;
  } 

}

void deactivateCell(int originalIndex, Cell *cellArr){
  cellArr[originalIndex].direction = 0;
  cellArr[originalIndex].type = EMPTY;
  cellArr[originalIndex].element = NOTHING;
  cellArr[originalIndex].density = 0.0f;
  cellArr[originalIndex].active = false;
}

void replaceCell(int originalIndex, int targetIndex, Cell *cellArr){
  cellArr[targetIndex].direction = cellArr[originalIndex].direction;
  cellArr[targetIndex].type = cellArr[originalIndex].type;
  cellArr[targetIndex].element = cellArr[originalIndex].element;
  cellArr[targetIndex].density = cellArr[originalIndex].density;
  cellArr[targetIndex].active = true;
  deactivateCell(originalIndex, cellArr);
}

void switchCells(int originalIndex, int targetIndex, Cell *cellArr){
  Cell tempCell = cellArr[targetIndex];
  
  cellArr[targetIndex].direction = cellArr[originalIndex].direction;
  cellArr[targetIndex].type = cellArr[originalIndex].type;
  cellArr[targetIndex].element = cellArr[originalIndex].element;
  cellArr[targetIndex].density = cellArr[originalIndex].density;
  cellArr[targetIndex].active = cellArr[originalIndex].active;

  cellArr[originalIndex].direction = tempCell.direction;
  cellArr[originalIndex].type = tempCell.type;
  cellArr[originalIndex].element = tempCell.element;
  cellArr[originalIndex].density = tempCell.density;
  cellArr[originalIndex].active = tempCell.active;
}

void moveDown(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveDownRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveDownLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction > 0){
    replaceCell(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
  }
  flipDirection(originalIndex, targetIndex, cellArr);
}

void moveLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction < 0){
    replaceCell(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
  }  
  flipDirection(originalIndex, targetIndex, cellArr);
}

void moveUp(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction == 0){
    replaceCell(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
  }
}

void consume(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].element == LIQUID && cellArr[originalIndex].density > cellArr[targetIndex].density){
    //replace the cell
    replaceCell(originalIndex, targetIndex, cellArr);
    //change the type
    switch(cellArr[targetIndex].type){
      case SAND:
        switchType(targetIndex, WET_SAND, cellArr);
        break;
      default:
        break;
    }
  }
  
  else if(cellArr[targetIndex + 1].element == LIQUID && cellArr[originalIndex].density > cellArr[targetIndex + 1].density){
    //replace the cell
    replaceCell(originalIndex, targetIndex + 1, cellArr);
    //change the type
    switch(cellArr[targetIndex + 1].type){
      case SAND:
        switchType(targetIndex + 1, WET_SAND, cellArr);
        break;
      default:
        break;
    }
  }
  
  else if(cellArr[targetIndex - 1].element == LIQUID && cellArr[originalIndex].density > cellArr[targetIndex - 1].density){
    //replace the cell
    replaceCell(originalIndex, targetIndex - 1, cellArr);
      //change the type
    switch(cellArr[targetIndex - 1].type){
      case SAND:
        switchType(targetIndex - 1, WET_SAND, cellArr);
        break;
      default:
        break;
    }
  }
}

void changeDirectionRandomly(Cell *cell){
  cell->direction = GetRandomValue(-1, 1);
}




