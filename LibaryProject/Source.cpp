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
		books[BookNum].numBooks_Max = 1;
		newBookArray = new BOOK[1];
	}
	else {
		books[BookNum].numBooks_Max = CurrentMaxBooks * 2;
		newBookArray = new BOOK[CurrentMaxBooks * 2];
	}

	for (int i = 0; i < CurrentMaxBooks; i++) {
		newBookArray[i] = books[BookNum].ptr[i];
	}

	delete[] books[BookNum].ptr;

}


int main() {
	BOOKLIST BookArray[26];
	for (int i = 0; i < 26; i++)
		BookArray[i].numBooks_Max = 0;




}
