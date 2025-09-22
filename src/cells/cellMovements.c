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

void consume(int originalIndex, int targetIndex, Cell *cellArr){
  //drinks the water for example
  if(cellArr[targetIndex].element == LIQUID && cellArr[originalIndex].density > cellArr[targetIndex].density){
    //replace the cell
    replaceCell(originalIndex, targetIndex, cellArr);
    //change the type
    switch(cellArr[targetIndex].type){
      case SAND:
        switchType(targetIndex, WET_SAND, cellArr);
        break;
      case DIRT:
        switchType(targetIndex, WET_DIRT, cellArr);
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
      case DIRT:
        switchType(targetIndex + 1, WET_DIRT, cellArr);
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
      case DIRT:
        switchType(targetIndex - 1, WET_DIRT, cellArr);
        break;
      default:
        break;
    }
  }
}

bool destroyCell(int originalIndex, int targetIndex, Cell *cellArr){
  if(cellArr[originalIndex].element == LIQUID){
    if(cellArr[targetIndex].type == WOOD){
      cellArr[targetIndex].temp += 10.0f;
      return true;
    }
    else if(cellArr[targetIndex].type == STONE){
      cellArr[targetIndex].temp += 10.0f;
      return true;
    }
    else if(cellArr[targetIndex].type == SAND){
      cellArr[targetIndex].temp += 10.0f;
      return true;
    }
    else if(cellArr[targetIndex].type == WATER){
      cellArr[targetIndex].temp += 90.0f;
      cellArr[originalIndex].temp -= 50.0f;

      if(cellArr[targetIndex + 1].type == WATER){
        cellArr[targetIndex].temp += 90.0f;
        cellArr[originalIndex].temp -= 50.0f;
      }
      if(cellArr[targetIndex - 1].type == WATER){
        cellArr[targetIndex].temp += 90.0f;
        cellArr[originalIndex].temp -= 50.0f;
      }
      if(cellArr[targetIndex - GRID_WIDTH].type == WATER){
        cellArr[targetIndex].temp += 90.0f;
        cellArr[originalIndex].temp -= 50.0f;
      }
      return true;
    }
    else if(cellArr[targetIndex].type == WET_SAND){
      cellArr[targetIndex].temp += 50.0f;
    }
  }
  return false;
}

void tempChange(int originalIndex, Cell *cellArr){
  if(cellArr[originalIndex].element == GAS){
    cellArr[originalIndex].temp -= worldTemp / 10000;
    if(cellArr[originalIndex].type == WATER_VAPOR && cellArr[originalIndex].temp <= 0.0f){
      switchType(originalIndex, WATER, cellArr);
    }
  }

  else if(cellArr[originalIndex].element == SOLID){
    if(cellArr[originalIndex].type == WET_SAND){
      cellArr[originalIndex].temp += worldTemp / 10000;
      if(cellArr[originalIndex].temp >= MAX_WATER_TEMP){
        switchType(originalIndex, SAND, cellArr);
      }
    }
    else if(cellArr[originalIndex].type == WET_DIRT){
      cellArr[originalIndex].temp += worldTemp / 1000;
      if(cellArr[originalIndex].temp >= MAX_WATER_TEMP){
        switchType(originalIndex, DIRT, cellArr);
      }
    }
    else if(cellArr[originalIndex].type == WOOD){
      if(cellArr[originalIndex].temp >= MELTING_POINT_OF_WOOD){
        switchType(originalIndex, LAVA, cellArr);
      }
    }
    else if(cellArr[originalIndex].type == STONE){
      if(cellArr[originalIndex].temp >= MELTING_POINT_OF_STONE){
        switchType(originalIndex, LAVA, cellArr);
      }
    }
    else if(cellArr[originalIndex].type == SAND){
      if(cellArr[originalIndex].temp >= MELTING_POINT_OF_SAND){
        switchType(originalIndex, GLASS, cellArr);
      }
    }
  }

  else if(cellArr[originalIndex].element == LIQUID){
    if(cellArr[originalIndex].type == WATER){
      cellArr[originalIndex].temp += worldTemp / 10000;
      if(cellArr[originalIndex].temp >= MAX_WATER_TEMP){
        switchType(originalIndex, WATER_VAPOR, cellArr);
      }
    }
    else if(cellArr[originalIndex].type == LAVA){
      if(cellArr[originalIndex].temp <= 10.0f){
        switchType(originalIndex, VOLCANIC_GLASS, cellArr);
      }
    }
  }
}

void changeDirectionRandomly(Cell *cell){
  cell->direction = GetRandomValue(-1, 1);
}

