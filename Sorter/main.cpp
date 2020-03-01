//#include <iostream>
//#include <string>
//#include <list>
//#include <vector>
#include <cstdlib>
#include <ctime>
#include "types.h"
#include "generator.h"
#include "sorter.h"

using namespace std;

int main(int argc,char** argv)
{
    int amount = stoi(argv[2]);
    string mode = argv[4];

    Generator generator(amount);
    generator.generate();


    Sorter<int> intSorter(numbers,amount,mode);
    Sorter<string> stringSorter(lines,amount,mode);
    Sorter<Employee> structSorter(emp,amount,mode);

    cout << "------Int------" << endl;
    intSorter.sort();
    cout << "\n------String------" << endl;
    stringSorter.sort();
    cout << "\n------Struct------" << endl;
    structSorter.sort();

    return 0;
}
