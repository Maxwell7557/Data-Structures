#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>
#include <list>
#include <ostream>

struct Employee
{
    std::string name;
    std::string surname;
    int salary;
    std::list<std::string> positions;
};

std::vector<int> numbers;
std::vector<std::string> lines;
std::vector<Employee> emp;

bool operator < (const Employee &first, const Employee &second)
{
    return first.salary < second.salary;
}

//bool operator > (const Employee &first, const Employee &second)
//{
//    return first.salary > second.salary;
//}

std::ostream& operator<< (std::ostream &out, const Employee &emp)
{
    out << emp.name << std::endl;
    out << emp.surname << std::endl;
    out << emp.salary << std::endl;
    for (auto it : emp.positions)
    {
        out << it << std::endl;
    }

    return out;
}

#endif // TYPES_H
