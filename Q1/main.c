#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "./src/Q1.h"

/**
 * @brief Função que exibe o menu geral
 * 
 * @param void
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
    printf(" Item VI. Visualizar 2-3                  \n");
    printf(" Item VII. Busca com caminho              \n");
    printf(" Item VIII. Exibir palavra buscada        \n");
    printf(" 0. Sair do programa                      \n");
    printf("\n");
}

/**
 * @brief Função que exibe o menu principal
 * 
 * @param void
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
 * @brief Função que preenche a árvore 2-3 com 100 palavras
 * 
 * @param raiz: raiz da árvore 2-3
 * @return void
 */
void preencher23(Arv23PT **raiz) {
    Info infos[100];
    int i;

    srand(time(NULL));

    for (i = 0; i < 100; i++) {
        Info *promove = (Info *)malloc(sizeof(Info));
        infos[i].palavra = (char *)malloc(50 * sizeof(char));
        infos[i].versaoIng = (IngPTBST *)malloc(sizeof(IngPTBST));
        infos[i].versaoIng->info = (InfoBST *)malloc(sizeof(InfoBST));
        infos[i].versaoIng->info->palavra = (char *)malloc(50 * sizeof(char));
        infos[i].versaoIng->info->unidades = (Unidades *)malloc(sizeof(Unidades));
        infos[i].versaoIng->info->unidades->prox = NULL;
        infos[i].versaoIng->esq = NULL;
        infos[i].versaoIng->dir = NULL;

        int randNum = rand() % 1000;

        sprintf(infos[i].palavra, "palavra%d", randNum);
        sprintf(infos[i].versaoIng->info->palavra, "word%d", randNum);
        infos[i].versaoIng->info->unidades->unidade = randNum + 1;

        inserirArv23(raiz, infos[i], NULL, promove);
    }
}

/**
 * @brief Função que busca uma palavra em uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return int: 1 se a palavra foi encontrada, 0 caso contrário
 */
int buscar23(Arv23PT *raiz, char *palavra){
    int enc = 0;
    if(raiz != NULL){
        enc |= buscar23(raiz->esq, palavra);

        if(strcmp(raiz->info1.palavra, palavra) == 0)
            enc = 1;

        enc |= buscar23(raiz->cen, palavra);

        if(raiz->ninfos == 2){
            if(strcmp(raiz->info2.palavra, palavra) == 0)
                enc = 1;
            enc |= buscar23(raiz->dir, palavra);
        }
    }
    return enc;
}

/**
 * @brief Função que busca a fonte de uma palavra em uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return Arv23PT*: nó da palavra
 */
Arv23PT *fontePalavra(Arv23PT **raiz, const char *palavra){
    Arv23PT *aux = NULL;
    if(raiz != NULL || *raiz != NULL){
        if(strcmp((*raiz)->info1.palavra, palavra) == 0)
            aux = *raiz;
        else if((*raiz)->ninfos == 2 && strcmp((*raiz)->info2.palavra, palavra) == 0)
            aux = *raiz;
        else{
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                aux = fontePalavra(&(*raiz)->esq, palavra);
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0)
                aux = fontePalavra(&(*raiz)->cen, palavra);
            else
                aux = fontePalavra(&(*raiz)->dir, palavra);
        }
    }

    return aux;
}

/**
 * @brief Função que exibe as palavras de uma unidade
 * 
 * @param raiz: raiz da árvore 2-3
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade foi encontrada, 0 caso contrário
 */
void exibirUnidades(Unidades *unidades){
    if(unidades != NULL){
        printf("%d ", unidades->unidade);
        exibirUnidades(unidades->prox);
    }
}

/**
 * @brief Função que exibe as palavras de uma unidade
 * 
 * @param raiz: raiz da árvore 2-3
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade foi encontrada, 0 caso contrário
 */
void printarBST(IngPTBST *raiz){
    if(raiz != NULL){
        printarBST(raiz->esq);
        printf("[ING] %s\n", raiz->info->palavra);
        printf("[UNIDADES]\n");
        exibirUnidades(raiz->info->unidades);
        printarBST(raiz->dir);
    }
}

/**
 * @brief Função que exibe a informação buscada
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return void
 */
