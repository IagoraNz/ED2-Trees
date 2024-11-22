#include <stdio.h>
#include "./src/Q1.h"

void insere(Arv23PT **pi, const Info info) {
    Info promove;
    Arv23PT *novoNo = inserirArv23(pi, info, &promove, NULL);

    if (novoNo) {
        *pi = criaNo(promove, *pi, novoNo);
    }
}

void exibirEmOrdem(const Arv23PT *no) {
    if(no){
        exibirEmOrdem(no->esq);

        printf("%s\n", no->info1.palavra);

        exibirEmOrdem(no->cen);

        if (no->ninfos == 2) {
            printf("%s\n", no->info2.palavra);
            exibirEmOrdem(no->dir);
        }
    }
}

void exibirPreOrdem(const Arv23PT *no ){
    if (no) {
        printf("%s\n", no->info1.palavra);

        if(no->ninfos == 2)
            printf(("%s\n"), no->info2.palavra);

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
    removerArv23(raiz, palavra, NULL, raiz);
    printf("Elemento '%s' removido com sucesso.\n", palavra);
}

int main() {
    const Info info1 = {"oculos", NULL};
    const Info info2 = {"zebra", NULL};
    const Info info3 = {"casa", NULL};
    const Info info4 = {"abobora", NULL};
    const Info info6 = {"uva", NULL};
    const Info info7 = {"ovo", NULL};
    const Info info8 = {"rato", NULL};
    const Info info9 = {"vaso", NULL};
    const Info info10 = {"vento", NULL};

    Arv23PT *pI = NULL; // Inicializa a árvore como vazia

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

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    exibirEmOrdem(pI);

    // Remoções de elementos
    printf("\nRemovendo elementos:\n");
    removerElemento(&pI, "rato");
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);
    removerElemento(&pI, "zebra");
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);
    removerElemento(&pI, "vento");
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);

    // Exibe a árvore novamente após remoções
    printf("\nArvore em ordem apos remocoes:\n");
    exibirEmOrdem(pI);
    printf("\n\n");
    exibirPreOrdem(pI);
    printf("\n\n");
    exibirPosOrdem(pI);

    return 0;
}