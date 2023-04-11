#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
typedef struct Book {
    int id;
    char* title;
    char* author;
} bookRecord;

void delimiterTitle(char* title){
    strtok(title, "\n");
    strcat(title, "|");
}

bookRecord readRegister(){
    bookRecord myBook;
    char buffer[100];
    int delimiter = -1;

    scanf("%d", &myBook.id);
    getchar(); 

    fgets(buffer, sizeof(buffer), stdin);
    delimiterTitle(buffer);
    myBook.title = (char*) malloc(strlen(buffer) + 1);
    strcpy(myBook.title, buffer);

    fgets(buffer, sizeof(buffer), stdin);
    strtok(buffer, "\n");
    int sizeAuthor = strlen(buffer);
    myBook.author = (char*) malloc(sizeAuthor + 2);
    sprintf(myBook.author, "%d%s%d", sizeAuthor, buffer, delimiter);

    return myBook;
}

int checkOpenFile (FILE *file){
    if (file == NULL)
        return 0;
    else
        return 1;
}

void displayBookRecords(FILE *arq, int total) {
    bookRecord book;
    int byteOffset = 0; 
    for (int i = 0; i < total; i++) {
        fseek(arq, byteOffset, SEEK_SET);
        fread(&book, sizeof(bookRecord), 1, arq);

        printf("Id: %d\n", book.id);
        printf("Titulo: %s\n", book.title); 
        printf("Autor: %s\n", book.author);
        printf("Byte offset: %d\n", byteOffset); 
        byteOffset += sizeof(bookRecord); 
    }
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

int main(){
    int totalBook = 0;
    bookRecord *books;
    FILE* arq; 

    if (openFile(&arq, "wb")){
        printf("Enter total number of books: ");
        scanf ("%d", &totalBook);

        books = (bookRecord*) malloc (sizeof(bookRecord)*totalBook);

        for (int i = 0; i < totalBook; i++){
            books[i] = readRegister();
            fwrite(&books[i], sizeof(bookRecord), 1, arq);
        }

        fclose(arq);

        // Abrir o arquivo novamente em modo de leitura binária
        if (openFile(&arq, "rb")){
            displayBookRecords(arq, totalBook);
            fclose(arq);
        }

        // Liberar a memória alocada dinamicamente
        for (int i = 0; i < totalBook; i++){
            free(books[i].title);
            free(books[i].author);
       
}
    free(books);
    }

    return 0;
}