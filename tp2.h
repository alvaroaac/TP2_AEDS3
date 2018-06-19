#include <stdio.h>
#include <string.h> // funcoes para manipulacao de strings (e.g: strlen(s)).
#include <stdlib.h> // malloc, qsort...
#define MAX_SIZE 6001

// Declaring structs
struct dictionary {
    char word[MAX_SIZE];
    int distance;
};

// Declaracao de Funcoes

int levenshteinDistRecursivo(char *s1, int ls1, char *s2, int ls2);
int levenshteinDistIterativo(char *s1, char*s2);
int** inicializaMatriz(int n, int m, int initValue);
int distance(char *s1, char *s2, int **d, int ls1, int ls2, int i, int j);
void initSortPrintDict(int num_entries, int min_sizeWord, int max_sizeWord, char* q, int num_operations);
int isValidSizeEntry(int size_entry, int max_sizeWord, int min_sizeWord);
int compare_fun(const void * a, const void * b);
void getMinimumEditDistance(char *q, struct dictionary * dict, int n);
struct dictionary * initStructList(int num_entries);
void destructStructList(struct dictionary * d);
void destruirMatriz(int **d,int n);
