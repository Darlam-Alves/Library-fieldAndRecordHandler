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
    if (openFile(&arq, "wb")) {
        readTotalBooks(&totalBook);
        books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);
        readBooks(arq, totalBook, books);
        freeMemory(books, totalBook);
        fclose(arq);
    }
    if (openFile(&arq, "rb, ccs=UTF-8")) {
       books = (bookRecord*) malloc(sizeof(bookRecord)*totalBook);
       readElementsFile(arq, totalBook, books);
       fclose(arq);
    }
    freeMemory(books, totalBook);
    return 0;
}

void writeID(int id, FILE *file) {
    fwrite(&id, sizeof(int), 1, file); // write the ID to the file
}

int readId() {
    int id;
    scanf("%d", &id);
    getchar();
    return id;
}

void writeTitle(char *title, FILE *file) {
    char delimiter = '|';
    int sizeStringTitle = strlen(title);
    fwrite(title, sizeof(sizeStringTitle), 1, file); // write the title to the file
    fwrite(&delimiter, sizeof(char), 1, file);
}

void writeAuthor(char *author, FILE *file) {
    char delimiter = -1;
    int sizeStringAuthor = strlen(author);
    fwrite(&sizeStringAuthor, sizeof(int), 1, file); // write the string size
    fwrite(author, sizeof(sizeStringAuthor), 1, file); // write the author to the file
    fwrite(&delimiter, sizeof(char), 1, file); // add delimiter -1 to the author's name
}



void readString(char **element) {
    char buffer[SIZE_BUFFER];
    scanf(" %[^(\r|\n)]", buffer); 
    *element = (char*) malloc(sizeof(char) * (strlen(buffer) + 1));
    strcpy(*element, buffer);
}

bookRecord writeRegister(FILE *file) {
    bookRecord myBook;
    myBook.id = readId(); // Read ID
    writeID(myBook.id, file);   // Write ID to file
    
    readString(&myBook.title); // Read title
    writeTitle(myBook.title, file); // Write title to file
    
    readString(&myBook.author); // Read author
    writeAuthor(myBook.author, file); // Write author to file
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
    //printf("Enter total number of books: ");
    scanf("%d", totalBook);
    getchar(); 
}

void readBooks(FILE *arq, int totalBook, bookRecord *books) {
    for (int i = 0; i < totalBook; i++) 
        books[i] = writeRegister(arq);
}

void readTitle(FILE *arq, char **title) {
    char buffer[SIZE_BUFFER];
    int currentChar;
    int currentInputIndex = 0;
    
    while ((currentChar = fgetc(arq)) != EOF && (currentChar != '|')) 
        buffer[currentInputIndex++] = currentChar;
    buffer[currentInputIndex] = '\0';
    *title = (char*) malloc((currentInputIndex + 1) * sizeof(char));
    strcpy(*title, buffer);
}

void readAuthor(FILE *arq, char **author) {
    char buffer[SIZE_BUFFER];
    int currentInputIndex = 0;
    int currentChar;

    currentChar = fgetc(arq);
    if (currentChar == EOF) {
        return;
    }

    while (currentChar != EOF && currentChar != '|') {
        buffer[currentInputIndex++] = currentChar;
        currentChar = fgetc(arq);
        if (currentChar == EOF || currentInputIndex >= SIZE_BUFFER - 1) {
            break;
        }
    }

    buffer[currentInputIndex] = '\0';
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






