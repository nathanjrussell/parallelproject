// BinaryCode.cpp
#include "BinaryCode.h"

BinaryCode::BinaryCode(int x,int y)
{
  gx = x;
  gy = y;
}

int BinaryCode::getSum()
{
  return gx + gy;
}
