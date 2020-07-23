#include "SoftCopy.h"
/* YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. DO NOT MODIFY THE HEADER FILE AS IT WILL BE
REPLACED BY THE ORIGINAL HEADER DURING TESTING. THE REQUIRED
HEADER FILE IS ALREADY INCLUDED FOR YOU ABOVE THIS COMMENT BLOCK.
THE CONSTRUCTOR and DESTRUCTOR ARE ALREADY IMPLEMENTED.
START YOUR IMPLEMENTATIONS BELOW THOSE. */


// DONE
SoftCopy::SoftCopy(int ISBN, double price, int startPage, int endPage) : Book(ISBN, price) {
	this->startPage = startPage;
	this->endPage = endPage;
	this->numberOfPages = (endPage - startPage) + 1;
	this->firstHalf = NULL;
	this->secondHalf = NULL;
	this->pageContent = "";
}

// DONE
SoftCopy::~SoftCopy() {
	if (firstHalf != NULL)
		delete firstHalf;
	if (secondHalf != NULL)
		delete secondHalf;
}
