/*-----------------------------------------------------------------------------------------------------*/

/* Declaração das bibliotecas necessárias para a aplicação */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Q1.h"

/*-----------------------------------------------------------------------------------------------------*/

/* (pré-itens) funções necessárias para que os itens i, ii, iii e iv possam ocorrer */

void toupperString(char *string) {
    for (int i = 0; string[i] != '\0'; i++) {
        string[i] = toupper(string[i]);
    }
}

Arv23PT *criaNo(const Info informacao, Arv23PT *filhoesq, Arv23PT *filhocen){
    Arv23PT *no = (Arv23PT*)malloc(sizeof(Arv23PT));

    if(!no){
        printf("Nao foi possivel criar no\n");
    }

    if(no){
        no->info1 = informacao;
        no->esq = filhoesq;
        no->cen = filhocen;
        no->ninfos = 1;
    }

    return no;
}

void adicionaChave(Arv23PT *no, const Info informacao, Arv23PT *filho){
    if(strcmp(informacao.palavra, no->info1.palavra) > 0){
        no->info2 = informacao;
        no->dir = filho;
    }
    else{
        no->info2 = no->info1;
        no->dir = no->cen;
        no->info1 = informacao;
        no->cen = filho;
    }
    no->ninfos = 2;
}

Arv23PT *quebraNo(Arv23PT **no, const Info informacao, Info *promove, Arv23PT **filho){
    Arv23PT *maior;

    if(strcmp(informacao.palavra, (*no)->info2.palavra) > 0){
        *promove = (*no)->info2;
        if(filho)
            maior = criaNo(informacao, (*no)->dir, *filho);
        else
            maior = criaNo(informacao, (*no)->dir,  NULL);
    }
    else if(strcmp(informacao.palavra, (*no)->info1.palavra) > 0){
        *promove = informacao;
        if(filho)
            maior = criaNo((*no)->info2, *filho, (*no)->dir);
        else
            maior = criaNo((*no)->info2, NULL, (*no)->dir);
    }
    else{
        *promove = (*no)->info1;
        maior = criaNo((*no)->info2, (*no)->cen, (*no)->cen);
        (*no)->info1 = informacao;
        (*no)->cen = (filho ? *filho : NULL);
    }
    (*no)->ninfos = 1;

    return maior;
}

int ehFolha(const Arv23PT *no){
    return (no->esq == NULL);
}

