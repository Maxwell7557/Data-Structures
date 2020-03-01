#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <vector>
#include <string>

class MyQueue
{
private:
//    std::vector <std::string> buffer;
    std::string buffer[50];
public:
    MyQueue();
    void add(std::string);
    void show();
    int size();
    std::string value(int);
};

#endif // MYQUEUE_H
