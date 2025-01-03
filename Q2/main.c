#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "src/Q2.h"
#include <time.h>

/**
 * @brief Função que insere uma info em uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore
 * @param info: info a ser inserida
 * @return int: 1 se a inserção foi bem-sucedida, 0 caso contrário
 */
void insere(ArvVP **raiz, InfoArvBin info) {
    int resultado;
    resultado = inserirArvVP(raiz, info);
    (*raiz)->cor = 1;
}

/**
 * @brief Função que preenche uma árvore vermelho e preta com palavras aleatórias
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
void preencherVP(ArvVP **raiz){
    InfoArvBin info;
    int i;

    srand(time(NULL));

    for(i = 0; i < 100; i++){
        info.palavraPortugues = (char *)malloc(50 * sizeof(char));
        info.arvBinIngles = (IngPTBST *)malloc(sizeof(IngPTBST));
        info.arvBinIngles->info.unidades = (Unidades *)malloc(sizeof(Unidades));
        info.arvBinIngles->info.unidades->prox = NULL;
        info.arvBinIngles->esq = NULL;
        info.arvBinIngles->dir = NULL;
        info.arvBinIngles->info.palavraIngles = (char *)malloc(50 * sizeof(char));

        int randNum = rand() % 1000;

        sprintf(info.palavraPortugues, "palavra%d", randNum);
        sprintf(info.arvBinIngles->info.palavraIngles, "word%d", randNum);
        info.arvBinIngles->info.unidades->unidade = rand() + 1;

        insere(raiz, info);
    }
}

/**
 * @brief Função que realiza a busca de uma palavra em uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavra: palavra a ser buscada
 * @return int: 1 se a palavra foi encontrada, 0 caso contrário
 */
int buscarVP(ArvVP *raiz, char *palavra){
    int encontrou = 0;
    if (raiz != NULL){
        if (strcmp(raiz->info.palavraPortugues, palavra) == 0)
            encontrou = 1;
        else if (strcmp(raiz->info.palavraPortugues, palavra) > 0)
            encontrou = buscarVP(raiz->esq, palavra); 
        else
            encontrou = buscarVP(raiz->dir, palavra);
    }
    return encontrou;
}

/**
 * @brief Função que metrifica uma unidade em uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param unidade: unidade a ser metrificada
 * @return void
 */
void metrificarbusca(){
    clock_t inicio, fim;
    double tempo, media = 0;
    ArvVP *raizMet = NULL;
    int i;
    char palavra[50];

    preencherVP(&raizMet);

    for(i = 0; i < 30; i++){
        int randNum = rand() % 1000;
        sprintf(palavra, "palavra%d", randNum);
        inicio = clock();
        buscarVP(raizMet, palavra);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC / 30;
        media += tempo;
    }

    printf("Tempo médio de busca: %.9f\n", media);
}

/**
 * @brief Função que exibe uma árvore vermelho e preta em ordem
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
void exibirArvVPEmOrdem(ArvVP *raiz){
    if (raiz != NULL){
        exibirArvVPEmOrdem(raiz->esq);
        if(raiz->cor == 1)
            printf("[P] %s\n", raiz->info.palavraPortugues);
        else
            printf("[V] %s\n", raiz->info.palavraPortugues);
        exibirArvVPEmOrdem(raiz->dir);
    }
}

/**
 * @brief Função que exibe o caminho percorrido em uma busca em uma árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @param palavra: palavra a ser buscada
 * @param nivel: nível da árvore
 * @return void
 */
void buscarVPComCaminho(ArvVP *raiz, const char *palavra, int nivel){
    int i;

    if (raiz == NULL) {
        for (i = 0; i < nivel; i++)
            printf("  ");
        printf("NULL\n");
        return;
    }

    for (i = 0; i < nivel; i++)
        printf("  ");
    if (raiz->cor == 1)
        printf("[P] %s\n", raiz->info.palavraPortugues);
    else
        printf("[V] %s\n", raiz->info.palavraPortugues);

    if (strcmp(raiz->info.palavraPortugues, palavra) == 0) {
        for (i = 0; i < nivel; i++)
            printf("  ");
        printf("ENCONTRADO\n");
        return;
    }

    if (strcmp(palavra, raiz->info.palavraPortugues) < 0) {
        for (i = 0; i < nivel; i++)
            printf("  ");
        printf("ESQ -->\n");
        buscarVPComCaminho(raiz->esq, palavra, nivel + 1);
    } 
    else {
        for (i = 0; i < nivel; i++)
            printf("  ");
        printf("DIR -->\n");
        buscarVPComCaminho(raiz->dir, palavra, nivel + 1);
    }
}


/**
 * @brief Função que exibe o menu principal
 * 
 * @return void
 */
void menuprincipal(){
    printf("                                         \n");
    printf("       M E N U   P R I N C I P A L       \n");
    printf("                                         \n");
    printf(" 1. Menu geral                           \n");
    printf(" 2. Sair do programa                     \n");
    printf("                                         \n");
    printf(" Developers:                             \n");
    printf("      I. Iago Roberto Esmerio Almeida    \n");
    printf("      II. Francinaldo de Sousa Barbosa   \n");
    printf("                                         \n");
    printf(" Professora:                             \n");
    printf("      Juliana Oliveira de Carvalho       \n");
    printf("                                         \n");
    printf("                                         \n");
    printf("                    Aproveite o sistema! \n");
    printf("                                         \n");
    printf("                                         \n");
    printf(" Pressione o numero para                 \n");
    printf(" escolher o menu...                      \n");
    printf("\n");
}

/**
 * @brief Função que exibe o menu geral
 * 
 * @return void
 */
