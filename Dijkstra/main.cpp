#include <iostream>
#include <fstream>
#include "dijkstra.h"

using namespace std;

int main(int argc, char* argv[])
{
    Dijkstra dijkstra;
    fstream file;
    file.open("data.txt",ios::in);

    string flag;
    string numbersOfVertices;
    string vertices[9];
    int quantity = 0;
    bool matrixMode = false;

    string arg1 = argv[1];
    string arg3 = argv[3];

    int startVertex = 0;
    int endVertex = 0;

    file >> numbersOfVertices;
    file >> flag;

    quantity = stoi(numbersOfVertices);

    if (arg1 == "--start_vertex")
    {
        startVertex = atoi(&argv[2][0]);
        cout << "Start:   " << argv[2][0] << endl;
    }

    if (arg3 == "--end_vertex")
    {
        endVertex = atoi(&argv[4][0]);
        cout << "End:   " << argv[4][0] << endl;
    }

//    cout << argv[1] << endl;
//    cout << argv[3] << endl;
//    cout << argc << endl;

    dijkstra.takeVertices(startVertex,endVertex);

    for (int i = 0; i < quantity; i++)
    {
        file >> vertices[i];
    }

    if (flag == "matrix")
    {
        matrixMode = true;
        cout << "MATRIX" << endl;
        dijkstra.createData(quantity,vertices,matrixMode);
    }

    if (flag == "list")
    {
        cout << "LIST" << endl;
        dijkstra.createData(quantity,vertices,matrixMode);
    }

    file.close();

    return 0;
}
