/*
 * Name: Erich Seifert
 * Fret Class Member Function Definitions
 * Course: CSI218 (Spring 2025)
 * Date: 05/07/2025
 * Description: Card member function definitions.
 */

#ifndef CARD_CCP
#define CARD_CPP

#include <string>
#include <fstream>      // for file streams
#include "card.h"
using namespace std;

// default ctor 
Card::Card()
        : name(""), cost(Manacost())
    {
    }
// ctor 
Card::Card(string inName, Manacost inCost)
        : name(inName), cost(inCost)
{
}
// accesors 
string Card::getName() const
{return name;}

Manacost Card::getCost() const
 {return cost;}

int Card::getValue() const
{
    return cost.white +
    cost.blue +
    cost.black +
    cost.red +
    cost.green +
    cost.colorless;
}
// input stolen from class 
void Card::input(ifstream& inStream)
{
    string line;
    string inName = "";
    Manacost inCost;
    int firstParnth = 0;
    
    char c;
    
    getline(inStream, line);
    
    // find the name it must be a dynamic array ... 
    // find the values between ( and ) 
    for (int i = 0; i < line.length(); i++)
    {
        c = line[i];
    
        if (c == '(' || c == ')')
            firstParnth = i;
        else if (firstParnth > 0)
            switch (c)
            {
            case 'W':
                inCost.white++;
                break;
            case 'U':
                inCost.blue++;
                break;
            case 'B':
                inCost.black++;
                break;
            case 'R':
                inCost.red++;
                break;
            case 'G':
                inCost.green++;
                break;
            default:
                // need to static cast the char to the mana value 
                // https://www.asciitable.com/
                // so interesting, but subtracting by 0 shifts
                // the values to corresponding int value
                // so '1' would be 49, minus '0' which is 48 = 1
                // it will work only if values are 0-9 which works for mtg 
                inCost.colorless += static_cast<int>(c - '0');;
            }
        else
            inName.append(1, c);
    }
    name = inName;
    cost = inCost;
    
}
#endif