void mostrarBusca23ComCaminho(Arv23PT *raiz, const char *palavra){
    Arv23PT *res = NULL;
    if(raiz != NULL){
        res = fontePalavra(&raiz, palavra);
        if(res){
            printf("[PT] %s\n", res->info1.palavra);
            if(strcmp(res->info1.palavra, palavra) == 0)
                printarBST(res->info1.versaoIng);
            else
                printarBST(res->info2.versaoIng);
        }
        else
            printf("Palavra não encontrada!\n");
    }
}

/**
 * @brief Função que busca uma palavra em uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @param nivel: nível da árvore
 * @return void
 */
void buscar23ComCaminho(Arv23PT *raiz, const char *palavra, int nivel) {
    if (raiz == NULL) {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("NULL\n");
        return;
    }

    for (int i = 0; i < nivel; i++)
        printf("  ");
    if (raiz->ninfos == 1)
        printf("[PT] %s\n", raiz->info1.palavra);
    else
        printf("[PT] %s - %s\n", raiz->info1.palavra, raiz->info2.palavra);

    if ((raiz->ninfos >= 1 && strcmp(raiz->info1.palavra, palavra) == 0) ||
        (raiz->ninfos == 2 && strcmp(raiz->info2.palavra, palavra) == 0)) {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("Palavra encontrada: %s\n", palavra);
        return;
    }

    if (strcmp(palavra, raiz->info1.palavra) < 0) {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("[ESQ] -->\n");
        buscar23ComCaminho(raiz->esq, palavra, nivel + 1);
    } 
    else if (raiz->ninfos == 2 && strcmp(palavra, raiz->info2.palavra) > 0) {
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("[DIR] -->\n");
        buscar23ComCaminho(raiz->dir, palavra, nivel + 1);
    } 
    else{
        for (int i = 0; i < nivel; i++)
            printf("  ");
        printf("[CEN] -->\n");
        buscar23ComCaminho(raiz->cen, palavra, nivel + 1);
    }
}

/**
 * @brief Função que exibe as palavras de uma unidade
 * 
 * @param raiz: raiz da árvore 2-3
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade foi encontrada, 0 caso contrário
 */
void metrificarbusca(){
    clock_t inicio, fim;
    double tempo;
    Arv23PT *raizMet = NULL;
    int i;
    char palavra[50];
    double media = 0;

    preencher23(&raizMet);

    for(i = 0; i < 30; i++){
        int randNum = rand() % 1000;
        sprintf(palavra, "palavra%d", randNum);
        inicio = clock();
        buscar23(raizMet, palavra);
        fim = clock();
        tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) / 30;
        media += tempo;
    }

    printf("Tempo médio de busca: %.9f\n", media);
}

/**
 * @brief Função que exiber a árvore 2-3 em ordem
 * 
 * @param raiz: raiz da árvore 2-3
 * @return void
 */
void exibirArv23EmOrdem(Arv23PT *raiz){
    if(raiz != NULL){
        exibirArv23EmOrdem(raiz->esq);
        printf("%s -> ", raiz->info1.palavra);
        exibirArv23EmOrdem(raiz->cen);
        if(raiz->ninfos == 2){
            printf("%s -> ", raiz->info2.palavra);
            exibirArv23EmOrdem(raiz->dir);
        }
    }
}

/**
 * @brief Função que insere uma palavra em uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param info: informação a ser inserida
 * @return void
 */
void insere(Arv23PT **raiz, Info info){
    Info *promove = (Info*)malloc(sizeof(Info));
    Arv23PT *novaRaiz = inserirArv23(raiz, info, NULL, promove);
    if(novaRaiz != NULL)
        *raiz = novaRaiz;
    free(promove);
    printf("Inserção realizada com sucesso!\n");
}

/**
 * @brief Função que realiza o ltrim em uma string, que consiste em
 * remover espaços em branco do início de uma string
 * 
 * @param str: string a ser modificada
 * @return void
 */
void ltrim(char *str){
    if(str != NULL && str[0] == ' ')
        memmove(str, str + 1, strlen(str)); 
}

