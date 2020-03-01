#include "parser.h"
#include <iostream>

Parser::Parser()
{
    alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    digits = "0123456789";
    allowedSymbols = "+-*/()";
    filename = "variables.txt";
    isThereAnyVariables = false;
}

void Parser::analysis(std::string input)
{
    std::string token;
    bool isTokenFound = false;

    for (int i = 0; i < input.size(); i++)
    {
        if ((input[i] == '-' && i == 0) || (input[i] == '-' && input[i-1] && i == 1) || (input[i-1] == '(' && input[i] == '-') && isTokenFound == false)  // С унарным минусом
        {
            bool isItWhole = false;
            token.push_back(input[i]);
            while (isItWhole == false)
            {
                i++;
                if (i > input.size())
                    break;

                bool isItSymbol = false;
                for (int k = 0; k < alphabet.size(); k++)       //
                {
                    if (input[i] == alphabet[k])
                        isThereAnyVariables = true;
                }
                for (int j = 0; j < allowedSymbols.size(); j++)
                {
                    if (input[i] == allowedSymbols[j])
                    {
                        isItSymbol = true;
                        break;
                    }
                }

                if (isItSymbol == false)
                    token.push_back(input[i]);
                else
                {
                    i--;
                    isItWhole = true;
                }
            }
            isTokenFound = true;
        }

        for (size_t k = 0; k < digits.size(); k++) // Числа
        {
            if (input[i] == digits[k] && isTokenFound == false)
            {
                bool isItWhole = false;
                token.push_back(input[i]);
                while (isItWhole == false)
                {
                    bool isItNumber = false;
                    i++;
                    for (int j = 0; j < digits.size(); j++)
                    {
                        if (input[i] == digits[j] || input[i] == '.')
                        {
                            token.push_back(input[i]);
                            isItNumber = true;
                            break;
                        }
                    }

                    if (isItNumber == false)
                    {
                        i--;
                        isItWhole = true;
                    }
                }
                isTokenFound = true;
            }
        }

        for (size_t k = 0; k < alphabet.size(); k++) // Переменные
        {
            if (input[i] == alphabet[k] && isTokenFound == false)
            {
                bool isItWhole = false;
                token.push_back(input[i]);
                isThereAnyVariables = true;     //
                while (isItWhole == false)
                {
                    i++;
                    bool isItLetter = false;
                    for (int j = 0; j < alphabet.size(); j++)
                    {
                        if (input[i] == alphabet[j])
                        {
                            isItLetter = true;
                            token.push_back(input[i]);
                        }
                    }

                    if (isItLetter == false)
                    {
                        i--;
                        isItWhole = true;
                    }
                }
                isTokenFound = true;
            }
        }

        for (size_t z = 0; z < allowedSymbols.size(); z++)
        {
            if (input[i] == allowedSymbols[z] && isTokenFound == false)
            {
                isTokenFound = true;
                token.push_back(input[i]);
                break;
            }
        }

//        std::cout << token << std::endl;
        stringOfTokens.push_back(token);
        isTokenFound = false;
        token.clear();
    }

}

void Parser::distribution(MyQueue& queue, MyStack& stack)
{
    bool isItDefined = false;

    for (size_t i = 0; i < stringOfTokens.size(); i++)
    {
        if (stringOfTokens[i].size() > 1 && isItDefined == false)
        {
            queue.add(stringOfTokens[i]);
            isItDefined = true;
        }

        for (size_t q = 0; q < allowedSymbols.size(); q++)
        {
            if (stringOfTokens[i][0] == allowedSymbols[q] && isItDefined == false)
            {
                checkSymbol(stringOfTokens[i],queue,stack);
                isItDefined = true;
            }

        }

        if (isItDefined == false)
        {
            queue.add(stringOfTokens[i]);
            isItDefined = true;
        }

        isItDefined = false;
    }

//    std::cout << "End of distribution" << std::endl;

    reversePolishNotation(queue,stack);
}

void Parser::checkSymbol(std::string str, MyQueue& queue, MyStack& stack)
{
    std::string* buffer = stack.returnBuffer();

    if (stack.size() == 0 || str[0] == '(')
    {
        stack.add(str);
    }
    else
    {

        if (str[0] == '*' || str[0] == '/')
        {
            if (buffer[stack.size()-1][0] == '-' || buffer[stack.size()-1][0] == '+' ||
                buffer[stack.size()-1][0] == '(' || buffer[stack.size()-1][0] == ')')
            {
                stack.add(str);
            }
            else
            {
                bool isItSolved = false;
                while (isItSolved == false)
                {
                    int i = stack.size()-1;
                    if (buffer[i][0] == '/' || buffer[i][0] == '*')
                    {
                        queue.add(buffer[i]);

                        remove(i,buffer);
                        stack.deleteElement(i);
                    }
                    else
                    {
                        stack.add(str);
                        isItSolved = true;
                        break;
                    }
                    i--;
                    if (i < 0)
                    {
                        stack.add(str);
                        isItSolved = true;
                    }
                }
            }


        }

        if (str[0] == '+' || str[0] == '-')
        {
            if (buffer[stack.size()-1][0] == '(' || buffer[stack.size()-1][0] == ')')
            {
                stack.add(str);
            }
            else
            {
                bool isItSolved = false;
                while (isItSolved == false)
                {
                    int i = stack.size()-1;
                    if (buffer[i][0] == '/' || buffer[i][0] == '*' || buffer[i][0] == '+' || buffer[i][0] == '-')
                    {
                        queue.add(buffer[i]);

                        remove(i,buffer);
                        stack.deleteElement(i);
                    }
                    else
                    {
                        stack.add(str);
                        isItSolved = true;
                        break;
                    }
                    i--;
                    if (i < 0)
                    {
                        stack.add(str);
                        isItSolved = true;
                    }
                }
            }


        }

        if (str[0] == ')')
        {
            bool isItSolved = false;
            while (isItSolved == false)
            {
                int i = stack.size()-1;
                if (buffer[i][0] != '(')
                {
                    queue.add(buffer[i]);

                    remove(i,buffer);
                    stack.deleteElement(i);
                }
                else if (buffer[i][0] == '(')
                {
                    remove(i,buffer);
                    stack.deleteElement(i);

                    isItSolved = true;
                }
                i--;
            }
        }
    }
//    std::cout << "End of checking" << std::endl;
}

