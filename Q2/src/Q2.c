/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../src/Q2.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

/**
 * @brief Função que insere uma unidade em uma lista de unidades
 * 
 * @param unidades: lista de unidades
 * @param unidade: unidade a ser inserida
 * @return void
 */
void inserirunidade(Unidades **unidades, int unidade){
    if (*unidades == NULL){
        *unidades = (Unidades*)malloc(sizeof(Unidades));
        (*unidades)->unidade = unidade;
        (*unidades)->prox = NULL;
    } 
    else
        inserirunidade(&(*unidades)->prox, unidade);
}

/**
 * @brief Função que insere uma informação em uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param info: informação a ser inserida
 * @return void
 */
void inserirArvBin(IngPTBST **raiz, InfoArvoreIngPTBST info){
    if(*raiz == NULL){
        *raiz = (IngPTBST*)malloc(sizeof(IngPTBST));
        (*raiz)->info = info;
        (*raiz)->esq = NULL;
        (*raiz)->dir = NULL;
    } 
    else{
        if (strcmp((*raiz)->info.palavraIngles, info.palavraIngles) == 0)
            inserirunidade(&(*raiz)->info.unidades, info.unidades->unidade);
        else if (strcmp((*raiz)->info.palavraIngles, info.palavraIngles) > 0)
            inserirArvBin(&(*raiz)->esq, info);
        else
            inserirArvBin(&(*raiz)->dir, info);
    }
}

/**
 * @brief Função que cria um nó de uma árvore vermelho e preta
 * 
 * @param no: nó a ser criado
 * @param info: informação a ser inserida no nó
 * @return void
 */
void criarNo(ArvVP **no, InfoArvBin info){
    *no = (ArvVP*)malloc(sizeof(ArvVP));
    (*no)->info = info;
    (*no)->info.palavraPortugues = strdup(info.palavraPortugues);
    (*no)->cor = VERMELHO;
    (*no)->esq = NULL;
    (*no)->dir = NULL;
}

/**
 * @brief Função que troca a cor de um nó
 * 
 * @param raiz: nó a ser trocado a cor
 * @return void
 */
void trocaCor(ArvVP **raiz){
    (*raiz)->cor = !(*raiz)->cor;
    if ((*raiz)->esq != NULL)
        (*raiz)->esq->cor = !(*raiz)->esq->cor;
    if ((*raiz)->dir != NULL)
        (*raiz)->dir->cor = !(*raiz)->dir->cor;
}

/**
 * @brief Função que realiza uma rotação à esquerda
 * 
 * @param raiz: raiz da árvore
 * @return void
 */
void rotacaoEsq(ArvVP **raiz){
    ArvVP *aux = (*raiz)->dir;
    (*raiz)->dir = aux->esq;
    aux->esq = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = VERMELHO;
    *raiz = aux;
}

/**
 * @brief Função que realiza uma rotação à direita
 * 
 * @param raiz: raiz da árvore
 * @return void
 */
void rotacaoDir(ArvVP **raiz){
    ArvVP *aux = (*raiz)->esq;
    (*raiz)->esq = aux->dir;
    aux->dir = *raiz;
    aux->cor = (*raiz)->cor;
    (*raiz)->cor = VERMELHO;
    *raiz = aux;
}

/**
 * @brief Função que pega a cor de um nó
 * 
 * @param raiz: nó a ser verificado
 * @return int: cor do nó
 */
int pegarCor(ArvVP *raiz){
    int cor = 1;
    if (raiz != NULL)
        cor = raiz->cor;
    return cor;
}

/**
 * @brief Função que balanceia uma árvore vermelho e preta, realizando rotações e trocas de cor
 * 
 * @param raiz: raiz da árvore
 * @return void
 */
void balancear(ArvVP **raiz){
    if (pegarCor((*raiz)->esq) == PRETO && pegarCor((*raiz)->dir) == VERMELHO)
        rotacaoEsq(raiz);
    if ((*raiz)->esq != NULL && (*raiz)->esq->cor == VERMELHO && (*raiz)->esq->esq != NULL && (*raiz)->esq->esq->cor == VERMELHO)
        rotacaoDir(raiz);
    if (pegarCor((*raiz)->esq) == VERMELHO && pegarCor((*raiz)->dir) == VERMELHO)
        trocaCor(raiz);
}

