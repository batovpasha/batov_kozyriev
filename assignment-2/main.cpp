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
  first_point->data.G = 12;
  first_point->data.H = 15;
  head = first_point;
  List *tail = first_point;
  cout << first_point->data.G << endl;
  Queue queue;
  queue.push(&head, 15, 20);
  queue.push(&head, 325, 430);
  queue.push(&head, 1115, 255);
  queue.push(&head, 143, 50);
  queue.print(head);
  cout << endl;
  queue.pop(&tail);
  queue.pop(&tail);
  queue.print(head);
  return 0;
}
