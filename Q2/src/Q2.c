#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/Q2.h"

void inserirArvBin(IngPTBST **raiz, InfoArvoreIngPTBST info){
    if(*raiz == NULL){
        *raiz = (IngPTBST*)malloc(sizeof(IngPTBST));
        (*raiz)->info = info;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    } else
    {
        if (strcmp((*raiz)->info.palavraIngles, info.palavraIngles) > 0)
            inserirArvBin(&(*raiz)->esq, info);
        else
            inserirArvBin(&(*raiz)->dir, info);
    }
}

void criarNo(ArvVP **no, InfoArvBin info){
    *no = (ArvVP*)malloc(sizeof(ArvVP));
    (*no)->info = info;
    (*no)->info.palavraPortugues = strdup(info.palavraPortugues);
    (*no)->cor = VERMELHO;
    (*no)->esq = NULL;
    (*no)->dir = NULL;
}

void trocaCor(ArvVP **raiz){
    (*raiz)->cor = !(*raiz)->cor;
    if ((*raiz)->esq != NULL)
        (*raiz)->esq->cor = !(*raiz)->esq->cor;
    if ((*raiz)->dir != NULL)
        (*raiz)->dir->cor = !(*raiz)->dir->cor;
}

void rotacaoEsq(ArvVP **raiz)
{
  ArvVP *aux = (*raiz)->dir;
  (*raiz)->dir = aux->esq;
  aux->esq = *raiz;
  aux->cor = (*raiz)->cor;
  (*raiz)->cor = VERMELHO;
  *raiz = aux;
}

void rotacaoDir(ArvVP **raiz)
{
  ArvVP *aux = (*raiz)->esq;
  (*raiz)->esq = aux->dir;
  aux->dir = *raiz;
  aux->cor = (*raiz)->cor;
  (*raiz)->cor = VERMELHO;
  *raiz = aux;
}

int pegarCor(ArvVP *raiz){
    int cor = 1;
    if (raiz != NULL)
        cor = raiz->cor;
    return cor;
}

