#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "mystack.h"
#include "myqueue.h"

class Parser
{
private:
    std::map <std::string,double> variables;
    std::vector <std::string> stringOfTokens;
    std::string alphabet;// = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
    std::string digits;// = {"0123456789"};
    std::string allowedSymbols;// = {"+-*/()"};
    std::string filename;// = "variables.txt";
    std::fstream file;
    bool isThereAnyVariables;// = false;
public:
    Parser();
    void analysis(std::string input);
    void distribution(MyQueue&, MyStack&);
    void checkSymbol(std::string, MyQueue&, MyStack&);
    void reversePolishNotation(MyQueue&,MyStack&);
    void remove(int,std::string*);
    void readFromFile();
    void writeToFile(std::string, std::string);
};

#endif // PARSER_H
