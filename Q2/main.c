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

void menu() {
    printf("\n==============================================\n");
    printf("1 - Palavras por Unidade\n");
    printf("2 - Palavras em Portugues\n");
    printf("3 - Remover palavra em Ingles\n");
    printf("4 - Remover palavra em Portugues\n");
    printf("5 - Metrificar tempo busca\n");
    printf("0 - Sair\n");
    printf("==============================================\n");
    printf("Opcao: ");
}

int main() {
    ArvVP *raiz = NULL;
    char linha[200];
    int unidadeAtual = 0, sucesso = 1; // Para controlar a unidade atual

    // Iniciando Leitura do Arquivo exemplo.txt
    FILE *arquivo;
    arquivo = fopen("../exemplo.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        sucesso = 0;
    }
    if (sucesso = 1) {
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
        int enc = 0;

        exibirUnidade(raiz, 2, &enc);

        int op = 0, unidade = 0;
        char palavra[50];
        do
        {
            enc = 0;
            menu();
            scanf("%d", &op);
            getchar();
            switch (op)
            {
            case 1:
                printf("Informe a unidade: ");
                scanf("%d", &unidade);
                exibirUnidade(raiz, unidade, &enc);
                break;
            case 2:
                printf("Informe a palavra em portugues: ");
                scanf("%[^\n]", palavra);
                getchar();
                exibirArvBinPT(raiz, palavra);
                break;
            case 3:
                printf("Informe a palavra em ingles: ");
                scanf("%[^\n]", palavra);
                getchar();
                printf("Informe a unidade: ");
                scanf("%d", &unidade);
                removerArvVPEN(&raiz, palavra, unidade);
                break;
            case 4:
                printf("Informe a palavra em portugues: ");
                scanf("%[^\n]", palavra);
                getchar();
                printf("Informe a unidade: ");
                scanf("%d", &unidade);
                removerArvVPPTBR(&raiz, palavra, unidade);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
            }
        } while (op != 0);
    }
    
    return sucesso == 1 ? 0 : 1;
}
