#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int id;
  char *titulo;
  char *autor;
} Livro;
void lerTitulo(FILE *arq, char **titulo);
void lerAutor(FILE *arq, char **autor);
void imprime(FILE *arq, Livro *livro);

int main(void) {
  int numeroLivros;
  FILE *arq;
  Livro *livro;
  int tamTitulo, tamAutor;
  char delimitadorTitulo = '|';
  char delimitador = -1;
  char buffer[100];

  scanf("%d", &numeroLivros);

  arq = fopen("livros.bin", "wb+");
  if (arq == NULL) {
    printf("erro");
    exit(0);
  } else {
    livro = (Livro *)malloc(sizeof(Livro) * numeroLivros);

    for (int i = 0; i < numeroLivros; i++) {

      scanf("%d", &livro[i].id);
      fwrite(&livro[i].id, sizeof(int), 1, arq); // escreve id no arquivo

      scanf(" %[^(\r|\n)]", buffer);
      tamTitulo = strlen(buffer);
      livro[i].titulo = malloc(sizeof(char) * (tamTitulo + 1));
      strcpy(livro[i].titulo, buffer);
      fwrite(livro[i].titulo, sizeof(char) * tamTitulo, 1,
             arq); // escreve titulo no arquivo
      fwrite(&delimitadorTitulo, sizeof(char), 1,
             arq); // escreve delimitador no arquivo

      scanf(" %[^(\r|\n)]", buffer);
      tamAutor = strlen(buffer);
      livro[i].autor = malloc(sizeof(char) * (tamAutor + 1));
      strcpy(livro[i].autor, buffer);
      fwrite(&tamAutor, sizeof(int), 1,
             arq); // escreve tamanho do autor no arquivo
      fwrite(livro[i].autor, sizeof(char) * tamAutor, 1,
             arq); // escreve autor no arquivo
      fwrite(&delimitador, sizeof(char), 1,
             arq); // escreve delimitador no arquivo
    }

    for (int i = 0; i < numeroLivros; i++) {
      free(livro[i].titulo);
      free(livro[i].autor);
    }
    free(livro);

    fclose(arq);

    arq = fopen("livros.bin", "rb"); // MODO LEITURA
    if (arq == NULL) {
      printf("erro");
      exit(0);
    } else {
      // livro = (Livro *)malloc(sizeof(Livro) * numeroLivros);

      for (int i = 0; i < numeroLivros; i++) {

        fread(&livro[i].id, sizeof(int), 1, arq); // leitura do id
        lerTitulo(arq, &livro[i].titulo);         // leitura do titulo
        lerAutor(arq, &livro[i].autor);
        imprime(arq, &livro[i]);
      }
    }
    for (int i = 0; i < numeroLivros; i++) {
      free(livro[i].titulo);
      free(livro[i].autor);
    }

    free(livro);
    fclose(arq);
  }
}
void lerTitulo(FILE *arq, char **titulo) {
  char buffer[100];
  int charAtual;
  int i = 0;

  while ((charAtual = fgetc(arq)) != EOF && charAtual != '|')
    buffer[i++] = charAtual;
  buffer[i] = '\0';
  *titulo = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
  strcpy(*titulo, buffer);
}
void lerAutor(FILE *arq, char **autor) {
  char buffer[100];
  int charAtual;
  int i = 0;
  int tamAutor = 0;

  fread(&tamAutor, sizeof(int), 1, arq);
  fread(buffer, sizeof(char), tamAutor, arq);

  int j;
  for (j = 0; j < tamAutor; j++) {
    if (buffer[j] == -1)
      break;
  }

  *autor = (char *)malloc(sizeof(char) * (j + 1));
  strncpy(*autor, buffer, j);
  (*autor)[i] = '\0';
}

void imprime(FILE *arq, Livro *livro) {
  printf("Id: %d\n", livro->id);
  printf("Titulo: %s\n", livro->titulo);
  printf("Autor: %s\n", livro->autor);
}
