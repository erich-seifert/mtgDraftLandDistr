/*
DS final project proposal
* What problem will your project solve/simulate?
    
    Given a txt file of magic cards:
    Aetherize UU2
    Akal Pakal, First Among Equals U3
    An Offer You Can't Refuse U
    Arcane Signet 2 
    Arcanis the Omnipotent UUU3
    Archivist of Oghma W1
    Azor, the Lawbringer UUWW2
    Cataclysmic Gearhulk UU4
    Dovin's Veto UW
    Dovin's Veto UW
    Dragonlord Ojutai UW3
    Elspeth Conquers Death WW3

    So i'm realizing now there might be a white space issue, maybe for name
    i just say no spaces or weird characters to simplify :)

    1) what is the ideal distribution of mana in a given draft deck based on the mana
    cost associated with your drafted pile of cards
        - count all the distinct mana symbols in your deck of playable cards (23)
        - figure out what distribution of lands is ideal for your card pool
    2) given 10 turns, what are the chances you can cast a spell for the maximum
    mana value each turn
        - magic is a turn based game, you start with 7 cards
        and draw a card each turn
        - if you have a land in your hand you can play 1 a turn
        - given your ideal mana distribution what are the odds
        you can play a spell in your hand (for maximum value)
        each turn

     A little background - 
    * In the game magic the gathering there is a format called limited 
    in this mode you draft from a specified collection (set) and 
    build a deck which you use to battle against other opponents
    * The draft portion of the game leads you to unique combinations of the cards in the set
    * Each ‘card’ has a certain mana cost (mana value)
        * Either the mana needs to come from a forest, island, mountain, swamp, or plains, or it can come from a generic value
        * Cards are denoted with their cost by
            * White (W) - plains
            * Blue (U) - island
            * Red (R) - mountain
            * Black (B) - swamp
            * Green (G) - forest
            * 1,2,3,n (for any cost)
        * The Card; Betor, Kin To All would have the mana cost WBG2
            * Indicating there most be a plains,  swamp, forest, and two of any land to cast this spell (for a total mana value of 5)
    * At the end of the draft you have 45 of cards and can add any combination of lands (plains, island, etc noted above)
    * You pick 23 that you want to play, and add 17 lands you think will be the right amount to cast your spells!

* Identify a class you will write to store data critical to the application.
    - The Class would be a distinct card, its name, mana cost/value
* What will be stored in a dynamic array?  A linked List?
    - drawing the hand could be a dynamic array 
      sorting would be easy in order to figure out what 
      mana cost you should attempt to play on each turn 
* What template class will you write?
    - I'm thinking i make a deck a template class, could be anything
    - but in my case i would specifically use my class of card 
    - is stored in a deck that has a queue 
* How will you use a stack, queue or tree?
    - Stack of cards = a deck
* What will you search for?
    - while figuring out the distribution you must count the 
      amount of mana symbols in each card 
    
* What will you sort (put in order)?
    - so after we get the ideal mana distribution we create a deck of cards
      we shuffle it, then draw 7 cards and sort the 7 cards in hand by mana value 
    
* How will you use an STL container class?  An STL function?
    - I am thinking either a vector or a stack
      draw 7 cards would be top() 



*/

// DSFinalProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>       // for default_random_engine
#include <chrono>       // for chrono::system_clock
#include <fstream>      // for file streams
#include <string>

using namespace std;

struct Manacost {
    int white = 0;
    int blue = 0;
    int black = 0;
    int red = 0;
    int green = 0;
};
class Card {
public:
    string getName() const
    {
        return name;
    }
    Manacost getCost() const
    {
        return cost;
    }

    void input(ifstream& inStream)
    {
        string line;
        string inName = "";
        Manacost inCost;
        int firstParnth = 0;
        int lastParnth = 0;

        getline(inStream, line);

        // find the name it must be a dynamic array ... 
        // find the values between ( and ) 
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '(')
                firstParnth = i;
            else if (line[i] == ')')
                lastParnth = i;
            // we are still reading the name
            else if (firstParnth <= i)
                inName[i] = line[i];
            // we must be between the paranthesis 
            else
            {
                switch (line[i])
                {
                case 'W':
                    cost.white += 1;
                    break;
                case 'U':
                    cost.blue += 1;
                case 'B':
                    cost.black += 1;
                case 'R':
                    cost.red += 1;
                case 'G':
                    cost.green += 1;
                }

            }
        }

        name = inName;
        cost = inCost;

    }
private:
    string name;
    struct Manacost cost;
};

class Deck {
public:
    void add(const Card& card) 
    {
        deck.push(card);
    }
    int size() const 
    {
        return deck.size();
    }
    bool empty() const 
    {
        return deck.empty();
    }
    Card draw()
    {
        if (deck.empty())
            return Card();

        Card topCard = deck.top();
        deck.pop();
        return topCard;
    }

    void input(ifstream& inStream)
    {
        // can assume deck size will be 23 :)
        int deckSize = 23;
        Card card;
        for (int i = 0; i < deckSize; i++)
        {
            card.input(inStream);
            deck.push(card);
        }
    }

    void shuffle()
    {
        // in order to leverage shuffle 
        // we need to dump into a vector 
        vector<Card> deckVec;
        while (!deck.empty())
        {
            deckVec.push_back(deck.top());
            // remove all cards from the stack 
            // so we put back on empty 
            deck.pop();
        }
        // shuffle has been figured out (standin onthe shoudlers of giants)
        // https://cplusplus.com/reference/algorithm/shuffle/?kw=shuffle
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deckVec.begin(), deckVec.end(), default_random_engine(seed));

        // iterate through deck and put back into stack 
        for (vector<Card>::const_iterator i = deckVec.begin();
            i != deckVec.end(); i++
            )
        {
            deck.push(*i);
        }

    }
private:
    stack<Card> deck;
};



int main()
{
    Deck d;

    // reading from file 
    // stolen from 12/19/2024 
    // CSI108-Topic6a-File Streams Code [completed]
    const char inputFilename[] = "draftdeck.txt";
    ifstream deckInFile(inputFilename);

    if (deckInFile.fail())
    {
        cerr << "Cannot read deck from file: "
            << inputFilename << endl;
    }
    else
    {
        d.input(deckInFile);
        deckInFile.close();
        cout << "\Deck read from file:" << endl;
    }

    cout << d.size();

    Card c;
    c = d.draw();
    cout << c.getName();


}

