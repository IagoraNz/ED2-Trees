#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Q1Copy.h"
#include "Q1.h"

void no23_adicionar_info(Arv23PT *no, Info info, Arv23PT *filho_maior)
{
    if(strcmp(info.palavra, no->info1.palavra) > 0)
    {
        no->info2 = info;
        no->dir = filho_maior;
    }
    else
    {
        no->info2 = no->info1;
        no->dir = no->cen;
        no->cen = filho_maior;
        no->info1 = info;
    }
    no->ninfos = 2;
}

int eh_folha(Arv23PT no){
    return no.esq == NULL;
}

int eh_info1(Arv23PT no, Info info){
    int aux = 0;
    if(no.info1.palavra && info.palavra)
        aux = strcmp(no.info1.palavra, info.palavra) == 0;
    return aux;
}

int eh_info2(Arv23PT no, Info info){
    int aux = 0;
    if(no.info2.palavra && info.palavra)
        aux = strcmp(no.info2.palavra, info.palavra) == 0;
    return aux;
}

void troca_infos(Info *info1, Info *info2){
    Info aux = *info1;
    *info1 = *info2;
    *info2 = aux;
}

Arv23PT *no23_alocar(){
    Arv23PT *no;
    no = (Arv23PT *)malloc(sizeof(Arv23PT));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore");
        exit(EXIT_FAILURE);
    }

    return no;
}

void no23_desalocar(Arv23PT **no){
    free(*no);
    *no = NULL;
}

Arv23PT *no23_criar(Info info, Arv23PT *filho_esq, Arv23PT *filho_cen){
    Arv23PT *no;
    no = no23_alocar();

    no->info1 = info;
    no->esq = filho_esq;
    no->cen = filho_cen;
    no->dir = NULL;
    no->ninfos = 1;
    return no;
}

Arv23PT *no23_quebrar(Arv23PT *no, Info info, Info *promove, Arv23PT *filho_maior){
    Arv23PT *maior;
    if(strcmp(info.palavra, no->info2.palavra) > 0){
        *promove = no->info2;
        maior = no23_criar(info, no->dir, filho_maior);
    }
    else if(strcmp(info.palavra, no->info1.palavra) > 0){
        *promove = info;
        maior = no23_criar(no->info2, filho_maior, no->dir);
    }
    else{
        *promove = no->info1;
        maior = no23_criar(no->info2, no->cen, no->dir);
        no->info1 = info;
        no->cen = filho_maior;
    }
    no->ninfos = 1;

    return maior;
}

Arv23PT *no23_juntar(Arv23PT *filho1, Info info, Arv23PT *maior, Arv23PT **raiz)
{
    if(filho1->ninfos == 2)
        filho1->ninfos = 1;
        
    no23_adicionar_info(filho1, info, maior);

    (*raiz)->ninfos--;

    if((*raiz)->ninfos == 0)
        no23_desalocar(raiz);

    return filho1;
}

Arv23PT *buscar_menor_filho(Arv23PT *raiz, Arv23PT **pai)
{
    Arv23PT *filho;
    filho = raiz;

    while(!eh_folha(*filho))
    {
        *pai = filho;
        filho = filho->esq;
    }

    return filho;
}

Info maior_info(Arv23PT *raiz)
{
    return raiz->ninfos == 2 ? raiz->info2 : raiz->info1;
}

Arv23PT *buscar_maior_filho(Arv23PT *raiz, Arv23PT **pai, Info *maior_valor)
{
    Arv23PT *filho;
    filho = raiz;

    while(!eh_folha(*filho))
    {
        *pai = filho;
        if(filho->ninfos == 1)
            filho = filho->cen;
        else
            filho = filho->dir;
    }

    if(filho != NULL)
        *maior_valor = maior_info(filho);

    return filho;
}

Arv23PT *buscar_pai(Arv23PT *raiz, Info info)
{
    Arv23PT *pai;
    pai = NULL;

    if(raiz != NULL)
    {
        if(!eh_info1(*raiz, info) && !eh_info2(*raiz, info))
        {
            if(strcmp(info.palavra, raiz->info1.palavra) < 0)
                pai = buscar_pai(raiz->esq, info);
            else if(raiz->ninfos == 1 || strcmp(info.palavra, raiz->info2.palavra) < 0)
                pai = buscar_pai(raiz->cen, info);
            else
                pai = buscar_pai(raiz->dir, info);

            if(pai == NULL)
                pai = raiz;
        }
    }

    return pai;
}

