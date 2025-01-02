/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Q1.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

/**
 * @brief Função que transforma uma string em maiúscula
 * 
 * @param string: string a ser transformada
 * @return void
 */
void toupperString(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

/**
 * @brief Função que cria um nó de uma árvore 2-3
 * 
 * @param informacao informação a ser inserida no nó
 * @param filhoesq: filho esquerdo do nó
 * @param filhocen: filho central do nó
 * @return Arv23PT*: nó criado
 */
Arv23PT *criaNo(Info informacao, Arv23PT *filhoesq, Arv23PT *filhocen){
    Arv23PT *no = (Arv23PT*)malloc(sizeof(Arv23PT));

    if(!no){
        printf("Nao foi possivel criar no\n");
        exit(EXIT_FAILURE);
    }

    no->info1 = informacao;
    no->esq = filhoesq;
    no->cen = filhocen;
    no->dir = NULL;
    no->ninfos = 1;

    return no;
}

/**
 * @brief Função que adiciona uma chave a um nó
 * 
 * @param no: nó a ser adicionado a chave
 * @param informacao: informação a ser adicionada
 * @param filho: filho a ser adicionado ao nó
 * @return void
 */
void adicionaChave(Arv23PT *no, Info informacao, Arv23PT *filho){
    if(strcmp(informacao.palavra, no->info1.palavra) > 0){
        no->info2 = informacao;
        no->dir = filho;
    }
    else{
        no->info2 = no->info1;
        no->dir = no->cen;
        no->cen = filho;
        no->info1 = informacao;
    }
    no->ninfos = 2;
}

/**
 * @brief Função que quebra um nó, caso ele tenha 2 informações e seja necessário adicionar uma terceira
 * ela é quebrada em dois nós e a informação promovida é retornada para ser inserida no nó pai
 * 
 * @param no: nó a ser quebrado
 * @param informacao: informação a ser inserida
 * @param promove: informação a ser promovida
 * @param filho: filho a ser inserido
 * @return Arv23PT*: nó criado
 */
Arv23PT *quebraNo(Arv23PT *no, Info informacao, Info *promove, Arv23PT *filho){
    Arv23PT *maior;

    if(strcmp(informacao.palavra, no->info2.palavra) > 0){
        *promove = no->info2;
        maior = criaNo(informacao, no->dir, filho);
    }
    else if(strcmp(informacao.palavra, no->info1.palavra) > 0){
        *promove = informacao;
        maior = criaNo(no->info2, filho, no->dir);
    }
    else{
        *promove = no->info1;
        maior = criaNo(no->info2, no->cen, no->dir);
        no->info1 = informacao;
        no->cen = filho;
    }
    no->ninfos = 1;

    return maior;
}

/**
 * @brief Função que verifica se um nó é folha
 * 
 * @param no: nó a ser verificado
 * @return int: 1 se for folha, 0 caso contrário
 */
int ehFolha(Arv23PT no){
    return no.esq == NULL;
}

/**
 * @brief Função que insere uma informação em uma árvore 2-3
 * 
 * @param no: nó que será inserido a informação
 * @param informacao: informação a ser inserida
 * @param pai: nó pai, que será utilizado para inserir a informação promovida
 * @param promove: informação a ser promovida, sendo a que for a informação intermediária na quebra de um nó
 * @return Arv23PT*: o maior nó
 */
Arv23PT *inserirArv23(Arv23PT **no, Info informacao, Arv23PT *pai, Info *promove){
    Arv23PT *maiorNo;
    maiorNo = NULL;

    if(*no == NULL)
        *no = criaNo(informacao, NULL, NULL);
    else{
        if(ehFolha(**no)){
            if((*no)->ninfos == 1)
                adicionaChave(*no, informacao, NULL);
            else{
                maiorNo = quebraNo(*no, informacao, promove, NULL);
                if(pai == NULL){
                    *no = criaNo(*promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else{
            if(strcmp(informacao.palavra, (*no)->info1.palavra) < 0)
                maiorNo = inserirArv23(&((*no)->esq), informacao, *no, promove);
            else if((*no)->ninfos == 1 || (strcmp(informacao.palavra, (*no)->info2.palavra) < 0))
                maiorNo = inserirArv23(&((*no)->cen), informacao, *no, promove);
            else
                maiorNo = inserirArv23(&((*no)->dir), informacao, *no, promove);

            if(maiorNo != NULL){
                if((*no)->ninfos == 1){
                    adicionaChave(*no, *promove, maiorNo);
                    maiorNo = NULL;
                }
                else{
                    Info promove_aux;
                    maiorNo = quebraNo(*no, *promove, &promove_aux, maiorNo);
                    *promove = promove_aux;
                    if(pai == NULL){
                        *no = criaNo(promove_aux, *no, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}

/**
 * @brief Função que libera a memória de uma árvore 2-3
 * 
 * @param no: nó a ser liberado
 * @return void
 */
void freeTree(Arv23PT *no){
    if(no != NULL){
        freeTree(no->esq);
        freeTree(no->cen);
        freeTree(no->dir);
        free(no);
    }
}

/**
 * @brief Função que insere uma unidade em uma lista de unidades
 * 
 * @param unidades: lista encadeada de unidades
 * @param unidade: unidade a ser inserida
 * @return void
 */
void inserirunidade(Unidades **unidades, int unidade){
    if (*unidades == NULL){
        *unidades = (Unidades*)malloc(sizeof(Unidades));
        (*unidades)->unidade = unidade;
        (*unidades)->prox = NULL;
    } 
    else
        inserirunidade(&(*unidades)->prox, unidade);
}

/**
 * @brief Função que insere uma informação em uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária
 * @param info: informação a ser inserida
 * @return int: 1 se a inserção foi bem sucedida, 0 caso contrário
 */
int insereArvBin(IngPTBST **raiz, InfoBST *info) {
    int sucesso = 0;
    if((*raiz) == NULL){
        IngPTBST *novo = (IngPTBST *)malloc(sizeof(IngPTBST));
        novo->info = (InfoBST *)malloc(sizeof(InfoBST));
        novo->info->palavra = (char *)malloc(strlen(info->palavra) + 1);
        strcpy(novo->info->palavra, info->palavra);
        toupperString(novo->info->palavra);
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        sucesso = 1;
    } 
    else{
        if(strcmp((*raiz)->info->palavra, info->palavra) == 0)
            inserirunidade(&(*raiz)->info->unidades, info->unidades->unidade);
        if(strcmp(info->palavra, (*raiz)->info->palavra) < 0)
            sucesso = insereArvBin(&(*raiz)->esq, info);
        else
            sucesso = insereArvBin(&(*raiz)->dir, info);
    }
    return sucesso;
}

/*-----------------------------------------------------------------------------------------------------*/

/* (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
equivalentes em inglês */

/**
 * @brief Função que verifica se uma unidade está presente em uma lista de unidades
 * 
 * @param unidades: lista encadeada de unidades
 * @param unidade: unidade a ser verificada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int unidadePresente(Unidades *unidades, int unidade){
    int presente = 0;
    if(unidades != NULL){
        if(unidades->unidade == unidade)
            presente = 1;
        else
            presente = unidadePresente(unidades->prox, unidade);
    }
    return presente;
}

/**
 * @brief Função que busca uma unidade em uma árvore binária de busca
 * 
 * @param raiz: raiz da árvore binária
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int buscarUnidade(IngPTBST *raiz, int unidade){
    int enc = 0;
    if(raiz != NULL){
        int presente = unidadePresente(raiz->info->unidades, unidade);
        if(presente)
            enc = 1;
        else{
            int enc_esq = buscarUnidade(raiz->esq, unidade);
            int enc_dir = buscarUnidade(raiz->dir, unidade);
            enc = enc_esq || enc_dir;
        }
    }
    return enc;
}

/**
 * @brief Função que exibe a palavra em inglês
 * 
 * @param raiz: raiz da árvore 2-3
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
void exibirEN(const IngPTBST *raiz) {
    if(raiz != NULL){
        exibirEN(raiz->esq);
        printf("[ING] %s", raiz->info->palavra);
        exibirEN(raiz->dir);
    }
}

/**
 * @brief Função que exibe as palavras em português e inglês de uma unidade
 * 
 * @param raiz: raiz da árvore 2-3
 * @param unidade: unidade a ser buscada
 * @return int: 1 se a unidade está presente, 0 caso contrário
 */
int ExibirPalavrasUnidade(Arv23PT *raiz, int unidade){
    if(raiz != NULL){
        ExibirPalavrasUnidade(raiz->esq, unidade);
        int enc = buscarUnidade(raiz->info1.versaoIng, unidade);
        if(enc){
            printf("[PT] %s\n", raiz->info1.palavra);
            exibirEN(raiz->info1.versaoIng);
            printf("\n\n");
        }
        ExibirPalavrasUnidade(raiz->cen, unidade);
        if(raiz->ninfos == 2){
            int enc = buscarUnidade(raiz->info2.versaoIng, unidade);
            if(enc){
                printf("[PT] %s\n", raiz->info2.palavra);
                exibirEN(raiz->info2.versaoIng);
                printf("\n\n");
            }
            ExibirPalavrasUnidade(raiz->dir, unidade);
        }
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (ii) informar uma palavra em português e então imprima todas as palavras em inglês equivalente à palavra em
português dada, independente da unidade */

/**
 * @brief Função que exibe as palavras em inglês referente a uma palavra em português dada
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavraPTBR: palavra em português
 * @return void
 */
void ExibirPalavrasEN(Arv23PT *raiz, char *palavraPTBR){
    if(raiz != NULL){
        ExibirPalavrasEN(raiz->esq, palavraPTBR);
        if(strcmp(palavraPTBR, raiz->info1.palavra) == 0){
            printf("Palavras em ingles referente a (%s)\n", palavraPTBR);
            exibirEN(raiz->info1.versaoIng);
        }

        ExibirPalavrasEN(raiz->cen, palavraPTBR);

        if(raiz->ninfos == 2){
            if (strcmp(palavraPTBR, raiz->info2.palavra) == 0){
                printf("Palavras em ingles referente a (%s)\n", palavraPTBR);
                exibirEN(raiz->info2.versaoIng);
            }
            ExibirPalavrasEN(raiz->dir, palavraPTBR);
        }
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iii) informar uma palavra em inglês e a unidade a qual a mesma pertence removê-la das árvores binárias
das quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da
árvore 2-3 */

/**
 * @brief Função que realiza o movimento de informações dentro da árvore 2-3
 * 
 * @param saindo: informação a ser deslocada para outro nó
 * @param entrada: informação a ser inserida no nó, vinda de outro nó
 * @param pai: nó pai
 * @param origem: nó de origem
 * @param raiz: raiz da árvore 2-3
 * @param maior: maior nó
 * @param funcao_remover: função de remoção, do tipo 1 ou 2
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrárioZ
 */
int onda(Info saindo, Info *entrada, Arv23PT *pai, Arv23PT **origem, Arv23PT **raiz, Arv23PT **maior, int (*funcao_remover)(Arv23PT **, char *, Arv23PT *, Arv23PT **, Arv23PT **)){
    int removeu = funcao_remover(raiz, saindo.palavra, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

/**
 * @brief Função que calcula a altura de um nó
 * 
 * @param no: nó a ser calculado a altura
 * @return int: altura do nó
 */
int calcAltura(Arv23PT *no){
    int alt = -1;
    if(no != NULL)
        alt = 1 + calcAltura(no->esq);
    return alt;
}

/**
 * @brief Função que verifica se um nó é removível
 * 
 * @param raiz: raiz da árvore 2-3
 * @return int: 1 se o nó é removível, 0 caso contrário
 */
int removivel(Arv23PT *raiz) {
    int pode = 0;

    if(raiz != NULL) {
        pode = raiz->ninfos == 2;
        if(!pode) {
            pode = removivel(raiz->cen);
            if(!pode)
                pode = removivel(raiz->esq);
        }
    }
    return pode;
}

/**
 * @brief Função que busca o menor filho de um nó, ou seja, o filho mais à esquerda
 * 
 * @param raiz: raiz da árvore 2-3
 * @param pai: nó pai
 * @return Arv23PT*: menor filho
 */
Arv23PT *buscarMenorFilho(Arv23PT *raiz, Arv23PT **pai){
    Arv23PT *filho;
    filho = raiz;

    while(!ehFolha(*filho)){
        *pai = filho;
        filho = filho->esq;
    }
    return filho;
}

/**
 * @brief Função que verifica um nó, quantas informações ele possui
 * 
 * @param raiz da árvore 2-3
 * @return Info: maior informação
 */
Info maiorFilho(Arv23PT *raiz){
    return raiz->ninfos == 2 ? raiz->info2 : raiz->info1;
}

/**
 * @brief Função que busca o maior filho de um nó, ou seja, o filho mais à direita da info
 * 
 * @param raiz: raiz da árvore 2-3
 * @param pai: nó pai
 * @param maiorValor: maior valor
 * @return Arv23PT*: maior filho
 */
Arv23PT *buscarMaiorFilho(Arv23PT *raiz, Arv23PT **pai, Info *maiorValor){
    Arv23PT *filho;
    filho = raiz;

    while(!ehFolha(*filho)){
        *pai = filho;
        if(filho->ninfos == 1)
            filho = filho->cen;
        else
            filho = filho->dir;
    }

    if(filho != NULL)
        *maiorValor = maiorFilho(filho);

    return filho;
}

/**
 * @brief Função que desaloca um nó
 * 
 * @param no: nó a ser desalocado
 * @return void
 */
void desalocaNo(Arv23PT **no) {
    free(*no);
    *no = NULL;
}

/**
 * @brief Função que adiciona uma informação a um nó
 * 
 * @param no: nó a ser adicionado a informação
 * @param info: informação a ser adicionada
 * @param filhomaior: filho maior
 * @return void
 */
void adicionarInfo(Arv23PT *no, Info info, Arv23PT *filhomaior){
    if(strcmp(info.palavra, no->info1.palavra) > 0){
        no->info2 = info;
        no->dir = filhomaior;
    }
    else{
        no->info2 = no->info1;
        no->dir = no->cen;
        no->cen = filhomaior;
        no->info1 = info;
    }
    no->ninfos = 2;
}

/**
 * @brief Função que junta um nó com outro
 * 
 * @param filho1: filho 1
 * @param info: informação
 * @param maior: maior nó
 * @param raiz: raiz da árvore 2-3 que será desalocada
 */
Arv23PT *juntaNo(Arv23PT *filho1, Info info, Arv23PT *maior, Arv23PT **raiz){
    adicionarInfo(filho1, info, maior);

    (*raiz)->ninfos--;

    if((*raiz)->ninfos == 0)
        desalocaNo(raiz);

    return filho1;
}

/**
 * @brief Função que verifica se uma informação é a primeira informação de um nó
 * 
 * @param no: nó a ser verificado
 * @param palavra: palavra a ser verificada
 * @return int: 1 se a informação é a primeira, 0 caso contrário
 */
int ehInfo1(Arv23PT no, char *palavra){
    return strcmp(palavra, no.info1.palavra) == 0;
}

/**
 * @brief Função que verifica se uma informação é a segunda informação de um nó
 * 
 * @param no: nó a ser verificado
 * @param palavra: palavra a ser verificada
 * @return int: 1 se a informação é a segunda, 0 caso contrário
 */
int ehInfo2(Arv23PT no, char *palavra){
    return no.ninfos == 2 && (strcmp(palavra, no.info2.palavra) == 0);
}

/**
 * @brief Função que busca o pai de um nó
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return Arv23PT*: pai do nó
 */
Arv23PT *buscapai(Arv23PT *raiz, char *palavra) {
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL) {
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscapai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || (strcmp(palavra, raiz->info2.palavra) < 0))
                pai = buscapai(raiz->cen, palavra);
            else
                pai = buscapai(raiz->dir, palavra);

            if(pai == NULL)
                pai = raiz;
        }
    }
    return pai;
}

/**
 * @brief Função que busca o maior pai de um nó
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return Arv23PT*: maior pai do nó
 */
Arv23PT *buscarMaiorPai(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMaiorPai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || (strcmp(palavra, raiz->info2.palavra) < 0))
                pai = buscarMaiorPai(raiz->cen, palavra);
            else
                pai = buscarMaiorPai(raiz->dir, palavra);

            if(pai == NULL && ((raiz->ninfos == 1 && (strcmp(raiz->info1.palavra, palavra) > 0)) || (raiz->ninfos == 2 && (strcmp(raiz->info2.palavra, palavra) > 0))))
                pai = raiz;
        }
    }

    return pai;
}

/**
 * @brief Função que busca o menor pai de um nó
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return Arv23PT*: menor pai do nó
 */
Arv23PT *buscarMenorPai(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMenorPai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || (strcmp(palavra, raiz->info2.palavra) < 0))
                pai = buscarMenorPai(raiz->cen, palavra);
            else
                pai = buscarMenorPai(raiz->dir, palavra);

            if(pai == NULL && (strcmp(raiz->info1.palavra, palavra) < 0))
                pai = raiz;
        }
    }
    return pai;
}

/**
 * @brief Função que busca o menor pai de um nó com duas informações
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser buscada
 * @return Arv23PT*: menor pai do nó
 */
Arv23PT *buscarMenorPai2Infos(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMenorPai2Infos(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || (strcmp(palavra, raiz->info2.palavra) < 0))
                pai = buscarMenorPai2Infos(raiz->cen, palavra);
            else
                pai = buscarMenorPai2Infos(raiz->dir, palavra);

            if(pai == NULL && raiz->ninfos == 2 && (strcmp(raiz->info2.palavra, palavra) < 0))
                pai = raiz;
        }
    }
    return pai;
}

/**
 * @brief Função que desaloca uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @return void
 */
void desalocarArv23(Arv23PT **raiz){
    if(*raiz != NULL){
        desalocarArv23(&((*raiz)->esq));
        desalocarArv23(&((*raiz)->dir));

        if((*raiz)->ninfos == 2)
            desalocarArv23(&((*raiz)->dir));

        desalocaNo(raiz);
    }
}

/**
 * @brief Função que remove de um nó que não é folha
 * 
 * @param origem: nó de origem
 * @param raiz: raiz da árvore 2-3
 * @param info: informação a ser removida
 * @param filho1: filho 1
 * @param filho2: filho 2
 * @param maior: maior nó
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int removerNaoFolha1(Arv23PT **origem, Arv23PT *raiz, Info *info, Arv23PT *filho1, Arv23PT *filho2, Arv23PT **maior){
    int removeu;
    Arv23PT *filho, *pai;
    Info info_filho;
    pai = raiz;

    filho = buscarMaiorFilho(filho1, &pai, &info_filho);

    if(filho->ninfos == 2){
        *info = info_filho;
        filho->ninfos = 1;
        removeu = 1;
    }
    else{
        filho = buscarMenorFilho(filho2, &pai);
        removeu = onda(filho->info1, info, pai, origem, &filho, maior, Remover1Arv23);
    }

    return removeu;
}

/**
 * @brief Função que remove de um nó que não é folha
 * 
 * @param origem: nó de origem
 * @param raiz: raiz da árvore 2-3
 * @param info: informação a ser removida
 * @param filho1: filho 1
 * @param filho2: filho 2
 * @param maior: maior nó
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int removerNaoFolha2(Arv23PT **origem, Arv23PT *raiz, Info *info, Arv23PT *filho1, Arv23PT *filho2, Arv23PT **maior){
    int removeu;
    Arv23PT *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = buscarMenorFilho(filho1, &pai);

    if(filho->ninfos == 2){
        *info = filho->info1;
        filho->info1 = filho->info2;
        filho->ninfos = 1;
        removeu = 1;
    }
    else{
        filho = buscarMaiorFilho(filho2, &pai, &info_filho);
        removeu = onda(info_filho, info, pai, origem, &filho, maior, Remover2Arv23);
    }

    return removeu;
}

/**
 * @brief Função do tipo 1 que remove uma informação de uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser removida
 * @param pai: nó pai
 * @param origem: nó de origem
 * @param maior: maior nó
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int Remover1Arv23(Arv23PT **raiz, char *palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior){
    int removeu = 0;

    if(*raiz != NULL){
        int info1 = ehInfo1(**raiz, palavra);
        int info2 = ehInfo2(**raiz, palavra);

        if(info1 || info2){
            removeu = 1;
            if(ehFolha(**raiz)){
                if((*raiz)->ninfos == 2){
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->ninfos = 1;
                }
                else{
                    if(pai == NULL)
                        desalocaNo(raiz);
                    else{
                        Arv23PT *paiaux;
                        Info info_pai;
                        if(*raiz == pai->esq || (pai->ninfos == 2 && *raiz == pai->cen)){
                            paiaux = buscapai(*origem, pai->info1.palavra);
                            
                            if(*raiz == pai->esq)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = onda(info_pai, &((*raiz)->info1), paiaux, origem, &pai, maior, Remover1Arv23);                            
                        }
                        else{
                            paiaux = buscarMaiorPai(*origem, (*raiz)->info1.palavra);

                            Arv23PT *menorpai;
                            menorpai = buscarMenorPai2Infos(*origem, (*raiz)->info1.palavra);

                            if(paiaux != NULL){
                                if(strcmp(paiaux->info1.palavra, (*raiz)->info1.palavra) > 0)
                                    info_pai = paiaux->info1;
                                else
                                    info_pai = paiaux->info2;
                            }

                            int alturaMenorPai = calcAltura(menorpai);
                            int alturaPaiAux = calcAltura(paiaux);

                            if(paiaux == NULL || (paiaux != pai && menorpai != NULL && alturaMenorPai <= alturaPaiAux && (strcmp(info_pai.palavra, menorpai->info2.palavra) > 0))){
                                *maior = pai;
                                (*raiz)->ninfos = 0;
                                removeu = -1;
                            }
                            else{
                                Arv23PT *avo;
                                avo = buscapai(*origem, info_pai.palavra);
                                removeu = onda(info_pai, &((*raiz)->info1), avo, origem, &paiaux, maior, Remover1Arv23);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = removerNaoFolha1(origem, *raiz, &((*raiz)->info2), (*raiz)->cen, (*raiz)->dir, maior);
            else if(info1)
                removeu = removerNaoFolha1(origem, *raiz, &((*raiz)->info1), (*raiz)->esq, (*raiz)->cen, maior);
        }
        else{
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                removeu = Remover1Arv23(&(*raiz)->esq, palavra, *raiz, origem, maior);
            else if((*raiz)->ninfos == 1 || (strcmp(palavra, (*raiz)->info2.palavra) < 0))
                removeu = Remover1Arv23(&(*raiz)->cen, palavra, *raiz, origem, maior);
            else
                removeu = Remover1Arv23(&(*raiz)->dir, palavra, *raiz, origem, maior);
        }
    }
    return removeu;
}

/**
 * @brief Função do tipo 2 que remove uma informação de uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser removida
 * @param pai: nó pai
 * @param origem: nó de origem
 * @param maior: maior nó
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int Remover2Arv23(Arv23PT **raiz, char *palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior){
    int removeu = 0;

    if(*raiz != NULL){
        int info1 = ehInfo1(**raiz, palavra);
        int info2 = ehInfo2(**raiz, palavra);

        if(info1 || info2){
            removeu = 1;
            if(ehFolha(**raiz)){
                if((*raiz)->ninfos == 2){
                    if(info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->ninfos = 1;
                }
                else{
                    if(pai == NULL)
                        desalocaNo(raiz);
                    else{
                        Arv23PT *paiaux;
                        Info info_pai;
                        if(*raiz == pai->cen || (pai->ninfos == 2 && *raiz == pai->dir)){
                            paiaux = buscapai(*origem, pai->info1.palavra);

                            if(*raiz == pai->cen)
                                info_pai = pai->info1;
                            else
                                info_pai = pai->info2;

                            removeu = onda(info_pai, &((*raiz)->info1), paiaux, origem, &pai, maior, Remover2Arv23);
                        }
                        else{
                            paiaux = buscarMenorPai(*origem, (*raiz)->info1.palavra);

                            Arv23PT *menorpai;
                            menorpai = buscarMenorPai2Infos(*origem, (*raiz)->info1.palavra);

                            Arv23PT *avo;

                            if(paiaux == NULL || (paiaux != pai && menorpai != NULL)){
                                removeu = -1;
                                *maior = pai;
                            }
                            else{
                                if(paiaux->ninfos == 2 && (strcmp(paiaux->info2.palavra, (*raiz)->info1.palavra) < 0))
                                    info_pai = paiaux->info2;
                                else
                                    info_pai = paiaux->info1;

                                avo = buscapai(*origem, info_pai.palavra);
                                removeu = onda(info_pai, &((*raiz)->info1), avo, origem, &paiaux, maior, Remover2Arv23);
                            }
                        }
                    }
                }
            }
            else if(info2)
                removeu = removerNaoFolha2(origem, *raiz, &((*raiz)->info2), (*raiz)->dir, (*raiz)->cen, maior);
            else if(info1)
                removeu = removerNaoFolha2(origem, *raiz, &((*raiz)->info1), (*raiz)->cen, (*raiz)->esq, maior);
        }
        else{
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                removeu = Remover2Arv23(&(*raiz)->esq, palavra, *raiz, origem, maior);
            else if((*raiz)->ninfos == 1 || (strcmp(palavra, (*raiz)->info2.palavra) < 0))
                removeu = Remover2Arv23(&(*raiz)->cen, palavra, *raiz, origem, maior);
            else
                removeu = Remover2Arv23(&(*raiz)->dir, palavra, *raiz, origem, maior);
        }
    }
    return removeu;
}

/**
 * @brief Função que realiza o balanceamento de um nó
 * 
 * @param raiz: raiz da árvore 2-3
 * @param filho1: filho 1
 * @param filho2: filho 2
 * @param info: informação
 * @param maior: maior nó
 * @return int: 1 se o balanceamento foi bem sucedido, 0 caso contrário
 */
int balanceamento(Arv23PT **raiz, Arv23PT *filho1, Arv23PT **filho2, Info info, Arv23PT **maior){
    int balanceou = 0;
    if(*filho2 == NULL || (*filho2)->ninfos == 0){
        if(*filho2 != NULL)
            desalocaNo(filho2);

        *maior = juntaNo(filho1, info, *maior, raiz);
        balanceou = 1;
    }
    return balanceou;
}

/**
 * @brief Função que realiza o rebalanceamento de uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser rebalanceada
 * @param maior: maior nó
 * @return int: 1 se o rebalanceamento foi bem sucedido, 0 caso contrário
 */
int Arv23Rebalancear(Arv23PT **raiz, char *palavra, Arv23PT **maior){
    int balanceou = 0;
    if(*raiz != NULL){
        if(!ehFolha(**raiz)){
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                balanceou = Arv23Rebalancear(&((*raiz)->esq), palavra, maior);
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0){
                if((*raiz)->esq->ninfos == 2 && !removivel((*raiz)->cen))
                    balanceou = -1;
                else
                    balanceou = Arv23Rebalancear(&(*raiz)->cen, palavra, maior);
            }
            else{
                if((*raiz)->cen->ninfos == 2 && !removivel((*raiz)->dir))
                    balanceou = -1;
                else    
                    balanceou = Arv23Rebalancear(&((*raiz)->dir), palavra, maior);
            }

            if(balanceou != -1){
                if((*raiz)->ninfos == 1)
                    balanceou = balanceamento(raiz, (*raiz)->esq, &((*raiz)->cen), (*raiz)->info1, maior);
                else if((*raiz)->ninfos == 2)
                    balanceou = balanceamento(raiz, (*raiz)->cen, &((*raiz)->dir), (*raiz)->info2, maior);
            }
        }
    }
    return balanceou;
}

/**
 * @brief Função principal que reune todas as funções para remover uma palavra de uma árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavra: palavra a ser removida
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int Arv23Remover(Arv23PT **raiz, char *palavra){
    Arv23PT *maior, *posicao;
    int removeu = Remover1Arv23(raiz, palavra, NULL, raiz, &posicao);

    if(removeu == -1){
        removeu = 1;
        Info valor = maiorFilho(posicao);
        maior = NULL;
        removeu = Arv23Rebalancear(raiz, valor.palavra, &maior);

        if(removeu == -1){
            Arv23PT *pai, *posicao2;
            Info *entrada;
            pai = buscapai(*raiz, valor.palavra);

            if(ehInfo1(*posicao, valor.palavra))
                entrada = &(posicao->cen->info1);
            else
                entrada = &(posicao->dir->info1);

            removeu = onda(valor, entrada, pai, raiz, &posicao, &posicao2, Remover2Arv23);
            
            if(removeu == -1){
                valor = posicao2->info1;
                pai = buscapai(*raiz, valor.palavra);
                removeu = onda(valor, &(posicao2->esq->info1), pai, raiz, &posicao2, &posicao, Remover1Arv23);

                valor = maiorFilho(posicao);
                maior = NULL;
                removeu = Arv23Rebalancear(raiz, valor.palavra, &maior);
            }
        }
        if(*raiz == NULL)
            *raiz = maior;
    } 
    return removeu;
}

/**
 * @brief Função que remove uma unidade de uma lista encadeada de unidades
 * 
 * @param unidades: lista encadeada de unidades
 * @param unidade: unidade a ser removida
 * @return void
 */
int removerPalavraListaEnc(Unidades **uni, int unidade){
    int removeu = 1;
    if((*uni) != NULL){
        if((*uni)->unidade == unidade){
            Unidades *aux = *uni;
            *uni = aux->prox;
            free(aux);
            removeu = 1;
        }
        else
            removerPalavraListaEnc(&(*uni)->prox, unidade);
    }
    return removeu;
}

int percorrerBST(IngPTBST **raiz, int unidade, char *palavraIN){
    int enc = 0;
    if((*raiz) != NULL){
        enc = percorrerBST(&(*raiz)->esq, unidade, palavraIN);
        enc = percorrerBST(&(*raiz)->dir, unidade, palavraIN);
        if(strcmp((*raiz)->info->palavra, palavraIN) == 0)
            enc = removerPalavraListaEnc(&(*raiz)->info->unidades, unidade);
        if(enc && (*raiz)->info->unidades == NULL)
            removerBST(raiz, (*raiz)->info->palavra);
    }
    return enc;
}

/**
 * @brief Função que recebe uma palavra em inglês e a sua unidade para removê-la das árvores binárias das
 * quais ela pertence. Caso ela seja a única palavra em uma das árvores binárias, remover também da árvore 2-3
 * 
 * @param raiz: raiz da árvore 2-3
 * @param palavraIN: palavra a ser removida
 * @param unidade: unidade da palavra
 * @return int: 1 se a remoção foi bem sucedida, 0 caso contrário
 */
int removerMain(Arv23PT **raiz, char *palavraIN, int unidade, Arv23PT *ref){
    int enc = 0;
    if(ref != NULL){
        enc = removerMain(raiz, palavraIN, unidade, ref->esq);

        enc = percorrerBST(&ref->info1.versaoIng, unidade, palavraIN);
        if((*raiz)->info1.versaoIng == NULL)
            Arv23Remover(raiz, ref->info1.palavra);

        enc = removerMain(raiz, palavraIN, unidade, ref->cen);

        if((*raiz)->ninfos == 2){
            enc = percorrerBST(&ref->info2.versaoIng, unidade, palavraIN);
            if((*raiz)->info2.versaoIng == NULL)
                Arv23Remover(raiz, ref->info2.palavra);
            enc = removerMain(raiz, palavraIN, unidade, ref->dir);
        }
    }
    return enc;
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iv) informar uma palavra em português e a unidade a qual a mesma pertence e então removê-la, para isto
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
árvore 2-3 */

int ehFolhaBST(const IngPTBST *raiz){
    return (raiz->esq == NULL);
}

IngPTBST *soumFilho(IngPTBST *raiz){
    IngPTBST *filho = NULL;

    if(raiz->esq == NULL)
        filho = raiz->dir;
    else if(raiz->dir == NULL)
        filho = raiz->esq;

    return filho;
}

IngPTBST *menorFilhoEsq(IngPTBST *raiz){
    IngPTBST *filho;
    filho = NULL;

    if(raiz){
        filho = menorFilhoEsq(raiz->esq);
        if(!filho)
            filho = raiz;
    }

    return filho;
}

int removerBST(IngPTBST **raiz, const char *palavra){
    int removeu = 1;
    if(*raiz != NULL){
        if(strcmp(palavra, (*raiz)->info->palavra) == 0){
            IngPTBST *aux;
            if(ehFolhaBST(*raiz)){
                aux = *raiz;
                free(aux);
                *raiz = NULL;
                removeu = 1;
            }
            else if((aux = soumFilho(*raiz)) != NULL){
                IngPTBST *temp;
                temp = *raiz;
                free(temp);
                *raiz = aux;
                removeu = 1;
            }
            else{
                IngPTBST *menorFilho = menorFilhoEsq((*raiz)->dir);
                (*raiz)->info = menorFilho->info;
                removeu = removerBST(&(*raiz)->dir, menorFilho->info->palavra);
            }
        }
        else if(strcmp(palavra, (*raiz)->info->palavra) < 0)
            removeu = removerBST(&(*raiz)->esq, palavra);
        else
            removeu = removerBST(&(*raiz)->dir, palavra);
    }
    return removeu;
}

int buscaBST(IngPTBST *raiz, int unidade){
    int enc = 0;
    if(raiz != NULL){
        buscaBST(raiz->esq, unidade);
        if(raiz->info->unidades->unidade == unidade && raiz->info->unidades->prox == NULL){
            // removeu = removerBST(&raiz, raiz->info->palavra);
            enc = 1;
        }
        else{
            Unidades *aux = raiz->info->unidades->prox;

            while(aux != NULL && !enc){
                if(aux->unidade == unidade)
                    enc = 1;
                else
                    aux = aux->prox;
            }
        }
        buscaBST(raiz->dir, unidade);
    }
    return enc;
}

void removerPTporUnidade(Arv23PT **raiz, char *palavra, int unidade){
    int enc = 0;
    if(*raiz != NULL){
        if(ehInfo1(**raiz, palavra)){
            // enc = buscaBST((*raiz)->info1.versaoIng, unidade);
            // if(enc)
            //     Arv23Remover(raiz, palavra);
        }
        else if(ehInfo2(**raiz, palavra)){
            enc = buscaBST((*raiz)->info2.versaoIng, unidade);
            if(enc)
                Arv23Remover(raiz, palavra);
        }
        else{
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                removerPTporUnidade(&(*raiz)->esq, palavra, unidade);
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0)
                removerPTporUnidade(&(*raiz)->cen, palavra, unidade);
            else
                removerPTporUnidade(&(*raiz)->dir, palavra, unidade);
        }
    }
}