void balancear(ArvVP **raiz){
    if (pegarCor((*raiz)->esq) == PRETO && pegarCor((*raiz)->dir) == VERMELHO)
        rotacaoEsq(raiz);
    if ((*raiz)->esq != NULL && (*raiz)->esq->cor == VERMELHO && (*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == VERMELHO)
        rotacaoDir(raiz);
    if (pegarCor((*raiz)->esq) == VERMELHO && pegarCor((*raiz)->dir) == VERMELHO)
        trocaCor(raiz);
}

int inserirArvVP(ArvVP **raiz, InfoArvBin info){
    int inseriu = 0;
    if ((*raiz) == NULL){
        criarNo(raiz, info);
        inseriu = 1;
    }
    else{
        if (strcmp((*raiz)->info.palavraPortugues, info.palavraPortugues) == 0){
            inserirArvBin(&(*raiz)->info.arvBinIngles, info.arvBinIngles->info);
            inseriu = 1;
        }
        else if (strcmp((*raiz)->info.palavraPortugues, info.palavraPortugues) > 0)
            inseriu = inserirArvVP(&(*raiz)->esq, info);
        else
            inseriu = inserirArvVP(&(*raiz)->dir, info);

        balancear(raiz);
        
    }
    return inseriu;
}
/*
(i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das 
equivalentes em inglês; 
*/

void exibirArvBin(IngPTBST *raiz){
    if(raiz != NULL){
        exibirArvBin(raiz->esq);
        printf("%s\n", raiz->info.palavraIngles);
        printf("Unidade: %d\n", raiz->info.unidade);
        exibirArvBin(raiz->dir);
    }
}

void exibirUnidade(ArvVP *raiz, int unidade){
    if (raiz != NULL){
        exibirUnidade(raiz->esq, unidade);
        if (raiz->info.arvBinIngles->info.unidade == unidade){
            printf("Palavra PT-BR: %s\nPalavras EN:\n", raiz->info.palavraPortugues);
            exibirArvBin(raiz->info.arvBinIngles);
        }
        exibirUnidade(raiz->dir, unidade);
    }
}

/*
(ii)informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em 
português dada, independente da unidade; 
*/

void exibirArvBinPT(IngPTBST *raiz, char *palavra){
    if(raiz != NULL){
        exibirArvBinPT(raiz->esq, palavra);
        if (strcmp(raiz->info.palavraIngles, palavra) == 0){
            printf("Palavra PT-BR: %s\nPalavras EN:\n", raiz->info.palavraIngles);
            exibirArvBin(raiz);
        }
        exibirArvBinPT(raiz->dir, palavra);
    }
}

/*
(iii)informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias 
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da 
árvore Rubro Negra. 
*/
int ehfolha(IngPTBST *raiz){
    return (raiz->esq == NULL && raiz->dir == NULL);
}

IngPTBST* soumfilho(IngPTBST *raiz){
    IngPTBST *aux;
    aux = NULL;
    if(raiz->esq == NULL) 
        aux = raiz->dir;
    else if (raiz->dir == NULL)
        aux = raiz->esq;
    return aux;
}

IngPTBST* menorfilhoesq(IngPTBST *raiz){
    IngPTBST *aux;
    aux = NULL;
    if(raiz){
        aux = menorfilhoesq(raiz->esq);
        if(!aux)
            aux = raiz;
    }
    return aux;
}

int removerPalavraEN(IngPTBST **raiz, const char *palavraEN, int unidade){
    int encontrou = 0;
    if ((*raiz) != NULL){
        if (strcmp((*raiz)->info.palavraIngles, palavraEN) == 0 && (*raiz)->info.unidade == unidade){
            IngPTBST *aux = *raiz;
            if (ehfolha(*raiz)){
                free(aux);
                *raiz = NULL;
            } else if (soumfilho(*raiz)){
                IngPTBST *aux = *raiz;
                *raiz = soumfilho(*raiz);
                free(aux);
            } else {
                IngPTBST *aux = menorfilhoesq((*raiz)->dir);
                (*raiz)->info = aux->info;
                removerPalavraEN(&(*raiz)->dir, aux->info.palavraIngles, aux->info.unidade);
            }

            encontrou = 1;

        } else if (strcmp((*raiz)->info.palavraIngles, palavraEN) > 0)
            encontrou = removerPalavraEN(&(*raiz)->esq, palavraEN, unidade);
        else
            encontrou = removerPalavraEN(&(*raiz)->dir, palavraEN, unidade);
    }
    return encontrou;
}

void percorrerArvVP(ArvVP **raiz, const char *palavraEN, int unidade, char *palavraPT, int *remover){
    if ((*raiz) != NULL){
        percorrerArvVP(&(*raiz)->esq, palavraEN, unidade, palavraPT, remover);
        int encontrou = removerPalavraEN(&(*raiz)->info.arvBinIngles, palavraEN, unidade);
        if (encontrou && (*raiz)->info.arvBinIngles == NULL){
            *remover = 1;
            strcpy(palavraPT, (*raiz)->info.palavraPortugues);
        }
        percorrerArvVP(&(*raiz)->dir, palavraEN, unidade, palavraPT, remover);
    }
}

void move2EsqRed(ArvVP **raiz){
    trocaCor(raiz);
    if (pegarCor((*raiz)->dir->esq) == VERMELHO){
        rotacaoDir(&(*raiz)->dir);
        rotacaoEsq(raiz);
        trocaCor(raiz);
    }
}

void move2DirRed(ArvVP **raiz){
    trocaCor(raiz);
    if (pegarCor((*raiz)->esq->esq) == VERMELHO){
        rotacaoDir(raiz);
        trocaCor(raiz);
    }
}

ArvVP* procuraMenor(ArvVP *raiz) {
    ArvVP *no1 = raiz;
    ArvVP *no2 = raiz->esq;
    while (no2) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

int removerMenor(ArvVP **raiz) {
    if (!(*raiz)->esq) {
        free(*raiz);
        *raiz = NULL;
    } else {
        if (pegarCor((*raiz)->esq) == PRETO && pegarCor((*raiz)->esq->esq) == PRETO) {
            move2EsqRed(raiz);
        }
        removerMenor(&(*raiz)->esq);
    }
    if (*raiz) {
        balancear(raiz);
    }
}

int removerArvVP(ArvVP **raiz, char *palavraPT) {
    int removido = 0;
    if (*raiz) {
        if (strcmp(palavraPT, (*raiz)->info.palavraPortugues) < 0) {
            if (pegarCor((*raiz)->esq) == PRETO && pegarCor((*raiz)->esq->esq) == PRETO)
                move2EsqRed(raiz);
            removido = removerArvVP(&(*raiz)->esq, palavraPT);
        } else {
            if (pegarCor((*raiz)->esq) == VERMELHO)
                rotacaoDir(raiz);
            if (!strcmp(palavraPT, (*raiz)->info.palavraPortugues) && !(*raiz)->dir) {
                free(*raiz);
                *raiz = NULL;
                return 1;
            }
            if (pegarCor((*raiz)->dir) == PRETO && pegarCor((*raiz)->dir->esq) == PRETO)
                move2DirRed(raiz);
            if (!strcmp(palavraPT, (*raiz)->info.palavraPortugues)) {
                ArvVP *aux = procuraMenor((*raiz)->dir);
                (*raiz)->info = aux->info;
                removerMenor(&(*raiz)->dir);
                removido = 1;
            } else {
                removido = removerArvVP(&(*raiz)->dir, palavraPT);
            }
        }
    }
    if (*raiz) {
        balancear(raiz);
    }
    return removido;
}

void removerArvVPEN(ArvVP **raiz, const char *palavraEN, int unidade){
    char palavraPT[50];
    int remover = 0;
    percorrerArvVP(raiz, palavraEN, unidade, palavraPT, &remover);
    if (remover){
        int sucesso = 0;
        sucesso = removerArvVP(raiz, palavraPT);
        if (!sucesso)
            printf("Erro ao remover.\n");
        else
            printf("Remocao bem-sucedida!\n");
    }
    if ((*raiz) != NULL)
        (*raiz)->cor = PRETO;
}

/*
(iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto 
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma 
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da 
árvore Rubro Negra.  
*/

void buscarPalavraEN(IngPTBST *raiz, int unidade, char *palavraEN, int *encontrou){
    if (raiz != NULL){
        if (*encontrou != 1)
            buscarPalavraEN(raiz->esq, unidade, palavraEN, encontrou);
        if (raiz->info.unidade == unidade){
            strcpy(palavraEN, raiz->info.palavraIngles);
            *encontrou = 1;
        }
        if (*encontrou != 1)
            buscarPalavraEN(raiz->dir, unidade, palavraEN, encontrou);
    }
}

int percorrerArvVPPTBR(ArvVP **raiz, char *palavraPT, int unidade, int *remover){
    if ((*raiz) != NULL){
        if (strcmp(palavraPT, (*raiz)->info.palavraPortugues) == 0){
            char palavraEN[50];
            int encontrou = 0;
            buscarPalavraEN((*raiz)->info.arvBinIngles, unidade, palavraEN, &encontrou);
            if (encontrou == 1){
                encontrou = removerPalavraEN(&(*raiz)->info.arvBinIngles, palavraEN, unidade);
                if (encontrou == 1 && (*raiz)->info.arvBinIngles == NULL){
                    printf("Encontrou!\n");
                    *remover = 1;
                }
            }
        }else
        {
            if (strcmp(palavraPT, (*raiz)->info.palavraPortugues) < 0)
                percorrerArvVPPTBR(&(*raiz)->esq, palavraPT, unidade, remover);
            else
                percorrerArvVPPTBR(&(*raiz)->dir, palavraPT, unidade, remover);
        } 
    }
}

void removerArvVPPTBR(ArvVP **raiz, char *palavraPT, int unidade){
    int remover = 0;
    percorrerArvVPPTBR(raiz, palavraPT, unidade, &remover);
    printf("Remover: %d\n", remover);
    if (remover == 1){
        int sucesso = 0;
        sucesso = removerArvVP(raiz, palavraPT);
        if (!sucesso)
            printf("Erro ao remover.\n");
        else
            printf("Remocao bem-sucedida!\n");
    }

    if ((*raiz) != NULL)
        (*raiz)->cor = PRETO;
}