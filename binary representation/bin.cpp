#include <iostream>
#include <string>

using namespace std;

union{
    char binaryRepresentation[8];
    float floatValue;
    double doubleValue;
} Union;

string binaryIntPart(int value)
{
    string binRep;
    int intPart = value;
    int fracPart = 0;

    for (int i = 0; intPart != 0 ; i++)
    {
        fracPart = intPart % 2;
        intPart = intPart / 2;
        binRep.push_back(fracPart + '0');
    }

    for (int k = 0; k < binRep.size()/2; k++)
    {
        char buf;
        buf = binRep[k];
        binRep[k] = binRep[binRep.size()-k-1];
        binRep[binRep.size()-k-1] = buf;
    }

//    cout << "INT" << binRep << endl;

    return binRep;
}

template <typename FracPartType>
string binaryFractionalPart (FracPartType & value, bool flag)
{
    string binRep;
    FracPartType fracValue (value);
    int boarder;

    flag == false ? boarder = 23 : boarder = 52;

    for (int i=0; i<boarder*2; i++)
    {
        fracValue *= 2;
        binRep.push_back(int(fracValue) + '0');
        if (fracValue - int(fracValue) == 0)
        {
            while (binRep.size() != boarder*2)
                binRep.push_back('0');
            break;
        }
        if (fracValue >= 1)
            fracValue = fracValue - int(fracValue);
    }

//    cout << "FRAC" << binRep << endl;

    return binRep;
}

string unity (char sign, string exponent, string mantissa, bool flag)
{
    string binaryRepresentation;

    binaryRepresentation.push_back(sign);
    binaryRepresentation += exponent + mantissa;

    if (flag == false && binaryRepresentation.size() > 32)
        binaryRepresentation.erase(32);
    else if (flag == true && binaryRepresentation.size() > 64)
        binaryRepresentation.erase(64);

    return binaryRepresentation;
}

void formattedOutput (string value)
{
    cout << "My representation:" << endl;
    for (int i = 0; i < value.size() ; i++)
    {
        cout << value[i];
        if (value.size() == 64 && (i == 0 || i == 11))
            cout << " ";
        else if (value.size() == 32 && (i == 0 || i == 8))
            cout << " ";
    }
    cout << endl;
}

void unionRepresentation(bool flag)
{
    cout << "Union representation:" << endl;
    if (flag == false)
    {
        for (int i = 3; i>=0 ; i--)
        {
            for (int k = 7; k>=0; k--)
            {
                cout << ((Union.binaryRepresentation[i] >> k) & 1);
                if ((i == 3 && k == 7) || (i == 2 && k == 7))
                            cout << " ";
            }
        }
        cout << endl;
    } else {
        for (int i = 7; i>=0 ; i--)
        {
            for (int k = 7; k>=0; k--)
            {
                cout << ((Union.binaryRepresentation[i] >> k) & 1);
                if ((i == 7 && k == 7) || (i == 6 && k == 4))
                            cout << " ";
            }
        }
        cout << endl;
    }
}

int power(string mantissa, bool flag)
{
    int counter = 0;
    for (int g = 0; g < mantissa.size(); g++)
    {
        if (mantissa[g] == '0')
            counter += 1;
        else
            break;
    }
    return counter+1;
}

int main(int argc, char* argv[])
{
    bool flag = false;

    float floatValue;
    double doubleValue;

    if (argv[2][1] == 'f')
    {
        floatValue = stof(argv[1]);
    } else if (argv[2][1] == 'd'){
        doubleValue = stod(argv[1]);
        flag = true;
    }

    int integerPart;
    float floatFractionalPart;
    double doubleFractionalPart;

    string exponent;
    string mantissa;
    string binInt;
    char sign = '0';

//    flag = true;

    if (flag == false)
    {
//        cin >> floatValue;
        Union.floatValue = floatValue;

        integerPart = abs(int(floatValue));
        floatFractionalPart = abs(abs(floatValue) - float(integerPart));

        (floatValue >= 0) ? sign = '0' : sign = '1';
        binInt = binaryIntPart(integerPart);
        mantissa += binInt + binaryFractionalPart (floatFractionalPart, flag);
        if (integerPart != 0)
            exponent = binaryIntPart(127 + binInt.size()-1);
        else
        {
            int pow = power(mantissa, flag);
            exponent.push_back('0');
            exponent += binaryIntPart(127 - pow);
            mantissa.erase(0,pow-1);
        }
    } else {
//        cin >> doubleValue;
        Union.doubleValue = doubleValue;

        integerPart = abs(int(doubleValue));
        doubleFractionalPart = abs(abs(doubleValue) - double(integerPart));

        (doubleValue >= 0) ? sign = '0' : sign = '1';
        binInt = binaryIntPart(integerPart);
        mantissa += binInt + binaryFractionalPart (doubleFractionalPart, flag);
        if (integerPart != 0)
            exponent = binaryIntPart(1023 + binInt.size()-1);
        else
        {
            int pow = power(mantissa, flag);
            exponent.push_back('0');
            exponent += binaryIntPart(1023 - pow);
            mantissa.erase(0,pow-1);
        }
    }

    unionRepresentation(flag);

    mantissa.erase(0,1);

    formattedOutput(unity(sign, exponent, mantissa, flag));
}