void Parser::reversePolishNotation(MyQueue& queue, MyStack& stack)
{
    std::string RPN[100];

    int stackBoarder = stack.size();
    for (int i = 0; i < stackBoarder; i++)
    {
        RPN[i] = stack.value(i);
    }

    int queueBoarder = queue.size();
    for (int j = 0; j < queueBoarder; j++)
    {
        RPN[stackBoarder+j] = queue.value(j);
    }

    int size = 0;
    while (RPN[size].size() != 0)
        size++;

    for (int i = 0; i < size/2; i++)
    {
        std::string temporary;
        temporary = RPN[i];
        RPN[i] = RPN[size-i-1];
        RPN[size-i-1] = temporary;
    }

    stack.clean();

    if (isThereAnyVariables == true)
    {
        readFromFile();
        for (int g = 0; g < size; g++)
        {
            for (int f = 0; f < alphabet.size(); f++)
            {
                if (RPN[g][0] == alphabet[f] || RPN[g][1] == alphabet[f])
                {
                    if (RPN[g][0] == '-')
                    {
                        auto iter = variables.find(RPN[g].substr(1));
                        if (iter != variables.end())
                        {
                            RPN[g] = std::to_string(-variables[RPN[g].substr(1)]);
                        }
                    }
                    else
                    {
                        auto iter =  variables.find(RPN[g]);
                        if (iter != variables.end())
                        {
                            RPN[g] = std::to_string( variables[RPN[g]]);
                        }
                    }
//                    std::cout << RPN[g].substr(1) << std::endl;
                }
            }
        }
    }
//    int k = 0;
//    std::cout << "RPN:  " << std::endl;
//    while (RPN[k].size() != 0)
//    {
//        std::cout << RPN[k] << "    ";
//        k++;
//    }

    for (int i = 0; i < size; i++)
    {
        bool isItDefined = false;
        double firstElement = 0;
        double secondElement = 0;
        double result = 0;

        if(size == 1)
        {
            stack.add(RPN[0]);
            break;
        }

        if (size == 2 && RPN[0].size() > 1)
        {
            double value;
            if (RPN[1][0] == '-')
            {
                value = -std::stod(RPN[0]);
                stack.add(std::to_string(value));
            }
            else if (RPN[1][0] == '+')
            {
                value = std::stod(RPN[0]);
                stack.add(std::to_string(value));
            }
            break;
        }

        if (RPN[i].size() > 1 && isItDefined == false)
        {
            stack.add(RPN[i]);
            isItDefined = true;
        }

        for (size_t k = 0; k < allowedSymbols.size(); k++)
        {
            if (RPN[i][0] == allowedSymbols[k] && isItDefined == false)
            {
                firstElement = std::stod(stack.value(stack.size()-2));
                secondElement = std::stod(stack.value(stack.size()-1));
//                std::cout << "\n" << firstElement << "  " << secondElement << std::endl;

                if (RPN[i][0] == '+')
                {
                    result = firstElement + secondElement;
                }
                if (RPN[i][0] == '-')
                {
                    result = firstElement - secondElement;
                }
                if (RPN[i][0] == '*')
                {
                    result = firstElement * secondElement;
                }
                if (RPN[i][0] == '/')
                {
                    result = firstElement / secondElement;
                }

//                std::cout << "RES:  " << result << std::endl;
                stack.replace(stack.size()-2,std::to_string(result));
                isItDefined = true;
            }

        }

        if (isItDefined == false)
        {
            stack.add(RPN[i]);
            isItDefined = true;
        }

//        stack.show();

    }

    std::cout << "Result:   " << stack.value(0) << std::endl;
//    std::cout << "End of reverse Polish notation" << std::endl;
}

void Parser::remove(int index, std::string *buffer)
{
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

void Parser::readFromFile()
{
    file.open(filename,std::ios::in);
    while (!file.eof())
    {
        std::string variableName;
        std::string variableValue;
        double value;

        file >> variableName;
        file >> variableValue;

//        std::cout << variableName << " = " << variableValue<< std::endl;

        if (variableValue != "" && variableName != "")
        {
            value = std::stod(variableValue);
            variables[variableName] = value;
        }
    }

//    for (auto iter = variables.begin(); iter != variables.end(); iter++)
//    {
//        std::cout << iter->first << " = " << iter->second << std::endl;
//    }

    file.close();
}

void Parser::writeToFile(std::string name,std::string value)
{
    file.open(filename,std::ios::app);
    file << name << " " << value << std::endl;
    file.close();
}
