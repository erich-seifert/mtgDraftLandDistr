
DS final project proposal
* What problem will your project solve/simulate?
    1) what is the ideal distribution of mana in a given draft deck based on the mana
    cost associated with your drafted pile of cards
        - count all the distinct mana symbols in your deck of playable cards (23)
        - figure out what distribution of lands is ideal for your card pool
    2) Draw cards from a ideal distribution deck and sort them in your hand 

* Identify a class you will write to store data critical to the application.
    - The Class would be a distinct card, its name, mana cost/value
    - A Deck contains cards and is a template function
    - a Hand contains cards and must be sorted 

* What will be stored in a dynamic array?  A linked List?
    - Dynamic array = Original Deck
    - Linked List = Hand 
* What template class will you write?
    - The deck will be a template class, you could have a deck of anything
    - and you can shuffle anything
* How will you use a stack, queue or tree?
    - After making the deck as an array pop it into a stack, to simulate drawing 
* What will you search for?
    - I want to find the largest mana value of card in my deck 
* What will you sort (put in order)?
    - After you draw your hand from the deck sort it 
* How will you use an STL container class?  An STL function?
    - Leveraging Stack, push and pop 

