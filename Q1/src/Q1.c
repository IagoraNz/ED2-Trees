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

/*
    summary
        Função para inserir uma palavra em uma árvore 2-3
    parameters
        Arv23pt **no: nó da árvore 2-3
        char *word: palavra a ser inserida
        char *promove: palavra a ser promovida
        Arv23pt **pai: nó pai da árvore 2-3
*/
Arv23pt *insere(Arv23pt **no, char *word, char *promove, Arv23pt **pai){
    Arv23pt *maiorno;
    int promove1;
    maiorno = NULL;

    // Verifica se o nó é nulo, se for, cria um novo nó
    if(*no = NULL)
        *no = criaNo(word, NULL, NULL);
    else{ // Caso contrário, insere a palavra no nó
        if(ehFolha(*no)){ // Verifica se o nó é folha
            if((*no)->ninfos == 1) // Verifica se o nó possui apenas uma informação, ou seja, possui um slot disponível
                *no = adicionaChave(*no, word, NULL);
            else{ 
            /*
            Se o nó possuir duas informações, quebra o nó e promove a palavra para o nó pai
            de modo que o nó pai possua uma informação e os filhos possuam uma informação cada
            */
                maiorno = quebraNo(no, word, promove, NULL);
                if(*pai == NULL){
                    *no = criaNo(*promove, *no, maiorno);
                    maiorno = NULL;
                }
            }
        }
        else{ // Caso contrário, insere a palavra no nó filho
            /*
            1. Verifica se a palavra é menor que a palavra1 do nó, se for, insere a palavra no nó esquerdo
            2. Verifica se há apenas uma informação no nó ou se a palavra é maior que a palavra1 do nó, 
            se for, insere a palavra no nó do meio  
            3. Caso contrário, insere a palavra no nó direito
            */
            if(strcmp(word, (*no)->word) < 0) 
                maiorno = insere(&(*no)->esq, word, promove, no);
            else if(((*no)->ninfos == 1) || (strcmp(word, (*no)->word) > 0))
                maiorno = insere(&(*no)->meio, word, promove, no);
            else
                maiorno = insere(&(*no)->dir, word, promove, no);

            // Se o nó filho retornar um nó, ou seja, o nó foi quebrado, insere a palavra promovida no nó pai
            if(maiorno != NULL){
                if((*no)->ninfos == 1)
                    *no = adicionaChave(*no, *promove, maiorno);
                else
                    maiorno = quebraNo(no, *promove, promove, maiorno);
                    if(*pai == NULL){
                        *no = criaNo(*promove, *no, maiorno);
                        maiorno = NULL;
                    }
            }
        }
    }

    return maiorno;
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