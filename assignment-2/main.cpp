#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector <string> data;
int X1 = 6, X2 = 1, Y1 = 1, Y2 = 6; //start coordinate

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
    int F;
  } data;
};

List *U_tail = nullptr;
List *Q_tail = nullptr;
List *Q_head = nullptr;
List *U_head = nullptr;

class Queue {
  public:
    bool empty(List *tail) { return tail == nullptr ? true : false; }
    void push(List **head, List **tail, int x, int y){
      // List *temp = new List;
      // temp->data.x = x;
      // temp->data.y = y;
      // int g = abs(X1 - x) + abs(Y1 - y);
      // int h = abs(X2 - x) + abs(Y2 - y);
      // temp->data.G = g;
      // temp->data.H = h;
      // int f = g + h;
      // temp->data.F = f;
      // temp->next = nullptr;
      // if (!(*head)) {
      //   temp->prev = nullptr;
      //   (*head) = temp;
      //   (*tail) = temp;
      // } else {
      //   temp->prev = (*tail);
      //   temp->next = nullptr;
      //   (*tail)->next = temp;
      //   (*tail) = temp;
      // }
      List *el = new List;
       int g = abs(X1 - x) + abs(Y1 - y);
       int h = abs(X2 - x) + abs(Y2 - y);
       int f = g + h;
       el->data.G = g;
       el->data.H = h;
       el->data.x = x;
       el->data.y = y;
       el->data.F = f;
       el->prev = nullptr;
       el->next = *tail;
       (*tail)->prev = el;
       *tail = el;
    }

    void print(List *head, List *tail){
      tail = head;
      while (tail) {
        cout << tail->data.x << " " << tail->data.y << endl;
        cout << "--------" << endl;
        tail = tail->next;
      }
    }

  void pop(List **head, List **tail){
    if ((*head) == (*tail)) {(*head) = (*tail) = nullptr;}
    else if ((*head)) {
        List *temp = (*head);
        (*head)->next->prev = nullptr;
        (*head) = (*head)->next;
        delete temp;
    }
  };

  bool include(List **head, List **tail, int x, int y){
  (*tail) = (*head);
  while((*tail)){
    if (((*tail)->data.x == x)&&((*tail)->data.y == y)) return true;
    (*tail) = (*tail)->next;
  }
  return false;
  }

  List *getMin(List **head){
    List *temp = *head;
    List *min_f = *head;
    while (temp -> next) {
      if (temp->data.F < min_f->data.F) {
        min_f = temp;
      }
    }
    swap(*head, min_f);
    swap((*head)->next, min_f->next);
    swap((*head)->prev, min_f->prev);
    return *head;
  }

};

void A_star(){
  Queue U; //visited queue
  Queue Q; //unvisited queue
  Q.push(&Q_head, &Q_tail, X1, X2);
  List *current;

 // while(!Q.empty(Q_tail)){
    current = Q.getMin(&Q_head);
    int c_x = current->data.x;
    int c_y = current->data.y;
    if ((c_x == X2) && (c_y == Y2)){
      cout << "Vse zaebis" << endl;
    }

    //Q.pop(&Q_head, &Q_tail);
    // U.push(&U_head, &U_tail, c_x, c_y);

    if (((U.include(&U_head, &U_tail, c_x-1, c_y) == false)||(gValue(c_x-1,c_y) < current->data.G))&&(U.include(&U_head, &U_tail, c_x-1,c_y) == false)){
      if (data[c_x-1][c_y] != 'X') Q.push(&Q_head, &Q_tail, c_x-1, c_y);
    }
    if (((U.include(&U_head, &U_tail, c_x+1, c_y) == false)||(gValue(c_x+1,c_y) < current->data.G))&&(U.include(&U_head, &U_tail, c_x+1,c_y) == false)){
      if (data[c_x+1][c_y] != 'X') Q.push(&Q_head, &Q_tail, c_x+1, c_y);
    }
    if (((U.include(&U_head, &U_tail, c_x, c_y+1) == false)||(gValue(c_x,c_y+1) < current->data.G))&&(U.include(&U_head, &U_tail, c_x,c_y+1) == false)){
      if (data[c_x][c_y+1] != 'X') Q.push(&Q_head, &Q_tail, c_x, c_y+1);
    }
    if (((U.include(&U_head, &U_tail, c_x, c_y-1) == false)||(gValue(c_x,c_y-1) < current->data.G))&&(U.include(&U_head, &U_tail, c_x,c_y-1) == false)){
      if (data[c_x][c_y-1] != 'X') Q.push(&Q_head, &Q_tail, c_x, c_y-1);
    }
    Q.print(Q_head, Q_tail);

// }
}


int main() {

  ifstream fin("input.txt");
  string line;



  while(getline(fin, line))
    data.push_back(line);
    A_star();

  // int x1 = 1, y1 = 6, x2 = 6, y2 = 1; // (x1, y1) - start point (x2, y2) - end point
  fin.close();
  return 0;
}
