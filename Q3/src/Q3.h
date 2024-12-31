#ifndef Q3_H
#define Q3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LIVRE 1
#define OCUPADO 0

typedef struct Info
{
    int inicio;
    int fim;
    int status;
} Info;

typedef struct ArvMemoria
{
    struct ArvMemoria *left;
    Info *info1;
    struct ArvMemoria *center;
    Info *info2;
    struct ArvMemoria *right;

    int numKeys;
} Memoria;

Info *criarInfo(int inicio, int fim, int status);

Memoria *insereArv23(Memoria **no, Info *info, Info *promove, Memoria **noPai);

void exibirInfos(Memoria *raiz);

int alocaEspaco(Memoria **raiz, int quantEspaco, int *return_inicio);

void freeEspaco(Memoria *memoria, int inicio, int fim);

int removeMemoria(Memoria **raiz, int info);

void mergeNosInicio(Memoria **raiz, int *return_inicio);

void mergeNosMeio(Memoria **raiz, int *aux1, int *aux2);

void mergeNosFim(Memoria **raiz, int *return_inicio);

int removeMemoria1(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior);

int removeMemoria2(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior);

int rebalancearMemoria(Memoria **raiz, int info, Memoria **maior);

void no23free(Memoria **no);

Memoria *no23Juntar(Memoria *filho1, Info info, Memoria *maior, Memoria **raiz);

#endif