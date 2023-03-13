// BinaryCode.cpp
#include "BinaryCode.h"

BinaryCode::~BinaryCode() {
  delete[] gen_mat;
  delete[] wt_dist;
  delete[] punct_wt_dist;
}

BinaryCode::BinaryCode(int length, char * genString) {
  int totalCount = 0;
  len = length;
  int i = 0;
  while (genString[i] != '\0') {
    if (genString[i] == '0' || genString[i] == '1') {
      ++totalCount;
    } else {
      throw "Invalid bit found. Bits must be either a 0 or 1";
    }
    ++i;
  }
  if (totalCount%length != 0) {
    throw "Total number of bits must be a multiple of the length";
  }
  dim = totalCount/length;
  wt_dist = new int[length+1]();
  punct_wt_dist = new int[length*length*(length+1)]();
  gen_mat = new int[length*dim];
  for (i = 0; i<totalCount; ++i) {
    if  (genString[i] ==  '0') {
      gen_mat[i] = 0;
    } else {
      gen_mat[i] = 1;
    }
  }
}
