#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector <string> data;
vector <int> path;
int X1 = 6, X2 = 1, Y1 = 1, Y2 = 6; //start coordinate
int points = 0;

int gValue (int x, int y) {
  return abs(X1 - x) + abs(Y1 - y);
}

struct List {
  List *prev;
  List *next;
  struct {
    int p;
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
    void q_push(List **head, List **tail, int x, int y, int p){
      List *temp = new List;
      temp->data.x = x;
      temp->data.y = y;
      points++;
      path.push_back(p);
      temp->data.p = points;
      int g = abs(X1 - x) + abs(Y1 - y);
      int h = abs(X2 - x) + abs(Y2 - y);
      temp->data.G = g;
      temp->data.H = h;
      int f = g + h;
      temp->data.F = f;
      temp->next = nullptr;
      if (!(*head)) {
        temp->prev = nullptr;
        temp->next = nullptr;
        (*head) = temp;
        (*tail) = temp;
      } else {
        temp->prev = (*tail);
        temp->next = nullptr;
        (*tail)->next = temp;
        (*tail) = temp;
      }
    }

    void u_push(List **head, List **tail, int x, int y){
      List *temp = new List;
      temp->data.x = x;
      temp->data.y = y;
      int g = abs(X1 - x) + abs(Y1 - y);
      int h = abs(X2 - x) + abs(Y2 - y);
      temp->data.G = g;
      temp->data.H = h;
      int f = g + h;
      temp->data.F = f;
      temp->next = nullptr;
      if (!(*head)) {
        temp->prev = nullptr;
        temp->next = nullptr;
        (*head) = temp;
        (*tail) = temp;
      } else {
        temp->prev = (*tail);
        temp->next = nullptr;
        (*tail)->next = temp;
        (*tail) = temp;
      }
    }

    void print(List *head){
      List *temp = head;
      while (temp) {
        cout << temp->data.x << " " << temp->data.y << " " << temp->data.p << endl;
        cout << "--------" << endl;
        temp = temp->next;
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

  void getMin(List **head){
    List *temp = *head;
    List *min_f = *head;
    while (temp) {
      if (temp->data.F < min_f->data.F) {
        min_f = temp;
      }
      temp = temp->next;
    }
    swap(min_f->data.x, (*head)->data.x);
    swap(min_f->data.y, (*head)->data.y);
    swap(min_f->data.G, (*head)->data.G);
    swap(min_f->data.H, (*head)->data.H);
    swap(min_f->data.F, (*head)->data.F);

  }

  bool include(List **head, List **tail, int x, int y){
  List *temp = (*head);
  while(temp){
    if ((temp->data.x == x)&&(temp->data.y == y)) return true;
    temp = temp->next;
  }
  return false;
  }

};



void A_star(){
  Queue U; //visited queue
  Queue Q; //unvisited queue
  Q.q_push(&Q_head, &Q_tail, X1, X2, 1);
  Q.getMin(&Q_head);
  List *current;

  while(!Q.empty(Q_tail)){
    Q.getMin(&Q_head);
    current = Q_head;
    int c_x = current->data.x;
    int c_y = current->data.y;
    int c_p = current->data.p;
    cout << c_x << " " << c_y << " " << path[c_p - 1] << endl;
    if ((c_x == X2) && (c_y == Y2)){
      cout << "Vse zaebis" << endl;
      cout << "Sha vivedem put'" << endl;
      return;
    }
    Q.pop(&Q_head, &Q_tail);
    U.u_push(&U_head, &U_tail, c_x, c_y);
    if (((U.include(&U_head, &U_tail, c_x-1, c_y) == false)||(gValue(c_x-1,c_y) < current->data.G))&&(U.include(&U_head, &U_tail, c_x-1,c_y) == false)){
      if (data[c_x-1][c_y] != 'X') Q.q_push(&Q_head, &Q_tail, c_x-1, c_y, c_p);
    }
    if (((U.include(&U_head, &U_tail, c_x+1, c_y) == false)||(gValue(c_x+1,c_y) < current->data.G))&&(U.include(&U_head, &U_tail, c_x+1,c_y) == false)){
      if (data[c_x+1][c_y] != 'X') Q.q_push(&Q_head, &Q_tail, c_x+1, c_y, c_p);
    }
    if (((U.include(&U_head, &U_tail, c_x, c_y+1) == false)||(gValue(c_x,c_y+1) < current->data.G))&&(U.include(&U_head, &U_tail, c_x,c_y+1) == false)){
      if (data[c_x][c_y+1] != 'X') Q.q_push(&Q_head, &Q_tail, c_x, c_y+1, c_p);
    }
    if (((U.include(&U_head, &U_tail, c_x, c_y-1) == false)||(gValue(c_x,c_y-1) < current->data.G))&&(U.include(&U_head, &U_tail, c_x,c_y-1) == false)){
      if (data[c_x][c_y-1] != 'X') Q.q_push(&Q_head, &Q_tail, c_x, c_y-1, c_p);
    }
 }

}


int main() {

  ifstream fin("input.txt");
  string line;



  while(getline(fin, line)){
    data.push_back(line);
  }

  A_star();

  // int x1 = 1, y1 = 6, x2 = 6, y2 = 1; // (x1, y1) - start point (x2, y2) - end point
  fin.close();
  return 0;
}