Arv23PT *buscar_maior_pai(Arv23PT *origem, Arv23PT *pai, Info info, Info *maior)
{
    while(pai != NULL && ((pai->ninfos == 1 && strcmp(pai->info1.palavra, info.palavra) < 0) || (pai->ninfos == 2 && strcmp(pai->info2.palavra, info.palavra) < 0)))
        pai = buscar_pai(origem, pai->info1);

    if(pai != NULL)
        *maior = maior_info(pai);

    return pai;
}

Arv23PT *Arv23PT_criar()
{
    return NULL;
}

void Arv23PT_desalocar(Arv23PT **raiz)
{
    if(*raiz != NULL)
    {
        Arv23PT_desalocar(&((*raiz)->esq));
        Arv23PT_desalocar(&((*raiz)->cen));

        if((*raiz)->ninfos == 2)
            Arv23PT_desalocar(&((*raiz)->dir));

        no23_desalocar(raiz);
    }
}

Arv23PT *Arv23PT_inserir(Arv23PT **raiz, Info info, Arv23PT *pai, Info *promove)
{
    Arv23PT *maior;
    maior = NULL;

    if(*raiz == NULL)
        *raiz = no23_criar(info, NULL, NULL);
    else
    {
        if(eh_folha(**raiz))
        {
            if((*raiz)->ninfos == 1)
                no23_adicionar_info(*raiz, info, NULL);
            else
            {
                maior = no23_quebrar(*raiz, info, promove, NULL);
                if(pai == NULL)
                {
                    *raiz = no23_criar(*promove, *raiz, maior);
                    maior = NULL;
                }
            }
        }
        else
        {
            if(strcmp(info.palavra, (*raiz)->info1.palavra) < 0)
                maior = Arv23PT_inserir(&((*raiz)->esq), info, *raiz, promove);
            else if((*raiz)->ninfos == 1 || strcmp(info.palavra, (*raiz)->info2.palavra) < 0)
                maior = Arv23PT_inserir(&((*raiz)->cen), info, *raiz, promove);
            else
                maior = Arv23PT_inserir(&((*raiz)->dir), info, *raiz, promove);

            if(maior != NULL)
            {
                if((*raiz)->ninfos == 1)
                {
                    no23_adicionar_info(*raiz, *promove, maior);
                    maior = NULL;
                }
                else
                {
                    Info promove_aux;
                    maior = no23_quebrar(*raiz, *promove, &promove_aux, maior);
                    *promove = promove_aux;
                    if(pai == NULL)
                    {
                        *raiz = no23_criar(promove_aux, *raiz, maior);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return maior;
}

int possivel_remover(Arv23PT *raiz)
{
    int possivel = 0;

    if(raiz != NULL)
    {
        possivel = raiz->ninfos == 2;

        if(!possivel)
        {
            possivel = possivel_remover(raiz->cen);

            if(!possivel)
                possivel = possivel_remover(raiz->esq);
        }
    }

    return possivel;
}

int Arv23PT_remover1(Arv23PT **raiz, Info info, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior)
{
    int removeu = 0;

    if(*raiz != NULL)
    {
        Arv23PT *pai_aux;
        pai_aux = pai;
        int info1 = eh_info1(**raiz, info);
        int info2 = eh_info2(**raiz, info);

        if(info1 || info2)
        {
            removeu = 1;
            if(eh_folha(**raiz))
            {
                if((*raiz)->ninfos == 2)
                {
                    if(info1)
                        troca_infos(&((*raiz)->info1), &((*raiz)->info2));

                    (*raiz)->ninfos = 1;
                }
                else
                {
                    if(pai != NULL)
                    {
                        
                        if(*raiz == pai->esq || (pai->ninfos == 2 && *raiz == pai->cen))
                        {
                            pai_aux = buscar_pai(*origem, pai->info1);
                            
                            if(*raiz == pai->esq)
                                removeu = movimento_onda(pai->info1, &((*raiz)->info1), pai_aux, origem, origem, maior);
                            else 
                                removeu = movimento_onda(pai->info2, &((*raiz)->info1), pai_aux, origem, origem, maior);
                        }
                        else
                        {
                            Info info_pai;
                            pai_aux = buscar_maior_pai(*origem, pai, (*raiz)->info1, &info_pai);
                            if(pai_aux != NULL)
                            {
                                Arv23PT *avo;
                                avo = buscar_pai(*origem, info_pai);
                                removeu = movimento_onda(info_pai, &((*raiz)->info1), avo, origem, origem, maior);
                            }
                            else
                            {
                                (*raiz)->ninfos = 0;
                                removeu = -1;
                                // TODO desalocar verificando
                                // no23_desalocar(raiz);
                            }
                        }
                    }
                    else
                        no23_desalocar(raiz);
                }
            }
            else
            {
                Arv23PT *filho, *filho2;
                Arv23PT *pai_aux2;
                filho2 = NULL;
                Info info_filho;

                if(info2)
                {
                    filho = buscar_menor_filho((*raiz)->dir, &pai_aux);

                    if(filho->ninfos == 1)
                        filho2 = buscar_maior_filho((*raiz)->cen, &pai_aux2, &info_filho);
                    
                    if(filho2 != NULL && filho2->ninfos == 2)
                    {
                        (*raiz)->info2 = filho2->info2;
                        filho2->ninfos = 1;
                    }
                    else
                    {
                        if(pai_aux == NULL)
                            pai_aux = *raiz;
                        removeu = movimento_onda(filho->info1, &((*raiz)->info2), pai_aux, origem, &filho, maior);
                    }
                }
                else if(info1)
                {
                    filho2 = buscar_maior_filho((*raiz)->esq, &pai_aux, &info_filho);

                    if(filho2->ninfos == 2)
                    {
                        (*raiz)->info1 = info_filho;
                        filho2->ninfos = 1;
                    }
                    else
                    {
                        filho = buscar_menor_filho((*raiz)->cen, &pai_aux);

                        if(pai_aux == NULL)
                            pai_aux = *raiz;
                        removeu = movimento_onda(filho->info1, &((*raiz)->info1), pai_aux, origem, &filho, maior);
                    }
                }
            }
        }
        else
        {
            if(strcmp(info.palavra, (*raiz)->info1.palavra) < 0)
                removeu = Arv23PT_remover1(&(*raiz)->esq, info, *raiz, origem, maior);
            else
            {
                if((*raiz)->ninfos == 1 || strcmp(info.palavra, (*raiz)->info2.palavra) < 0)
                    removeu = Arv23PT_remover1(&(*raiz)->cen, info, *raiz, origem, maior);
                else
                    removeu = Arv23PT_remover1(&(*raiz)->dir, info, *raiz, origem, maior);
            }
        }
    }

    // if(*raiz != NULL && !eh_folha(**raiz))
    // {
    //     if((*raiz)->ninfos == 1 && ((*raiz)->cen == NULL || (*raiz)->cen->ninfos == 0))
    //     {
    //         if((*raiz)->cen != NULL)
    //             no23_desalocar(&((*raiz)->cen));
    //         *maior = no23_juntar((*raiz)->esq, (*raiz)->info1, *maior, raiz);
    //     }
    //     else if((*raiz)->ninfos == 2 && ((*raiz)->dir == NULL || (*raiz)->dir->ninfos == 0))
    //     {
    //         if((*raiz)->dir != NULL)
    //             no23_desalocar(&((*raiz)->dir));
    //         *maior = no23_juntar((*raiz)->cen, (*raiz)->info2, *maior, raiz);
    //     }
    // }

    // if(*origem == NULL)
    //     *origem = *maior;

    return removeu;
}

int movimento_onda(Info saindo, Info *entrada, Arv23PT *pai, Arv23PT **origem, Arv23PT **raiz, Arv23PT **maior)
{
    int removeu = Arv23PT_remover1(raiz, saindo, pai, origem, maior);
    *entrada = saindo;
    return removeu;
}

int rebalancear(Arv23PT **raiz, Arv23PT **maior)
{
    int balanceou = 0;
    if(*raiz != NULL)
    {
        if(!eh_folha(**raiz))
        {
            if((*raiz)->ninfos == 1)
            {
                balanceou = rebalancear(&((*raiz)->cen), maior);
                if((*raiz)->cen == NULL || (*raiz)->cen->ninfos == 0)
                {
                    if((*raiz)->cen != NULL)
                        no23_desalocar(&((*raiz)->cen));
                    *maior = no23_juntar((*raiz)->esq, (*raiz)->info1, *maior, raiz);
                    balanceou = 1;
                }
            }
            else if((*raiz)->ninfos == 2 || (*raiz)->dir->ninfos == 0)
            {
                balanceou = rebalancear(&((*raiz)->dir), maior);
                if((*raiz)->dir == NULL || (*raiz)->dir->ninfos == 0)
                {
                    if((*raiz)->dir != NULL)
                        no23_desalocar(&((*raiz)->dir));
                    *maior = no23_juntar((*raiz)->cen, (*raiz)->info2, *maior, raiz);
                    balanceou = 1;
                }
            }
        }
    }
    return balanceou;
}

int Arv23PT_remover(Arv23PT **raiz, Info info){
    Arv23PT *maior;
    maior = NULL;
    int removeu = Arv23PT_remover1(raiz, info, NULL, raiz, &maior);
    if(removeu == -1){
        removeu = rebalancear(raiz, &maior);
        if(*raiz == NULL)
            *raiz = maior;
    }
    return removeu;
}

void Arv23PT_exibir_pre(Arv23PT *raiz)
{
    if(raiz != NULL)
    {
        printf("[1º] %s -> ", raiz->info1.palavra);
        if(raiz->ninfos == 2)
            printf("[2º] %s -> ", raiz->info2.palavra);

        Arv23PT_exibir_pre(raiz->esq);
        Arv23PT_exibir_pre(raiz->cen);
        if(raiz->ninfos == 2)
            Arv23PT_exibir_pre(raiz->dir);
    }
}

void Arv23PT_exibir_ordem(Arv23PT *raiz)
{
    if(raiz != NULL)
    {
        Arv23PT_exibir_ordem(raiz->esq);
        printf("[1º] %s -> ", raiz->info1.palavra);
        Arv23PT_exibir_ordem(raiz->cen);

        if(raiz->ninfos == 2)
        {
            printf("[2º] %s -> ", raiz->info2.palavra);
            Arv23PT_exibir_ordem(raiz->dir);
        }
    }
}

void Arv23PT_exibir_pos(Arv23PT *raiz)
{
    if(raiz != NULL)
    {
        Arv23PT_exibir_pos(raiz->esq);
        Arv23PT_exibir_pos(raiz->cen);
        if(raiz->ninfos == 2)
            Arv23PT_exibir_pos(raiz->dir);

        printf("[1º] %s -> ", raiz->info1.palavra);
        if(raiz->ninfos == 2)
            printf("[2º] %s -> ", raiz->info2.palavra);
    }
}

int main() {
    Arv23PT *raiz = Arv23PT_criar();
    Info info;
    // Arv23PT *maior = NULL;
    Info promove;

    // Inserir elementos
    char *palavras[] = {"banana", "maca", "uva", "laranja", "abacaxi", "pera", "melao"};
    for (int i = 0; i < 7; i++) {
        info.palavra = palavras[i];
        Arv23PT_inserir(&raiz, info, NULL, &promove);
    }

    printf("Árvore em pré-ordem:\n");
    Arv23PT_exibir_pre(raiz);
    printf("\n");

    printf("Árvore em ordem:\n");
    Arv23PT_exibir_ordem(raiz);
    printf("\n");

    printf("Árvore em pós-ordem:\n");
    Arv23PT_exibir_pos(raiz);
    printf("\n");

    // Remover elementos
    printf("Árvore após remoções:\n");
    for (int i = 0; i < 4; i++) {
        info.palavra = palavras[i];
        Arv23PT_remover(&raiz, info);
        Arv23PT_exibir_ordem(raiz);
        printf("\n");
    }

    Arv23PT_desalocar(&raiz);
    return 0;
}