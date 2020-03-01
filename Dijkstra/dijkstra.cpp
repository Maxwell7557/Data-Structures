#include "dijkstra.h"

#include <iostream>
#include <list>
#include <utility>
#include <vector>

Dijkstra::Dijkstra()
{

}

Dijkstra::~Dijkstra()
{

}

void Dijkstra::takeVertices(int start, int end)
{
    startVertex = start;
    endVertex = end;
}

void Dijkstra::createData(int quantity, std::string *vertices, bool matrixMode)
{
    if (matrixMode == true)
    {
        matrix = new int* [quantity];
        for (int i = 0; i < quantity; i++)
            matrix[i] = new int [quantity];

        for (int x = 0; x < quantity; x++)
        {
            for (int y = 0; y < quantity; y++)
            {
                matrix[x][y] = 0;
            }
        }
    } else {
        myList = new std::list<std::pair<int,int> > [quantity];
    }

    for (int i = 0; i < quantity; i++)
    {
        std::string currentVertex;
        currentVertex.push_back(vertices[i][0]);
        int currentVertexNumber = std::stoi(currentVertex);

        int nextVertexNumber = 0;
        int nextVertexValueNumber = 0;
        std::pair<int,int> vertexAndValue;

        for (size_t k = 0; k < vertices[i].size(); k++)
        {
            char nextVertex;
            std::string nextVertexValue;

            if (vertices[i][k] == '(')
            {
                nextVertex = vertices[i][k+1];
                if (matrixMode == true)
                {
                    nextVertexNumber = std::atoi(&nextVertex);
                } else {
                    vertexAndValue.first = std::atoi(&nextVertex);
                }
            }


            if (vertices[i][k] == ',')
            {
                k++;
                while (vertices[i][k] != ')')
                {
                    nextVertexValue.push_back(vertices[i][k]);
                    k++;
                }

                if (matrixMode == true)
                {
                    nextVertexValueNumber = std::stoi(nextVertexValue);
                    matrix[currentVertexNumber-1][nextVertexNumber-1] = nextVertexValueNumber;
                    nextVertexNumber = 0;
                    nextVertexValueNumber = 0;
                } else {
                    vertexAndValue.second = std::stoi(nextVertexValue);
                    myList[currentVertexNumber-1].push_back(vertexAndValue);
                    vertexAndValue.first = 0;
                    vertexAndValue.second = 0;
                }
            }
        }
    }

    std::cout << "Data pack has been created successfully." << std::endl;

    dijkstraMethod(quantity,matrixMode);

    if (matrixMode == true)
    {
//        for (int i = 0; i < quantity; i++)
//        {
//            for (int j = 0; j < quantity; j++)
//                std::cout << matrix[i][j] << "   ";
//            std::cout << std::endl;
//        }

        for (int i = 0; i < quantity; i++)
            delete [] matrix[i];
        delete [] matrix;

    } else {
//        for (int i = 0; i < quantity; i++)
//        {
//            std::cout << i+1 << " vertex:   ";
//            for (auto vertex : myList[i])
//            {
//                std::cout << vertex.first << " " << vertex.second << "   ";
//            }
//            std::cout << std::endl;
//        }

        delete [] myList;
    }
}

