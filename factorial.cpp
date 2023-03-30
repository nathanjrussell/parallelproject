#include <iostream>
using namespace std;
int factorial(int n) {
  int result = 1;
  for (int i=1; i<=n; ++i) {
    result *= i;
  }
  return result;
}

void printResult(int k, int n) {
  int poss = factorial(n)/(factorial(n-k) * factorial(k));
  cout<<"The number of possible outcomes for choosing ";
  cout<<k<<" items from "<<n<<" items is "<<poss<<endl;
}

int main(int argc, char *argv[]) {
  printResult(4,6);
  printResult(5,9);
  printResult(3,11);
  printResult(8,12);
  printResult(8,15);
  cout<<factorial(15)<<endl;
}
