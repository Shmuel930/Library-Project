#include <iostream>
using namespace std;


//Note: Remmber to use DELETE command to delete the heap memory. delete []arr.
const int BOOK_NAME = 30;
const int AUTHOR = 20;

typedef struct book {
	char name[BOOK_NAME];
	char author[AUTHOR];
	int numCopies;
	double price;
}BOOK;

typedef struct booklist {
	BOOK * ptr;
	int numBooks_Max;
	int numBooks_Exist;
} BOOKLIST;

void UpdateMaxBooks(BOOKLIST books[], int BookNum) {
	int CurrentMaxBooks = books[BookNum].numBooks_Max;
	BOOK * newBookArray;
	if (CurrentMaxBooks == 0) {
		newBookArray = new (nothrow) BOOK[1];
		books[BookNum].numBooks_Max = 1;
	}
	else {
		newBookArray = new (nothrow) BOOK[CurrentMaxBooks * 2];
		if (!newBookArray) {
			// check that theres enough space in memory for the array.
			cout << "Not enough memory for new array.";
			return;
		}
		books[BookNum].numBooks_Max = CurrentMaxBooks * 2;
	}


	for (int i = 0; i < CurrentMaxBooks; i++) {
		newBookArray[i] = books[BookNum].ptr[i];
	}

	delete[] books[BookNum].ptr; // delete the old array.
	books[BookNum].ptr = newBookArray; // point the old array to the new array.

}


int main() {
	BOOKLIST BookArray[26];
	for (int i = 0; i < 26; i++) {
		BookArray[i].numBooks_Max = 0;
		BookArray[i].ptr = new BOOK[0];
	}

	for (int i = 0; i < 100; i++) {
		UpdateMaxBooks(BookArray, 2);
		cout << i << endl;
	}
	UpdateMaxBooks(BookArray, 2);



}
