#ifndef MAKECELL_H
#define MAKECELL_H

#include "common.h"

  Cell createEmptyCell(int posX, int posY);
  void createSand(Cell *cell);
  void createWetSand(Cell *cell);
  void createDirt(Cell *cell);
  void createWetDirt(Cell *cell);
  void createWater(Cell *cell);
  void createLava(Cell *cell);
  void createStone(Cell *cell);
  void createWood(Cell *cell);
  void createGlass(Cell *cell);
  void createVolcanicGlass(Cell *cell);
  void createSmoke(Cell *cell);
  void createWaterVapor(Cell *cell);

#endif
