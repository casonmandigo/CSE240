// CSE 240
// READ BEFORE YOU START:
// You are given a partially completed program that creates a list of books with the dates that they have been bought.
// Each book has the corresponding information: title, author, price, and a linked list of dates that has been bought.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk failing the automated test cases.
//
// You are to assume that all input is valid:
// Valid title:	String containing alphabetical letters beginning with a capital letter
// Valid author: String containing alphabetical letters beginning with a capital letter
// Valid price: A float number
// Valid date:	String in the following format: "MM/DD/YYYY" ex: "01/01/2010"
// All input will be a valid length and no more than the allowed amount of memory will be used
//
// Q1 : CLASS METHODS Part 1 : Constructor, Accessor, and set Methods for Book class in Book.cpp file	(5 points)
// Q2 : CLASS METHODS Part 2 : Class methods for Book class in Book.cpp file							(10 points)
// Q3 : Add Function in hw09.cpp file																	(5 points)
// Q4 : Search Function in hw09.cpp file																(5 points)
// Q5 : Change Price Function in hw09.cpp file															(5 points)
// Q6 : Remove Book Function in hw09.cpp file															(10 points)
// Q7 : Print_all function using cin and cout in hw09.cpp file											(10 points)

#include <iostream>
#include <fstream>
#include <string>

#include "Container.h"
#include "Book.h"
#include "Buy.h"

using namespace std;

// forward declarations
void flush();
void branching(char);
void helper(char);
void add_book(string, string, float);
void change_price(Book *);
Book* search_book(string,string);
void remove_book(string,string);
void print_all(Container*);


Container* list = NULL; // global list

int main()
{

	char ch = 'i';

	do {

		cout << "Please enter your selection\n";
		cout << "\ta: add a new book to the list\n";
		cout << "\tc: change the price of a book\n";
		cout << "\tb: buy a book\n";
		cout << "\tr: remove a book from the list\n";
		cout << "\tp: print all books on the list\n";
		cout << "\tq: quit\n";
		cin >> ch;		

		flush();
		branching(ch);
	} while (ch != 'q');

	list = NULL;
	return 0;
}

void flush()
{
	int c;
	do c = getchar(); while (c != '\n' && c != EOF);
}

void branching(char c)
{
	switch (c) {
	case 'a':
	case 'b':
	case 'c':
	case 'r':
	case 'p':
		helper(c);
		break;
	case 'q':
		break;
	default:
		printf("\nInvalid input!\n\n");
	}
}

// The helper function is used to determine how much data is needed and which function to send that data to.
// It uses pointers and values that are returned from some functions to produce the correct ouput.
// There is no implementation needed here, but you should study this function and know how it works.
// It is always helpful to understand how the code works before implementing new features.
// Do not change anything in this function or you risk failing the automated test cases.
void helper(char c)
{
	string title, author;
	float price;
	if (c == 'p')
		print_all(list);
	else
	{
		cout << endl << "Please enter the books's title: " << endl;
		cin >> title;
		cout << "Please enter the books's author: " << endl;
		cin >> author; 
		cout << "Please enter the price of the book: " << endl;
		cin >> price;
		flush();

		Book* book_result = search_book(title,author);

		if (c == 'a') // add book
		{
			if (book_result == NULL)
			{
				add_book(title, author,price);
				cout << endl << "Book was added." << endl << endl;
			}
			else
				cout << endl << "Book is already on the list." << endl << endl;
		}
		else if (c == 'c')
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}
			change_price(book_result);

			
		}
		else if (c == 'b') // buy book
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}

			string date;
			cout << "Please enter the date of the buying: " << endl;
			cin >> date; flush();

			book_result->buyBook(date);
			cout << endl << "Date of buying is added." << endl << endl;
		}
		else if (c == 'r') // remove book
		{
			if (book_result == NULL)
			{
				cout << endl << "Book was not found." << endl << endl;
				return;
			}

			remove_book(title,author);
			cout << endl << "Book is removed from the list." << endl << endl;
		}
	}
}

// Q3: Add Book (5 points)
// This function will be used to add a new book to the head of you linked list of containers, no need for sorting.
// The search function is called before this function, therefore you can assume the book is not already on the list.
void add_book(string title, string author, float price)
{
	Book* temp = new Book(title, author, price);
	Container *p1 = new Container();
	p1->book = temp;

	if (list == NULL)
	{
		list = p1;
	}
	else
	{
		p1->next = list;
		list = p1;
	}
}

// Q4: Search Book (5 points)
// This function will be used to search for a book on the list. 
// You must traverse the list and return a pointer to a 'Book' with the desired title AND author.
// If the book does not exist on the list, return NULL. (See helper function for use of this function).
Book* search_book(string title,string author)
{
	Container *traverser = list;
	
	while (traverser != NULL)
	{
		if (traverser->book->getTitle().compare(title) == 0)
		{
			if (traverser->book->getAuthor().compare(author) == 0)
			{
				return traverser->book;
			}
			else
			{
				traverser = traverser->next;
			}
		}
		else
		{
			traverser = traverser->next;
		}
	}
	return NULL; 
}
// Q5: Change price (5 points)
// This function will be used to change the price of a book. 
// The function gets a pointer to the book and change the value of price using the set function inside the book class.
void change_price(Book * book) 
{
	float newprice;
	printf("Please enter the new price for the book: \n");
	cin >> newprice;
	book->setPrice(newprice);
	printf("The price of the book was changed\n");

}

// Q6: Remove Book (15 points)
// This function will be used to remove a book from the list. 
// Traverse the list and use the parameters to remove the book. 
// You must remove all the elements in the buys linked list. 
void recursivefunc(Container* list, string author, string title)
{
	if (list->next == NULL)
	{
		return;
	}

	if (list->next->book->getTitle().compare(title) == 0)
	{
		if (list->next->book->getAuthor().compare(author) == 0)
		{
			Container* traverser = list->next->next;

			delete list->next->book->buys;
			delete list->next->book;
			delete list->next;

			list->next = NULL;
			list->next = traverser;
		}
		else
		{
			recursivefunc(list->next, author, title);
		}
	}
	else
	{
		recursivefunc(list->next, author, title);
	}
}

void remove_book(string title, string author)
{
	Container* p1 = list;

	if (p1 == NULL)
	{
		return;
	}
	
	if (p1->book->getTitle().compare(title) == 0)
	{
		if (p1->book->getAuthor().compare(author) == 0)
		{
			list = p1->next;

			delete p1->book->buys;
			delete p1->book;
			delete p1;

			p1 = NULL;

			printf(" Book is removed form the list.\n");
			return;
		}
	}
	else
	{
		recursivefunc(p1, author, title);
	}
}

// Question 7. Print_all (10 points for this question)
// Write a recursive function to implement the print_all function. 
// You will not receive any point if you use a while loop. 
// Please use comments to indicate the four steps (1 point each step): 
// (1) size-n problem, (2) stopping condition and return value, 
// (3) size-(n-1) problem, (4) construct the solution of size-n problem
// You should print out the information of a book and also the number of times a book has been bought.
// For each time that a book has been bought, you should print out the date.
// You should use the methods inside the book.cpp file to print. 
void print_all(Container* top)		// Size-n Problem
{
	if (top == NULL)	// Stopping Condition
	{
		return;			// Stopping Condition returns nothing
	}
	else
	{
		// Constructin the solution of the size-n problem
		cout << top->book->toString();
		cout << "Bought " << top->book->timesBought() << " times" << endl;
		cout << "Dates:" << top->book->displayBought() << endl;
		cout << endl;

		// Size-(n-1) problem
		print_all(top->next);
	}
}