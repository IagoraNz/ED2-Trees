#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "./utils/Q1.h"

void insere(Arv23PT **pi, const Info info) {
    Info promove;
    Arv23PT *novoNo = inserirArv23(pi, info, &promove, NULL);

    if (novoNo) {
        *pi = criaNo(promove, *pi, novoNo);
    }
}

void exibirEmOrdem(const Arv23PT *ptIn) {
    if (ptIn) {
        exibirEmOrdem(ptIn->esq);

        if (ptIn->info1.palavra != NULL) {
            printf("%s\n", ptIn->info1.palavra);
        }

        exibirEmOrdem(ptIn->cen);

        if (ptIn->ninfos == 2) {
            printf("%s\n", ptIn->info2.palavra);
            exibirEmOrdem(ptIn->dir);
        }
    }
}

void adicionarPalavraEN(Arv23PT **raiz, const char *palavraPTBR, char *palavraIngles) {

    if ((*raiz) != NULL) {
        char *palavraPTUpper = (char*)malloc(strlen(palavraPTBR) + 1);
        strcpy(palavraPTUpper, palavraPTBR);
        toupperString(palavraPTUpper);

        if (strcmp((*raiz)->info1.palavra, palavraPTUpper) == 0)
            insereArvBin(&((*raiz)->info1.versaoIng), palavraIngles);
        else if ((*raiz)->ninfos == 2 && strcmp(palavraPTUpper, (*raiz)->info2.palavra) == 0)
            insereArvBin(&((*raiz)->info2.versaoIng), palavraIngles);
        else{
            if (strcmp((*raiz)->info1.palavra, palavraPTUpper) > 0)
                adicionarPalavraEN(&((*raiz)->esq), palavraPTUpper, palavraIngles);
            else if ((*raiz)->ninfos == 2 && strcmp((*raiz)->info2.palavra, palavraPTUpper) > 0)
                adicionarPalavraEN(&((*raiz)->cen), palavraPTUpper, palavraIngles);
            else
                adicionarPalavraEN(&((*raiz)->dir), palavraPTUpper, palavraIngles);
        }
    }

}

void exibirPreOrdem(const Arv23PT *no ){
    if (no) {
        if(no->info1.palavra != NULL)
            printf("%s\n", no->info1.palavra);
        exibirPreOrdem(no->esq);
        exibirPreOrdem(no->cen);

        if (no->ninfos == 2)
            exibirPreOrdem(no->dir);
    }
}

void exibirPosOrdem(const Arv23PT *no ){
    if (no) {
        exibirPosOrdem(no->esq);
        exibirPosOrdem(no->cen);

        if (no->ninfos == 2) 
            exibirPosOrdem(no->dir);

        printf("%s\n", no->info1.palavra);

        if(no->ninfos == 2)
            printf("%s\n", no->info2.palavra);
    }
}

void removerElemento(Arv23PT **raiz, const char *palavra) {
    if (removerArv23(raiz, palavra, NULL, raiz))
        printf("Elemento '%s' removido com sucesso.\n", palavra);
    else
        printf("Elemento '%s' nao encontrado.\n", palavra);
}

int main() {
    Info *info1 = (Info *)malloc(sizeof(Info));
    info1->palavra = "oculos";
    info1->versaoIng = NULL;
    info1->unidade = 10;

    Info *info2 = (Info *)malloc(sizeof(Info));
    info2->palavra = "zebra";
    info2->versaoIng = NULL;
    info2->unidade = 9;

    Info *info3 = (Info *)malloc(sizeof(Info));
    info3->palavra = "casa";
    info3->versaoIng = NULL;
    info3->unidade = 7;

    Info *info4 = (Info *)malloc(sizeof(Info));
    info4->palavra = "abobora";
    info4->versaoIng = NULL;
    info4->unidade = 10;

    Info *info6 = (Info *)malloc(sizeof(Info));
    info6->palavra = "uva";
    info6->versaoIng = NULL;
    info6->unidade = 9;

    Info *info7 = (Info *)malloc(sizeof(Info));
    info7->palavra = "ovo";
    info7->versaoIng = NULL;
    info7->unidade = 9;

    Info *info8 = (Info *)malloc(sizeof(Info));
    info8->palavra = "rato";
    info8->versaoIng = NULL;
    info8->unidade = 8;

    Info *info9 = (Info *)malloc(sizeof(Info));
    info9->palavra = "vaso";
    info9->versaoIng = NULL;
    info9->unidade = 9;

    Info *info10 = (Info *)malloc(sizeof(Info));
    info10->palavra = "vento";
    info10->versaoIng = NULL;
    info10->unidade = 10;

    Arv23PT *pI = NULL; // Inicializa a árvore como vazia

    // Insere os elementos na árvore
    insere(&pI, *info1);
    insere(&pI, *info2);
    insere(&pI, *info6);
    insere(&pI, *info3);
    insere(&pI, *info4);
    insere(&pI, *info7);
    insere(&pI, *info8);
    insere(&pI, *info9);
    insere(&pI, *info10);

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    exibirEmOrdem(pI);

    // Remoções de elementos
    printf("\nRemovendo elementos:\n");
    removerElemento(&pI, "oculos");
    // removerElemento(&pI, "rato");
    // removerElemento(&pI, "zebra");

    // Exibe a árvore novamente após remoções
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);
    printf("\n\n");
    exibirPreOrdem(pI);
    printf("\n\n");
    exibirPosOrdem(pI);

    return 0;
}