#include "haffman.h"

Haffman::Haffman()
{
    originalText = "data.txt";
    archivedText = "packed.txt";
    unarchivedText = "unpacked.txt";
    numberOfCharacters = 0;
    numberOfUsedCharacters = 0;
    lengthOfArchivedText = 0;
    prefix = "HF11";
    tree = nullptr;
}

Haffman::~Haffman()
{
    deleteTree(tree);
}

void Haffman::getFilenames(std::string inFile, std::string outFile, bool compress)
{
    if (compress)
    {
        originalText = inFile;
        archivedText = outFile;
    } else {
        archivedText = inFile;
        unarchivedText = outFile;
    }
}

void Haffman::gettingStatistics()
{
    firstFile.open(originalText,std::ios::in);

    unsigned char symbol;
    while (!firstFile.eof())
    {
        symbol = firstFile.get();
//        if (symbol == '\n')
//            continue;
        if (firstFile.eof())
            break;
        if (statistic[symbol] == 0)
            numberOfUsedCharacters++;
        statistic[symbol]++;
        numberOfCharacters++;
    }

//    for (auto it : statistic)
//    {
//        std::cout << "'" << it.first << "'" << ":   " << it.second << std::endl;
//    }
//    std::cout << numberOfUsedCharacters << std::endl;
//    std::cout << numberOfCharacters << std::endl;

    firstFile.close();
}

void Haffman::fillTheList()
{
    for (auto it : statistic)
    {
        HaffmanTree *temp = new HaffmanTree;

        temp->symbol = it.first;
        temp->weight = it.second;

        myList.push_back(temp);
    }
}

void Haffman::createTree()
{
    if (numberOfCharacters == 0)
        return;

    while (myList.size() != 1)
    {
        myList.sort(FunctorOfComparison());

        HaffmanTree *leftTemp = myList.front();
        myList.pop_front();
        HaffmanTree *rightTemp = myList.front();
        myList.pop_front();

        HaffmanTree *father = new HaffmanTree(leftTemp,rightTemp);
        myList.push_back(father);
//        myList.push_front(father);
    }

    tree = myList.front();

//    show(tree);
    fillingTheTable(tree);

//    for (auto outsideIt : tableOfCodes)
//    {
//        std::cout << "'" << outsideIt.first << "':   ";
//        for (auto insideIt : outsideIt.second)
//        {
//            std::cout << insideIt;
//        }
//        std::cout << std::endl;
//    }

    for (auto it : tableOfCodes)
    {
        lengthOfArchivedText += statistic[it.first] * it.second.size();
    }
}

void Haffman::fillingTheTable(HaffmanTree *currentNode)
{
    if (currentNode->left != nullptr)
    {
        code.push_back(0);
        fillingTheTable(currentNode->left);
    }
    if (currentNode->right != nullptr)
    {
        code.push_back(1);
        fillingTheTable(currentNode->right);
    }

    if (currentNode->symbol)
    {tableOfCodes[currentNode->symbol] = code;}

    code.pop_back();
}

void Haffman::archiving()
{
    if (numberOfCharacters == 0)
    {    
	std::cout << "Input file is empty." << std::endl;
	return;
    }

    int left = lengthOfArchivedText % 8;

//    std::cout << lengthOfArchivedText << std::endl;
//    std::cout << left << std::endl;

    firstFile.open(originalText,std::ios::in);
    secondFile.open(archivedText,std::ios::out);

    secondFile << prefix << " ";
    secondFile << numberOfCharacters << " ";
    for (auto it : statistic)
    {
        secondFile << it.second << " ";
        secondFile << it.first << " ";
    }

    unsigned char symbol;
    while (!firstFile.eof())
    {
        symbol = firstFile.get();
//        if (symbol == '\n')
//            continue;
        if (firstFile.eof())
            break;

	int count = 0;
	char res;
        for (auto it : tableOfCodes[symbol])
        {	    
//	    secondFile << it;
	    
	    for (size_t y=0; y<it.size(); y++)
	    {
		if (it[y] == 1)
		{
		    res = res | 1 << (8-count);		
		}

		if (count == 8)
		{
		    secondFile << res;
		    count = 0;
		}	


		count++;
	    }

//	    std::cout << it;
        }
    }

    if (left)
    {
        for (int k=0; k<8-left; k++)
        {
            secondFile << 0;
//	    std::cout << "check" << std::endl;
        }
    }

    firstFile.close();
    secondFile.close();
}

void Haffman::unarchiving()
{
    if (!secondFile.is_open())
	return;

    firstFile.open(unarchivedText,std::ios::out);

    HaffmanTree *tmp = tree;
    char symbol;
    for (int i=0; i<lengthOfArchivedText; i++)
    {
        secondFile >> symbol;
        if (symbol == '1')
            tmp = tmp->right;
        else
            tmp = tmp->left;

        if (tmp->left == nullptr && tmp->right == nullptr)
        {
            firstFile << tmp->symbol;
            tmp = tree;
        }
    }

    secondFile.close();
    firstFile.close();
}

void Haffman::gettingArchivedStatistic()
{
    secondFile.open(archivedText,std::ios::in);

    int currNumOfcharacters = 0;
    std::string pref;
    secondFile >> pref;

    if (pref == prefix)
	std::cout << "Current method of archiving is Haffman." << std::endl;
    else
    {
	std::cout << "Current method of archiving is not Haffman." << std::endl;
	secondFile.close();	
	return;
    }
    
    secondFile >> numberOfCharacters;

    secondFile.get();
    while (!secondFile.eof())
    {
        int amount;
        unsigned char symbol;

        secondFile >> amount;
        secondFile.get();
        symbol = secondFile.get();
        secondFile.get();

        currNumOfcharacters += amount;

        statistic[symbol] = amount;

        if (currNumOfcharacters == numberOfCharacters)
            break;
    }

//    std::cout << pref << std::endl;
//    std::cout << numberOfCharacters << std::endl;

//    for (auto it : statistic)
//    {
//        std::cout << "'" << it.first << "'" << ":   " << it.second << std::endl;
//    }
}

//void show(HaffmanTree *tree, unsigned k)
//{
//    if (tree != nullptr)
//    {
//       show(tree->left,k+3);
//       for (unsigned i=0; i<k; i++)
//       {std::cout << "   ";}
//       if (tree->symbol)
//           std::cout << tree->weight << "(" << tree->symbol << ")" << std::endl;
//       else
//           std::cout << tree->weight << std::endl;
//       show(tree->right,k+3);
//    }
//}

void deleteTree(HaffmanTree *tree)
{
    if (tree != nullptr)
    {
       deleteTree(tree->left);
       deleteTree(tree->right);
       delete tree;
       tree = nullptr;
    }
}

HaffmanTree::HaffmanTree()
{
    weight = 0;
//    symbol = '0';
    left = nullptr;
    right = nullptr;
}

HaffmanTree::HaffmanTree(HaffmanTree *leftSon, HaffmanTree *rightSon)
{
    weight = leftSon->weight + rightSon->weight;
    symbol = '\0';
    left = leftSon;
    right = rightSon;
}
