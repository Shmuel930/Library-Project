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
	return Name[i + 1];
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
	}


	for (int i = 0; i < CurrentMaxbooks; i++) {
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
	cout << "Please enter book name: ";
	cin.getline(NewbookName, book_NAME);
	cout << "Please enter author name: ";
	cin.getline(NewbookAuthor, AUTHOR);

	int ArrayIndex = LastNameLetter(NewbookAuthor) - 'a';
	for (int i = 0; i < LengthOfArray((books[ArrayIndex].ptr)); i++) {
		// iteration of all books in booklist.
		if (strcmp(books[ArrayIndex].ptr[i].name, NewbookName) == 0 && strcmp(books[ArrayIndex].ptr[i].author, NewbookAuthor) == 0)
		{
			// this is in case that the book is already exist.
			cout << "Please enter how many books: ";
			cin >> numberOfNewbooks;
			if (numberOfNewbooks + books[ArrayIndex].numbooks_Exist > books[ArrayIndex].numbooks_Max)
				UpdateMaxbooks(books, ArrayIndex);

			books[ArrayIndex].ptr[i].numCopies += numberOfNewbooks;
			return;
		}
	}


	// if the book isnt exist and theres full books in booklist. double the space.
	if (books[ArrayIndex].numbooks_Exist == books[ArrayIndex].numbooks_Max)
		UpdateMaxbooks(books, ArrayIndex);


	int index = 0;
	while (books[ArrayIndex].ptr[index].name)
		index++;

	cout << "Please enter how many books: ";
	cin >> numberOfNewbooks;
	cout << "Please enter price ";
	cin >> PriceOfNewBook;

	strcpy_s(books[ArrayIndex].ptr[index].name, NewbookName);
	strcpy_s(books[ArrayIndex].ptr[index].author, NewbookAuthor);
	books[ArrayIndex].ptr[index].numCopies = numberOfNewbooks;
	books[ArrayIndex].ptr[index].price = PriceOfNewBook;

}

void printbooks(booklist books[], char first) {
	
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < books[i].numbooks_Exist; j++)
			if (books[i].ptr[j].author[0] == first) // if the first letter of the author is 'first' than print his book
				cout << books[i].ptr[j].name << endl;
	
}

int main() {
	booklist bookArray[26]; // the array index is the aothor Last name.
	for (int i = 0; i < 26; i++) {
		bookArray[i].numbooks_Max = 0;
		bookArray[i].ptr = new book[0];
	}

	purchasebook(bookArray);
}
