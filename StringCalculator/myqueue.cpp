#include "myqueue.h"

#include <iostream>

MyQueue::MyQueue()
{

}

void MyQueue::add(std::string str)
{
//    auto iter = buffer.begin();
//    buffer.insert(iter,str);
//    std::string temporaryBuffer;

    for (int i = 49; i > 0; i--)
    {
        if (buffer[i-1].size() != 0)
        {
            buffer[i] = buffer[i-1];
        }
    }
    buffer[0] = str;

//    std::cout << "Queue:    " << std::endl;
//    for (size_t i = 0; i < 50; i++)
//        std::cout << buffer[i] << " " << std::endl;
}

void MyQueue::show()
{
    std::cout << "Queue:    " << std::endl;
    int counter = 0;
    while (buffer[counter].size() != 0)
    {
        std::cout << buffer[counter] << "   ";
        counter++;
    }
    std::cout << std::endl;

}

int MyQueue::size()
{
    int size = 0;
    while (buffer[size].size() != 0)
        size++;

    return size;
}

std::string MyQueue::value(int index)
{
    return buffer[index];
}
