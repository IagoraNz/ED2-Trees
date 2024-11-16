#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./src/Q1.h"

Info criaInfo(const char *palavra, const int unidade) {
    Info info;
    info.versaoIng = NULL;
    info.palavra = strdup(palavra);
    info.unidade = unidade;
    info.versaoIng = (IngPTBST*)malloc(sizeof(IngPTBST));
    info.versaoIng->esq = NULL;
    info.versaoIng->dir = NULL;
    return info;
}

void adicionarTraducaoEmIngles(Info *info, const char *palavraIng) {
    if(info->versaoIng == NULL){
        info->versaoIng = (IngPTBST*)malloc(sizeof(IngPTBST));
        info->versaoIng->esq = NULL;
        info->versaoIng->dir = NULL;
    }

    info->versaoIng->palavra = strdup(palavraIng);
}

void exibir_tree23(const Arv23PT *raiz){
    if(raiz != NULL){
        exibir_tree23(raiz->esq);
        printf("Palavra (PT): %s, Unidade: %d", raiz->info1.palavra, raiz->info1.unidade);

        if(raiz->info1.versaoIng != NULL && raiz->info1.versaoIng->palavra != NULL){
            printf(", Traducao (EN): %s", raiz->info1.versaoIng->palavra);
            printf("\n");
        }

        // Se houver o segundo elemento (ninfos == 2), exibe o segundo filho
        if(raiz->ninfos == 2){
            printf("Palavra (PT): %s, Unidade: %d", raiz->info2.palavra, raiz->info2.unidade);

            // Exibir a tradução em inglês, se houver
            if(raiz->info2.versaoIng != NULL && raiz->info2.versaoIng->palavra != NULL)
                printf(", Traducao (EN): %s", raiz->info2.versaoIng->palavra);
            printf("\n");
        }
        exibir_tree23(raiz->cen);
        if(raiz->ninfos == 2) {
            exibir_tree23(raiz->dir);
        }
    }
}

int main(){
    Arv23PT *raiz = NULL;

    Info info2 = criaInfo("gato", 2);
    adicionarTraducaoEmIngles(&info2, "cat");

    Info info1 = criaInfo("cachorro", 1);
    adicionarTraducaoEmIngles(&info1, "dog");

    Info info3 = criaInfo("passarinho", 3);
    adicionarTraducaoEmIngles(&info3, "bird");

    Info info4 = criaInfo("peixe", 4);
    adicionarTraducaoEmIngles(&info4, "fish");

    Info info5 = criaInfo("cavalo", 5);
    adicionarTraducaoEmIngles(&info5, "horse");

    Info promovido;
    inserirArv23(&raiz, &info1, &promovido, &raiz);
    printf(("\n\nTESTE 1\n\n"));
    exibir_tree23(raiz);
    inserirArv23(&raiz, &info2, &promovido, &raiz);
    printf(("\n\nTESTE 2\n\n"));
    exibir_tree23(raiz);
    inserirArv23(&raiz, &info3, &promovido, &raiz);
    printf(("\n\nTESTE 3\n\n"));
    exibir_tree23(raiz);
    inserirArv23(&raiz, &info4, &promovido, &raiz);
    printf(("\n\nTESTE 4\n\n"));
    exibir_tree23(raiz);
    inserirArv23(&raiz, &info5, &promovido, &raiz);
    printf(("\n\nTESTE 5\n\n"));
    exibir_tree23(raiz);

    printf("\nExibindo a arvore 23 com traducoes:\n");
    exibir_tree23(raiz);

    // freeTree(&raiz);

    return 0;
}