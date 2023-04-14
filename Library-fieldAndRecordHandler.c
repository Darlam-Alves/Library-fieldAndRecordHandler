#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define SIZE_BUFFER 100

typedef struct Book {
    int id;
    int byteOfSet;
    char* title;
    char* author;
} bookRecord;

void writeID(int id, FILE *file);
int readId();
void writeTitle(char *title, FILE *file); 
void writeAuthor(char *author, FILE *file); 
void readBuffer(char *buffer, int bufferSize); 
void readString(char **element);
bookRecord writeRegister(FILE *file); 
int openFile(FILE **arq, char *type);
int checkOpenFile(FILE *file);
void readTotalBooks(int *totalBook); 
void readBooks(FILE *arq, int totalBook, bookRecord *books); 
void readTitle(FILE *arq, char **title);
void readAuthor (FILE *arq, char **author);
void displayBookRecords(FILE *arq, int total, bookRecord *book);
void readElementsFile(FILE *arq, int total, bookRecord *book);
void freeMemory(bookRecord *books, int totalBook);

int main() {
    int totalBook = 0;
    bookRecord *books;
    FILE* arq;
    if (openFile(&arq, "wb+")) {
        readTotalBooks(&totalBook);
        books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);
        readBooks(arq, totalBook, books);
        freeMemory(books, totalBook);
        fclose(arq);
    }
    if (openFile(&arq, "rb+")) {
        books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);

       readElementsFile(arq, totalBook, books);
     freeMemory(books, totalBook);

       fclose(arq);
    }
    return 0;
}

void writeID(int id, FILE *file) {
    fwrite(&id, sizeof(int), 1, file); 
}

int  readId() {
    int id;
    scanf("%d", &id);
    return id;
}

void writeTitle(char *title, FILE *file) {
    int sizeStringTitle = strlen(title);
    char a = '|';
    fwrite(title, sizeof(char), sizeStringTitle, file); 
    fwrite(&a, sizeof(char), 1, file);
}

void writeAuthor(char *author, FILE *file) {
	char delimiter = -1; 
    int sizeStringAuthor = strlen(author);
    fwrite(&sizeStringAuthor, sizeof(int), 1, file); 
    fwrite(author, sizeof(char), sizeStringAuthor, file); 
    fwrite(&delimiter, sizeof(char), 1, file); 
}

void readBuffer(char *buffer, int bufferSize) {
    scanf(" %[^(\r|\n)]", buffer);
    buffer[strcspn(buffer, "\n")] = '\0'; 
}

void readString(char **element) {
    char buffer[SIZE_BUFFER];
    readBuffer(buffer, SIZE_BUFFER);
    *element = (char*) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(*element, buffer);
}

bookRecord writeRegister(FILE *file) {
    bookRecord myBook;
    myBook.id = readId(); 
    writeID(myBook.id, file);   

    readString(&myBook.title); 
    writeTitle(myBook.title, file); 

    readString(&myBook.author); 
    writeAuthor(myBook.author, file); 

    return myBook;
}

int openFile(FILE **arq, char *type){
    *arq = fopen("library.bin", type);
    if (*arq == NULL){
        printf("Error opening file.\n");
        return FALSE;
    } else {
        return TRUE; 
    }
}

int checkOpenFile(FILE *file){
    if (file == NULL)
        return 0;
    else
        return 1;
}

void readTotalBooks(int *totalBook) {
     scanf("%d", totalBook);
}

void readBooks(FILE *arq, int totalBook, bookRecord *books) {
    for (int i = 0; i < totalBook; i++) 
        books[i] = writeRegister(arq);
}

void readTitle(FILE *arq, char **title){ 
	char buffer[SIZE_BUFFER]; 
    int currentChar;
    int currentInputIndex = 0;

    while ((currentChar = fgetc(arq)) != EOF && currentChar != '|') 
    {
    	buffer[currentInputIndex++] = currentChar;
    }	
    buffer[currentInputIndex] = '\0';
    *title = (char*) malloc((strlen(buffer) + 1) * sizeof(char));
    strcpy(*title, buffer);

}

void readAuthor (FILE *arq, char **author){
	char buffer[SIZE_BUFFER]; 
    int sizeAuthor = 0;
    fread(&sizeAuthor, sizeof(int), 1, arq);
	fread(buffer, sizeof(char), sizeAuthor, arq);
	*author = (char*) malloc((strlen(buffer) + 1) * sizeof(char)); 
	strcpy(*author, buffer);
}

void displayBookRecords(FILE *arq, int total, bookRecord *book){
		book->byteOfSet = ftell(arq); 
        printf("Id: %d\n", book->id);
        printf("Title: %s\n", book->title);
        printf("Author: %s\n", book->author);
        printf ("ByteOfSet: %d\n", book->byteOfSet);
}

void readElementsFile(FILE *arq, int total, bookRecord *book) { 
	for (int i = 0; i < total; i++){

		fread(&book[i].id, sizeof(int), 1, arq);
		readTitle(arq, &book[i].title);
		readAuthor(arq, &book[i].author); 
        fgetc(arq);
		displayBookRecords(arq, book[i].byteOfSet, &book[i]);
	}
}

void freeMemory(bookRecord *books, int totalBook) {
    for (int i = 0; i < totalBook; i++) {
        free(books[i].title);
        free(books[i].author);
    }
    free(books);
}






