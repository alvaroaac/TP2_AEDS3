#include "tp2.h"

/**
 * Algoritmo que calcula a distancia de Levenshtein entre 2 strings s1 e s2
 * algoritmo parecido com o recursivo porem mais eficiente,
 * pois utiliza uma matriz para memorizar os calculos ja realizados
 * param: *s1, *s2, strings a serem comparadas
 * return: numero de operacoes necessarias para chegar de s1 em s2
 */
int levenshteinDistIterativo(char *s1, char *s2) {

    int ls1 = strlen(s1);
    int ls2 = strlen(s2);

    int **d = inicializaMatriz(ls1+1, ls2+1, -1);

    int resp = distance(s1, s2, d, ls1, ls2, 0,0);
    destruirMatriz(d,ls1+1);
    return resp;
    // to pensando que posso desalocar ela aqui
}

/**
 * Funcao auxiliar para calcular e memorizar as distancias de levenshtein
 */
int distance(char *s1, char *s2, int **d, int ls1, int ls2, int i, int j) {
    if (d[i][j] >= 0) {
        return d[i][j];
    }

    int num_edit;

    if (i == ls1) {
        num_edit = ls2 - j;
    } else if (j == ls2) {
        num_edit = ls1 - i;
    } else if (s1[i] == s2[j]) {
        num_edit = distance(s1, s2, d, ls1, ls2, i + 1, j + 1);
    } else {
        num_edit = distance(s1, s2, d, ls1, ls2, i + 1, j + 1);

        int aux1, aux2;
        aux1 = distance(s1, s2, d, ls1, ls2, i, j + 1);
        aux2 = distance(s1, s2, d, ls1, ls2, i + 1, j);
        num_edit = num_edit < aux1 ? num_edit : aux1;
        num_edit = num_edit < aux2 ? num_edit : aux2;

        num_edit++;
    }
    d[i][j] = num_edit;
    return num_edit;
}

/**
 * Inicializa uma matriz de n linhas e m colunas
 * alocando memoria e depois inicializando todos os elementos para initValue
 * params: n linhas, m colunas, initValue Valor inicial dos elementos
 * return: a matriz inicializada
 */
int ** inicializaMatriz(int n, int m, int initValue) {
    int **matriz = (int**)malloc(n * sizeof(int*));
    int i,j;
    for (i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(m * sizeof(int));
        for(j = 0; j < m; j++) {
            matriz[i][j] = initValue;
        }
    }
    return matriz;
}

/**
 * Destroi uma matriz de n linhas (desalocar memoria)
 * params: d matriz de n linhas
 */
void destruirMatriz(int **d,int n) {
    int i;
    for (i=0;i<n;i++)
        free(d[i]);
    free(d);
}

struct dictionary * initStructList(int num_entries) {
    struct dictionary * d = malloc(num_entries * sizeof(struct dictionary));
    return d;
}

void destructStructList(struct dictionary * d) {
    free(d);
}
/**
 * Testa se a palavra do dicionario tem tamanho valido
 * se o tamanho da palavra for maior que o minimo aceito
 * e menor que o maximo aceito, retorna 1, caso contrario, 0
 */
int isValidSizeEntry(int size_entry, int max_sizeWord, int min_sizeWord) {
    return (size_entry >= min_sizeWord && size_entry <= max_sizeWord);
}

/**
 * Inicializa o dicionario com a lista de palavras lidas do std input
 * primeiramente inicializa a lista de structs, cada struct suporta a palavra
 * e a distancia minima de edicao da palavra origem, inicializada em -1
 * serao consideradas apenas as palavras com tamanho apropriado em relacao a palavra de origem
 * considerando o numero de operacoes permitido, podemos determinar o tamanho
 * minimo e maximo que a palavra no dicionario pode ter para ter uma chance de ser valida
 * este filtro inicial nao considera substituicoes, apenas operacoes de inserir e remover
 * Em seguida, as distancias sao calculadas e ordenadas, e depois sao impressas na tela
 * em ordem crescente todas as palavras do dicionario que podem ser alcancadas a partir da original
 * utilizando um maximo de [num_operations] operacoes
 *
 * param: num_entries: o numero de palavras existentes no dicionario a serem lidas
 * param: min_sizeWord: o tamanho minimo que a palavra do dicionario deve ter
 * param: max_sizeWord: o tamanho maximo que a palavra do dicionario deve ter
 * param: q: a palavra original (de consulta)
 * param: num_operations: o numero maximo de operacoes permitidas em cima de q
 */
void initSortPrintDict(int num_entries, int min_sizeWord, int max_sizeWord, char* q, int num_operations) {
    // cria a lista de strings do dicionario a serem avaliadas
    struct dictionary *dict = initStructList(num_entries);
    char entry[MAX_SIZE];
    int countDict = 0;
    int i;
    for (i=0;i<num_entries;i++) {
        scanf("%s",entry);
        int size_entry = strlen(entry);
        if (isValidSizeEntry(size_entry, max_sizeWord, min_sizeWord)) {
            sprintf(dict[countDict].word,"%s", entry);
            dict[countDict].distance = -1;
            countDict++;
        }
    }

    getMinimumEditDistance(q, dict, countDict-1);
    qsort(dict, countDict,sizeof(struct dictionary),compare_fun);

    for (i=0;i<countDict;i++) {
        if (dict[i].distance <= num_operations) {
            printf("%s\n", dict[i].word);
        } else {
            break;
        }
    }
    
    destructStructList(dict);
}

/**
 * Itera a lista de palavras do dicionario e calcula a distancia minima de edicao
 * para cada palavra, armazenando na struct.
 * depois, ordena utilizando qsort
 */
void getMinimumEditDistance(char *q, struct dictionary * dict, int n) {
    int i;
    for (i=0;i<n;i++) {
        dict[i].distance = levenshteinDistIterativo(q, dict[i].word);
    }
}

/**
 * Funcao comparadora para uso de qsort.
 */
int compare_fun(const void * a, const void * b) {

    struct dictionary *dictA = (struct dictionary *)a;
    struct dictionary *dictB = (struct dictionary *)b;

    if (dictA->distance != dictB->distance) {
        return (dictA->distance - dictB->distance);
    } else {
        int i=0;
        while ((dictA->word[i] && dictB->word[i]) && dictA->word[i] == dictB->word[i]) {
            i++;
        }
        return (dictA->word[i] - dictB->word[i]);
    }
}
