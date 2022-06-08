#include <iostream>

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
    {
    public:
        //bool 
        int count = 0;
        Node* current() { return curNode; }
        Node* first() { return head; }
        Node* last() { return tail; }
        void moveFirst() { curNode = head; }
        void moveLast() { curNode = tail; }
        void nextNode() { curNode = curNode.next; }
        void countNodes() { return count++; }


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

  void PushFront(const T& value)
  {
      Node* temp = new Node{ value };
      //temp->next = head;
      if (head != nullptr) 
      {
          head->prev = temp;
          temp->next = head;
          temp->prev = nullptr;
      }
      if (tail == nullptr) tail = head;
      head = temp;
  }

  void PushBack(const T& value)
  {
      Node* temp = new Node{ value };
      if (tail) tail->next = temp;
      if (head == nullptr) head = temp;
      tail = temp;
  }

  void Insert(const T& value, T& searchedVal)
  {
      Node* temp = new Node{ value };
      searchedVal.next->prev = temp;
      temp->next = searchedVal.next;
      searchedVal.next = temp;
      temp->prev = &searchedVal;
  }

  bool isEmpty() { return head == nullptr; }

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

  void PrintValues()
  {
      Node* last;

      
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
    //LinkedList<int>::Node node = list.PushFront(1);
    //list.PushFront(5);
    list.PushFront(1);
    auto print = [](LinkedList<int>::Node& node)
    {
        std::cout << node.data << std::endl;
    };



    //for(LinkedList<int>::Node nodes : list)
    //{

    //}

    //for(LinkedList<int>::Node b : list)
    //{
    //    std::cout << b.data << std::endl;
    //}
}