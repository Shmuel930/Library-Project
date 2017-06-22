#include <iostream>
using namespace std;

/*
Project number 3, Libray project.

Made by:
Shmuel Cohen, ID:313326258
Eran Atia,	  ID:204122055

*/
const int book_NAME = 30;
const int AUTHOR = 20;
const int MAX_BOOKS = 26;

struct book {
	char name[book_NAME];
	char author[AUTHOR];
	int numCopies;
	double price;
};
struct booklist {
	book * ptr;
	int numbooks_Max;
	int numbooks_Exist;
};

char LastNameLetter(char Name[]) {
	// get a string and return the last name letter of the author.
	int i = 0;
	while (Name[i] != ' ')
		i++;

	return tolower(Name[i + 1]);
}
int MyStrCmp(char str1[], char str2[]) {
	// return -1 if str1 < str2 (by alfabetic order).
	// return 0 is str1 equals str2.
	// return 1 if str1 > str2.
	// all of thoes without case sensetive.

	int i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (tolower(str1[i]) < tolower(str2[i]))
			return -1;
		if ((tolower(str1[i]) > tolower(str2[i])))
			return 1;
		i++;
	}

	return 0;
}
void UpdateMaxbooks(booklist books[], int bookNum) {
	int CurrentMaxbooks = books[bookNum].numbooks_Max;
	book * newbookArray;
	// if theres no books, then the max books is 1.
	if (CurrentMaxbooks == 0) {
		newbookArray = new (nothrow) book[1];
		books[bookNum].numbooks_Max = 1;
	}
	else {
		newbookArray = new (nothrow) book[CurrentMaxbooks * 2];
		if (!newbookArray) {
			// check that theres enough space in memory for the array.
			cout << "Not enough memory for new array.";
			return;
		}
		books[bookNum].numbooks_Max = CurrentMaxbooks * 2;

		for (int i = 0; i < CurrentMaxbooks; i++)
			newbookArray[i] = books[bookNum].ptr[i];

	}
	delete[] books[bookNum].ptr; // delete the old array.
	books[bookNum].ptr = newbookArray; // point the old array to the new array.

}
void purchasebook(booklist books[]) {

	char NewbookName[book_NAME];
	char NewbookAuthor[AUTHOR];
	int numberOfNewbooks;
	int PriceOfNewBook;
	cout << "Please enter author name: ";
	cin.getline(NewbookAuthor, AUTHOR);
	cout << "Please enter book name: ";
	cin.getline(NewbookName, book_NAME);


	int ArrayIndex = LastNameLetter(NewbookAuthor) - 'a';
	for (int i = 0; i <books[ArrayIndex].numbooks_Exist; i++) {
		// iteration of all books in booklist.
		if (MyStrCmp(books[ArrayIndex].ptr[i].name, NewbookName) == 0 && MyStrCmp(books[ArrayIndex].ptr[i].author, NewbookAuthor) == 0)
		{
			// this is in case that the book is already exist.
			cout << "Please enter how many books: ";
			cin >> numberOfNewbooks;
			cin.ignore();
			if (numberOfNewbooks + books[ArrayIndex].numbooks_Exist > books[ArrayIndex].numbooks_Max)
				UpdateMaxbooks(books, ArrayIndex);

			books[ArrayIndex].ptr[i].numCopies += numberOfNewbooks;
			return;
		}
	}


	// if the book isnt exist and theres full books in booklist. double the space.
	if (books[ArrayIndex].numbooks_Exist == books[ArrayIndex].numbooks_Max)
		UpdateMaxbooks(books, ArrayIndex);


	cout << "Please enter how many books: ";
	cin >> numberOfNewbooks;
	cout << "Please enter price: ";
	cin >> PriceOfNewBook;
	cin.ignore(); // flush the newline out of the buffer


	int InsertIndex = books[ArrayIndex].numbooks_Exist; // this is where the new book is gonna be inserted.

	strcpy_s(books[ArrayIndex].ptr[InsertIndex].name, NewbookName);
	strcpy_s(books[ArrayIndex].ptr[InsertIndex].author, NewbookAuthor);
	books[ArrayIndex].ptr[InsertIndex].price = PriceOfNewBook;
	books[ArrayIndex].ptr[InsertIndex].numCopies = numberOfNewbooks;
	books[ArrayIndex].numbooks_Exist++;

}
void printBooks(booklist books[], char first) {
	int ArrayIndex = tolower(first) - 'a';

	if (books[ArrayIndex].numbooks_Exist == 0)
		cout << "This author dosent have any book in the libary";
	else
	{
		cout << "These are the books of the authors start with " << first << endl;
		for (int i = 0; i < books[ArrayIndex].numbooks_Exist; i++)
			cout << "(" << i + 1 << ") " << books[ArrayIndex].ptr[i].name << endl;
	}

}
void printSortedBooks(booklist books[], char first) {

	int IndexArray = tolower(first) - 'a';
	int NumberOfBooks = books[IndexArray].numbooks_Exist;
	if (NumberOfBooks == 0) {
		cout << "The author has no books !\n";
		return;
	}
	int InsertIndex = 0; //
	book *SortedArray = new book[NumberOfBooks];

	// loop all the books and instert them to the SortedArray by the value.
	for (int i = 0; i < NumberOfBooks; i++) {
		for (int j = 0; j < NumberOfBooks; j++) {
			if (MyStrCmp(books[IndexArray].ptr[i].name, books[IndexArray].ptr[j].name) > 0)
				InsertIndex++;
		}
		SortedArray[InsertIndex] = books[IndexArray].ptr[i];
		InsertIndex = 0;
	}

	cout << "Sorted Books: " << endl;
	for (int i = 0; i < NumberOfBooks; i++) {
		cout << SortedArray[i].name << endl;
	}

	delete[] SortedArray; // free the memory after using the array.
}
void printAll(booklist books[]) {
	// print all the books in the libary.

	int bookCounter = 1;

	for (int j = 0; j < MAX_BOOKS; j++)
		for (int i = 0; i < books[j].numbooks_Exist; i++) {
			cout << "(" << bookCounter << ") " << books[j].ptr[i].name << endl;
			bookCounter++;
		}

	if (bookCounter == 1)
		cout << "There is no books in the libary" << endl;

}
void cheapest(booklist books[]) {
	// print the cheapest books in the libary.

	bool EmptyLibary = true;
	double minPrice;


	for (int j = 0; j < MAX_BOOKS; j++)
		for (int i = 0; i < books[j].numbooks_Exist; i++) {
			if (EmptyLibary) {
				// if the first book is found
				minPrice = books[j].ptr[i].price;
				EmptyLibary = false;
			}
			if (books[j].ptr[i].price < minPrice)
				minPrice = books[j].ptr[i].price;
		}

	if (EmptyLibary)
		cout << "Library is empty" << endl;

	else
	{
		cout << "Those books are the cheapest, with price of: " << minPrice << endl;
		for (int j = 0; j < MAX_BOOKS; j++)
			for (int i = 0; i < books[j].numbooks_Exist; i++) {
				if (books[j].ptr[i].price == minPrice)
					cout << books[j].ptr[i].name << endl;
			}
	}

}
void removeBookCopy(booklist books[], char* author, char* bookName, int NumOfCopies)
{
	int ArrayIndex = LastNameLetter(author) - 'a';
	int NumberOfBooks = books[ArrayIndex].numbooks_Exist;

	for (int i = 0; i < NumberOfBooks; i++) {
		if (MyStrCmp(bookName, books[ArrayIndex].ptr[i].name) == 0)
		{
			// if theres a match between the books.

			if (books[ArrayIndex].ptr[i].numCopies - NumOfCopies > 0) {
				books[ArrayIndex].ptr[i].numCopies -= NumOfCopies;
				return;
			}
			else
			{
				for (int j = i; j < NumberOfBooks - 1; j++)
					books[ArrayIndex].ptr[j] = books[ArrayIndex].ptr[j + 1];

				books[ArrayIndex].numbooks_Exist--;
			}
			break;
		}
	}
}
int numCopies(booklist books[], char* Word) {
	// return the number of copies of book.

	int cntCopies = 0;
	for (int j = 0; j < MAX_BOOKS; j++)
		for (int i = 0; i < books[j].numbooks_Exist; i++)
			if (strstr(books[j].ptr[i].name, Word) != NULL)
				cntCopies += books[j].ptr[i].numCopies;

	return cntCopies;
}

