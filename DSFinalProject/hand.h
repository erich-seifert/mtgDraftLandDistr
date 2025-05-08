/*
 * Name: Erich Seifert
 * Hand Class Definition
 * Course: CSI 218 (Spring 2025)
 * Date: 05/07/2025
 * Description: Hand class definition declaring
 *				data members and member functions.
 */
#ifndef HAND_H
#define HAND_H
#include "card.h"
// Node stores data in linked list.
struct Node
{
	Card info;
	Node* linkP;
};

class Hand
{
public:
	// Constructors
	Hand();  // no size since can grow

	// Copy constructor
	Hand(const Hand& otherHand);

	// Assignment operator
	Hand& operator =(
		const Hand& otherHand);

	// Destructor
	~Hand();

	// Accessors

	Card get(int i) const;
	// Precondition: "i" is zero-based index.

	void output() const;

	// Mutators

	void add(const Card& val);

	void clear();

	// sorts the linked list via insertion sort 
	void sort();

	// Accessor and Mutator 
	// removes card from hand and returns it
	//Card play();

private:
	Node* firstP;  // point to first node (head) of linked list

	// Append items to end of history (make
	// this "public" if useful to "client").
	void append(const Hand& otherHand);
};

#endif
