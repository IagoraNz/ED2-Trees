#ifndef Q1_H
#define Q1_H

/*
    Estruturas de Árvores Binarias e Árvore Vermelho e Preta
*/

typedef struct unidades
{
  int unidade;
  struct unidades *prox;
} Unidades;

typedef struct infoArvoreingptbst
{
  char *palavraIngles;
  Unidades *unidades;
} InfoArvoreIngPTBST;

typedef struct ingptbst
{
  InfoArvoreIngPTBST info;
  struct ingptbst *esq;
  struct ingptbst *dir;
} IngPTBST;

typedef enum cor
{
  VERMELHO = 0,
  PRETO = 1
} Cor;

typedef struct infoArvBin
{
  IngPTBST *arvBinIngles;
  char *palavraPortugues;
} InfoArvBin;

typedef struct arvvp
{
  InfoArvBin info;

  Cor cor;
  struct arvvp *esq;
  struct arvvp *dir;
} ArvVP;

/*
=====================================================================================================
*/

int inserirArvVP(ArvVP **raiz, InfoArvBin info);

int removerArvVP(ArvVP **raiz, char *palavraPT);

void removerArvVPEN(ArvVP **raiz, const char *palavraEN, int unidade);

void removerArvVPPTBR(ArvVP **raiz, char *palavraPT, int unidade);

void exibirUnidade(ArvVP *raiz, int unidade, int *enc);

void exibirArvBinPT(ArvVP *raiz, char *palavra);

#endif