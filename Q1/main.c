#include <stdio.h>
#include "./src/Q1.h"

void insere(Arv23PT **pi, const Info info) {
    Info promove;
    Arv23PT *novoNo = inserirArv23(pi, info, &promove, NULL);

    if(novoNo){
        *pi = criaNo(promove, *pi, novoNo);
    }
}

void exibirEmOrdem(const Arv23PT *ptIn) {
    if (ptIn) {
        exibirEmOrdem(ptIn->esq);

        printf("%s\n", ptIn->info1.palavra);

        exibirEmOrdem(ptIn->cen);

        if (ptIn->ninfos == 2) {
            printf("%s\n", ptIn->info2.palavra);
            exibirEmOrdem(ptIn->dir);
        }
    }
}

int main() {
    const Info info1 = {"ola", NULL};
    const Info info2 = {"zebra", NULL};
    const Info info3 = {"casa", NULL};
    const Info info4 = {"abobora", NULL};
    const Info info5 = {"pera", NULL};
    const Info info6 = {"uva", NULL};

    Arv23PT *pI = NULL; // Inicializa a árvore como vazia

    // Insere os elementos na árvore
    insere(&pI, info1);
    insere(&pI, info2);
    insere(&pI, info6);
    insere(&pI, info3);
    insere(&pI, info4);
    insere(&pI, info5);

    // Exibe a árvore em ordem
    printf("\nArvore em ordem:\n");
    exibirEmOrdem(pI);

    // Libera memória alocada
    freeTree(pI);

    return 0;
}