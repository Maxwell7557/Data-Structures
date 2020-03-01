#ifndef HAFFMAN_H
#define HAFFMAN_H

#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>

class HaffmanTree
{
public:
    int weight;
    unsigned char symbol;
    HaffmanTree *right, *left;
    HaffmanTree();
    HaffmanTree(HaffmanTree*,HaffmanTree*);
};

struct FunctorOfComparison
{
    bool operator() (HaffmanTree *left, HaffmanTree *right) const
    {return left->weight < right->weight;}
};

void show(HaffmanTree*,unsigned k=0);
void deleteTree(HaffmanTree*);

class Haffman
{
private:
    int numberOfUsedCharacters;
    int numberOfCharacters;
    int positionInArchivedFile;
    long long int lengthOfArchivedText;
    std::string prefix;
    std::string originalText;
    std::string archivedText;
    std::string unarchivedText;
    std::fstream firstFile;
    std::fstream secondFile;
    std::map <unsigned char,int> statistic;
    std::list <HaffmanTree*>  myList;
    std::vector <int> code;
    std::map<unsigned char,std::vector<int> > tableOfCodes;
    HaffmanTree *tree;
public:
    Haffman();
    ~Haffman();
    void getFilenames(std::string,std::string,bool);
    void gettingStatistics();
    void gettingArchivedStatistic();
    void fillTheList();
    void createTree();
    void fillingTheTable(HaffmanTree*);
    void archiving();
    void unarchiving();
};

#endif // HAFFMAN_H
