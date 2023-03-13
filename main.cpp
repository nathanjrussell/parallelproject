#include <iostream>
#include <vector>
#include "BinaryCode.h"
using namespace std;

int main(int argc, char *argv[]) {
  int len = atoi(argv[1]);
  char *genstringptr;
  if (len < 1) {
    cout <<"Code length must be greater than or equal to 1.\n";
    exit(1);
  }
  if (argc == 4) {
    if (argv[2][0] == 'g') {
      try {
        BinaryCode Code(len,argv[3]);
      } catch(char const *error) {
        cerr<<"Error: "<<error<<endl;
      }
    } else if (argv[2][0] == 'f') {
      int a = 1;
    } else {
      cout <<"Second argument must be 'g' or 'f'\n";
      exit(1);
    }
  } else {
    cout <<"Command Line arguments are not correct\n";
    exit(1);
  }
  return 0;
}
