#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <list>
#include <utility>

class Dijkstra
{
private:
    int **matrix;
    int startVertex;
    int endVertex;
    std::list<std::pair<int,int> > *myList;
public:
    Dijkstra();
    ~Dijkstra();
    void takeVertices(int,int);
    void createData(int,std::string*,bool);
    void dijkstraMethod(int,bool);
//    void createList(int,std::string*);
};

#endif // DIJKSTRA_H
