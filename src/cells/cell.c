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
    case BASALT:
      DrawRectangle(cell->pos.x, cell->pos.y, CELL_SIZE, CELL_SIZE, DARKGRAY); 
      break;
   default:
      break;
  }
}

//have to go up so we dont cycle already moved cells
void moveCells(Cell *cellArr){
  for(int i = AMOUNT_OF_CELLS - 1; i >= 0; i--){
    if(cellArr[i].active && !cellArr[i].moved){
      int *tiles = malloc(sizeof(int) * 9);
      tiles[0] = i; //center 0
      tiles[1] = i + 1; //right 1
      tiles[2] = i - 1; //left 2
      tiles[3] = i + GRID_WIDTH; //below 3
      tiles[4] = i - GRID_WIDTH; //above 4
      tiles[5] = i + GRID_WIDTH + 1; //belowRight 5
      tiles[6] = i + GRID_WIDTH - 1; // belowLeft 6
      tiles[7] = i - GRID_WIDTH + 1; //aboveRight 7 
      tiles[8] = i - GRID_WIDTH - 1; // aboveLeft 8
      if(tiles[3] < AMOUNT_OF_CELLS){
        switch(cellArr[i].type){
          case SAND:
            checkNeigbouringTiles(tiles, cellArr);
            moveDown(tiles[0], tiles[3], cellArr);
            moveDownRight(tiles[0], tiles[5], cellArr);
            moveDownLeft(tiles[0], tiles[6], cellArr);
            break;
          case WET_SAND:
            checkNeigbouringTiles(tiles, cellArr);
            moveDown(tiles[0], tiles[3], cellArr);
            moveDownRight(tiles[0], tiles[5], cellArr);
            moveDownLeft(tiles[0], tiles[6], cellArr);
           break;
          case DIRT:
            checkNeigbouringTiles(tiles, cellArr);
            moveDown(tiles[0], tiles[3], cellArr);
            moveDownRight(tiles[0], tiles[5], cellArr);
            moveDownLeft(tiles[0], tiles[6], cellArr);
            break;
          case WET_DIRT:
            checkNeigbouringTiles(tiles, cellArr);
            moveDown(tiles[0], tiles[3], cellArr);
            moveDownRight(tiles[0], tiles[5], cellArr);
            moveDownLeft(tiles[0], tiles[6], cellArr);
           break;
          case WATER:
            checkNeigbouringTiles(tiles, cellArr);
            if(cellArr[tiles[0]].type == WATER && updateCounter % cellArr[tiles[0]].vescocity == 0){
              moveDown(tiles[0], tiles[3], cellArr);
              moveRight(tiles[0], tiles[1], cellArr);
              moveLeft(tiles[0], tiles[2], cellArr);
            }
            break;
          case LAVA:
            if(updateCounter % cellArr[tiles[0]].vescocity == 0){
              moveDown(tiles[0], tiles[3], cellArr);
              moveRight(tiles[0], tiles[1], cellArr);
              moveLeft(tiles[0], tiles[2], cellArr);
            }
            changeTemp(tiles[0], cellArr);
            break;
          case SMOKE:
            if(tiles[4] >= 0){
              changeDirectionRandomly(&cellArr[tiles[0]]);
              moveUp(tiles[0], tiles[4], cellArr);
              moveLeft(tiles[0], tiles[2], cellArr);
              moveRight(tiles[0], tiles[1], cellArr);
            }
            break;
          case WATER_VAPOR:
            if(tiles[4] >= 0){
              changeDirectionRandomly(&cellArr[tiles[0]]);
              moveUp(tiles[0], tiles[4], cellArr);
              moveLeft(tiles[0], tiles[2], cellArr);
              moveRight(tiles[0], tiles[1], cellArr);
            }
            changeTemp(tiles[0], cellArr);
            break;
          case BASALT:
            moveDown(tiles[0], tiles[3], cellArr);
            moveDownRight(tiles[0], tiles[3], cellArr);
            moveDownLeft(tiles[0], tiles[3], cellArr);
            changeTemp(tiles[0], cellArr);
            break;
          case VOLCANIC_GLASS:
            changeTemp(tiles[0], cellArr);
            break;
          case WOOD:
            checkNeigbouringTiles(tiles, cellArr);
            break;
          case STONE:
            checkNeigbouringTiles(tiles, cellArr);
            break;
          default:
            break;
        }
      }
      free(tiles);
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
