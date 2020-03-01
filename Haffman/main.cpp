#include <iostream>
#include "haffman.h"

using namespace std;

int main(int argc, char **argv)
{
    Haffman haffman;
    bool compress = false;
    string inFile;
    string outFile;
    string mode = argv[1];

    if (argc > 2)
    {
        string arg1 = argv[2];
        if (arg1 == "--input_file")
        {
//            int pos = arg1.find('=');
            inFile = argv[3]; //arg1.substr(pos+1);
	    cout << "Input file: " << inFile << endl;
        }
        string arg2 = argv[4];
        if (arg2 == "--output_file")
        {
//            int pos = arg2.find('=');
            outFile = argv[5]; //arg2.substr(pos+1);
	    cout << "Output file: " << outFile << endl;        
	}
    }

    if (mode == "--compress")
    {
        mode.erase(0,2);
	cout << "Current mode: " << mode << endl;

        compress = true;
        haffman.getFilenames(inFile,outFile,compress);
        haffman.gettingStatistics();
        haffman.fillTheList();
        haffman.createTree();
        haffman.archiving();
    }

    if (mode == "--decompress")
    {
        mode.erase(0,2);
	cout << "Current mode: " << mode << endl;

        compress = false;
        haffman.getFilenames(inFile,outFile,compress);
        haffman.gettingArchivedStatistic();
        haffman.fillTheList();
        haffman.createTree();
        haffman.unarchiving();
    }

    return 0;
}
