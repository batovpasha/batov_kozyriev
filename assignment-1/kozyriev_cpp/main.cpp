#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
using namespace std;

void sortAndRate(int arr[][2], int n, int res[]){
  for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        if (arr[i][0] > arr[j][0]){
          swap(arr[i],arr[j]);
      }
    }
  }
  res[arr[0][1]] += 12;
  res[arr[1][1]] += 10;
  for (int i = 2; i < 10; i++){
   res[arr[i][1]] += 10-i;
  }
}

int main() {
  ifstream fin;
  fin.open("eurovision.csv");
  ofstream fout("results.csv");

  vector<string>data;
  string line;

  while(getline(fin,line)){
    data.push_back(line);
  }
  string all_countries[data.size()];
  string points[data.size()][data.size()];
  int column[data.size()][2];
  int results[data.size()];

  for (int i = 0; i < data.size(); i++){
    results[i] = 0;
  }

   for (int i = 0; i < data.size(); i++){
     stringstream ss(data[i]);
     string token;
     int counter = 0;
     while(getline(ss, token, ',')) {
       if (counter == 0) {
         all_countries[i] = token;
         counter++;
         continue;
       } else {
         points[i][counter - 1] = token;
         counter++;
       }
     }
   }

   for (int j = 0; j < data.size(); j++){
     for (int i = 0; i < data.size(); i++){
       column[i][0] = stoi(points[i][j]);
       column[i][1] = i;
     }
     sortAndRate(column, data.size(), results);
   }




   for (int i = 0; i < data.size(); i++) {
     for (int j = 0; j < data.size(); j++){
       if (results[i] > results[j]) {
         swap(results[i],results[j]);
         swap(all_countries[i],all_countries[j]);
       };
     }
   }

   for (int i = 0; i < 10; i++) {
     fout << all_countries[i] <<','<< results[i] << endl;
   }



  fin.close();
  fout.close();
}
