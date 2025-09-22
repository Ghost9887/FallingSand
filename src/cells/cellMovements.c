#include "cellMovements.h"

//INCLUDES ALL OF THE WAYS DIFFERENT CELLS CAN MOVE AND HELPER FUNCTION AS WELL

extern float worldTemp;

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
      cellArr[originalIndex].temp = 2.0f;
      break;
    case WET_DIRT:
      cellArr[originalIndex].type = WET_DIRT;
      cellArr[originalIndex].density = 2.0f;
      cellArr[originalIndex].temp = 1.0f;
      break;
    case WATER: 
      cellArr[originalIndex].type = WATER;
      cellArr[originalIndex].element = LIQUID;
      cellArr[originalIndex].density = 1.0f;
      cellArr[originalIndex].temp = 1;
      cellArr[originalIndex].direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
      break;
    case SAND:
      cellArr[originalIndex].type = SAND;
      cellArr[originalIndex].density = 1.5f;
      cellArr[originalIndex].temp = worldTemp;
      break;
    case DIRT:
      cellArr[originalIndex].type = DIRT;
      cellArr[originalIndex].density = 1.5f;
      cellArr[originalIndex].temp = worldTemp;
      break;
    case WATER_VAPOR:
      cellArr[originalIndex].element = GAS;
      cellArr[originalIndex].type = WATER_VAPOR;
      cellArr[originalIndex].temp = MAX_WATER_TEMP - 1;
      cellArr[originalIndex].density = 0.0f;
      break;
    case LAVA:
      cellArr[originalIndex].element = LIQUID;
      cellArr[originalIndex].type = LAVA;
      cellArr[originalIndex].temp = 200.0f;
      cellArr[originalIndex].density = 2.9f;
      break;
    case GLASS:
      cellArr[originalIndex].type = GLASS;
      cellArr[originalIndex].temp = 23.0f;
      cellArr[originalIndex].density = 2.8f;
      cellArr[originalIndex].isSolid = true;
      break;
    case VOLCANIC_GLASS:
      cellArr[originalIndex].element = SOLID;
      cellArr[originalIndex].type = VOLCANIC_GLASS;
      cellArr[originalIndex].temp = 23.0f;
      cellArr[originalIndex].density = 4.5f;
    default:
      break;
  } 
}

void deactivateCell(int originalIndex, Cell *cellArr){
  cellArr[originalIndex].direction = 0;
  cellArr[originalIndex].type = EMPTY;
  cellArr[originalIndex].element = NOTHING;
  cellArr[originalIndex].density = 0.0f;
  cellArr[originalIndex].active = false;
  cellArr[originalIndex].temp = 0.0f;
}

void replaceCell(int originalIndex, int targetIndex, Cell *cellArr){
  cellArr[targetIndex].direction = cellArr[originalIndex].direction;
  cellArr[targetIndex].type = cellArr[originalIndex].type;
  cellArr[targetIndex].element = cellArr[originalIndex].element;
  cellArr[targetIndex].density = cellArr[originalIndex].density;
  cellArr[targetIndex].temp = cellArr[originalIndex].temp;
  cellArr[targetIndex].vescocity = cellArr[originalIndex].vescocity;
  cellArr[targetIndex].active = true;
  deactivateCell(originalIndex, cellArr);
}

void switchCells(int originalIndex, int targetIndex, Cell *cellArr){
  Cell tempCell = cellArr[targetIndex];
  
  cellArr[targetIndex].direction = cellArr[originalIndex].direction;
  cellArr[targetIndex].type = cellArr[originalIndex].type;
  cellArr[targetIndex].element = cellArr[originalIndex].element;
  cellArr[targetIndex].density = cellArr[originalIndex].density;
  cellArr[targetIndex].temp = cellArr[originalIndex].temp;
  cellArr[targetIndex].vescocity = cellArr[originalIndex].vescocity;
  cellArr[targetIndex].active = cellArr[originalIndex].active;

  cellArr[originalIndex].direction = tempCell.direction;
  cellArr[originalIndex].type = tempCell.type;
  cellArr[originalIndex].element = tempCell.element;
  cellArr[originalIndex].density = tempCell.density;
  cellArr[originalIndex].temp = tempCell.temp;
  cellArr[originalIndex].vescocity = tempCell.vescocity;
  cellArr[originalIndex].active = tempCell.active;
}

void moveDown(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density && !cellArr[targetIndex].isSolid){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveDownRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density && !cellArr[targetIndex].isSolid){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveDownLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].density > cellArr[targetIndex].density && !cellArr[targetIndex].isSolid){
    //replaceCell(originalIndex, targetIndex, cellArr);
    switchCells(originalIndex, targetIndex, cellArr);
  }
}

void moveRight(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction > 0 && !cellArr[targetIndex].isSolid){
    replaceCell(originalIndex, targetIndex, cellArr);
    cellArr[targetIndex].moved = true;
  }
  flipDirection(originalIndex, targetIndex, cellArr);
}

void moveLeft(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type == EMPTY && cellArr[originalIndex].direction < 0 && !cellArr[targetIndex].isSolid){
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




void changeDirectionRandomly(Cell *cell){
  cell->direction = GetRandomValue(-1, 1);
}

