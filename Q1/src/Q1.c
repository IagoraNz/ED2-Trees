/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "Q1.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

Arv23PT *criaNo(Info informacao, Arv23PT *filhoesq, Arv23PT *filhocen){
    Arv23PT *no;
    no = (Arv23PT*)malloc(sizeof(Arv23PT));

    no->info1 = informacao;
    no->esq = filhoesq;
    no->cen = filhocen;
    no->ninfos = 1;

    return no;
}

int ehFolha(Arv23PT *no){
    /* Basta verificar se a esquerda é NULL */
    return (no->esq == NULL) ? 1 : 0;
}

Arv23PT *inserirArv23(Arv23PT **no, Info informacao, Info *promove, Arv23PT **pai){
    Info promove1;
    Arv23PT *maiorNo;
    maiorNo = NULL;

    if(*no == NULL)
        *no = criaNo(informacao, NULL, NULL);
    else{
        if(ehfolha(*no)){
            if((*no)->ninfos == 1)
                *no = adicionaChave(*no, informacao, NULL);
            else{
                maiorNo = quebraNo(no, informacao, promove, NULL);
                if(*pai == NULL){
                    *no = criaNo(*promove, *no, maiorNo);
                    maiorNo == NULL;
                }
            }
        }
        else{
            if(strcmp(informacao->palavra, (*no)->info1.palavra) < 0){
                maiorNo = inserirArv23(&((*no)->esq), informacao, promove, no);
            }
            else if((*no)->ninfos == 1 || (strcmp(informacao->palavra, (*no)->info2.palavra))){
                maiorNo = inserirArv23(&((*no)->cen), informacao, promove, no);
            }
            else{
                maiorNo = inserirArv23(&((*no)->dir), informacao, promove, no);
            }
        }

        if(maiorNo){
            if((*no)->ninfos == 1){
                *no = adicionaChave(*no, *promove, maiorNo);
                maiorNo = NULL;
            }
            else{
                maiorNo = quebraNo(no, *promove, &promove1, maiorNo);
                if(*pai){
                    *no = criaNo(promove1, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
equivalentes em inglês */

/*-----------------------------------------------------------------------------------------------------*/

/* (ii) informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em
português dada, independente da unidade */

/*-----------------------------------------------------------------------------------------------------*/

/* (iii) informar uma palavra em inglês e a unidade a qual a mesma pertence remove-la das árvores binárias
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
árvore 2-3 */

/*-----------------------------------------------------------------------------------------------------*/

/* (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
árvore 2-3 */