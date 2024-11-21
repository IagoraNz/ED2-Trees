/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Q1.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

Arv23PT *criaNo(const Info informacao, Arv23PT *filhoesq, Arv23PT *filhocen){
    Arv23PT *no = (Arv23PT*)malloc(sizeof(Arv23PT));

    if(!no){
        printf("Nao foi possivel criar no\n");
    }

    if(no){
        no->info1 = informacao;
        no->esq = filhoesq;
        no->cen = filhocen;
        no->ninfos = 1;
    }

    return no;
}

void adicionaChave(Arv23PT *no, const Info informacao, Arv23PT *filho){
    if(strcmp(informacao.palavra, no->info1.palavra) > 0){
        no->info2 = informacao;
        no->dir = filho;
    }
    else{
        no->info2 = no->info1;
        no->dir = no->cen;
        no->info1 = informacao;
        no->cen = filho;
    }
    no->ninfos = 2;
}

Arv23PT *quebraNo(Arv23PT **no, const Info informacao, Info *promove, Arv23PT **filho){
    Arv23PT *maior;

    if(strcmp(informacao.palavra, (*no)->info2.palavra) > 0){
        *promove = (*no)->info2;
        if(filho)
            maior = criaNo(informacao, (*no)->dir, *filho);
        else
            maior = criaNo(informacao, (*no)->dir,  NULL);
    }
    else if(strcmp(informacao.palavra, (*no)->info1.palavra) > 0){
        *promove = informacao;
        // Check if filho is not NULL before dereferencing
        if(filho)
            maior = criaNo((*no)->info2, *filho, (*no)->dir);
        else
            maior = criaNo((*no)->info2, NULL, (*no)->dir);
    }
    else{
        *promove = (*no)->info1;
        // If filho is NULL, handle it by using NULL explicitly
        maior = criaNo((*no)->info2, (*no)->cen, (*no)->cen);
        (*no)->info1 = informacao;
        (*no)->cen = (filho ? *filho : NULL);
    }
    (*no)->ninfos = 1;

    return maior;
}

int ehFolha(const Arv23PT *no){
    return (no->esq == NULL);
}

