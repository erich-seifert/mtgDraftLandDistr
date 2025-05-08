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


1) linked list
2) template the deck class 
3) once you have lands in deck put into queue
4) draw 7 cards and put into linked list 
5) sort the 7 cards 
6) search for lowest mana value in hand 
*/