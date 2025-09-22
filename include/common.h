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

#define CELL_SIZE 2 
#define GRID_WIDTH (SCREEN_WIDTH / CELL_SIZE)
#define GRID_HEIGHT (SCREEN_HEIGHT / CELL_SIZE)
#define AMOUNT_OF_CELLS (GRID_WIDTH * GRID_HEIGHT)

#define BRUSH_RADIUS 1

#define MAX_WATER_TEMP 100
#define MELTING_POINT_OF_WOOD 1000 //not accurate
#define MELTING_POINT_OF_STONE 1300
#define MELTING_POINT_OF_SAND 1700

typedef enum CellType{
  EMPTY,
  SAND,
  WET_SAND,
  GLASS,
  VOLCANIC_GLASS,
  DIRT,
  WET_DIRT,
  WATER,
  SMOKE,
  WATER_VAPOR,
  STONE,
  WOOD,
  LAVA
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
  float temp;
  int vescocity;
  bool isSolid;
  bool moved;
  bool active;
}Cell;

typedef struct User{
  CellType equippedType;
}User;

#endif