/**
 * @brief Função que insere uma informação em uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore
 * @param info: informação a ser inserida
 * @return int: 1 se a inserção foi bem sucedida, 0 caso contrário
 */
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

/*-----------------------------------------------------------------------------------------------------*/

/* (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das 
equivalentes em inglês;  */

/**
 * @brief Função que verifica se uma unidade está presente em uma lista de unidades
 * 
 * @param unidades: lista de unidades
 * @param unidade: unidade a ser verificada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int unidadePresente(Unidades *unidades, int unidade) {
    int resultado = 0;
    if (unidades != NULL) {
        if (unidades->unidade == unidade) {
            resultado = 1; 
        } else {
            resultado = unidadePresente(unidades->prox, unidade); 
        }
    }
    return resultado;
}

/**
 * @brief Função que exibe uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param unidade: unidade a ser exibida
 * @return void
 */
void exibirArvBin(IngPTBST *raiz, int unidade) {
    if (raiz != NULL) {
        exibirArvBin(raiz->esq, unidade);

        int presente = unidadePresente(raiz->info.unidades, unidade);
        if (presente) {
            printf("%s\n", raiz->info.palavraIngles);
            printf("Unidade: %d\n", unidade);
        }

        exibirArvBin(raiz->dir, unidade);
    }
}

/**
 * @brief Função que busca uma unidade em uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int buscarUnidade(IngPTBST *raiz, int unidade) {
    int encontrou = 0;
    if (raiz != NULL) {
        int presente = unidadePresente(raiz->info.unidades, unidade);
        if (presente) {
            encontrou = 1;
        } else {
            int encontrouEsq = buscarUnidade(raiz->esq, unidade);
            int encontrouDir = buscarUnidade(raiz->dir, unidade);
            encontrou = encontrouEsq || encontrouDir; 
        }
    }
    return encontrou;
}

/**
 * @brief Função que exibe uma unidade de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param unidade: unidade a ser exibida
 * @param enc: variável de controle
 * @return void
 */
