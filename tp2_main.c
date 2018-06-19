/*
 * Universidade Federal de Minas Gerais - Escola de Engenharia
 * Departamento de Ciência da Computação
 * Disciplina de Algoritmos e Estrutura de Dados III
 * Trabalho Pratico 2
 * Alvaro Augusto Alves de Carvalho - 2015430231
 */

#include "tp2.h"

int main() {

    int num_entries; // numero de palavras no dicionario
    int num_operations; // numero de operacoes permitidas
    char q[MAX_SIZE]; // palavra de consulta
    int size_q;
    int min_sizeWord;
    int max_sizeWord;

    scanf("%d", &num_entries);
    scanf("%d", &num_operations);
    scanf("%s", q);

    size_q = strlen(q);
    min_sizeWord = size_q - num_operations;
    max_sizeWord = size_q + num_operations;

    initSortPrintDict(num_entries, min_sizeWord, max_sizeWord, q, num_operations);


    return 0;
}
