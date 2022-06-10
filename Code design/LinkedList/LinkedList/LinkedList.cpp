#include <iostream>
#include <algorithm>

template <typename T>
class LinkedList
{
 public:

    struct Node 
    {
      T data;
      Node* prev{ nullptr };
      Node* next{ nullptr };
    };

    struct Iterator 
    { //look at map/multimap for iterator thing
    public:
        //bool 
        int count = 0;
        Node* current() { return curNode; }
        Node* first() { return head; }
        Node* last() { return tail; }
        void moveFirst() { curNode = head; }
        void moveLast() { curNode = tail; }
        void nextNode() { curNode = curNode.next; }
        //void countNodes() { }


    private:
        Node* curNode;
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

  bool isEmpty() { return head == nullptr; }

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

  void Insert(const T& value,  T& searchedVal)
  {
      Node* temp = new Node{ value };
      searchedVal->next->prev = temp;
      temp->next = searchedVal.next;
      searchedVal->next = temp;
      temp->prev = &searchedVal;
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

  Node* begin() {return head;}
  Node* end() { return tail; }


private:
     Node* head{ nullptr };
     Node* tail{ nullptr };
};

int main()
{
    LinkedList<int> list;
    list.PushFront(1);
    list.PushFront(5);
    list.PushBack(2);
    list.Insert(4, 1);

    for(LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next)
    {
        std::cout << node->data << std::endl;
    }

    

}