#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH (GetScreenWidth()) 
#define SCREEN_HEIGHT (GetScreenHeight())
#define FPS 0

#define CELL_SIZE 5 
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)
#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

typedef enum CellType{
  EMPTY,
  SAND,
  DIRT,
  WET_SAND,
  WATER,
  SMOKE,
  STONE
}CellType;

typedef enum ElementType{
  NOTHING,
  GAS,
  LIQUID,
  SOLID
}ElementType;

typedef struct Cell{
  Vector2 pos;
  int direction;
  CellType type;
  ElementType element; 
  float density;
  bool isSolid;
  bool moved;
  bool active;
}Cell;

typedef struct User{
  CellType equippedType;
}User;

#endif
