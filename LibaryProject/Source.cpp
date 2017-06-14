#include <iostream>
using namespace std;


//Note: Remmber to use DELETE command to delete the heap memory. delete []arr.
const int book_NAME = 30;
const int AUTHOR = 20;

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

void CompareName(char str1[], char str2[]) {

}
char LastNameLetter(char Name[]) {
	int i = 0;
	while (Name[i] != ' ')
		i++;
	//&&Ask raid if can use tolower.
	return tolower(Name[i + 1]);
}

int LengthOfArray(book* arr) {
	return sizeof(arr) / sizeof(arr[0]);
}
void UpdateMaxbooks(booklist books[], int bookNum) {
	int CurrentMaxbooks = books[bookNum].numbooks_Max;
	book * newbookArray;
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
		if (strcmp(books[ArrayIndex].ptr[i].name, NewbookName) == 0 && strcmp(books[ArrayIndex].ptr[i].author, NewbookAuthor) == 0)
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
	int ArrayIndex =(int)first - 'a';

	if (books[ArrayIndex].numbooks_Exist == 0)
		cout << "This author dosent have any book in the libary";
	else
	{
		cout << "This are the books of the authors start with " << first << endl;
		for (int i = 0; i < books[ArrayIndex].numbooks_Exist; i++)
			cout << "(" << i+1 << ") " << books[ArrayIndex].ptr[i].name << endl;
	}
	
}

void printSortedBooks(booklist books[], char first) {
	int ArrayIndex = (int)first - 'a';

	if (books[ArrayIndex].numbooks_Exist == 0)
		cout << "This author dosent have any book in the libary";
	else
	{
		cout << "This are the books of the authors start with " << first << endl;
		for (int i = 0; i < books[ArrayIndex].numbooks_Exist; i++)
			cout << "(" << i + 1 << ") " << books[ArrayIndex].ptr[i].name << endl;
	}

}

void printAll(booklist books[]) {
	int bookCounter = 1;

		for (int j = 0; j < 26; j++)
			for (int i = 0; i < books[j].numbooks_Exist; i++) {
				cout << "(" << bookCounter << ") " << books[j].ptr[i].name << endl;
				bookCounter++;
			}

		if (bookCounter == 1) 
			cout << "There is no books in the libary" << endl;

} 
void cheapest(booklist books[]) {
	bool EmptyLibary = true;
	int minPrice;
	

	for (int j = 0; j < 26; j++)
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
		for (int j = 0; j < 26; j++)
			for (int i = 0; i < books[j].numbooks_Exist; i++) {
				if (books[j].ptr[i].price == minPrice)
					cout << books[j].ptr[i].name << endl;
			}
	}

}
void removeBookCopy(booklist books[], char* author, char* bookName, int NumOfCopies)
{

}

int main() {
	booklist bookArray[26]; // the array index is the aothor Last name.
	for (int i = 0; i < 26; i++) {
		bookArray[i].numbooks_Max = 0;
		bookArray[i].numbooks_Exist = 0;
		bookArray[i].ptr = new book[0];
	}
	int x = 5;
	int *px = &x;
	int **ppx = &px;

}