void Dijkstra::dijkstraMethod(int quantity, bool matrixMode)
{
    std::pair<bool,int> *tag;
    tag = new std::pair<bool,int> [quantity];

    std::vector<int> queue;
    std::vector<int> path;

    for (int i = 0; i < quantity; i++)
    {
        tag[i].first = false;
        tag[i].second = 9999;
    }

    tag[startVertex-1].first = true;
    tag[startVertex-1].second = 0;

    bool isCycleEnded = false;
    int counter = startVertex - 1;


    bool isStartVertexRemote = true;
    bool isEndVertexRemote = true;
//    for (int c = 0; c<quantity; c++)
//    {
        if (matrixMode == true)
        {
            for (int h = 0; h<quantity; h++)
            {
                if (matrix[startVertex-1][h] != 0)
                {
                    isStartVertexRemote = false;
//                    break;
                }
                if (matrix[endVertex-1][h] != 0)
                {
                    isEndVertexRemote = false;
//                    break;
                }
            }
        } else {
            for (auto vertex : myList[startVertex-1])
            {
                if (vertex.second != 0)
                {
                    isStartVertexRemote = false;
                    break;
                }
            }
            for (auto vertex : myList[endVertex-1])
            {
                if (vertex.second != 0)
                {
                    isEndVertexRemote = false;
                    break;
                }
            }
        }
//    }

//    std::cout << isStartVertexRemote << "   " << isEndVertexRemote <<  std::endl;

    if (isStartVertexRemote == true || isEndVertexRemote == true)
        isCycleEnded = true;

    while ( isCycleEnded == false )
    {
        tag[counter].first = true;

        if (matrixMode == true)
        {
            for (int i = 0; i < quantity; i++)
            {
                if (tag[i].first == true)
                    continue;

                if (matrix[counter][i] == 0)
                    continue;

                if (matrix[counter][i] != 0)
                {
                    bool isItIn = false;
                    for (size_t k = 0; k < queue.size(); k++)
                    {
                        if (queue[k] == i)
                            isItIn = true;
                    }

                    if (isItIn == false && i != endVertex-1)
                        queue.push_back(i);

                    if (tag[counter].second + matrix[counter][i] < tag[i].second)
                        tag[i].second = tag[counter].second + matrix[counter][i];
                }
            }
        } else {
            for (auto vertex : myList[counter])
            {
                if (tag[vertex.first-1].first == true)
                    continue;

                bool isItIn = false;
                for (size_t k = 0; k < queue.size(); k++)
                {
                    if (queue[k] == vertex.first-1)
                        isItIn = true;
                }

                if (isItIn == false && vertex.first-1 != endVertex-1)
                    queue.push_back(vertex.first-1);

                if (tag[counter].second + vertex.second < tag[vertex.first-1].second)
                    tag[vertex.first-1].second = tag[counter].second + vertex.second;
            }
        }

        bool isItInQueue = false;

        for (size_t k = 0; k < queue.size(); k++)
        {
            if (queue[queue.size()-1] == counter)
            {
                isItInQueue = true;
                queue.clear();
                isCycleEnded = true;
                break;
            }

            if (queue[k] == counter)
            {
                counter = queue[k+1];
                isItInQueue = true;
                break;
            }
        }

        if (isItInQueue == false)
        {
            counter = queue[0];
        }

    }

    bool isPathFounded = false;
    int tail = endVertex-1;
    while ( isPathFounded == false && isStartVertexRemote == false && isEndVertexRemote == false)
    {
        if (matrixMode == true )
        {
            for (int j = 0; j<quantity; j++)
            {

                if (matrix[j][tail] == 0)
                    continue;

                if (tag[tail].second - matrix[j][tail] == tag[j].second)
                {
                    path.push_back(j);
                    tail = j;
                    break;
                }
            }
        } else {
            for (int k = 0; k<quantity; k++)
            {
                for (auto vertex : myList[k])
                {
                    if (vertex.first-1 != tail)
                        continue;

                    if (tag[tail].second - vertex.second == tag[k].second)
                    {
                        path.push_back(k);
                        tail = k;
                        break;
                    }
                }
            }
        }        

        if (tail == startVertex-1)
            isPathFounded = true;
    }

    if (isStartVertexRemote == false && isEndVertexRemote == false)
    {
        std::cout << "Weight of shortest path:   " << tag[endVertex-1].second << std::endl;
        std::cout << "Shortest path:   ";
        for (size_t t = 0; t<path.size(); t++)
        {
            std::cout << path[path.size()-1-t]+1 << "->";
        }
        std::cout << endVertex << std::endl;
    } else {
        std::cout << "Weight of shortest path:   " << "does not exist" << std::endl;
        std::cout << "Shortest path:   " << "does not exist" << std::endl;
    }
    
    delete [] tag;
}

