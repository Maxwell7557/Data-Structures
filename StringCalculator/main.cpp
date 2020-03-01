#include <iostream>
#include <vector>
#include "parser.h"
#include "mystack.h"
#include "myqueue.h"

using namespace std;

int main(int argc, char* argv[])
{
    MyStack stack;
    MyQueue queue;
    Parser parser;

    string input;
    string variable;
    string arg = argv[1];
    if (arg == "--expression") // !!!
    {
        input = argv[2];
//        cout << input << endl;
        parser.analysis(input);
        parser.distribution(queue,stack);
    }
    else if (arg == "--variable")
    {
        variable = argv[2];
        int pos = 0;
        for (int i = 0; i < variable.size(); i++)
        {
            if (variable[i] == '=')
            {
                pos = i;
                break;
            }
        }
        parser.writeToFile(variable.substr(0,pos),variable.substr(pos+1));
    }

//    cout << "Enter an expression" << endl;
//    cin >> input;

//    parser.analysis(input);
//    parser.distribution(queue,stack);

//    parser.readFromFile();
//    parser.writeToFile("kek","22");
//    parser.readFromFile();

//    cout << "End of main function" << endl;

    return 0;
}
