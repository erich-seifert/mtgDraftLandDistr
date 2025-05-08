/*
 * Name: Erich Seifert
 * Card Class Definition
 * Course: CSI 218 (Spring 2025)
 * Date: 05/07/2025
 * Description: Card class definition declaring
 *				data members and member functions.
 */
#ifndef CARD_H
#define CARD_H

#include <string>
#include <fstream>      // for file streams
using namespace std;

// im including this here so that it gets picked up
// through the .h header files 
// essentially represents the manacosts of cards
// also used to represent total mana cost of a deck 
struct Manacost {
    int white = 0;
    int blue = 0;
    int black = 0;
    int red = 0;
    int green = 0;
    int colorless = 0;
    bool isLand = 0;
};

class Card {
public:
    // default ctor 
    Card();
    // ctor 
    Card(string inName, Manacost inCost);

    // accesors 
    string getName() const;
    Manacost getCost() const;
    int getValue() const;

    // input stolen from class 
    // read in a txt file 
    void input(ifstream& inStream);
private:
    string name;
    struct Manacost cost;
};

#endif 