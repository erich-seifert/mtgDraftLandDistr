/*
 * Name: Erich Seifert
 * Deck Class Definition
 * Course: CSI 218 (Spring 2025)
 * Date: 05/07/2025
 * Description: Card class definition declaring
 *				data members and member functions.
 */

#ifndef DECK_H
#define DECK_H

#include <fstream>      // for file streams
#include <algorithm>    // for shuffle 
#include <random>       // for default_random_engine
#include <chrono>       // for chrono::system_clock
#include <fstream>      // for file streams
#include <cstdlib>      // for rand()
#include <string>
#include "card.h"
using namespace std;
template<class T>
class Deck {
public:
    // ctor 
    Deck(T inValue, int inDeckSize);
    Deck(const Deck& otherDeck);
    // dtor 
    ~Deck();

    // accessor 
    int size() const;
    bool empty() const;

    // operator overloading 
    Deck& operator =(const Deck& otherDeck);
    // reading 
    T operator[](const int pos) const;
    // editing 
    T& operator[](int pos);

    // mutators 
    void input(T inCard, int index);
    void input(ifstream& inStream);
    void shuffle();

private:
    T* deck;
    int deckSize;
};

#endif 