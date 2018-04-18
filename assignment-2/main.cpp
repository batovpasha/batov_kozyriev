#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int X1 = 1, X2 = 6, Y1 = 6, Y2 = 1; //start coordinate

int gValue (int x, int y) {
  return abs(X1 - x) + abs(Y1 - y);
}

struct List {
  List *prev;
  List *next;
  struct {
    int x;
    int y;
    int G;
    int H;
  } data;
};

class Queue {
  public:
      bool empty(List *tail) { return tail == nullptr ? true : false; }
      void print(List *tail) {
        List *mid = tail;
        while (mid->next) {
            cout << mid->data.x << " " << mid->data.y << endl;
            cout << mid->data.G << " " << mid->data.H << endl;
            mid = mid->next;
        }
      }
      void push(List **tail, int x, int y) {
        List *el = new List;
        int g = abs(X1 - x) + abs(Y1 - y);
        int h = abs(X2 - x) + abs(Y2 - y);
        el->data.G = g;
        el->data.H = h;
        el->data.x = x;
        el->data.y = y;
        el->prev = nullptr;
        el->next = *tail;
        (*tail)->prev = el;
        *tail = el;
      }
      void pop(List **tail) {
        List *temp = *tail;
        (*tail)->prev->next = nullptr;
        *tail = (*tail)->prev;
        delete temp;
      }
      bool include(List **tail, int x, int y){
        List *mid = *tail;
        while(mid){
          if ((mid->data.x == x)&&(mid->data.y == y)) return true;
          mid = mid->next;
        }
        return false;
      }
};

void A_star(List **start, List **goal){
  List *U_tail = new List;
  List *Q_tail = new List;

  Queue U; //visited queue
  Queue Q; //unvisited queue
  Q.push(&Q_tail, X1, Y1);
  Q.print(Q_tail);

  while(!Q.empty(Q_tail)){
    List *current = Q_tail;
    int c_x = current->data.x;
    int c_y = current->data.y;
    if ((current->data.x == X2) && (current->data.y == Y2))
      cout << "Vse zaebis" << endl;

    Q.pop(&current);
    U.push(&U_tail, current->data.x, current->data.y);
    if (U.include(&U_tail, c_x-1, c_y) && gValue(c_x-1,c_y) >= current->data.G);
    if (!U.include(&U_tail, c_x-1, c_y) || gValue(c_x-1,c_y) < current->data.G){
      if (!Q.include(&Q_tail, c_x-1,c_y)) Q.push(&Q_tail, c_x-1,c_y);
    }

  }
}


int main() {
  List *tail = nullptr;
  List *start = new List;
  List *goal = new List;

  ifstream fin("input.txt");
  string line;
  vector <string> data;

  A_star(&start, &goal);

  while(getline(fin, line))
    data.push_back(line);

  // int x1 = 1, y1 = 6, x2 = 6, y2 = 1; // (x1, y1) - start point (x2, y2) - end point
  fin.close();
  return 0;
}