int main(){
    Arv23PT *raiz = NULL;
    char linha[200];
    int unidadeAtual = 0, sucesso = 1;
    printf("Lendo arquivo...\n");
    FILE *arquivo;
    arquivo = fopen("./exemploQ1.txt", "r");

    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo\n");
        sucesso = 0;
    }
    if(sucesso){
        while(fgets(linha, sizeof(linha), arquivo) != NULL){
            linha[strcspn(linha, "\n")] = '\0';

            if(strncmp(linha, "% Unidade", 9) == 0)
                sscanf(linha, "%% Unidade %d", &unidadeAtual);
            else if (linha[0] != '\0' && linha[0] != '%'){
                char palavaraING[50];

                char *token = strtok(linha, ":");
                if(token != NULL)
                    strcpy(palavaraING, token);
                ltrim(palavaraING);

                token = strtok(NULL, ";");
                if(token != NULL){
                    char *palavra = strtok(token, ",");
                    while(palavra != NULL){
                        Info info;
                        info.palavra = (char*)malloc(50 * sizeof(char));
                        info.versaoIng = (IngPTBST*)malloc(sizeof(IngPTBST));
                        info.versaoIng->info = (InfoBST*)malloc(sizeof(InfoBST));
                        info.versaoIng->info->unidades = (Unidades*)malloc(sizeof(Unidades));
                        info.versaoIng->info->unidades->prox = NULL;
                        info.versaoIng->esq = NULL;
                        info.versaoIng->dir = NULL;
                        info.versaoIng->info->palavra = (char*)malloc(50 * sizeof(char));

                        ltrim(palavra);
                        printf("Palavra: %s\n", palavra);
                        strcpy(info.palavra, palavra);
                        strcpy(info.versaoIng->info->palavra, palavaraING);
                        info.versaoIng->info->unidades->unidade = unidadeAtual;

                        insere(&raiz, info);
                        palavra = strtok(NULL, ",");
                    }
                }
            }
        }

        printf("Deseja exibir a árvore 2-3 em ordem? (s/n): ");
        char esc;
        scanf(" %c", &esc);
        if(esc == 's')
            exibirArv23EmOrdem(raiz);
        printf("\n");
        #ifdef _WIN32
            system("PAUSE");
        #else
            system("read -p 'Pressione Enter para continuar...' var");
        #endif
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        fclose(arquivo);
        int opc = -1, opc2 = -1, unidade = 0, enc = 0;
        char palavra[50];
        while(opc != 2){
            menuprincipal();
            printf("Digite a opção desejada: ");
            scanf("%d", &opc);
            switch(opc){
                case 1:
                    do{
                        menugeral();
                        printf("Digite a opção desejada: ");
                        scanf("%d", &opc);
                        switch(opc){
                            case 1:
                                printf("Digite a unidade: ");
                                scanf("%d", &unidade);
                                ExibirPalavrasUnidade(raiz, unidade);
                                break;
                            case 2:
                                printf("Digite a palavra em português: ");
                                scanf("%s", palavra);
                                ExibirPalavrasEN(raiz, palavra);
                                break;
                            case 3:
                                printf("Digite a palavra em inglês: ");
                                scanf("%s", palavra);
                                printf("Digite a unidade: ");
                                scanf("%d", &unidade);
                                enc = removerMain(&raiz, palavra, unidade, raiz);
                                enc ? printf("Palavra removida com sucesso!\n") : printf("Palavra não encontrada!\n");
                                break;
                            case 4:
                                printf("Digite a palavra em português: ");
                                scanf("%s", palavra);
                                printf("Digite a unidade: ");
                                scanf("%d", &unidade);
                                enc = removerPTporUnidade(&raiz, palavra, unidade, raiz);
                                enc ? printf("Palavra removida com sucesso!\n") : printf("Palavra não encontrada!\n");
                                break;
                            case 5:
                                for(int i = 0; i < 30; i++)
                                    metrificarbusca();
                                break;
                            case 6:
                                printf("\n\n");
                                exibirArv23EmOrdem(raiz);
                                break;
                            case 7:
                                printf("Digite a palavra em PT: ");
                                scanf("%s", palavra);
                                buscar23ComCaminho(raiz, palavra, 0);
                                break;
                            case 8:
                                printf("Digite a palavra em PT: ");
                                scanf("%s", palavra);
                                mostrarBusca23ComCaminho(raiz, palavra);
                                break;
                            case 0:
                                printf("Saindo do menu geral...\n");
                                exit(0);
                                break;
                            default:
                                printf("Opção inválida\n");
                                break;
                        }
                    }while(opc2 != 0);
                    break;
                case 2:
                    printf("Saindo do programa...\n");
                    exit(0);
                    break;
                default:
                    printf("Opção inválida\n");
                    break;
            }
        }
    }
    return 0;
}