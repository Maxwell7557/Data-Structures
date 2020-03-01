#ifndef SORTER_H
#define SORTER_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <cmath>
#include "types.h"

using namespace std::chrono;

template <typename Type>
class Sorter
{
private:
    std::vector<Type> array;
    std::vector<Type> tmpArray;
    int sizeOfData;
    std::vector<int> seq;
    std::string currentMode;
public:
    Sorter(std::vector<Type> &arr,int size, std::string mode)
    {
        array = arr;
        tmpArray = array;
        sizeOfData = size;
        currentMode = mode;
    }

    void bubleSort()
    {
        bool flag = true;
        while (flag)
        {
            flag = false;
            for (int j=sizeOfData-1; j>0; j--)
            {
                if (array[j] < array[j-1])
                {
                    std::swap(array[j],array[j-1]);
                    flag = true;
                }
            }
        }

//        for (int k=0; k<sizeOfData; k++)
//        {
//            std::cout << array[k] << std::endl;
//        }
    }

    void increment(std::vector<int> &inc)
    {
        if (currentMode == "Shell")
        {
            int cnt = 0;
            for (int step = sizeOfData/2; step > 0; step /=2)
            {
                inc.push_back(step);
//                std::cout << step << " ";
            }
        }
        else if (currentMode == "Hibbard")
        {
            int step;
            int cnt = 0;
            int count = 1;
            for (step = int(exp2(count))-1; step <= sizeOfData; step = int(exp2(count))-1)
            {
                inc.push_back(step);
                count++;
                cnt++;
//                std::cout << step << " ";
            }
            std::reverse(inc.begin(),inc.end());
        }
        else if (currentMode == "Sedjvick")
        {
            int step;
            int cnt = 0;
            for (step = 1; step*3 <= sizeOfData; )
            {
                inc.push_back(step);
                cnt++;
//                std::cout << step << " ";
                if (cnt%2 == 0)
                    step = 9*int(exp2(cnt)) - 9*int(exp2(cnt/2)) + 1;
                else
                    step = 8*int(exp2(cnt)) - 6*int(exp2((cnt+1)/2)) + 1;
            }
            std::reverse(inc.begin(),inc.end());
        }
    }

    void shellSort()
    {
        int i, j, step;
//        int seq[40];
        int cnt = 0;
        Type tmp;
//        increment(seq);
        step = seq.at(0);
        while (step >= 0)
        {
            for (i = step; i < sizeOfData; i++)
            {
                tmp = array[i];
                for (j = i; j >= step; j -= step)
                {
                    if (tmp < array[j - step])
                        array[j] = array[j - step];
                    else
                        break;
                }
                array[j] = tmp;
            }
            cnt++;
            if(cnt < seq.size())
                step = seq.at(cnt);
            else
                break;
//            std::cout << step << std::endl;
        }

//        for (int k=0; k<sizeOfData; k++)
//        {
//            std::cout << array[k] << std::endl;
//        }
    }

    void stdSort()
    {
        std::sort(array.begin(),array.end());

//        for (int k=0; k<sizeOfData; k++)
//        {
//            std::cout << array[k] << std::endl;
//        }
    }

    void callingTheBubleSort()
    {
        std::cout << "Buble sort" << std::endl;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        bubleSort();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        auto secDuration = duration*pow(10,-6);
        std::cout << "Execution time: " << secDuration << std::endl;
    }

    void callingTheShellSort()
    {
        increment(seq);
        std::cout << currentMode << " sort" << std::endl;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        shellSort();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        auto secDuration = duration*pow(10,-6);
        std::cout << "Execution time: " << secDuration << std::endl;
    }

    void callingTheStdSort()
    {
        std::cout << "Std sort" << std::endl;
        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        stdSort();
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        auto duration = duration_cast<microseconds>( t2 - t1 ).count();
        auto secDuration = duration*pow(10,-6);
        std::cout << "Execution time: " << secDuration << std::endl;
    }

    void sort()
    {
        callingTheBubleSort();
        array = tmpArray;
        callingTheShellSort();
        array = tmpArray;
        callingTheStdSort();
    }
};

#endif // SORTER_H
