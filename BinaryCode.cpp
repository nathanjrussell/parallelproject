// BinaryCode.cpp
#include <iostream>
#include "BinaryCode.h"

using namespace std;

BinaryCode::~BinaryCode() {

  if (gen_mat != NULL) { //check if gen_mat was allocated
    delete[] gen_mat; //deallocate space
  } //close gen_mat if statement
  //wt_dist mem not allocated till calculated
  if (wt_dist != NULL) { //check if allocated
    delete[] wt_dist; //deallocate space
  } // close wt_dist if statement
  //punct_wt_dist not allocated till calculated
  if (punct_wt_dist != NULL) { //check if allocated
      delete[] punct_wt_dist; //deallocate space
  } //close punct_wt_dist statement
} //close ~BinaryCode()

//constructor when length and generator matrix given as char array
BinaryCode::BinaryCode(int length, char * genString) {
  int totalCount = 0; //count total number of bits in gen_matrix
  len = length; //length of code (length of rows in gen matrix)
  int i = 0; //iterating variable
  while (genString[i] != '\0') { //iterate till null character
    //check if bits are actually ones or zeros
    if (genString[i] == '0' || genString[i] == '1') {
      ++totalCount; //increment every valid bit for verification later
    } else { //close and open if/else genstring[i] ==  1 || 0 statement
      //throw exception if a nonbinary digit (1 or 0) was found.
      throw "Invalid bit found. Bits must be either a 0 or 1";
    } //close else statement of genstring[i] == 1,0 statement
    ++i; //increment iteration variable
  } //close while genstring[i] not null char statement
  //total bit count must be a multiple of length
  if (totalCount%length != 0) {
    //thow exception if total bits is not a multiple of length
    throw "Total number of bits must be a multiple of the length";
  } //close if checking totalcount multiple of length statement
  dim = totalCount/length; //determine dimension from length
  gen_mat = new int[length*dim]; //allocate space for generator matrix
  for (i = 0; i<totalCount; ++i) { //iterate over all bits received
    //determine if bit is a one or zero and set generator matrix accordingly
    if  (genString[i] ==  '0') {
      gen_mat[i] = 0; //set bit to zero
    } else { //open/close if/else statement checking whether bit 1 or 0
      gen_mat[i] = 1; //set bit to one
    } //close else
  } //close for loop
} //close BinaryCode(length, genstring)

//print general weight distribution of code
void BinaryCode::printWtDist() {
  //check if wt dist has been calculated by checking if space allocated
  if (wt_dist == NULL) {
    BinaryCode::calcWtDist(); //if not calculated then calculate wt_dist
  } //close if (checking if wt_dist ptr is null)
  //iterate over all items in array
  for (int wt=0; wt<len+1; ++wt) {
    cout<<"Weight "<<wt<<": "<<wt_dist[wt]<<endl; //print individual wt dist
  } //close for loop
} //close printWtDist()

//calculate hamming wt of a code (perhaps should be inlined)
int BinaryCode::hammingWeight(int *codeWord) {
  int popCount = 0; //initialize hamming weight to zero
  for (int col=0; col<len; ++col) { //iterate over codeword bits
    popCount += codeWord[col]; //add zero or one to the total
  } //close for loop
  return popCount; //return hamming weight
} //close hammingWeight( codeword)


//calculate weight distribution of code.
void BinaryCode::calcWtDist() {
  //check if wt dist has been calculated by checking if space allocated
  if (wt_dist != NULL) {
    return void(); //if allocated, wt dist has already been calculated
  } //close if statement checking if wt_dist is null
  int popCount; //hammingweight of codeword
  int *codeWord = new int[len](); //allocate space for codeword
  int numCodewords = 1 << dim; //number of codewords is 2^dim;
  wt_dist = new int[len+1]; //allocate space for wt_dist
  //iterate through all possible gen matrix linear combinations
  for (int linearComb =0; linearComb<numCodewords; ++linearComb) {
    //reset codeword to array of zeros
    for (int j=0; j<len; ++j) { //
      codeWord[j] = 0; //set inidividual bit coordiates to zero
    } //close for loop initializing codeword bits to zero
    //iterate over gen rows to see if it is part of linear combination
    for (int genRow = 0; genRow<dim; ++genRow) {
      //check if row of generator matrix is part of linear combination
      if (linearComb & (1 << genRow)) {
        //iterate through columns
        for (int col = 0; col<len; ++col) {
          //addition over Field GF(2) is equivalent to XOR
          codeWord[col] ^= gen_mat[genRow*len + col];
        } //close foor loop XOR
      } //close if statement checking if gen row is part of linear combination
    } //close for loop iterating over generator matrix rows
    popCount = hammingWeight(codeWord); //get the hammingweight of codeword
    ++wt_dist[popCount]; //increment array element representing hamming wt
  } //close for loop iterating over linear combinations
  return void(); //return void for void function
} //close calcWtDist()

//calculate double punctured wt distribution of code (and single punct)
void BinaryCode::calcPunctWtDist() {
  //check if punct_wt_dist has already been calculated by checking if allocated
  if (punct_wt_dist != NULL) {
    return void(); //if space allocated then punct wt dist already calculated
  } //close if statement checking if punct_wt_dist ptr is null
  int popCount; //hamming weight of codeword
  int *codeWord = new int[len]; //allocate space for codeword
  int numCodewords = 1 << dim; //number of codewords is 2^dim;
  //allocate space for punct_wt_dist and initialize to zero
  punct_wt_dist = new int[len*len*(len+1)](); //allocate space and zero
  //iterate over all possible pairs of coordinates (order does not matter)
  for (int punct1 = 0; punct1<len; ++punct1) { //iterate over all coordinates
    //iterate over all coordinates greater than equal to punct1
    for (int punct2 = punct1; punct2<len; ++punct2) {
      //iterate over all linear combinations
      for (int linearComb =0; linearComb<numCodewords; ++linearComb) {
        //reset codeword to array of zeros
        for (int j=0; j<len; ++j) {
          codeWord[j] = 0; //set inidividual codeword bits to zero
        } //close for loop that sets codeword bits to zero
        //iterate over gen rows to see if it is part of linear combination
        //iterate over all rows of generating matrix
        for (int genRow = 0; genRow<dim; ++genRow) {
          if (linearComb & (1 << genRow)) { //check if gen row is in linear comb
            //iterate through columns
            for (int col = 0; col<len; ++col) {
              //check if cols have NOT been punctured out
              if (col != punct1 && col != punct2){
                //addition over GF(2) is equivalent to XOR
                codeWord[col] ^= gen_mat[genRow*len + col];
              } //close if XOR that checks whether cols are punctured
            } //close for loop iterating over columns
          } //close if statement checking whether gen row is part of lin comb
        } //close for loop iterating over genenerating matrix rows
        popCount = hammingWeight(codeWord); //calculate hammingwt of codeword
        //increment punct_wt_dist representing puncture and hammingweight
        ++punct_wt_dist[punct1*len*(len+1) + punct2*(len+1) + popCount];
      } //close for loop iterating over all possible linear combinations
    } //close for loop representing second column puncture
  } //close for loop representing first column puncture
  return void(); //return void for void function
} //close calcPunctWtDist()
