#include <iostream>
using namespace std;


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

}
int main() {
	int Max_numBooks = 0;
	BOOKLIST* bookArray = new BOOKLIST[Max_numBooks];
}
