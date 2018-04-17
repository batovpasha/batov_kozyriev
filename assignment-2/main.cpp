#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct List {
  List *prev;
  List *next;
  struct {
    int G;
    int H;
  } data;
};

class Queue {
  public:
      void print(List *head) {
        List *mid = head;
        while(mid) {
            cout << mid->data.G << " " << mid->data.H << endl;
            mid = mid->next;
        }
      }
      void push(List **head, int g, int h) {
        List *el = new List;
        el->data.G = g;
        el->data.H = h;
        el->prev = nullptr;
        el->next = *head;
        (*head)->prev = el;
        *head = el;
      }
      void pop(List **tail) {
        List *temp = *tail;
        (*tail)->prev->next = nullptr;
        *tail = (*tail)->prev;
        delete temp;
      }
};

int main() {
  List *head = nullptr;
  List *first_point = new List;
  Queue queue;

  ifstream fin("input.txt");
  string n;
  vector <string> data;

  while(getline(fin,n)){
    data.push_back(n);
  }




  fin.close();
  return 0;
}
