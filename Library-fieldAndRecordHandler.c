//Darlam Alves da Silva
//12682435


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Library-fieldAndRecordHandler.h"

#define TRUE 1
#define FALSE 0
#define SIZE_BUFFER 100

int main() {
    int totalBook = 0;
    //int* contTotalBook = 0;
    int ptrBooks = 0; 
    bookRecord *books;
    FILE* arq;
    if (openFile(&arq, "wb+, ccs=UTF-8")) {
        readTotalBooks(&totalBook);
        books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);
        readBooks(arq, totalBook, books);
        freeMemory(books, totalBook);
        fclose(arq);
    }
    
    if (openFile(&arq, "rb+, ccs=UTF-8")) {
        books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);
     scanf ("%d", &ptrBooks); 
     readElementsFile(arq, totalBook, books, &ptrBooks);
     freeMemory(books, totalBook);
     fclose(arq);
    }
    return 0;
}
    







