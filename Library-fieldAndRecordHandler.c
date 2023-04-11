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
    strcpy(myBook.title, buffer);

    fgets(buffer, sizeof(buffer), stdin);
    strtok(buffer, "\n");
    int sizeAuthor = strlen(buffer);

    sprintf(myBook.author, "%d%s%d", sizeAuthor, buffer, delimiter);

    return myBook;
}

int checkOpenFile (FILE *file){
    if (file == NULL)
        return 0;
    else
        return 1;
}

void displayBookRecords(bookRecord *books, int total) {
    for (int i = 0; i < total; i++) {
        printf("%d", books[i].id);
        printf("%s", books[i].title); 
        printf("%s\n", books[i].author);
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

        books = malloc (sizeof(bookRecord)*totalBook);

        for (int i = 0; i < totalBook; i++){
            books[i] = readRegister();
            fwrite(&books[i], sizeof(bookRecord), 1, arq);
        }
        fclose(arq);

        if (openFile(&arq, "rb")){
            if (checkOpenFile(arq)){
                displayBookRecords(books, totalBook);
        fclose(arq);
            } else {
                printf("Error opening file.\n");
            }
        }

        // Libere a memória alocada
        free(books);
    } else {
        printf("Error opening file.\n");
    }

    return 0;
}