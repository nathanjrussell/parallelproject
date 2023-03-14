//BinaryCode.h
#ifndef BINARYCODE_H
#define BINARYCODE_H

#include <cstddef> //simply allows macro that sets NULL=0

//class that defines BinaryCode
class BinaryCode
{
  //private members and methods
  private:
    int len; //length of code (length of rows in generating matrix)
    int dim; //dimension of code (number of rows in generating matrix)
    int *gen_mat = NULL; //allocate space for rows of generating matrix
    int *wt_dist = NULL; //allocate space for wt distribution of code
    int *punct_wt_dist = NULL; //allocate space for punct_wt_dist(twice) of code

    //private Functions
    int hammingWeight(int *codeword); //calculate hamming weight of codeword

  //public members and methods
  public:
    ~BinaryCode(); //destructor checks and deallocates space
    BinaryCode(int length, char *genString); //constructor given len and gen
    void calcWtDist(); //calculate wt distriibution of code
    void calcPunctWtDist(); //calculate wt distribution of code

    //functions that return values
    int getWtDistComp(int wt); //returns the number of codwords having weight wt
    int getWtDistComp(int col1, int col2, int wt); //wt dist comp

    //Functions that print output
    void printWtDist(); //print weight distribution of code
    void print2punctWtDist(); //prints entire twice punctured wt distribution
    void print2punctWtDist(int col1,int col2); //prints dist for two col punct
}; //close class BinaryCode

#endif