Arv23PT *inserirArv23(Arv23PT **no, const Info informacao, Info *promove, Arv23PT **pai){
    Info promove1;
    Arv23PT *maiorNo = NULL;

    if(*no == NULL)
        *no = criaNo(informacao, NULL, NULL);
    else{
        if(ehFolha(*no)){
            if((*no)->ninfos == 1)
                adicionaChave(*no, informacao, NULL);
            else{
                maiorNo = quebraNo(no, informacao, promove, NULL);
                if(pai && !(*pai)){
                    *no = criaNo(*promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else{
            if(strcmp(informacao.palavra, (*no)->info1.palavra) < 0){
                maiorNo = inserirArv23(&((*no)->esq), informacao, promove, no);
            }
            else if(((*no)->ninfos == 1) || (strcmp(informacao.palavra, (*no)->info2.palavra) < 0)){
                maiorNo = inserirArv23(&((*no)->cen), informacao, promove, no);
            }
            else{
                maiorNo = inserirArv23(&((*no)->dir), informacao, promove, no);
            }

            if(maiorNo){
                if((*no)->ninfos == 1){
                    adicionaChave(*no, *promove, maiorNo);
                    maiorNo = NULL;
                }
                else{
                    maiorNo = quebraNo(no, *promove, &promove1, &maiorNo);
                    if(pai && !(*pai)){
                        *no = criaNo(promove1, *no, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return maiorNo;
}

void freeTree(Arv23PT *no){
    if(no != NULL){
        freeTree(no->esq);
        freeTree(no->cen);
        freeTree(no->dir);
        free(no);
    }
}

void inserirunidade(Unidades **unidades, int unidade){
    if (*unidades == NULL){
        *unidades = (Unidades*)malloc(sizeof(Unidades));
        (*unidades)->unidade = unidade;
        (*unidades)->prox = NULL;
    } 
    else
        inserirunidade(&(*unidades)->prox, unidade);
}

int insereArvBin(IngPTBST **raiz, const InfoBST *info) {
    int sucesso = 0;
    if((*raiz) == NULL){
        IngPTBST *novo = (IngPTBST *)malloc(sizeof(IngPTBST));
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
            inserirunidade(&(*raiz)->info->unidades, info->unidades);
        if(strcmp(info->palavra, (*raiz)->info->palavra) < 0)
            sucesso = insereArvBin(&(*raiz)->esq, info->palavra);
        else
            sucesso = insereArvBin(&(*raiz)->dir, info->palavra);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (i) informar uma unidade e então imprima todas as palavras da unidade em português seguida das
equivalentes em inglês */

void exibirEN(const IngPTBST *raiz) {
    if(raiz != NULL){
        exibirEN(raiz->esq);
        printf("%s, ", raiz->info->palavra);
        exibirEN(raiz->dir);
    }
}

int percorreLista(const Unidades *uni, int unidade){
    int enc = 0;
    if(uni != NULL){
        if(uni == unidade)
            enc = 0;
        else
            enc = percorreLista(uni->prox, unidade);
    }

    return enc;
}

void ExibirPalavrasUnidade(Arv23PT *raiz, int unidade){
    if(raiz != NULL){
        ExibirPalavrasUnidade(raiz->esq, unidade);
        if(percorreLista(raiz->info1.versaoIng->info->palavra, unidade)){
            printf("%s: ", raiz->info1.palavra);
            exibirEN(raiz->info1.versaoIng);
            printf("\n");
        }

        ExibirPalavrasUnidade(raiz->cen, unidade);

        if(raiz->ninfos == 2){
            if(percorreLista(raiz->info2.versaoIng->info->unidades, unidade)){
                printf("%s: ", raiz->info2.palavra);
                exibirEN(raiz->info2.versaoIng);
                printf("\n");
            }
            ExibirPalavrasUnidade(raiz->dir, unidade);
        }
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (ii) informar uma palavra em português e então imprima todas as palavras em inglês equivalente à palavra em
português dada, independente da unidade */

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

int onda(Info saindo, Info *entrada, Arv23PT *pai, Arv23PT **origem, Arv23PT **raiz, Arv23PT **maior, char (*funcao_remover)(Arv23PT **, char, Arv23PT *, Arv23PT **, Arv23PT **)){
    int removeu = funcao_remover(raiz, saindo.palavra, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

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

Arv23PT *buscarMenorFilho(Arv23PT *raiz, Arv23PT **pai){
    Arv23PT *filho;
    filho = raiz;

    while(!ehFolha(filho)){
        *pai = filho;
        filho = filho->esq;
    }
    return filho;
}

Info maiorFilho(Arv23PT *raiz){
    return raiz->ninfos == 2 ? raiz->info2 : raiz->info1;
}

Arv23PT *buscarMaiorFilho(Arv23PT *raiz, Arv23PT **pai, Info *maiorValor){
    Arv23PT *filho;
    filho = raiz;

    while(!ehFolha(filho)){
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

void desalocaNo(Arv23PT **no) {
    free(*no);
    *no = NULL;
}

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

Arv23PT *juntaNo(Arv23PT *filho1, Info info, Arv23PT *maior, Arv23PT **raiz){
    adicionarInfo(filho1, info, maior);

    (*raiz)->ninfos--;

    if((*raiz)->ninfos == 0)
        desalocaNo(raiz);

    return filho1;
}

int ehInfo1(const Arv23PT no, const char *palavra){
    int aux = 0;
    if(no.ninfos == 1 && palavra && no.info1.palavra)
        aux = strcmp(no.info1.palavra, palavra) == 0;
    return aux;
}

int ehInfo2(const Arv23PT no, const char *palavra){
    int aux = 0;
    if(no.ninfos == 2 && palavra && no.info2.palavra)
        aux = strcmp(no.info2.palavra, palavra) == 0;
    return aux;
}

Arv23PT *buscapai(Arv23PT *raiz, char *palavra) {
    Arv23PT *pai = NULL;

    if(raiz != NULL) {
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)) {
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscapai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscapai(raiz->cen, palavra);
            else
                pai = buscapai(raiz->dir, palavra);

            if(!pai)
                pai = raiz;
        }
    }
    return pai;
}

Arv23PT *buscarMaiorPai(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMaiorPai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || strcmp(palavra, raiz->info2.palavra))
                pai = buscarMaiorPai(raiz->cen, palavra);
            else
                pai = buscarMaiorPai(raiz->dir, palavra);

            if(pai == NULL && ((raiz->ninfos == 1 && strcmp(raiz->info1.palavra, palavra) > 0 || (raiz->ninfos == 2 && strcmp(raiz->info2.palavra, palavra) > 0))))
                pai = raiz;
        }
    }

    return pai;
}

Arv23PT *buscarMaiorPai2Infos(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra))
                pai = buscarMaiorPai2Infos(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || strcmp(palavra, raiz->info2.palavra) < 0)
                pai = buscarMaiorPai2Infos(raiz->cen, palavra);
            else
                pai = buscarMaiorPai2Infos(raiz->dir, palavra);

            if(pai == NULL && raiz->ninfos == 2 && strcmp(raiz->info1.palavra, palavra) > 0)
                pai = raiz;
        }
    }
    return pai;
}

Arv23PT *buscarMenorPai(Arv23PT *raiz, char palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMenorPai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || strcmp(palavra, raiz->info2.palavra))
                pai = buscarMenorPai(raiz->cen, palavra);
            else
                pai = buscarMenorPai(raiz->dir, palavra);

            if(pai == NULL && strcmp(raiz->info1.palavra, palavra) < 0)
                pai = raiz;
        }
    }
    return pai;
}

Arv23PT *buscarMenorPai2Infos(Arv23PT *raiz, char *palavra){
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL){
        if(!ehInfo1(*raiz, palavra) && !ehInfo2(*raiz, palavra)){
            if(strcmp(palavra, raiz->info1.palavra) < 0)
                pai = buscarMenorPai(raiz->esq, palavra);
            else if(raiz->ninfos == 1 || strcmp(palavra, raiz->info2.palavra))
                pai = buscarMenorPai(raiz->cen, palavra);
            else
                pai = buscarMenorPai(raiz->dir, palavra);

            if(pai == NULL && raiz->ninfos == 2 && strcmp(raiz->info2.palavra, palavra) < 0)
                pai = raiz;
        }
    }
    return pai;
}

void desalocarArv23(Arv23PT **raiz){
    if(*raiz != NULL){
        desalocarArv23(&((*raiz)->esq));
        desalocarArv23(&((*raiz)->dir));

        if((*raiz)->ninfos == 2)
            desalocarArv23(&((*raiz)->dir));

        desalocaNo(raiz);
    }
}

int removerNaoFolha1(Arv23PT **origem, Arv23PT *raiz, Info *info, Arv23PT *filho1, Arv23PT *filho2, Arv23PT **maior){
    int removeu;
    Arv23PT *filho, *pai;
    Info info_filho;
    pai = raiz;

    filho = buscarMaiorFilho(filho1, &pai, &info_filho);

    if(filho->ninfos == 2){
        *info = info_filho;
        filho->ninfos == 1;
    }
    else{
        filho = buscarMenorFilho(filho2, &pai);
        removeu = onda(filho->info1, info, pai, origem, &filho, maior, Remover1Arv23);
    }

    return removeu;
}

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
    }
    else{
        filho = buscarMaiorFilho(filho2, &pai, &info_filho);
        removeu = onda(info_filho, info, pai, origem, &filho, maior, Remover2Arv23);
    }

    return removeu;
}

int Remover1Arv23(Arv23PT **raiz, char palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior){
    int removeu = 0;

    if(*raiz != NULL){
        int info1 = ehInfo1(**raiz, palavra);
        int info2 = ehInfo2(**raiz, palavra);

        if(info1 || info2){
            removeu = 1;
            if(ehFolha(raiz)){
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

                            if(paiaux == NULL || (paiaux != pai && menorpai != NULL)){
                                *maior = pai;
                                (*raiz)->ninfos = 0;
                                removeu = -1;
                            }
                            else{
                                if(strcmp(paiaux->info1.palavra, (*raiz)->info1.palavra) > 0)
                                    info_pai = paiaux->info1;
                                else
                                    info_pai = paiaux->info2;

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
            if(strcmp(palavra, (*raiz)->info1.palavra))
                removeu = Remover1Arv23(&(*raiz)->esq, palavra, *raiz, origem, maior);
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0)
                removeu = Remover1Arv23(&(*raiz)->cen, palavra, *raiz, origem, maior);
            else
                removeu = Remover1Arv23(&(*raiz)->dir, palavra, *raiz, origem, maior);
        }
    }
    return removeu;
}

int Remover2Arv23(Arv23PT **raiz, char palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior){
    int removeu = 0;

    if(*raiz != NULL){
        int info1 = ehInfo1(**raiz, palavra);
        int info2 = ehInfo2(**raiz, palavra);

        if(info1 || info2){
            removeu = 1;
            if(ehFolha(raiz)){
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
                                if(paiaux->ninfos == 2 && strcmp(paiaux->info2.palavra, (*raiz)->info2.palavra))
                                    info_pai = paiaux->info2;
                                else
                                    info_pai = paiaux->info1;

                                avo = buscamaior(*origem, info_pai.palavra);
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
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0)
                removeu = Remover2Arv23(&(*raiz)->cen, palavra, *raiz, origem, maior);
            else
                removeu = Remover2Arv23(&(*raiz)->dir, palavra, *raiz, origem, maior);
        }
    }
    return removeu;
}

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

int Arv23Rebalancear(Arv23PT **raiz, char palavra, Arv23PT **maior){
    int balanceou = 0;
    if(*raiz != NULL){
        if(!ehFolha(raiz)){
            if(strcmp(palavra, (*raiz)->info1.palavra) < 0)
                balanceou = Arv23Rebalancear(&((*raiz)->esq), palavra, maior);
            else if((*raiz)->ninfos == 1 || strcmp(palavra, (*raiz)->info2.palavra) < 0){
                if((*raiz)->esq->ninfos == 2 && !removivel((*raiz)->dir))
                    balanceou = -1;
                else
                    balanceou = Arv23Rebalancear(&(*raiz)->dir, palavra, maior);
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

int Arv23Remover(Arv23PT **raiz, char palavra){
    Arv23PT *maior, *posicao;
    int removeu = Remover1Arv23(raiz, palavra, NULL, raiz, &posicao);

    if(removeu == -1){
        Info valor = maiorFilho(posicao);
        maior = NULL;
        removeu = Arv23Rebalancear(raiz, valor.palavra, &maior);
    }
}

/*-----------------------------------------------------------------------------------------------------*/

/* (iv)informar uma palavra em português e a unidade a qual a mesma pertence e então removê-la, para isto
deve remover a palavra em inglês da árvore binária correspondente a palavra em português da mesma
unidade. Caso ela seja a única palavra na árvore binária, a palavra em português deve ser removida da
árvore 2-3 */