#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "src/Q2.h"

void insere(ArvVP **raiz, InfoArvBin info) {
    int resultado;
    resultado = inserirArvVP(raiz, info);
    // Verificar o resultado
    if (resultado == 1) {
        printf("Insercao bem-sucedida!\n");
    } else {
        printf("Erro ao inserir.\n");
    }
    (*raiz)->cor = 1;
}

void exibirArvVP(ArvVP *raiz) {
    if (raiz != NULL) {
        exibirArvVP(raiz->esq);
        printf("PALAVRA-PTBR: %s\nPALAVRASEN:\n", raiz->info.palavraPortugues);
        printf("Cor: %d\n", raiz->cor);
        exibirArvBin(raiz->info.arvBinIngles);
        exibirArvVP(raiz->dir);
    }
}

int main() {
    ArvVP *raiz = NULL;
    char linha[200];
    int unidadeAtual = 0; // Para controlar a unidade atual

    // Iniciando Leitura do Arquivo exemplo.txt
    FILE *arquivo;
    arquivo = fopen("../exemplo.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Loop para leitura do arquivo:
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Remover a nova linha no final da linha lida
        linha[strcspn(linha, "\n")] = '\0';

        // Verificar se a linha começa com '% Unidade'
        if (strncmp(linha, "% Unidade", 9) == 0) 
            sscanf(linha, "%% Unidade %d", &unidadeAtual);
        else if (linha[0] != '\0' && linha[0] != '%') {
           char palavraIN[50];

            // Separar a palavra em inglês (à esquerda do ':')
            char *token = strtok(linha, ":");
            if (token != NULL) {
                strcpy(palavraIN, token);
            }

            // Processar as palavras em português (à direita do ':')
            token = strtok(NULL, ";");
            if (token != NULL) {
                char *palavra = strtok(token, ",");
                while (palavra != NULL) {
                    InfoArvBin info;
                    info.palavraPortugues = (char *)malloc(50 * sizeof(char));
                    info.arvBinIngles = (IngPTBST *)malloc(sizeof(IngPTBST));
                    info.arvBinIngles->esq = NULL;
                    info.arvBinIngles->dir = NULL;
                    info.arvBinIngles->info.palavraIngles = (char *)malloc(50 * sizeof(char));

                    strcpy(info.palavraPortugues, palavra); 
                    strcpy(info.arvBinIngles->info.palavraIngles, palavraIN); 
                    info.arvBinIngles->info.unidade = unidadeAtual; 
                    insere(&raiz, info); 
                    palavra = strtok(NULL, ","); // Próxima palavra em português
                }
            }
        }
    }

    // Fechar o arquivo após a leitura
    fclose(arquivo);
    exibirArvVP(raiz); // Exibir a árvore
    return 0;
}
