//BinaryCode.h
#ifndef BINARYCODE_H
#define BINARYCODE_H

class BinaryCode
{
  private:
    int len;
    int dim;
    int *gen_mat;
    int *wt_dist;
    int *punct_wt_dist;

  public:
    ~BinaryCode();
    BinaryCode(int length, char *genString);

};

#endif
