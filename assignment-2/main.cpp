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
      bool empty(List *head) {
        return head == nullptr ? true : false;
      }
      void print(List *head) {
        List *mid = head;
        while (mid) {
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
  head = first_point;
  Queue queue;
  queue.push(&head, 23, 43);
  ifstream fin("input.txt");
  string line;
  vector <string> data;

  while(getline(fin, line))
    data.push_back(line);

  int x1 = 6, y1 = 1, x2 = 1, y2 = 6; // (x1, y1) - start point (x2, y2) - end point
  cout << queue.empty(head) << endl;
  fin.close();
  return 0;
}
