/*
 * Name: Erich Seifert
 * History Member Function Definitions
 * Course: CSI218 (Spring 2025)
 * Lecture: Linked Lists
 * Date: 05/07/2025
 * Description: Hand member function definitions.
 *				Linked list implementation, keeping track
 *				of list with pointer to first node in list.
 */

#ifndef HAND_CPP
#define HAND_CPP

#include <iostream>
#include "hand.h"

using namespace std;

// History member function definitions.

// Constructors
Hand::Hand()
{
	firstP = NULL;  // initially empty
}

// Copy constructor
Hand::Hand(const Hand& otherHand)
{
	firstP = NULL;  // initially empty

	// Copy list from other history.
	append(otherHand);
}

// Destructor
Hand::~Hand()
{
	clear();
}

// Assignment operator
Hand& Hand::operator =(
	const Hand& otherHand)
{
	// AVOID COPYING IF ASSIGNING OBJECT TO SELF.
	if (this != &otherHand)
	{
		// COPY NON-DYNAMIC MEMBERS (NONE HERE).


		// REMOVE CURRENT NODES, RESET POINTER.
		clear();

		// COPY ITEMS FROM OTHER HISTORY.
		append(otherHand);
	}

	// RETURN SELF.
	return *this;
}

// Accessors

// Precondition: "i" is zero-based index.
Card Hand::get(int i) const
{
	// TRAVERSE LIST TO FIND ith ITEM
	// ("COUNT" ITEMS TO DETERMINE ith).
	int count = 0;
	for (Node* traverseP = firstP;
		traverseP != NULL;
		traverseP = traverseP->linkP)
	{
		if (count == i)
			return traverseP->info;
		count++;
	}

	cerr << "Invalid history index: " << i << endl;
	return Card();
}

void Hand::output() const
{
	cout << "History:";

	for (Node* traverseP = firstP;
		traverseP != NULL;
		traverseP = traverseP->linkP)
		cout << " " << traverseP->info.getName();
}

// Mutators
void Hand::add(const Card& val)
{
	// Allocate new node and store data.
	Node* newNodeP = new Node;
	newNodeP->info = val;

	// ADD NEW NODE INTO LINKED LIST.
	newNodeP->linkP = firstP;

	firstP = newNodeP;
}

// Remove all items
void Hand::clear()
{
	while (firstP != NULL)
	{
		Node* nextP = firstP->linkP;

		delete firstP;

		firstP = nextP;
	}
}

// Add all items from other history
void Hand::append(const Hand& otherHand)
{
	for (Node* traverseP = otherHand.firstP;
		traverseP != NULL;
		traverseP = traverseP->linkP)
		add(traverseP->info);
}

#endif