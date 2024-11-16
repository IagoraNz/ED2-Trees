/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q1.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

Arv23PT *criaNo(const Info *informacao, Arv23PT *filhoesq, Arv23PT *filhocen){
    Arv23PT *no = (Arv23PT*)malloc(sizeof(Arv23PT));

    no->info1 = *informacao;
    no->esq = filhoesq;
    no->cen = filhocen;
    no->dir = NULL;
    no->ninfos = 1;

    return no;
}

Arv23PT *adicionaChave(Arv23PT *no, const Info *informacao, Arv23PT *filho){
    if(strcmp(informacao->palavra, no->info1.palavra) > 0){
        no->info2 = *informacao;
        no->dir = filho;
    }
    else{
        no->info2 = no->info1;
        no->dir = no->cen;
        no->info1 = *informacao;
        no->cen = filho;
    }
    no->ninfos = 2;

    return no;
}

Arv23PT *quebraNo(Arv23PT **no, const Info *informacao, Info *promove, Arv23PT **filho){
    Arv23PT *maior;

    if(strcmp(informacao->palavra, (*no)->info2.palavra) > 0){
        *promove = (*no)->info2;
        // Check if filho is not NULL before dereferencing
        maior = criaNo(informacao, (*no)->dir, (filho ? *filho : NULL));
    }
    else if(strcmp(informacao->palavra, (*no)->info1.palavra) > 0){
        *promove = *informacao;
        // Check if filho is not NULL before dereferencing
        maior = criaNo(&(*no)->info2, (filho ? *filho : NULL), (*no)->dir);
    }
    else{
        *promove = (*no)->info1;
        // If filho is NULL, handle it by using NULL explicitly
        maior = criaNo(&(*no)->info2, (*no)->cen, (*no)->cen);
        (*no)->info1 = *informacao;
        (*no)->cen = (filho ? *filho : NULL);
    }
    (*no)->ninfos = 1;

    return maior;
}

int ehFolha(const Arv23PT *no){
    return (no->esq == NULL);
}

Arv23PT *inserirArv23(Arv23PT **no, Info *informacao, Info *promove, Arv23PT **pai){
    Info promove1;
    Arv23PT *maiorNo = NULL;

    if(*no == NULL)
        *no = criaNo(informacao, NULL, NULL);
    else{
        if(ehFolha(*no)){
            if((*no)->ninfos == 1)
                *no = adicionaChave(*no, informacao, NULL);
            else{
                maiorNo = quebraNo(no, informacao, promove, NULL);
                if(pai == NULL){
                    *no = criaNo(promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else{
            if(strcmp(informacao->palavra, (*no)->info1.palavra) < 0){
                maiorNo = inserirArv23(&((*no)->esq), informacao, promove, no);
            }
            else if((*no)->ninfos == 1 || (strcmp(informacao->palavra, (*no)->info2.palavra) < 0)){
                maiorNo = inserirArv23(&((*no)->cen), informacao, promove, no);
            }
            else{
                maiorNo = inserirArv23(&((*no)->dir), informacao, promove, no);
            }
        }

        if(maiorNo){
            if((*no)->ninfos == 1){
                *no = adicionaChave(*no, promove, maiorNo);
                maiorNo = NULL;
            }
            else{
                maiorNo = quebraNo(no, promove, &promove1, &maiorNo);
                if(*pai != NULL){
                    *no = criaNo(&promove1, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
    }

    return maiorNo;
}

void freeTree(Arv23PT *no){
    if(no != NULL){
        freeTree(no->esq);
        freeTree(no->cen);
        freeTree(no->dir);
        free(no);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
equivalentes em inglês */

/*-----------------------------------------------------------------------------------------------------*/

/* (ii) informar uma palavra em português e então imprima todas as palavras em inglês equivalente à palavra em
português dada, independente da unidade */

/*-----------------------------------------------------------------------------------------------------*/

/* (iii) informar uma palavra em inglês e a unidade a qual a mesma pertence removê-la das árvores binárias
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
árvore 2-3 */

int ehFolha(Arv23PT *no){
    int aux = 0;
    if(no->esq == NULL)
        aux = 1;
    return aux;
}

Arv23PT *menorfilho(Arv23PT *no, Arv23PT **parente) {
    (*parente) = no;
    while(no->esq != NULL) {
        (*parente) = no;
        no = no->esq;
    }

    return no;
}

int removerArv23(Arv23PT **raiz, const Info *info, Arv23PT **pai){
    int removeu = 0;
    Arv23PT *paiaux = NULL, *resultado = NULL;

    if((*raiz) != NULL) {
        if(ehFolha(*raiz)) {
            if((*raiz)->ninfos == 2) {
                // Caso 1: remoção em nó folha com 2 infos, onde a palavra a ser removida é a info 2
                if(strcmp(info->palavra, (*raiz)->info2.palavra) == 0){
                    (*raiz)->ninfos = 1;
                    removeu = 1;
                }
                // Caso 2: remoção em nó folha com 2 infos, onde a palavra a ser removida é a info 1
                else if(strcmp(info->palavra, (*raiz)->info1.palavra) == 0) {
                    (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->ninfos = 1;
                    removeu = 1;
                }
            }
            else if((*raiz)->ninfos == 1) {
                // Caso 3: remoção em nó folha com 1 info e sem pai
                if((*pai) == NULL) {
                    free((*raiz));
                    (*raiz) = NULL;
                    removeu = 1;
                }
                else if((*pai) != NULL) {
                    /* Caso 4: remoção em nó folha com 1 info e com um pai, e a info
                    é o filho da esquerda*/
                    if((*raiz) == (*pai)->esq){
                        (*raiz)->info1 = (*pai)->info1;
                        paiaux = *pai;
                        resultado = menorfilho((*pai)->cen, &paiaux);
                        (*pai)->info1 = resultado->info1;
                        removeu = 1;
                        /* Caso 4.1: o menor no possui duas infos */
                        if(resultado->ninfos == 2) {
                            resultado->info1 = resultado->info2;
                            resultado->ninfos = 1;
                        }
                        /* Caso 4.2: o menor no possui uma info */
                        else {
                            /* Caso 4.2.1: o menor no possui uma info e o pai posui ninfos == 2 */
                            if((*pai)->ninfos == 2) {

                            }
                        }
                    }
                }
            }
        }
    }

    return removeu;
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então removê-la, para isto
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
árvore 2-3 */