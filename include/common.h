#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include "raymath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 800
#define FPS 0

#define CELL_SIZE 5 
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)
#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

typedef enum CellType{
  EMPTY,
  SAND,
  WATER,
  SMOKE,
  STONE
}CellType;

typedef enum ElementType{
  NOTHING,
  GAS,
  LIQUID,
  SOLID,
  CONSUMABLE_SOLID,
}ElementType;

typedef struct Cell{
  Vector2 pos;
  int direction;
  CellType type;
  ElementType element; 
  bool active;
  bool moved;
  bool isSolid;
  Color colour;
}Cell;

typedef struct User{
  CellType equippedType;
}User;

#endif
