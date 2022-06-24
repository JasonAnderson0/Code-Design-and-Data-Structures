#include <iostream>
#include <algorithm>
#include "raylib.h"
#include "raygui.h"

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS


template <typename T>
class LinkedList
{
 public:

    struct Node 
    {
    public:
      T data;
      Node* prev{ nullptr };
      Node* next{ nullptr };
      Color color = YELLOW;
      int posX = 80;
      int posY = 80;

      void Draw(int numb)
      {
          DrawRectangle(posX * numb,posY, 60, 60, color);
          DrawText((const char*)data, posX, posY, 20, BLACK);
      }
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
      while(iter != nullptr)
      {
          iter = iter->next;
          count++;
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
    LinkedList<int> list;
    int boxValue = 0;
    bool boxEdit = false;
    
    //for (LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next) \
    //{
    //    std::cout << node->data;

    //}

    //list.popFront();
    //list.popBack();
    //std::cout << std::endl;
    //for (LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next) \
    //{
    //    std::cout << node->data;

    //}
    //std::cout << list.Count();


    int screenWidth = 800;
    int screenHeight = 550;
    int numb = 0;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);



    while (!WindowShouldClose()) 
    {
        float delta = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, GUI_TEXT_ALIGN_CENTER);
        if (GuiValueBox(Rectangle{ 25,25,125,30 }, NULL, &boxValue, 0, 100, boxEdit)) boxEdit = !boxEdit;

        int count = 0;
        for (LinkedList<int>::Node* node = list.begin(); node != nullptr; node = node->next)
        {

            count++;
            node->Draw(count);
            if (node != nullptr && node->next != nullptr) 
            {
                DrawLine(node->posX, node->posY, node->next->posX, node->next->posY, BLACK);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}