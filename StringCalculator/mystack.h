#ifndef MYSTACK_H
#define MYSTACK_H

#include <vector>
#include <string>

typedef std::vector <std::string> Vec;

class MyStack
{
private:
    std::string buffer[50];
public:
    MyStack();
    void add(std::string);
    void deleteElement(int);
    std::string *returnBuffer();
    void show();
    int size();
    std::string value(int);
    void clean();
    void replace(int,std::string);
};

#endif // MYSTACK_H
