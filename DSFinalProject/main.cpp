#include <iostream>
#include <stack>
#include <string>
#include "deck.cpp" // template 
#include "hand.h"
using namespace std;

// specific to magic cards 
// loops through deck and sums total cost 
// returns total cost of deck as manacost structure 
Manacost totalCostDeck(Deck<Card>& deck);
// given the distribution of mana costs
// and a amount of lands
// figure out the distribution of lands that mirrors cost 
Manacost optimalLandDistribution(int landCount, const Manacost& totalCost);

// function to convert Deck into stack 
stack<Card> createPlayDeck(const Deck<Card> &inDeck );

// draw a card from a deck stack | top - pop
Card draw(stack<Card> &inDeck);
Hand drawHand(stack<Card>& inDeck, int handSize);

int main()
{
    // the deck of spells you input from file
    // this should always be 23 
    int spellCount = 23;
    int landCount = 17;
    Deck<Card> spellDeck(Card(), spellCount);
    Deck<Card> landDeck(Card(), landCount);
    Deck<Card> fullDeck(Card(), spellCount + landCount);

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
        spellDeck.input(deckInFile);
        deckInFile.close();
        cout << "Deck read from file: " << inputFilename << endl;
    }   

    Manacost totalManaSym;
    totalManaSym = totalCostDeck(spellDeck);
    Manacost landDistr = optimalLandDistribution(landCount, totalManaSym);

    // build land deck with cards
    Card plains("Plains", (Manacost{1, 0, 0, 0, 0, 0, true }));
    Card island ("Island", (Manacost{0, 1, 0, 0, 0, 0, true}));
    Card swamp ("Swamp", (Manacost{0, 0, 1, 0, 0, 0, true}));
    Card mountain ("Mountain", (Manacost{ 0, 0, 0, 1, 0, 0, true }));
    Card forest ("Forest", Manacost({ 0, 0, 0, 0, 1, 0, true }));

    // keep track of the land index 
    // populate lands 
    int landIndex = 0;
    for (int i = 0; i < landDistr.white; i++)
    {
        landDeck[landIndex++] = plains;
    }
    for (int i = 0; i < landDistr.blue; i++)
    {
        landDeck[landIndex++] = island;
    }
    for (int i = 0; i < landDistr.black; i++)
    {
        landDeck[landIndex++] = swamp;
    }
    for (int i = 0; i < landDistr.red; i++)
    {
        landDeck[landIndex++] = mountain;
    }
    for (int i = 0; i < landDistr.green; i++)
    {
        landDeck[landIndex++] =  forest;
    }

    // combine spellDeck and landDeck
    for (int i = 0; i < spellCount; i++)
        fullDeck[i] = spellDeck[i];
    for (int i = 0; i < landCount; i++)
        fullDeck[i + spellCount] = landDeck[i];

    // shuffle 
    fullDeck.shuffle();

    // put deck into stack
    stack<Card> playDeck = createPlayDeck(fullDeck); 

    // draw cards from stack into hand 
    Hand playHand = drawHand(playDeck, 7);

    cout << "Hand Presort" << endl;

    playHand.output();

    playHand.sort();

    cout << "Hand Postsort" << endl;

    playHand.output();


    // sort hand 

    // write function to find a given mana value in deck 
    // do i have a card with mana value 5?
}

Manacost totalCostDeck(Deck<Card>& deck)
{
    if (deck.empty())
        return Manacost();
    else
    {
        Manacost totalCost;

        for (int i = 0; i < deck.size(); i++)
        {
            // I wonder if you could overload the += operator for a struct
            // or could potentially turn this into a class?

            totalCost.white += deck[i].getCost().white;
            totalCost.blue += deck[i].getCost().blue;
            totalCost.black += deck[i].getCost().black;
            totalCost.red += deck[i].getCost().red;
            totalCost.green += deck[i].getCost().green;
            totalCost.colorless += deck[i].getCost().colorless;
        }
        return totalCost;
    }

}
Manacost optimalLandDistribution(int landCount, const Manacost& totalCost)
{
    // store the landDistribution 
    Manacost landDist;

    int totalManaSymb = totalCost.white +
        totalCost.blue +
        totalCost.black +
        totalCost.red +
        totalCost.green;

    // calculate the total land count as float
    float whiteTotal = totalCost.white / static_cast<float>(totalManaSymb) * landCount;
    float blueTotal = totalCost.blue / static_cast<float>(totalManaSymb) * landCount;
    float blackTotal = totalCost.black / static_cast<float>(totalManaSymb) * landCount;
    float redTotal = totalCost.red / static_cast<float>(totalManaSymb) * landCount;
    float greenTotal = totalCost.green / static_cast<float>(totalManaSymb) * landCount;

    // truncate to int, set the value 
    landDist.white = static_cast<int>(whiteTotal);
    landDist.blue = static_cast<int>(blueTotal);
    landDist.black = static_cast<int>(blackTotal);
    landDist.red = static_cast<int>(redTotal);
    landDist.green = static_cast<int>(greenTotal);

    // how many lands do we got?
    int currLand = landDist.white + landDist.blue + landDist.black + landDist.red + landDist.green;

    float maxRemainder = 0.0;
    char colorToAdd = 'X'; // not a color but want to initialize 

    // if we have lands left to distribute, add to largest remainder
    // this is a way of fixing the % distribution problem
    // and to make sure we add back up to 17 lands 
    while (currLand < landCount)
    {
        if ((whiteTotal - landDist.white) > maxRemainder)
        {
            maxRemainder = whiteTotal - landDist.white;
            colorToAdd = 'W';
        }
        if ((blueTotal - landDist.blue) > maxRemainder)
        {
            maxRemainder = blueTotal - landDist.blue;
            colorToAdd = 'U';
        }
        if ((blackTotal - landDist.black) > maxRemainder)
        {
            maxRemainder = blackTotal - landDist.black;
            colorToAdd = 'B';
        }
        if ((redTotal - landDist.red) > maxRemainder)
        {
            maxRemainder = redTotal - landDist.red;
            colorToAdd = 'R';
        }
        if ((greenTotal - landDist.green) > maxRemainder)
        {
            maxRemainder = greenTotal - landDist.green;
            colorToAdd = 'G';
        }

        if (colorToAdd == 'W')
            landDist.white++;
        else if (colorToAdd == 'U')
            landDist.blue++;
        else if (colorToAdd == 'B')
            landDist.black++;
        else if (colorToAdd == 'R')
            landDist.red++;
        else if (colorToAdd == 'g')
            landDist.green++;

        currLand++;
    }
    return landDist;
}

stack<Card> createPlayDeck(const Deck<Card>& inDeck)
{
    stack<Card> playDeck;
    for (int i = 0; i < inDeck.size(); i++)
    {
        playDeck.push(inDeck[i]);
    }
    return playDeck;
}

Card draw(stack<Card>& inDeck)
{
    if (inDeck.empty())
        return Card();
    Card topCard = inDeck.top();
    inDeck.pop();
    return topCard;
}
Hand drawHand(stack<Card>& inDeck, int handSize)
{
    Hand hand;
    for (int i = 0; i < handSize; i++)
        hand.add(draw(inDeck));

    return hand;
}

