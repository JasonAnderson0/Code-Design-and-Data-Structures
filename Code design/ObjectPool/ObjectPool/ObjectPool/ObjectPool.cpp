#include <iostream>
#include "Pool.h"
#include "GameObject.h"

int main()
{
    unsigned int size = 20;
    Pool<GameObject> objp(size);


    for (GameObject object : objp.GetActive()) 
    {
        std::cout << "No";
    }

    for (int i = 0; i < objp.GetInActive().size(); i++) 
    {
        std::cout << objp.GetIndex(i).GetData()<< " ";

    }
    std::cout << std::endl;

    objp.move(objp.GetIndex(2));

    for (int i = 0; i < objp.GetInActive().size(); i++)
    {
        std::cout << objp.GetIndex(i).GetData() << " ";
    }
    std::cout << std::endl;

    for (int i = 0; i < objp.GetActive().size(); i++) {
        std::cout << objp.GetIndex(i).GetData() << " ";
    }
}