void menugeral(){
    printf("                                          \n");
    printf("            M E N U   G E R A L           \n");
    printf("                                          \n");
    printf(" Item I. Exibir palavras por unidade      \n");
    printf(" Item II. Exibir palavras em português    \n");
    printf(" Item III. Remover palavra em inglês      \n");
    printf(" Item IV. Remover palavra em português    \n");
    printf(" Item V. Metrificar busca                 \n");
    printf(" Item VI. Visualizar VP                   \n");
    printf(" Item VII. Visualizar caminho             \n");
    printf(" 0. Sair do programa                      \n");
    printf("\n");
}

/**
 * @brief Função que exibe as unidades
 * 
 * @param raiz: raiz da árvore
 * @return void
 */
void exibirUnidades(Unidades *raiz){
    if (raiz != NULL){
        printf("%d, ", raiz->unidade);
        exibirUnidades(raiz->prox);
    }
}

/**
 * @brief Função que exibe as palavras em inglês da árvore BST
 * 
 * @param raiz: raiz da árvore BST
 * @return void
 */
void exibirIngles(IngPTBST *raiz){
    if (raiz != NULL){
        exibirIngles(raiz->esq);
        printf("%s, ", raiz->info.palavraIngles);
        exibirUnidades(raiz->info.unidades);
        exibirIngles(raiz->dir);
    }
}

/**
 * @brief Função que exibe as palavras da árvore vermelho e preta
 * 
 * @param raiz: raiz da árvore vermelho e preta
 * @return void
 */
void exibirPalavras(ArvVP *raiz){
    if (raiz != NULL){
        exibirPalavras(raiz->esq);
        printf("%s: ", raiz->info.palavraPortugues);
        exibirIngles(raiz->info.arvBinIngles);
        exibirPalavras(raiz->dir);
    }
}

/**
 * @brief Função que realiza o ltrim, removendo espaços na esquerda da string
 * 
 * @param str: string a ser tratada
 * @return void
 */
void ltrim(char *str) {
    if (str != NULL && str[0] == ' ') {
        memmove(str, str + 1, strlen(str)); 
    }
}

int main() {
    ArvVP *raiz = NULL;
    char linha[200];
    int unidadeAtual = 0, sucesso = 1;

    FILE *arquivo;
    arquivo = fopen("exemploQ2.txt", "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        sucesso = 0;
    }
    if (sucesso = 1) {
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            // Remover a nova linha no final da linha lida
            linha[strcspn(linha, "\n")] = '\0';

            // Verificar se a linha começa com '% Unidade'
            if (strncmp(linha, "% Unidade", 9) == 0) 
                sscanf(linha, "%% Unidade %d", &unidadeAtual);
            else if (linha[0] != '\0' && linha[0] != '%') {
            char palavraIN[50];

                char *token = strtok(linha, ":");
                if (token != NULL) {
                    strcpy(palavraIN, token);
                }
                ltrim(palavraIN);

                token = strtok(NULL, ";");
                if (token != NULL) {
                    char *palavra = strtok(token, ",");
                    while (palavra != NULL) {
                        InfoArvBin info;
                        info.palavraPortugues = (char *)malloc(50 * sizeof(char));
                        info.arvBinIngles = (IngPTBST *)malloc(sizeof(IngPTBST));
                        info.arvBinIngles->info.unidades = (Unidades *)malloc(sizeof(Unidades));
                        info.arvBinIngles->info.unidades->prox = NULL;
                        info.arvBinIngles->esq = NULL;
                        info.arvBinIngles->dir = NULL;
                        info.arvBinIngles->info.palavraIngles = (char *)malloc(50 * sizeof(char));

                        ltrim(palavra);
                        printf("Palavra: %s\n", palavra);
                        strcpy(info.palavraPortugues, palavra); 
                        strcpy(info.arvBinIngles->info.palavraIngles, palavraIN); 
                        info.arvBinIngles->info.unidades->unidade = unidadeAtual;

                        insere(&raiz, info); 
                        palavra = strtok(NULL, ",");
                    }
                }
            }
        }

        fclose(arquivo);
        int enc = 0, op = 0, unidade = 0, i;
        char palavra[50];

        do{
            menuprincipal();
            printf("Digite a opção desejada: ");
            scanf("%d", &op);
            switch(op){
                case 1:
                    do{
                        menugeral();
                        printf("Digite a opção desejada: ");
                        scanf("%d", &op);
                        switch(op){
                            case 1:
                                exibirPalavras(raiz);
                                break;
                            case 2:
                                exibirIngles(raiz->info.arvBinIngles);
                                break;
                            case 3:
                                printf("Digite a palavra em inglês a ser removida: ");
                                scanf("%s", palavra);
                                removerArvVP(&raiz, palavra);
                                break;
                            case 4:
                                printf("Digite a palavra em português a ser removida: ");
                                scanf("%s", palavra);
                                removerArvVP(&raiz, palavra);
                                break;
                            case 5:
                                for(i = 0; i < 100; i++)
                                    metrificarbusca();
                                break;
                            case 6:
                                printf("Visualização da árvore VP\n");
                                exibirArvVPEmOrdem(raiz);
                                break;
                            case 7:
                                printf("Digite a palavra a ser buscada: ");
                                scanf("%s", palavra);
                                buscarVPComCaminho(raiz, palavra, 0);
                                break;
                            case 0:
                                printf("Saindo do menu geral...\n");
                                break;
                            default:
                                printf("Opção inválida! Tente novamente...\n");
                                break;
                        }
                    }while(op != 0);
                    break;

                case 2:
                    printf("Saindo do programa...\n");
                    break;
                default:
                    printf("Opção inválida! Tente novamente...\n");
                    break;
            }
        }while(op != 2);
    }
    
    return 0;
}