void exibirUnidade(ArvVP *raiz, int unidade, int *enc) {
    if (raiz != NULL) {
        exibirUnidade(raiz->esq, unidade, enc);

        *enc = 1;
        printf("%s\n", raiz->info.palavraPortugues);
        exibirArvBin(raiz->info.arvBinIngles, unidade);
        printf("\n");

        exibirUnidade(raiz->dir, unidade, enc);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (ii)informar uma palavra em português e então imprima todas as palavras em inglês equivalente a palavra em 
português dada, independente da unidade;  */

/**
 * @brief Função que exibe as palavras em inglês de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @return void
 */
void exibirPalavrasIngles(IngPTBST *raiz){
    if(raiz != NULL){
        exibirPalavrasIngles(raiz->esq);
        printf("%s\n", raiz->info.palavraIngles);
        exibirPalavrasIngles(raiz->dir);
    }
}

/**
 * @brief Função que exibe uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavra: palavra a ser exibida
 * @return void
 */
void exibirArvBinPT(ArvVP *raiz, char *palavra){
    if(raiz != NULL){
        exibirArvBinPT(raiz->esq, palavra);
        if(strcmp(raiz->info.palavraPortugues, palavra) == 0){
            printf("Palavra PT-BR: %s\nPalavras EN:\n", raiz->info.palavraPortugues);
            exibirPalavrasIngles(raiz->info.arvBinIngles);
        }
        exibirArvBinPT(raiz->dir, palavra);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iii)informar uma palavra em inglês e e a unidade a qual a mesma pertence remove-la das árvores binárias 
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da 
árvore Rubro Negra. */

/**
 * @brief Função que verifica se um nó é folha de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @return int: 1 se o nó é folha, 0 caso contrário
 */
int ehfolha(IngPTBST *raiz){
    return (raiz->esq == NULL && raiz->dir == NULL);
}

/**
 * @brief Função que verifica se um nó é um filho de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @return IngPTBST*: nó filho
 */
IngPTBST* soumfilho(IngPTBST *raiz){
    IngPTBST *aux;
    aux = NULL;
    if(raiz->esq == NULL) 
        aux = raiz->dir;
    else if (raiz->dir == NULL)
        aux = raiz->esq;
    return aux;
}

/**
 * @brief Função que busca o menor filho à esquerda da subárvore direita
 * 
 * @param raiz: raiz da árvore binária de busca
 * @return IngPTBST*: menor filho
 */
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

/**
 * @brief Função que remove uma palavra de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param palavra: palavra a ser removida
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
Unidades* removerUnidadeRecursivo(Unidades *unidades, int unidade, int *removido) {
    Unidades *prox = unidades;
    if (unidades != NULL) {
        if (unidades->unidade == unidade) {
            prox = unidades->prox; 
            free(unidades);
            *removido = 1;
        } else {
            unidades->prox = removerUnidadeRecursivo(unidades->prox, unidade, removido);
        }
    }
    return prox;
}

/**
 * @brief Função que remove uma palavra de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param palavraEN: palavra em inglês a ser removida
 * @param unidade: unidade a ser removida
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int removerPalavraEN(IngPTBST **raiz, const char *palavraEN, int unidade){
    int encontrou = 0;
    if ((*raiz) != NULL){
        if (strcmp((*raiz)->info.palavraIngles, palavraEN) == 0){
            int unidadeRemovida = 0;
            (*raiz)->info.unidades = removerUnidadeRecursivo((*raiz)->info.unidades, unidade, &unidadeRemovida);
            if (unidadeRemovida){
                encontrou = 1;
                if ((*raiz)->info.unidades == NULL){
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
                        removerPalavraEN(&(*raiz)->dir, aux->info.palavraIngles, unidade);
                    }
                }
            }
        } else if (strcmp((*raiz)->info.palavraIngles, palavraEN) > 0)
            encontrou = removerPalavraEN(&(*raiz)->esq, palavraEN, unidade);
        else
            encontrou = removerPalavraEN(&(*raiz)->dir, palavraEN, unidade);
    }
    return encontrou;
}

/**
 * @brief Função que percorre uma árvore vermelho e preta e remove uma palavra em inglês
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavraEN: palavra em inglês a ser removida
 * @param unidade: unidade a ser removida
 * @return void
 */
void percorrerArvVP(ArvVP **raiz, const char *palavraEN, int unidade, char palavrasPT[][50], int *remover, int *removerCount){
    if ((*raiz) != NULL){
        percorrerArvVP(&(*raiz)->esq, palavraEN, unidade, palavrasPT, remover, removerCount);
        int encontrou = removerPalavraEN(&(*raiz)->info.arvBinIngles, palavraEN, unidade);
        if (encontrou && (*raiz)->info.arvBinIngles == NULL){
            *remover = 1;
            strcpy(palavrasPT[*removerCount], (*raiz)->info.palavraPortugues);
            (*removerCount)++;
        }
        percorrerArvVP(&(*raiz)->dir, palavraEN, unidade, palavrasPT, remover, removerCount);
    }
}

/**
 * @brief Função que move um nó para a esquerda e troca a cor
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
void move2EsqRed(ArvVP **raiz){
    trocaCor(raiz);
    if (pegarCor((*raiz)->dir->esq) == VERMELHO){
        rotacaoDir(&(*raiz)->dir);
        rotacaoEsq(raiz);
        trocaCor(raiz);
    }
}

/**
 * @brief Função que move um nó para a direita e troca a cor
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
void move2DirRed(ArvVP **raiz){
    trocaCor(raiz);
    if (pegarCor((*raiz)->esq->esq) == VERMELHO){
        rotacaoDir(raiz);
        trocaCor(raiz);
    }
}

/**
 * @brief Função que procura o menor nó de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return ArvVP*: menor nó
 */
ArvVP* procuraMenor(ArvVP *raiz) {
    ArvVP *no1 = raiz;
    ArvVP *no2 = raiz->esq;
    while (no2) {
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
}

/**
 * @brief Função que remove o menor nó de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
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

/**
 * @brief Função que remove um nó de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavraPT: palavra em português a ser removida
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
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

/**
 * @brief Função que remove uma palavra em inglês de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavraEN: palavra em inglês a ser removida
 * @param unidade: unidade a ser removida
 * @return void
 */
void removerArvVPEN(ArvVP **raiz, const char *palavraEN, int unidade){
    char palavraPT[100][50];
    int remover = 0;
    int removerCount = 0;
    percorrerArvVP(raiz, palavraEN, unidade, palavraPT, &remover, &removerCount);
    if (remover){
        for (int i = 0; i < removerCount; i++){
            int sucesso = 0;
            sucesso = removerArvVP(raiz, palavraPT[i]);
            if (!sucesso)
                printf("Erro ao remover.\n");
            else
                printf("Remocao bem-sucedida!\n");
        }
    }
    if ((*raiz) != NULL)
        (*raiz)->cor = PRETO;
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então remove-la, para isto 
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma 
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da 
árvore Rubro Negra. */

/**
 * @brief Função que procura uma unidade em uma lista de unidades
 * 
 * @param unidades: lista de unidades
 * @param unidade: unidade a ser procurada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int procurarUnidade(Unidades *unidades, int unidade) {
    int encontrou = 0;
    if (unidades != NULL) {
        if (unidades->unidade == unidade)
            encontrou = 1;
        else
            encontrou = procurarUnidade(unidades->prox, unidade);
    }
    return encontrou;
}

/**
 * @brief Função que busca uma palavra em inglês em uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param unidade: unidade a ser buscada
 * @param palavraEN: palavra em inglês a ser buscada
 * @param encontrou: variável de controle
 * @return void
 */
void buscarPalavraEN(IngPTBST *raiz, int unidade, char *palavraEN, int *encontrou) {
    if (raiz != NULL && *encontrou != 1) {
        buscarPalavraEN(raiz->esq, unidade, palavraEN, encontrou);

        if (*encontrou != 1 && procurarUnidade(raiz->info.unidades, unidade)) {
            strcpy(palavraEN, raiz->info.palavraIngles);
            *encontrou = 1;
        }

        if (*encontrou != 1)
            buscarPalavraEN(raiz->dir, unidade, palavraEN, encontrou);
    }
}

/**
 * @brief Função que remove uma palavra em inglês de uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária de busca
 * @param palavraEN: palavra em inglês a ser removida
 * @param unidade: unidade a ser removida
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int percorrerArvVPPTBR(ArvVP **raiz, char *palavraPT, int unidade, int *remover) {
    if ((*raiz) != NULL) {
        if (strcmp(palavraPT, (*raiz)->info.palavraPortugues) == 0) {
            char palavraEN[50];
            int encontrou = 0;

            buscarPalavraEN((*raiz)->info.arvBinIngles, unidade, palavraEN, &encontrou);

            if (encontrou == 1) {
                encontrou = removerPalavraEN(&(*raiz)->info.arvBinIngles, palavraEN, unidade);
                if (encontrou == 1 && (*raiz)->info.arvBinIngles == NULL) {
                    printf("Encontrou!\n");
                    *remover = 1;
                }
            }
        } else {
            if (strcmp(palavraPT, (*raiz)->info.palavraPortugues) < 0)
                percorrerArvVPPTBR(&(*raiz)->esq, palavraPT, unidade, remover);
            else
                percorrerArvVPPTBR(&(*raiz)->dir, palavraPT, unidade, remover);
        }
    }
    return *remover;
}

/**
 * @brief Função que remove uma palavra em português de uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavraPT: palavra em português a ser removida
 * @param unidade: unidade a ser removida
 * @return void
 */
void removerArvVPPTBR(ArvVP **raiz, char *palavraPT, int unidade) {
    int remover = 0;
    percorrerArvVPPTBR(raiz, palavraPT, unidade, &remover);
    printf("Remover: %d\n", remover);
    if (remover == 1) {
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