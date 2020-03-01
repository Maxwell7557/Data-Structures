#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string>
#include "types.h"

class Generator
{
private:
    int sizeOfData;
    std::string alphabet = {"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};
public:
    Generator(int size)
    {sizeOfData = size;}
    void generateInt()
    {
        for (int i=0; i<sizeOfData; i++)
        {
            numbers.push_back(rand());
//            std::cout << numbers[i] << std::endl;
        }
    }
    void generateString()
    {
        std::string tmp;
        for (int j=0; j<sizeOfData; j++)
        {
            for (int c=0; c<10; c++)
            {
                tmp.push_back(alphabet[rand() % (sizeof(alphabet) - 1)]);
            }
            lines.push_back(tmp);
            tmp.clear();
    //        std::cout << lines[j] << std::endl;
        }
    }
    void generateStruct()
    {
        for(int k=0; k<sizeOfData; k++)
        {
            Employee tmp;
            for(int c=0; c<10; c++)
            {
                tmp.name.push_back(alphabet[rand() % (sizeof(alphabet) - 1)]);
                tmp.surname.push_back(alphabet[rand() % (sizeof(alphabet) - 1)]);
            }
            tmp.salary = rand();
            for (int h=0; h<3; h++)
            {
                std::string stringTmp;
                for (int g=0; g<10; g++)
                {
                    stringTmp.push_back(alphabet[rand() % (sizeof(alphabet) - 1)]);
                }
                tmp.positions.push_back(stringTmp);
            }
            emp.push_back(tmp);
        }

    //    for (int y=0; y<sizeOfData; y++)
    //    {
    //        std::cout << emp[y].name << std::endl;
    //        std::cout << emp[y].surname << std::endl;
    //        std::cout << emp[y].salary << std::endl;
    //        for (auto it : emp[y].positions)
    //        {
    //            std::cout << it << std::endl;
    //        }
    //        std::cout << std::endl;
    //    }
    }
    void generate()
    {
        srand(0);
        generateInt();
        generateString();
        generateStruct();
    }
};

#endif // GENERATOR_H
