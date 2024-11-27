#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/Q2.h"

void insere(ArvVP **raiz, InfoArvBin info){
    int resultado;
    resultado = inserirArvVP(raiz, info);
    // Verificar o resultado
    if (resultado == 1)
    {
        printf("Insercao bem-sucedida!\n");
    }
    else
    {
        printf("Erro ao inserir.\n");
    }
    (*raiz)->cor = 1;
}

void exibirArvVP(ArvVP *raiz){
    if(raiz != NULL){
        exibirArvVP(raiz->esq);
        printf("%s\n", raiz->info.palavraPortugues);
        printf("Cor: %d\n", raiz->cor);
        exibirArvBin(raiz->info.arvBinIngles);
        exibirArvVP(raiz->dir);
    }
}

int main()
{
    ArvVP *raiz = NULL;
    int quant = 0;

    while (quant < 2)
    {
        InfoArvBin info;
        info.palavraPortugues = (char *)malloc(50 * sizeof(char));
        info.arvBinIngles = (IngPTBST *)malloc(sizeof(IngPTBST));
        info.arvBinIngles->esq = NULL;
        info.arvBinIngles->dir = NULL;
        info.arvBinIngles->info.palavraIngles = (char *)malloc(50 * sizeof(char));

        printf("Digite a palavra em portugues: ");
        scanf("%s", info.palavraPortugues);
        printf("Digite a palavra em ingles: ");
        scanf("%s", info.arvBinIngles->info.palavraIngles);
        printf("Digite a unidade: ");
        scanf("%d", &info.arvBinIngles->info.unidade);

        insere(&raiz, info);

        quant++;
    }
    
    printf("Cor da Raiz: %d\n", raiz->cor);

    exibirArvVP(raiz);

    removerPrincipal(&raiz, "Bus", 1);

    exibirArvVP(raiz);

    return 0;
}
