#include "Book.h"
#include <string>
#include <iostream>


// Q1 : CLASS METHODS Part 1 : Constructor, Accessor, and Set Methods for Book (5 points)

// Constructor
// Create a constructor for the class Book which takes 2 string parameters and one float parameter.
// Use the parameters to initialize the three private local variables title, author, and price.
// HINT: Don't forget to initialize your linked list of buys to NULL.

// Constructor for Container class
Book::Book(string s1, string s2, float f1) {
	Book::title = s1;
	Book::author = s2;
	Book::price = f1;
	buys = NULL;
}

// Accessor and Set Methods
// Create accessor and set methods for private local strings title and author and also float price.

string Book::getTitle()
{
	return Book::title;
}

string Book::getAuthor()
{
	return Book::author;
}

float Book::getPrice()
{
	return Book::price;
}

void Book::setTitle(string title1)
{
	Book::title = title1;
}

void Book::setAuthor(string author1)
{
	Book::author = author1;
}

void Book::setPrice(float f1)
{
	Book::price = f1;
}

// Q2 : CLASS METHODS Part 2 : Class Methods for Book (10 points)

// Create a method called "toString"
// This method has no input parameters and returns the string containing the title, author, and price of a book.
// This function is used in print_all function inside main to print the information of a book.
// The exact format can be found in the sample output of assignment description. 

string Book::toString()
{
	string str;
	str = "\nTitle: " + Book::title + "\nAuthor: " + Book::author + "\nPrice: " + to_string(Book::price) + "\n";
	return str;
}

// Create a method named "buyBook" which has one string parameter date and no return type (see helper function for use).
// This method is used to add a new date to the book's linked list of buys. The string parameter is the date of buying.
// You should add the date to the tail of the linked list "buys". Buys will be added in chronological order.

void Book::buyBook(string date)
{
	if (buys == NULL)
	{
		buys = new Buy(date);
		return;
	}
	else
	{
		Buy* p1 = buys;

		while (p1->next != NULL)
		{
			p1 = p1->next;
		}
		
		p1->next = new Buy(date);
		delete p1;
	}
}

// Create a method named "timesBought"
// This method has no input parameters and returns the number of times the book has been bought.
// This function is used in print_all function inside the main function. 

int Book::timesBought()
{
	Buy* p1 = buys;
	int count = 0;

	if (p1 == NULL)
	{
		return count;
	}
	else
	{
		while (p1 != NULL)
		{
			count++;
			p1 = p1->next;
		}
	}
	
	delete p1;
	return count;
}

// Create a method named "displayBought" which has no parameters and returns a string (see print_all function for use).
// This method will be used to return a string for the dates where the book has been bought.
// If the book was not bought, return an empty string.

string Book::displayBought()
{
	Buy* p1 = buys;
	string str;

	while (p1 != 0)
	{
		str = str + "\n" + p1->getDate();
		p1 = p1->next;
	}

	delete p1;
	return str;
}