void LibraryMenu(booklist books[]) {
	// this is custom made menu that can acess all the functions.

	int UserOption;
	char author;
	system("CLS");
	cout << "(1) Purchase Book " << endl;
	cout << "(2) Print Books" << endl;
	cout << "(3) Print Sorted Books" << endl;
	cout << "(4) Print All" << endl;
	cout << "(5) Cheapest books " << endl;
	cout << "(6) Remove Book Copy " << endl;
	cout << "(7) number of Copeis" << endl;
	cout << "(8) Exit" << endl;
	cin >> UserOption;

	while (UserOption < 1 || UserOption >8) {
		cout << "Please enter valid option." << endl;
		cin >> UserOption;
	}

	cin.ignore();

	switch (UserOption)
	{
	case 1:
		system("CLS");
		purchasebook(books);
		break;

	case 2:
		system("CLS");
		char first;
		cout << "Enter first char of author last name: ";
		cin >> first;
		printBooks(books, first);
		system("Pause");
		break;

	case 3:
		system("CLS");
		cout << "Enter letter of author: ";
		cin >> author;
		printSortedBooks(books, author);
		system("Pause");
		break;

	case 4:
		system("CLS");
		printAll(books);
		system("Pause");
		break;

	case 5:
		system("CLS");
		cheapest(books);
		system("Pause");
		break;

	case 6:
		system("CLS");
		cout << "Remove book by name." << endl;
		char bookName[book_NAME];
		char bookAuthor[AUTHOR];
		int numberofcopies;
		cout << "Please enter author name: ";
		cin.getline(bookAuthor, AUTHOR);
		cout << "Please enter book name: ";
		cin.getline(bookName, book_NAME);
		cout << "Please enter number of copies: ";
		cin >> numberofcopies;
		cin.ignore();
		removeBookCopy(books, bookAuthor, bookName, numberofcopies);
		break;

	case 7: {
		system("CLS");

		char* word = new char[30];
		cout << "Number of copies !" << endl << "Please enter the name of the book : ";
		cin >> word;
		cout << "Number of copies: " << numCopies(books, word) << endl;;
		delete[] word; // free the memory after using the array.
		system("Pause");
		break;
	}
	case 8:
		exit(0);
		break;


	}
}


int main() {
	booklist bookArray[MAX_BOOKS]; // the array index is the aothor Last name.
	for (int i = 0; i < MAX_BOOKS; i++) {
		bookArray[i].numbooks_Max = 0;
		bookArray[i].numbooks_Exist = 0;
		bookArray[i].ptr = new book[0];
	}

	while (true)
		LibraryMenu(bookArray);

}
