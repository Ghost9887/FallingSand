#ifndef CELLMOVEMENTS_H
#define CELLMOVEMENTS_H

#include "common.h"
#include "makeCell.h"

  void moveDown(int originalIndex, int targetIndex, Cell *cellArr);
  void moveDownRight(int originalIndex, int targetIndex, Cell *cellArr);
  void moveDownLeft(int originalIndex, int targetIndex, Cell *cellArr);
  void moveRight(int originalIndex, int targetIndex, Cell *cellArr);
  void moveLeft(int originalIndex, int targetIndex, Cell *cellArr);
  void moveUp(int originalIndex, int targetIndex, Cell *cellArr);
  void changeDirectionRandomly(Cell *cell);

#endif
