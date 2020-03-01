#include "mystack.h"

#include <iostream>

MyStack::MyStack()
{

}

void MyStack::add(std::string str)
{
    for (int i = 0; i < 50; i++)
    {
        if (buffer[i].size() == 0)
        {
            buffer[i] = str;
            break;
        }
    }

//    std::cout << "Stack:    " << std::endl;
//    for (size_t i = 0; i < 50; i++)
//        std::cout << buffer[i] << std::endl;
}

void MyStack::deleteElement(int index)
{
//    auto iter = buffer.begin() + index;
//    buffer.erase(iter);
    buffer[index] = "";
    for (int i = index; i < 50; i++)
    {
        buffer[i] = buffer[i+1];
        if (buffer[i+1].size() == 0)
        {
            buffer[i] = "";
            break;
        }
    }
}

std::string* MyStack::returnBuffer()
{
    return buffer;
}

void MyStack::show()
{
    std::cout << "Stack:    " << std::endl;
    int counter = 0;
    while (buffer[counter].size() != 0)
    {
        std::cout << buffer[counter] << "   ";
        counter++;
    }
    std::cout << std::endl;

}

int MyStack::size()
{
    int size = 0;
    while (buffer[size].size() != 0)
        size++;

    return size;
}

std::string MyStack::value(int index)
{
    return buffer[index];
}

void MyStack::clean()
{
    for(int i = 0; i < 50; i++)
    {
        buffer[i] = "";
    }
}

void MyStack::replace(int index, std::string str)
{
    buffer[index] = str;
    buffer[index+1] = "";
}
