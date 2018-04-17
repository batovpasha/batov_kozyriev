#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct List{
  struct {
    int g;
    int h;
  } data;
};

int main(int argc, char const *argv[]) {
  ifstream fin("input.txt");
  string n;
  vector <string> data;

  while(getline(fin,n)){
    data.push_back(n);
  }

  fin.close();
  return 0;
}
