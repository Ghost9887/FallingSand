#include "cellMovements.h"

//INCLUDES ALL OF THE WAYS DIFFERENT CELLS CAN MOVE AND HELPER FUNCTION AS WELL

extern float worldTemp;

void flipDirection(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[targetIndex].type != EMPTY){
    cellArr[originalIndex].direction *= -1;
  }
}

void changeDirectionRandomly(Cell *cell){
  cell->direction = GetRandomValue(-1, 1);
}

void switchType(int originalIndex, CellType type, Cell *cellArr){
  switch(type){
    case WET_SAND:
      createWetSand(&cellArr[originalIndex]);
      break;
    case WET_DIRT:
      createWetDirt(&cellArr[originalIndex]);
      break;
    case WATER: 
      createWater(&cellArr[originalIndex]);
      break;
    case SAND:
      createSand(&cellArr[originalIndex]);
      break;
    case DIRT:
      createDirt(&cellArr[originalIndex]);
      break;
    case WATER_VAPOR:
      createWaterVapor(&cellArr[originalIndex]);
      break;
    case LAVA:
      createLava(&cellArr[originalIndex]);
      break;
    case GLASS:
      createGlass(&cellArr[originalIndex]);
      break;
    case VOLCANIC_GLASS:
      createVolcanicGlass(&cellArr[originalIndex]);
      break;
    case BASALT:
      createBasalt(&cellArr[originalIndex]);
      break;
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

void checkNeigbouringTiles(int *tiles, Cell *cellArr){
  //RULES THAT DEPEND IF DIFFERENT TYPE OF CELLS ARE NEXT TO EACH OTHER
  int centerCellType = cellArr[tiles[0]].type;
  for(int i = 1; i < 9; i++){
    if(tiles[i] < 0 || tiles[i] >= AMOUNT_OF_CELLS || !cellArr[tiles[i]].active) continue;
    if(centerCellType == SAND){
      if(cellArr[tiles[i]].type == WATER){
        switchType(tiles[0], WET_SAND, cellArr);
        deactivateCell(tiles[i], cellArr);
      }
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000; 
        if(cellArr[tiles[0]].temp >= 1500){
          switchType(tiles[0], GLASS, cellArr);
        }
      }
    }

    else if(centerCellType == DIRT){
      if(cellArr[tiles[i]].type == WATER){
        switchType(tiles[0], WET_DIRT, cellArr);
        deactivateCell(tiles[i], cellArr);
      }
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= 800){
          switchType(tiles[0], BASALT, cellArr);
        }
      }
    }

    else if(centerCellType == WET_SAND){
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= worldTemp){
          switchType(tiles[0], SAND, cellArr);
        }
      }
    }

    else if(centerCellType == WET_DIRT){
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= worldTemp){
          switchType(tiles[0], DIRT, cellArr);
        }
      }
    }

    else if(centerCellType == WATER){
      if(cellArr[tiles[i]].type == LAVA){
        switchType(tiles[0], WATER_VAPOR, cellArr);
        switchType(tiles[i], VOLCANIC_GLASS, cellArr);
      }
      else if(cellArr[tiles[i]].type == BASALT || cellArr[tiles[i]].type == VOLCANIC_GLASS){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= 100){
          switchType(tiles[0], WATER_VAPOR, cellArr);
        }
      }
    }

    else if(centerCellType == STONE){
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= 1200){
          switchType(tiles[0], LAVA, cellArr);
        }
      }
    }

    else if(centerCellType == WOOD){
      if(cellArr[tiles[i]].type == LAVA){
        cellArr[tiles[0]].temp += cellArr[tiles[i]].temp / 1000;
        if(cellArr[tiles[0]].temp >= 400){
          switchType(tiles[0], LAVA, cellArr);
        }
      }
    }
  }
}

//cells that change thier temp always not when something is near them
void changeTemp(int originalIndex, Cell *cellArr){
  switch(cellArr[originalIndex].type){
    case WATER_VAPOR:
      cellArr[originalIndex].temp -= worldTemp / 100;
      if(cellArr[originalIndex].temp <= 0){
        switchType(originalIndex, WATER ,cellArr);
      }
      break;
    case LAVA:
      cellArr[originalIndex].temp -= worldTemp / 100;
      if(cellArr[originalIndex].temp <= 1000){
        switchType(originalIndex, BASALT, cellArr);
      }
    break;
    case WET_SAND:
      cellArr[originalIndex].temp += worldTemp / 100;
      if(cellArr[originalIndex].temp >= worldTemp){
        switchType(originalIndex, SAND, cellArr);
      }
      break;
    case WET_DIRT:
      cellArr[originalIndex].temp += worldTemp / 100;
      if(cellArr[originalIndex].temp >= worldTemp){
        switchType(originalIndex, DIRT, cellArr);
      }
      break;
    case VOLCANIC_GLASS:
      if(cellArr[originalIndex].temp > worldTemp){
        cellArr[originalIndex].temp -= worldTemp / 100;
      }
      break;
    case BASALT:
      if(cellArr[originalIndex].temp > worldTemp){
        cellArr[originalIndex].temp -= worldTemp / 100;
      }
      break;
    default:
      break;
  }
}


