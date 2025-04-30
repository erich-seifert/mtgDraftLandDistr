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

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <random>       // for default_random_engine
#include <chrono>       // for chrono::system_clock
#include <fstream>      // for file streams
#include <string>
#include <cstdlib> // for rand()

using namespace std;


// I RAELIZE NOW THE DECK SHOULD BE A VECTOR UNTIL YOUR READY TO ACTUALLY PLAY WITH IT
// VECTOR/ARRAY MAKE IT MUCH EASIER TO LOOK AT STATS ABOUT IT
// when you actually intialize a game you solidify the deck into a stack (then shuffle it)

struct Manacost {
    int white = 0;
    int blue = 0;
    int black = 0;
    int red = 0;
    int green = 0;
    int colorless = 0;
};


//Manacost totalCostDeck(stack<Card>&deck);

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
    int getValue() const
    {
        return cost.white +
            cost.blue +
            cost.black +
            cost.red +
            cost.green +
            cost.colorless;
    }

    void input(ifstream& inStream)
    {
        string line;
        string inName = "";
        Manacost inCost;
        int firstParnth = 0;
        int colorless;

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
private:
    string name;
    struct Manacost cost;
};

class Deck {
public:
    Deck(int inDeckSize)
    {
        deckSize = inDeckSize;

        deck = new Card[deckSize];

        for (int i = 0; i < deckSize; i++)
            deck[i] = Card();
    }

    Deck(const Deck& otherDeck)
    {
        deckSize = otherDeck.deckSize;

        for (int i = 0; i < deckSize; i++)
            deck[i] = otherDeck.deck[i];
    }
    ~Deck()
    {
        delete[] deck;
        deck = NULL;
        deckSize = 0;
    }

    Deck& operator =(const Deck& otherDeck)
    {
        if (this != &otherDeck)
        {
            delete[] deck;
        }

        deckSize = otherDeck.deckSize;

        deck = new Card[deckSize];

        for (int i = 0; i < deckSize; i++)
            deck[i] = otherDeck.deck[i];
    }

    Card operator[](const int pos) const 
    {
        if (pos >= deckSize || pos < 0)
            return Card();
        else
            return deck[pos];
    }
    void input(ifstream& inStream)
    {
        // can assume deck size will be 23 :)
        Card card;
        for (int i = 0; i < deckSize; i++)
        {
            card.input(inStream);
            deck[i] = card;
        }
    }
    void shuffle()
    {
        // shuffle has been figured out (standin onthe shoudlers of giants)
        // https://cplusplus.com/reference/algorithm/shuffle/?kw=shuffle
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck, deck + deckSize, default_random_engine(seed));
    }

    void cut()
    {
        // pick a random point in the deck say 10
        // if that is within the bounds of the deck
        // make a new arary taking 10 -> end of array
        // and put begin of array -> 9 after it
        srand((unsigned int)time(NULL));

        int deckSizeArr = deckSize - 1;
        int cutPos = rand() % (deckSizeArr);

        cout << cutPos << endl;

        Card * newDeck = new Card[deckSize];

        for (int i = 0; i < deckSize; i++)
        {
            // cycle through the decks
            // create a new deck shifting the position
            // if the deck would overlap leverage mod
            newDeck[i] = deck[ ((i + cutPos > deckSizeArr) ? 
                                (i + cutPos) % deckSizeArr - 1 
                                : i + cutPos)];
        }
        // leverage assignment operator 
        deck = newDeck;
        delete[] newDeck;
        newDeck = NULL;

    }
private:
    Card* deck;
    int deckSize;
};



int main()
{
    Deck d(23);

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



    cout << d[0].getName() << endl;
    // d.shuffle();

    d.cut();

    cout << d[0].getName();

    //d.shuffle();

    //Card c;
    //c = d.draw();
    //cout << "|" << c.getName() << "|" << endl;

    //Manacost m;
    //m = c.getCost();

    //cout << "white: " << m.white << endl;
    //cout << "blue: " << m.blue << endl;
    //cout << "black: " << m.black << endl;
    //cout << "red: " << m.red << endl;
    //cout << "green: " << m.green << endl;
    //cout << "colorless: " << m.colorless << endl;

    

}

//
//Manacost totalCostDeck(stack<Card>& deck)
//{
//    vector<Card> deckVec;
//    while (!deck.empty())
//    {
//        deckVec.push_back(deck.draw());
//    }
//}