Arv23PT *inserirArv23(Arv23PT **no, const Info informacao, Info *promove, Arv23PT **pai){
    Info promove1;
    Arv23PT *maiorNo = NULL;

    if(*no == NULL)
        *no = criaNo(informacao, NULL, NULL);
    else{
        if(ehFolha(*no)){
            if((*no)->ninfos == 1)
                adicionaChave(*no, informacao, NULL);
            else{
                maiorNo = quebraNo(no, informacao, promove, NULL);
                if(pai && !(*pai)){
                    *no = criaNo(*promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else{
            if(strcmp(informacao.palavra, (*no)->info1.palavra) < 0){
                maiorNo = inserirArv23(&((*no)->esq), informacao, promove, no);
            }
            else if(((*no)->ninfos == 1) || (strcmp(informacao.palavra, (*no)->info2.palavra) < 0)){
                maiorNo = inserirArv23(&((*no)->cen), informacao, promove, no);
            }
            else{
                maiorNo = inserirArv23(&((*no)->dir), informacao, promove, no);
            }

            if(maiorNo){
                if((*no)->ninfos == 1){
                    adicionaChave(*no, *promove, maiorNo);
                    maiorNo = NULL;
                }
                else{
                    maiorNo = quebraNo(no, *promove, &promove1, &maiorNo);
                    if(pai && !(*pai)){
                        *no = criaNo(promove1, *no, maiorNo);
                        maiorNo = NULL;
                    }
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

void onda(const Info info, Info *entrada, const Arv23PT *pai, Arv23PT **fonte, Arv23PT **raiz) {
    removerArv23(raiz, info.palavra, pai, fonte);
    if(entrada)
        *entrada = info;
}

int ehFolhaR(const Arv23PT *no){
    int aux = 0;
    if(no->esq == NULL)
        aux = 1;
    return aux;
}

int removivel(const Arv23PT *raiz) {
    int pode = 0;

    if(raiz != NULL) {
        pode = raiz->ninfos == 2;
        if(!pode) {
            pode = removivel(raiz->cen);
            if(!pode)
                pode = removivel(raiz->esq);
        }
    }
    return pode;
}

Arv23PT *menorfilho(Arv23PT *no, Arv23PT **pai, Info *res){
    *pai = no;
    Arv23PT *filho = no->esq;

    while(filho != NULL && !ehFolhaR(filho)){
        *pai = filho;
        filho = filho->esq;
    }
    if(filho != NULL)
        *res = filho->info1;

    return filho;
}

Arv23PT *maior(const Arv23PT *raiz) {
    return raiz->ninfos == 2 ? raiz->dir : raiz->cen;
}

Arv23PT *maiorfilho(Arv23PT *raiz, Arv23PT **pai, Info *maiorinfo) {
    Arv23PT *filho = maior(raiz);
    *pai = raiz;

    while(filho != NULL && maior(filho) != NULL) {
        *pai = filho;
        filho = maior(filho);
    }
    if(filho != NULL)
        *maiorinfo = filho->ninfos ? filho->info2 : filho->info1;

    return filho;
}

int ehInfo1(const Arv23PT no, const char *palavra){
    return strcmp(no.info1.palavra, palavra) == 0;
}

int ehInfo2(const Arv23PT no, const char *palavra){
    return strcmp(no.info2.palavra, palavra) == 0;
}

Arv23PT *buscpai(const Arv23PT *raiz, const char *palavra) {
    Arv23PT *pai = NULL;

    if(raiz != NULL) {
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)) {
            if(strcmp(palavra, raiz->info1.palavra) < 0)

        }
    }
}

int removerArv23(Arv23PT **raiz, const char *info, const Arv23PT *pai, Arv23PT **ref) {
    int removeu = 0;

    if(*raiz != NULL) {
        const int info1 = ehInfo1(**raiz, info);
        const int info2 = ehInfo2(**raiz, info);
        if(info1 || info2) {
            if(ehFolha(*raiz)) {
                if((*raiz)->ninfos == 2) {
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;
                    (*raiz)->ninfos = 1;
                }
                else {
                    if(pai != NULL) {
                        if((*raiz) == pai->esq)
                            onda(pai->info1, &((*raiz)->info1), NULL, ref, ref);
                        else {
                            if(pai->ninfos == 2) {
                                if(*raiz == pai->cen)
                                    onda(pai->info2, &((*raiz)->info1), NULL, ref, ref);
                                else
                                    onda(pai->info2, &((*raiz)->cen->info2), NULL, ref, ref);
                            }
                            else
                                onda(pai->info1, &((*raiz)->info1), NULL, ref, ref);
                        }
                    }
                    else {
                        free(*raiz);
                        *raiz = NULL;
                    }
                }
            }
            else {
                Arv23PT *filho, *auxpai;
                Info auxinfo;
                int juntou = 0;
                if(info2) {
                    if(removivel((*raiz)->dir)) {
                        filho = menorfilho((*raiz)->dir, &auxpai, &auxinfo);
                    }
                    else if(removivel((*raiz)->cen)) {
                        filho = maiorfilho((*raiz)->cen, &auxpai, &auxinfo);
                        //juntou = 1
                    }
                    if(!juntou)
                        onda(auxinfo, &((*raiz)->info2), auxpai, &filho, raiz);
                }
                if(info1){
                    if(removivel((*raiz)->esq))
                        filho = maiorfilho((*raiz)->esq, &auxpai, &auxinfo);
                    else if(removivel((*raiz)->cen))
                        filho = maiorfilho((*raiz)->cen, &auxpai, &auxinfo);
                    else if((*raiz)->ninfos == 1) {
                        if(pai != NULL) {
                            if(*raiz == pai->esq || (pai->ninfos == 2 && (*raiz == pai->cen))) {
                                filho = menorfilho((*raiz)->cen, &auxpai, &auxinfo);
                                auxpai =
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