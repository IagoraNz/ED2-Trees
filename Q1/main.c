#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./src/Q1.h"

void insere(Arv23PT **pi, const Info info) {
    Info promove;
    Arv23PT *novoNo = inserirArv23(pi, info, &promove, NULL);

    if(novoNo){
        *pi = criaNo(promove, *pi, novoNo);
    }
}

void exibirPTBR(const IngPTBST *raiz) {
    if (raiz != NULL) {
        exibirPTBR(raiz->esq);
        printf("Palavra Portugues: %s\n", raiz->palavra);
        exibirPTBR(raiz->dir);
    }
}

void exibirEmOrdem(const Arv23PT *ptIn) {
    if (ptIn) {
        exibirEmOrdem(ptIn->esq);

        printf("Palavra Ingles: %s\n", ptIn->info1.palavra);
        exibirPTBR(ptIn->info1.versaoIng);

        exibirEmOrdem(ptIn->cen);

        if (ptIn->ninfos == 2) {
            printf("Palavra Ingles: %s\n", ptIn->info2.palavra);
            exibirPTBR(ptIn->info2.versaoIng);
            exibirEmOrdem(ptIn->dir);
        }
    }
}

int adicionarPalavraPTBR(Arv23PT **raiz, char *palavraIngles, char *palavraPTBR) {
    int sucesso = 0;
    if ((*raiz) != NULL) {
        char *palavraENUpper = (char*)malloc(strlen(palavraIngles) + 1);
        strcpy(palavraENUpper, palavraIngles);
        toupperString(palavraENUpper);

        if (strcmp((*raiz)->info1.palavra, palavraENUpper) == 0) {
            sucesso = insereArvBin(&((*raiz)->info1.versaoIng), palavraPTBR);
        } else if ((*raiz)->ninfos == 2 && strcmp(palavraENUpper, (*raiz)->info2.palavra) == 0) {
            sucesso = insereArvBin(&((*raiz)->info2.versaoIng), palavraPTBR);
        } else
        {
            if (strcmp((*raiz)->info1.palavra, palavraENUpper) > 0) {
                sucesso = adicionarPalavraPTBR(&((*raiz)->esq), palavraENUpper, palavraPTBR);
            } else if ((*raiz)->ninfos == 2 && strcmp((*raiz)->info2.palavra, palavraENUpper) > 0) {
                sucesso = adicionarPalavraPTBR(&((*raiz)->cen), palavraENUpper, palavraPTBR);
            } else {
                sucesso = adicionarPalavraPTBR(&((*raiz)->dir), palavraENUpper, palavraPTBR);
            }
        }
    }
}

int main() {
    Info info1 = {malloc(strlen("Bus") + 1), NULL, 1};
    strcpy(info1.palavra, "Bus");

    Info info2 = {malloc(strlen("zebra") + 1), NULL, 1};
    strcpy(info2.palavra, "zebra");

    Info info3 = {malloc(strlen("casa") + 1), NULL, 1};
    strcpy(info3.palavra, "casa");

    Info info4 = {malloc(strlen("abobora") + 1), NULL, 1};
    strcpy(info4.palavra, "abobora");

    Info info5 = {malloc(strlen("pera") + 1), NULL, 1};
    strcpy(info5.palavra, "pera");

    Info info6 = {malloc(strlen("uva") + 1), NULL, 1};
    strcpy(info6.palavra, "uva");

    Arv23PT *pI = NULL; // Inicializa a árvore como vazia

    toupperString(info1.palavra);
    toupperString(info2.palavra);
    toupperString(info3.palavra);
    toupperString(info4.palavra);
    toupperString(info5.palavra);
    toupperString(info6.palavra);
    
    printf("%s\n", info1.palavra);
    printf("%s\n", info2.palavra);
    printf("%s\n", info3.palavra);
    printf("%s\n", info4.palavra);
    printf("%s\n", info5.palavra);
    printf("%s\n", info6.palavra);

    // Insere os elementos na árvore
    insere(&pI, info1);
    insere(&pI, info2);
    insere(&pI, info6);
    insere(&pI, info3);
    insere(&pI, info4);
    insere(&pI, info5);

    adicionarPalavraPTBR(&pI, "bus", "Onibus");
    adicionarPalavraPTBR(&pI, "BUS", "Barramento");

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    exibirEmOrdem(pI);

    // Libera memória alocada
    freeTree(pI);

    return 0;
}