/*
 * Name: Erich Seifert
 * Deck Class Member Function Definitions
 * Course: CSI218 (Spring 2025)
 * Date: 05/07/2025
 * Description: Deck member function definitions.
 */

#ifndef DECK_CPP
#define DECK_CPP

#include <fstream>      // for file streams
#include <algorithm>    // for shuffle 
#include <random>       // for default_random_engine
#include <chrono>       // for chrono::system_clock
#include <fstream>      // for file streams
#include <cstdlib>      // for rand()
#include <string>
#include "deck.h"
using namespace std;
// Definitions for template class member functions.
// Constructor to set up size and with initial value.
template<class T>
Deck<T>::Deck(T inValue, int inDeckSize)
{
    deckSize = inDeckSize;

    deck = new T[deckSize];

    for (int i = 0; i < deckSize; i++)
        deck[i] = T();
}
// Copy constructor 
template<class T>
Deck<T>::Deck(const Deck<T>& otherDeck)
{
    deckSize = otherDeck.deckSize;

    for (int i = 0; i < deckSize; i++)
        deck[i] = otherDeck.deck[i];
}
// Destructor 
template<class T>
Deck<T>::~Deck()
{
    delete[] deck;
    deck = NULL;
    deckSize = 0;
}
// Accessors
template<class T>
int Deck<T>::size() const
{
    return deckSize;
}
template<class T>
bool Deck<T>::empty() const
{
    return (deckSize == 0);
}
// operator overloading 
template<class T>
Deck<T>& Deck<T>::operator =(const Deck<T>& otherDeck)
{
    if (this != &otherDeck)
    {
        delete[] deck;
    }

    deckSize = otherDeck.deckSize;

    deck = new T[deckSize];

    for (int i = 0; i < deckSize; i++)
        deck[i] = otherDeck.deck[i];
    return *this;
}
// reading 
template<class T>
T Deck<T>::operator[](const int pos) const
{
    if (pos >= deckSize || pos < 0)
        return T();
    else
        return deck[pos];
}
// editing 
template<class T>
T& Deck<T>::operator[](int pos) {
    return deck[pos];
}
// mutators 
template<class T>
void Deck<T>::input(T inCard, int index)
{
    deck[index] = inCard;
}
template<class T>
void Deck<T>::input(ifstream& inStream)
{
    T card;
    for (int i = 0; i < deckSize; i++)
    {
        card.input(inStream);
        deck[i] = card;
    }
}
template<class T>
void Deck<T>::shuffle()
{
    // shuffle has been figured out (standin onthe shoudlers of giants)
    // https://cplusplus.com/reference/algorithm/shuffle/?kw=shuffle
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck, deck + deckSize, default_random_engine(seed));
}

#endif 