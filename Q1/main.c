#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "./src/Q1.h"

void menugeral(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    printf("                                          \n");
    printf("            M E N U   G E R A L           \n");
    printf("                                          \n");
    printf(" Item I. Exibir palavras por unidade      \n");
    printf(" Item II. Exibir palavras em português    \n");
    printf(" Item III. Remover palavra em inglês      \n");
    printf(" Item IV. Remover palavra em português    \n");
    printf(" Item V. Metrificar busca                 \n");
    printf(" 0. Sair do programa                      \n");
    printf("\n");
}

void menuprincipal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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

int buscar23(Arv23PT *raiz, char *palavra){
    int enc = 0;
    if(raiz != NULL){
        if(strcmp(palavra, raiz->info1.palavra) == 0)
            enc = 1;
        else if(raiz->ninfos == 2 && strcmp(palavra, raiz->info2.palavra) == 0)
            enc = 1;
        else if(strcmp(palavra, raiz->info1.palavra) < 0)
            enc = buscar23(raiz->esq, palavra);
        else if(raiz->ninfos == 2 && strcmp(palavra, raiz->info2.palavra) < 0)
            enc = buscar23(raiz->cen, palavra);
        else
            enc = buscar23(raiz->dir, palavra);
    }
    return enc;
}

void metrificarbusca(){
    clock_t inicio, fim;
    double tempo;
    Arv23PT *raizMet = NULL;
    int i;
    char palavra[50];

    preencher23(&raizMet);

    inicio = clock();
    for(i = 0; i < 30; i++){
        int randNum = rand() % 1000;
        sprintf(palavra, "palavra%d", randNum);
        buscar23(raizMet, palavra);
    }
    fim = clock();

    tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC) * 1000000 / 30;
    printf("Tempo médio de busca: %f\n", tempo);
}

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

void insere(Arv23PT **raiz, Info info){
    Info *promove = (Info*)malloc(sizeof(Info));
    Arv23PT *novaRaiz = inserirArv23(raiz, info, NULL, promove);
    if(novaRaiz != NULL)
        *raiz = novaRaiz;
    free(promove);
    printf("Inserção realizada com sucesso!\n");
}

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
        // Exibir a Árvore 2-3 em ordem
        // exibirArv23EmOrdem(raiz);
        fclose(arquivo);
        int opc = -1, opc2 = -1, unidade = 0;
        char palavra[50];
        #ifdef _WIN32
            system("PAUSE");
        #else
            system("read -p 'Pressione Enter para continuar...' var");
        #endif
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
                                // removerBST(raiz, palavra);
                                break;
                            case 4:
                                printf("Digite a palavra em português: ");
                                scanf("%s", palavra);
                                removerPTporUnidade(&raiz, palavra, unidade);
                                break;
                            case 5:
                                for(int i = 0; i < 30; i++)
                                    metrificarbusca();
                                break;
                            case 0:
                                printf("Saindo do menu geral...\n");
                                exit(0);
                                break;
                            default:
                                printf("Opção inválida\n");
                                break;
                        }
                        #ifdef _WIN32
                            system("PAUSE");
                        #else
                            system("read -p 'Pressione Enter para continuar...' var");
                        #endif
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

// int main1(){
//     Arv23PT *raiz = NULL, *pai = NULL;
//     Info infos[26];
//     int i;
//     char *palavrasPT[] = {
//         "abacaxi", "banana", "cachorro", "dado", "elefante", "foca", "gato", "hipopotamo", "iguana", "jacare",
//         "kiwi", "leao", "macaco", "navio", "ovelha", "pato", "quati", "rato", "sapo", "tigre",
//         "urso", "vaca", "wolverine", "xaxim", "yak", "zebra"
//     };
//     char *palavrasEN[] = {
//         "pineapple", "banana", "dog", "dice", "elephant", "seal", "cat", "hippopotamus", "iguana", "alligator",
//         "kiwi", "lion", "monkey", "ship", "sheep", "duck", "coati", "rat", "frog", "tiger",
//         "bear", "cow", "wolverine", "fern", "yak", "zebra"
//     };

//     for(i = 0; i < 26; i++){
//         Info *promove = (Info*)malloc(sizeof(Info));
//         infos[i].palavra = palavrasPT[i];
//         infos[i].versaoIng = (IngPTBST*)malloc(sizeof(IngPTBST));
//         infos[i].versaoIng->info = (InfoBST*)malloc(sizeof(InfoBST));
//         infos[i].versaoIng->info->palavra = palavrasEN[i];
//         infos[i].versaoIng->info->unidades = NULL;
//         infos[i].versaoIng->esq = NULL;
//         infos[i].versaoIng->dir = NULL;
//         inserirArv23(&raiz, infos[i], pai, promove);
//     }

//     exibirArv23EmOrdem(raiz);

//     printf("\n\n");

//     for(i = 0; i < 26; i++){
//         printf("Removendo %s\n", palavrasPT[i]);
//         Arv23Remover(&raiz, palavrasPT[i]);
//         printf("\n\n");
//         exibirArv23EmOrdem(raiz);
//         printf("\n\n");
//     }

//     desalocarArv23(&raiz);
//     return 0;
// }