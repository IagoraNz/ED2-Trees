#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./src/Q1.h"

void insere(Arv23PT **pi, const Info info) {
    Info promove;
    Arv23PT *novoNo = inserirArv23(pi, info, &promove, NULL);

    if (novoNo) {
        *pi = criaNo(promove, *pi, novoNo);
    }
}

void exibirPTBR(const IngPTBST *raiz) {
    if (raiz != NULL) {
        exibirPTBR(raiz->esq);
        printf("Palavra EN: %s\n", raiz->palavra);
        exibirPTBR(raiz->dir);
    }
}

void exibirEmOrdem(const Arv23PT *ptIn) {
    if (ptIn) {
        exibirEmOrdem(ptIn->esq);

        printf("Palavra PT-BR: %s\n", ptIn->info1.palavra);
        exibirPTBR(ptIn->info1.versaoIng);

        exibirEmOrdem(no->cen);

        if (ptIn->ninfos == 2) {
            printf("Palavra PT-BR: %s\n", ptIn->info2.palavra);
            exibirPTBR(ptIn->info2.versaoIng);
            exibirEmOrdem(ptIn->dir);
        }
    }
}

int adicionarPalavraEN(Arv23PT **raiz, char *palavraPTBR, char *palavraIngles) {
    int sucesso = 0;
    if ((*raiz) != NULL) {
        char *palavraPTUpper = (char*)malloc(strlen(palavraPTBR) + 1);
        strcpy(palavraPTUpper, palavraPTBR);
        toupperString(palavraPTUpper);

        if (strcmp((*raiz)->info1.palavra, palavraPTUpper) == 0) {
            sucesso = insereArvBin(&((*raiz)->info1.versaoIng), palavraIngles);
        } else if ((*raiz)->ninfos == 2 && strcmp(palavraPTUpper, (*raiz)->info2.palavra) == 0) {
            sucesso = insereArvBin(&((*raiz)->info2.versaoIng), palavraIngles);
        } else
        {
            if (strcmp((*raiz)->info1.palavra, palavraPTUpper) > 0) {
                sucesso = adicionarPalavraEN(&((*raiz)->esq), palavraPTUpper, palavraIngles);
            } else if ((*raiz)->ninfos == 2 && strcmp((*raiz)->info2.palavra, palavraPTUpper) > 0) {
                sucesso = adicionarPalavraEN(&((*raiz)->cen), palavraPTUpper, palavraIngles);
            } else {
                sucesso = adicionarPalavraEN(&((*raiz)->dir), palavraPTUpper, palavraIngles);
            }
        }
    }
}

void exibirPreOrdem(const Arv23PT *no ){
    if (no) {
        printf("%s\n", no->info1.palavra);
        exibirPreOrdem(no->esq);
        exibirPreOrdem(no->cen);

        if (no->ninfos == 2) {
            printf("%s\n", no->info2.palavra);
            exibirPreOrdem(no->dir);
        }
    }
}

void exibirPosOrdem(const Arv23PT *no ){
    if (no) {
        exibirPosOrdem(no->esq);
        exibirPosOrdem(no->cen);

        if (no->ninfos == 2) {
            exibirPosOrdem(no->dir);
            printf("%s\n", no->info2.palavra);
        }

        printf("%s\n", no->info1.palavra);
    }
}

void removerElemento(Arv23PT **raiz, const char *palavra) {
    if (removerArv23(raiz, palavra, NULL, raiz))
        printf("Elemento '%s' removido com sucesso.\n", palavra);
    else
        printf("Elemento '%s' nao encontrado.\n", palavra);
}

int main() {
    Info info1 = {malloc(strlen("Onibus") + 1), NULL, 1};
    strcpy(info1.palavra, "Onibus");

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
    insere(&pI, info7);
    insere(&pI, info8);
    insere(&pI, info9);
    insere(&pI, info10);

    adicionarPalavraEN(&pI, "onibus", "Bus");
    adicionarPalavraEN(&pI, "onibus", "Omnibus");
    adicionarPalavraEN(&pI, "onIbuS", "Coach");

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    exibirEmOrdem(pI);

    // Remoções de elementos
    printf("\nRemovendo elementos:\n");
    removerElemento(&pI, "rato");
    removerElemento(&pI, "zebra");
    removerElemento(&pI, "vento");

    // Exibe a árvore novamente após remoções
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);
    printf("\n\n");
    exibirPreOrdem(pI);
    printf("\n\n");
    exibirPosOrdem(pI);

    return 0;
}