#include <iostream>
#include <vector>
#include "BinaryCode.h"

using namespace std;

int main(int argc, char *argv[]) {
  int len = atoi(argv[1]); //command line argument giving code length
  char inputTypeFlag = argv[2][0]; //command line representing type passed
  //check if code length is a value greater than zero
  if (len < 1) {
    cout <<"Code length must be greater than or equal to 1.\n"; //error msg
    exit(1); //exit with error
  } //close if statement checking if len<1
  //check that exactly three command line arguments have been given
  if (argc == 4) {
    switch (inputTypeFlag) {

      case 'g'://g means string was provided for generator matrix
        try { //try the following code
          BinaryCode Code(len,argv[3]); //create binary code class
          Code.calcWtDist(); //calculate code wt distribution
          Code.printWtDist(); //print code wt distribution
          Code.calcPunctWtDist(); //calculate twice punct wt distr
        } catch(char const *error) { //catch errors
          cerr<<"Error: "<<error<<endl; //print error message
        } //close catch
        break;

      case 'f': //f means file was passed for generator
        break;

      default: //default case for switch
        cout <<"Second argument must be 'g' or 'f'\n";
        exit(1);
    } //close switch
  } else { //if/else for argc=4
    cout <<"Command Line arguments are not correct\n"; //error msg
    exit(1); //exit with error
  } //close else for argc=4
  return 0; //successful exit
} //close main()
