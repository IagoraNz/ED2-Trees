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

Memoria *insereArv23(Memoria **raiz, Info info, Memoria *pai, Info *promove);

void exibirInfos(Memoria *raiz);

int removeMemoria(Memoria **raiz, int info);

int removeMemoria1(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior);

int removeMemoria2(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior);

int rebalancearMemoria(Memoria **raiz, int info, Memoria **maior);

void no23free(Memoria **no);

Memoria *no23Juntar(Memoria *filho1, Info info, Memoria *maior, Memoria **raiz);

void alocarEDesalocar(Memoria **raiz, int quantNo, int status);

Memoria *buscaNoPai(Memoria *raiz, int info);

void noAddInfo(Memoria *no, Info info, Memoria *maiorFilho);

Memoria *buscaMaiorFilho(Memoria *raiz, Memoria **pai, Info **maior_valor);

Memoria *buscaMenorFilho(Memoria *raiz, Memoria **pai);

Memoria *buscaMaiorNoPai(Memoria *raiz, int info);

Info *no23MaiorInfo(Memoria *raiz);

#endif