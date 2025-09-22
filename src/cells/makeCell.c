#include "makeCell.h"

extern float worldTemp;

Cell createEmptyCell(int posX, int posY){
  Cell cell;
  cell.pos = (Vector2){ posX, posY };
  cell.element = NOTHING;
  cell.type = EMPTY;
  cell.density = 0.0f;
  cell.temp = 0.0f;
  cell.isSolid = false;
  cell.moved = false;
  cell.direction = 0;
  cell.active = false;
  return cell;
}

void createSand(Cell *cell){
  cell->element = SOLID;
  cell->type = SAND;
  cell->density = 1.5f;
  cell->temp = worldTemp;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 0;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createWetSand(Cell *cell){
  cell->element = SOLID;
  cell->type = WET_SAND;
  cell->density = 2.0f;
  cell->temp = worldTemp;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createDirt(Cell *cell){
  cell->element = SOLID;
  cell->type = DIRT;
  cell->density = 1.5f;
  cell->temp = worldTemp;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 0;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createWetDirt(Cell *cell){
  cell->element = SOLID;
  cell->type = WET_DIRT;
  cell->density = 1.5f;
  cell->temp = worldTemp;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createStone(Cell *cell){
  cell->element = SOLID;
  cell->type = STONE;
  cell->density = 3.0f;
  cell->temp = worldTemp;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = 0;
  cell->active = true;
}

void createWood(Cell *cell){
  cell->element = SOLID;
  cell->type = WOOD;
  cell->density = 1.6f;
  cell->temp = worldTemp;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = 0;
  cell->active = true;
}

void createGlass(Cell *cell){
  cell->element = SOLID;
  cell->type = GLASS;
  cell->density = 2.4f;
  cell->temp = 1400.0f;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = 0;
  cell->active = true;
}

void createVolcanicGlass(Cell *cell){
  cell->element = SOLID;
  cell->type = VOLCANIC_GLASS;
  cell->density = 2.4f;
  cell->temp = 800.0f;
  cell->isSolid = true;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = 0;
  cell->active = true;
}

void createWater(Cell *cell){
  cell->element = LIQUID;
  cell->type = WATER;
  cell->density = 1.0f;
  cell->temp = worldTemp;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 1.0f;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createLava(Cell *cell){
  cell->element = LIQUID;
  cell->type = LAVA;
  cell->density = 1.0f;
  cell->temp = 1000.0f;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 5;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}

void createSmoke(Cell *cell){
  cell->element = GAS;
  cell->type = SMOKE;
  cell->density = 0.0f;
  cell->temp = 450.0f;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1; 
  cell->active = true;
}

void createWaterVapor(Cell *cell){
  cell->element = GAS;
  cell->type = WATER_VAPOR;
  cell->density = 0.0f;
  cell->temp = 100.0f;
  cell->isSolid = false;
  cell->moved = false;
  cell->vescocity = 0.0f;
  cell->direction = (GetRandomValue(1, 2) % 2 == 0) ? -1 : 1;
  cell->active = true;
}


