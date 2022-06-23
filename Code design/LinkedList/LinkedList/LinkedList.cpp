#include <iostream>
#include <algorithm>
#include "raylib.h"

template <typename T>
class LinkedList
{
 public:

    struct Node 
    {
      T data;
      Node* prev{ nullptr };
      Node* next{ nullptr };
      Color color;
    };


  ~LinkedList() 
  {
      for(Node* node = head; node != nullptr;)
      {
          Node* next = node->next;
          delete node;
          node = next;
      }
  }

  //List nullptr <->Node1 <-> Node2 <-> nullptr

  bool isEmpty() { return (head == nullptr && tail==nullptr); }

  void PushFront(const T& value)
  {
      Node* temp = new Node{ value };
      if (head) 
      {
          temp->next = head;
          head->prev = temp;
      }
      if (tail == nullptr) tail = temp;
      head = temp;
  }

  void PushBack(const T& value)
  {
      Node* temp = new Node{ value };
      if (tail) 
      {
          tail->next = temp;
          temp->prev = tail;
      }
      if (head == nullptr) head = temp;
      tail = temp;
  }

  void Insert(T value,T searchedVal)
  {
      Node* temp = new Node{ value };
      auto iter = head;
      while (iter != tail) {
          if (iter->data = searchedVal) 
          {
              iter->next->prev = temp;
              temp->next = iter->next;
              iter->next = temp;
              temp->prev = iter;
              break;
          }
          else { iter = iter->next; }
      }

  }

  void popFront()
  {
      if (isEmpty())return;
      Node* temp = head->next;
      if (temp) temp->prev = nullptr;
      delete head;
      head = temp;

      if (isEmpty()) return;
  }

  void popBack()
  {
      if (isEmpty())return;
      Node* temp = tail->prev;
      if (temp) temp->next = nullptr;
      delete tail;
      tail = temp;
  }

  void popLocation(T& searchVal)
  {
      //use iterator to check if curNode == searchVal
      //if not then iterator++ until it is
      //when curNode == searchVal the nodes prev's next
      //= the nodes next. the nodes next's prev = 
      //nodes next then delete node

  }

  int Count() 
  {
      int count = 0;
      auto iter = head;
      while(iter != tail)
      {
          count++;
          iter->next;

      }
      return count;
  }

  Node* begin() {return head;}
  Node* end() { return tail; }


private:
     Node* head{ nullptr };
     Node* tail{ nullptr };
};

int main()
{
    int value = 5;
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(5);
    list.PushBack(2);
    list.Insert(4, value);

    for(LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next)
    {
        std::cout << node->data << std::endl;
    }
    if (list.isEmpty()) 
    {
       std::cout<<"Is empty";
    }
    else {
        std::cout << "Isn't empty" << list.Count();
    }

    
}