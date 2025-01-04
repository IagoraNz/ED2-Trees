#include "Q3.h"

Info *criarInfo(int inicio, int fim, int status)
{
    Info *info = (Info *)malloc(sizeof(Info));

    if (info != NULL)
    {
        info->inicio = inicio;
        info->fim = fim;
        info->status = status;
    }
    return (info);
}

Memoria *criarNo(const Info *info, Memoria *Filhoesq, Memoria *Filhocen)
{
    Memoria *No = (Memoria *)malloc(sizeof(Memoria));
    if (No == NULL)
        printf("Erro ao alocar memória para o nó.\n");

    No->info1 = (Info *)malloc(sizeof(Info));
    if (No->info1 == NULL)
    {
        printf("Erro ao alocar memória para info1.\n");
        free(No);
    }
    *(No->info1) = *info;

    No->info2 = NULL;
    No->left = Filhoesq;
    No->center = Filhocen;
    No->right = NULL;
    No->numKeys = 1;

    return (No);
}

int ehFolha(const Memoria *No)
{
    int validar = 0;

    if (No->left == NULL)
        validar = 1;

    return (validar);
}

Memoria *addKey(Memoria *no, const Info *info, Memoria *filho)
{
    if (info->inicio > no->info1->inicio)
    {
        no->info2 = (Info*)malloc(sizeof(Info));
        *(no->info2) = *info;
        no->right = filho;
    }
    else
    {
        no->info2 = no->info1;
        no->right = no->center;
        no->info1 = (Info*)malloc(sizeof(Info));
        *(no->info1) = *info;
        no->center = filho;
    }
    no->numKeys = 2;

    return (no);
}

void addInfo(Memoria *no, Info info, Memoria *maiorFilho)
{
    Info *novaInfo = (Info *)malloc(sizeof(Info));
    if (novaInfo != NULL)
    {
        *novaInfo = info;

        if (info.inicio > no->info1->inicio)
        {
            no->info2 = novaInfo;
            no->right = maiorFilho;
        }
        else
        {
            no->info2 = no->info1;
            no->right = no->center;
            no->center = maiorFilho;
            no->info1 = novaInfo;
        }
        no->numKeys = 2;
    }
}

Memoria *quebraNo(Memoria *no, Info info, Info *promove, Memoria *maiorFilho)
{
    Memoria *maior;
    if (info.inicio > no->info2->inicio)
    {
        *promove = *(no->info2);
        maior = criarNo(&info, no->right, maiorFilho);
    }
    else if (info.inicio > no->info1->inicio)
    {
        *promove = info;
        maior = criarNo(no->info2, maiorFilho, no->right);
    }
    else
    {
        *promove = *(no->info1);
        maior = criarNo(no->info2, no->center, no->right);
        no->info1 = &info;
        no->center = maiorFilho;
    }
    no->numKeys = 1;

    return (maior);
}

Memoria *insereArv23(Memoria **raiz, Info info, Memoria *pai, Info *promove)
{
    Memoria *maior;
    maior = NULL;

    if (*raiz == NULL)
        *raiz = criarNo(&info, NULL, NULL);
    else
    {
        if (ehFolha(*raiz))
        {
            if ((*raiz)->numKeys == 1)
                addInfo(*raiz, info, NULL);
            else
            {
                maior = quebraNo(*raiz, info, promove, NULL);
                if (pai == NULL)
                {
                    *raiz = criarNo(promove, *raiz, maior);
                    maior = NULL;
                }
            }
        }
        else
        {
            if (info.inicio < (*raiz)->info1->inicio)
                maior = insereArv23(&((*raiz)->left), info, *raiz, promove);
            else if ((*raiz)->numKeys == 1 || info.inicio < (*raiz)->info2->inicio)
                maior = insereArv23(&((*raiz)->center), info, *raiz, promove);
            else
                maior = insereArv23(&((*raiz)->right), info, *raiz, promove);

            if (maior != NULL)
            {
                if ((*raiz)->numKeys == 1)
                {
                    addInfo(*raiz, *promove, maior);
                    maior = NULL;
                }
                else
                {
                    Info promove_aux;
                    maior = quebraNo(*raiz, *promove, &promove_aux, maior);
                    *promove = promove_aux;
                    if (pai == NULL)
                    {
                        *raiz = criarNo(&promove_aux, *raiz, maior);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return (maior);
}

int avaliarQuant(Info info)
{
    return (info.fim - info.inicio + 1);
}

Memoria *buscaEspaco(Memoria **raiz, int quant, int status, Info **info)
{
    Memoria *no;
    if (*raiz != NULL)
    {
        no = buscaEspaco(&((*raiz)->left), quant, status, info);

        if (*info == NULL)
        {
            if ((*raiz)->info1->status == status && avaliarQuant(*((*raiz)->info1)) >= quant)
            {
                *info = (*raiz)->info1;
                no = *raiz;
            }
            else
            {
                no = buscaEspaco(&((*raiz)->center), quant, status, info);
                if ((*raiz)->numKeys == 2)
                {
                    if ((*raiz)->info2->status == status && avaliarQuant(*((*raiz)->info2)) >= quant)
                    {
                        *info = (*raiz)->info2;
                        no = *raiz;
                    }
                    else if (*info == NULL)
                        no = buscaEspaco(&((*raiz)->right), quant, status, info);
                }
            }
        }
    }
    else
        *info = NULL;

    return (no);
}



void exibirInfos(Memoria *raiz)
{
    if (raiz)
    {
        exibirInfos(raiz->left);
        printf("Começo: %d | Fim %d | Status: %d\n", raiz->info1->inicio, raiz->info1->fim, raiz->info1->status);
        exibirInfos(raiz->center);

        if (raiz->numKeys == 2)
        {
            printf("Começo: %d | Fim %d | Status: %d\n", raiz->info2->inicio, raiz->info2->fim, raiz->info2->status);
            exibirInfos(raiz->right);
        }
    }
}

Memoria *insereMemoriaNo(Memoria **raiz, Info info, Memoria *pai, Info *promove)
{
    Memoria *maior;
    maior = NULL;

    if (*raiz == NULL)
        *raiz = criarNo(&info, NULL, NULL);
    else
    {
        if (ehFolha(*raiz))
        {
            if ((*raiz)->numKeys == 1)
                noAddInfo(*raiz, info, NULL);
            else
            {
                maior = quebraNo(*raiz, info, promove, NULL);
                if (pai == NULL)
                {
                    *raiz = criarNo(&(*promove), *raiz, maior);
                    maior = NULL;
                }
            }
        }
        else
        {
            if (info.inicio < (*raiz)->info1->inicio)
                maior = insereMemoriaNo(&((*raiz)->left), info, *raiz, promove);
            else if ((*raiz)->numKeys == 1 || info.inicio < (*raiz)->info2->inicio)
                maior = insereMemoriaNo(&((*raiz)->center), info, *raiz, promove);
            else
                maior = insereMemoriaNo(&((*raiz)->right), info, *raiz, promove);

            if (maior != NULL)
            {
                if ((*raiz)->numKeys == 1)
                {
                    noAddInfo(*raiz, *promove, maior);
                    maior = NULL;
                }
                else
                {
                    Info promove_aux;
                    maior = quebraNo(*raiz, *promove, &promove_aux, maior);
                    *promove = promove_aux;
                    if (pai == NULL)
                    {
                        *raiz = criarNo(&promove_aux, *raiz, maior);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return maior;
}

Memoria *insereMemoria(Memoria **raiz, Info info)
{
    Info promove;
    return insereMemoriaNo(raiz, info, NULL, &promove);
}

static int ehInfo1(Memoria no, int info)
{
    return (info == no.info1->inicio);
}

static int ehInfo2(Memoria no, int info)
{
    return (no.numKeys == 2 && info == no.info2->inicio);
}

Memoria *buscaMenorNoPai(Memoria *raiz, int info)
{
    Memoria *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!ehInfo1(*raiz, info) && !ehInfo2(*raiz, info))
        {
            if (info < raiz->info1->inicio)
                pai = buscaMenorNoPai(raiz->left, info);
            else if (raiz->numKeys == 1 || info < raiz->info2->inicio)
                pai = buscaMenorNoPai(raiz->center, info);
            else
                pai = buscaMenorNoPai(raiz->right, info);

            if (pai == NULL && raiz->info1->inicio < info)
                pai = raiz;
        }
    }

    return (pai);
}

Memoria *buscaMenorBloco(Memoria **raiz, Memoria *no, Info *info, Info **menorValor)
{
    Memoria *menor, *pai;
    *menorValor = NULL;

    if (ehFolha(no))
    {
        if (no->info1->inicio != info->inicio)
            menor = no;
        else
            menor = buscaMenorNoPai(*raiz, info->inicio);

        if (menor != NULL)
        {
            if (menor->numKeys == 2 && menor->info2->inicio < info->inicio)
                *menorValor = menor->info2;
            else
                *menorValor = menor->info1;
        }
    }
    else if (no->info1->inicio == info->inicio)
        menor = buscaMaiorFilho(no->left, &pai, menorValor);
    else
        menor = buscaMaiorFilho(no->center, &pai, menorValor);

    return menor;
}

Memoria *buscaMaiorBloco(Memoria **raiz, Memoria *no, Info *info, Info **maiorValor)
{
    Memoria *Maior;
    Memoria *pai;
    *maiorValor = NULL;

    if(ehFolha(no))
    {
        if(no->numKeys == 2 && no->info1->inicio == info->inicio)
            Maior = no;
        else
            Maior = buscaMaiorNoPai(*raiz, info->inicio);

        if(Maior != NULL)
        {
            if(Maior->info1->inicio > info->inicio)
                *maiorValor = Maior->info1;
            else
                *maiorValor = Maior->info2;
        }
    }
    else
    {
        if(no->info1->inicio == info->inicio)
            Maior = buscaMenorFilho(no->center, &pai);
        else
            Maior = buscaMenorFilho(no->right, &pai);

        if(Maior != NULL)
            *maiorValor = Maior->info1;
    }

    return (Maior);
}

void concatenaNo(Memoria **raiz, int *ultimoNum, int limite, int valorRemove)
{
    *ultimoNum = limite;
    removeMemoria(raiz, valorRemove);
}

void modificarNo(Memoria **raiz, Memoria *no, Info *info, int quant)
{
    Memoria *menor;
    Info *menorValor;

    menor = buscaMenorBloco(raiz, no, info, &menorValor);

    if (quant < avaliarQuant(*info))
    {
        if (menor == NULL)
        {
            Info Info;
            Info.inicio = info->inicio;
            Info.fim = info->inicio + quant - 1;
            Info.status = !(info->status);

            info->inicio += quant;
            insereMemoria(raiz, Info);
        }
        else
        {
            menorValor->fim += quant;
            info->inicio += quant;
        }
    }
    else
    {
        Memoria *maior;
        Info *maiorValor;

        maior = buscaMaiorBloco(raiz, no, info, &maiorValor);

        if (menor == NULL && maior == NULL)
            info->status = !(info->status);
        else
        {
            if (menor == NULL)
            {
                info->status = !(info->status);
                concatenaNo(raiz, &(info->fim), maiorValor->fim, maiorValor->inicio);
            }
            else if (maior == NULL)
                concatenaNo(raiz, &(menorValor->fim), info->fim, info->inicio);
            else
            {
                int numero = maiorValor->inicio;
                concatenaNo(raiz, &(menorValor->fim), maiorValor->fim, info->inicio);
                removeMemoria(raiz, numero);
            }
        }
    }
}

void alocarEDesalocar(Memoria **raiz, int quantNo, int status)
{
    Info *info;
    info = NULL;
    Memoria *no;
    no = buscaEspaco(raiz, quantNo, status, &info);

    if (info != NULL)
        modificarNo(raiz, no, info, quantNo);
    else
        printf("\nNão há espaço disponível\n");
}

void no23free(Memoria **no)
{
    free(*no);
    *no = NULL;
}

Memoria *alocarNo23()
{
    Memoria *no;
    no = (Memoria *)malloc(sizeof(Memoria));

    if (!no)
    {
        printf("Erro ao alocar nó da árvore");
        exit(EXIT_FAILURE);
    }

    return no;
}


static int balancear(Memoria **raiz, Memoria *filho1, Memoria **filho2, Info info, Memoria **maior)
{
    int balanceado = 0;
    if (*filho2 == NULL || (*filho2)->numKeys == 0)
    {
        if (*filho2 != NULL)
            no23free(filho2);

        *maior = no23Juntar(filho1, info, *maior, raiz);
        balanceado = 1;
    }
    return (balanceado);
}

void noAddInfo(Memoria *no, Info info, Memoria *maiorFilho)
{
    if (info.inicio > no->info1->inicio)
    {
        if (no->info2 == NULL)
        {
            no->info2 = (Info *)malloc(sizeof(Info));
            if (no->info2 == NULL)
            {
                fprintf(stderr, "Erro ao alocar memória para info2\n");
                exit(EXIT_FAILURE);
            }
        }
        *(no->info2) = info;
        no->right = maiorFilho;
    }
    else
    {
        if (no->info2 == NULL)
        {
            no->info2 = (Info *)malloc(sizeof(Info));
            if (no->info2 == NULL)
            {
                fprintf(stderr, "Erro ao alocar memória para info2\n");
                exit(EXIT_FAILURE);
            }
        }
        *(no->info2) = *(no->info1);

        no->right = no->center;
        no->center = maiorFilho;
        *(no->info1) = info;
    }

    no->numKeys = 2;
}

Memoria *no23Juntar(Memoria *filho1, Info info, Memoria *maior, Memoria **raiz)
{
    noAddInfo(filho1, info, maior);

    (*raiz)->numKeys--;

    if ((*raiz)->numKeys == 0)
        no23free(raiz);

    return (filho1);
}

Memoria *buscaMenorFilho(Memoria *raiz, Memoria **pai)
{
    Memoria *filho;
    filho = raiz;

    while (!ehFolha(filho))
    {
        *pai = filho;
        filho = filho->left;
    }

    return (filho);
}

Info *no23MaiorInfo(Memoria *raiz)
{
    return (raiz->numKeys == 2 ? raiz->info2 : raiz->info1);
}

Memoria *buscaMaiorFilho(Memoria *raiz, Memoria **pai, Info **maior_valor)
{
    Memoria *filho;
    filho = raiz;

    while(!ehFolha(filho))
    {
        *pai = filho;
        if(filho->numKeys == 1)
            filho = filho->center;
        else
            filho = filho->right;
    }

    if(filho != NULL)
        *maior_valor = no23MaiorInfo(filho);

    return filho;
}

Memoria *buscaNoPai(Memoria *raiz, int info)
{
    Memoria *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!ehInfo1(*raiz, info) && !ehInfo2(*raiz, info))
        {
            if (info < raiz->info1->inicio)
                pai = buscaNoPai(raiz->left, info);
            else if (raiz->numKeys == 1 || info < raiz->info2->inicio)
                pai = buscaNoPai(raiz->center, info);
            else
                pai = buscaNoPai(raiz->right, info);

            if (pai == NULL)
                pai = raiz;
        }
    }

    return (pai);
}

Memoria *buscaMaiorNoPai(Memoria *raiz, int info)
{
    Memoria *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!ehInfo1(*raiz, info) && !ehInfo2(*raiz, info))
        {
            if (info < raiz->info1->inicio)
                pai = buscaMaiorNoPai(raiz->left, info);
            else if (raiz->numKeys == 1 || info < raiz->info2->inicio)
                pai = buscaMaiorNoPai(raiz->center, info);
            else
                pai = buscaMaiorNoPai(raiz->right, info);

            if (pai == NULL && ((raiz->numKeys == 1 && raiz->info1->inicio > info) || (raiz->numKeys == 2 && raiz->info2->inicio > info)))
                pai = raiz;
        }
    }

    return (pai);
}

static Memoria *buscaMenorNoPai2Infos(Memoria *raiz, int info)
{
    Memoria *pai;
    pai = NULL;

    if (raiz != NULL)
    {
        if (!ehInfo1(*raiz, info) && !ehInfo2(*raiz, info))
        {
            if (info < raiz->info1->inicio)
                pai = buscaMenorNoPai2Infos(raiz->left, info);
            else if (raiz->numKeys == 1 || info < raiz->info2->inicio)
                pai = buscaMenorNoPai2Infos(raiz->center, info);
            else
                pai = buscaMenorNoPai2Infos(raiz->right, info);

            if (pai == NULL && raiz->numKeys == 2 && raiz->info2->inicio < info)
                pai = raiz;
        }
    }

    return (pai);
}

int possivelRemover(Memoria *raiz)
{
    int possivel = 0;

    if (raiz != NULL)
    {
        possivel = raiz->numKeys == 2;

        if (!possivel)
        {
            possivel = possivelRemover(raiz->center);

            if (!possivel)
                possivel = possivelRemover(raiz->left);
        }
    }

    return (possivel);
}

static int MovimentoOnda(Info remove, Info *input, Memoria *pai, Memoria **origem, Memoria **raiz, Memoria **maior, int (*funcremover)(Memoria **, int, Memoria *, Memoria **, Memoria **))
{
    int removido = funcremover(raiz, remove.inicio, pai, origem, maior);
    *input = remove;

    return (removido);
}

Memoria *criarMemoria()
{
    return NULL;
}

void freeMemoria(Memoria **raiz)
{
    if (*raiz != NULL)
    {
        freeMemoria(&((*raiz)->left));
        freeMemoria(&((*raiz)->center));

        if ((*raiz)->numKeys == 2)
            freeMemoria(&((*raiz)->right));

        no23free(raiz);
    }
}

int removeMemoriaNaoFolha1(Memoria **origem, Memoria *raiz, Info *info, Memoria *filho1, Memoria *filho2, Memoria **maior)
{
    int remove;
    Memoria *filho, *pai;
    Info *info_filho;

    pai = raiz;
    filho = buscaMaiorFilho(filho1, &pai, &info_filho);

    if (filho->numKeys == 2)
    {
        info = info_filho;
        filho->numKeys = 1;
    }
    else
    {
        filho = buscaMenorFilho(filho2, &pai);
        remove = MovimentoOnda(*(filho->info1), info, pai, origem, &filho, maior, removeMemoria1);
    }

    return (remove);
}

// Não mudei totalmente
int removeMemoriaNaoFolha2(Memoria **origem, Memoria *raiz, Info *info, Memoria *filho1, Memoria *filho2, Memoria **maior)
{
    int remove;
    Memoria *filho, *pai;
    Info *info_filho;

    pai = raiz;

    filho = buscaMenorFilho(filho1, &pai);

    if (filho->numKeys == 2)
    {
        *info = *(filho->info1);
        *(filho->info1) = *(filho->info2);
        filho->numKeys = 1;
    }
    else
    {
        filho = buscaMaiorFilho(filho2, &pai, &info_filho);
        remove = MovimentoOnda(*info_filho, info, pai, origem, &filho, maior, removeMemoria2);
    }

    return remove;
}

int removeMemoria1(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior)
{
    int remove = 0;

    if (*raiz != NULL)
    {
        int info1 = ehInfo1(**raiz, info);
        int info2 = ehInfo2(**raiz, info);

        if (info1 || info2)
        {
            remove = 1;
            if (ehFolha(*raiz))
            {
                if ((*raiz)->numKeys == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->numKeys = 1;
                }
                else
                {
                    if (pai == NULL)
                        no23free(raiz);
                    else
                    {
                        Memoria *auxpai;
                        Info info_pai;
                        if (*raiz == pai->left || (pai->numKeys == 2 && *raiz == pai->center))
                        {
                            auxpai = buscaNoPai(*origem, pai->info1->inicio);

                            if (*raiz == pai->left)
                                info_pai = *(pai->info1);
                            else
                                info_pai = *(pai->info2);

                            remove = MovimentoOnda(info_pai, (*raiz)->info1, auxpai, origem, &pai, maior, removeMemoria1);
                        }
                        else 
                        {
                            auxpai = buscaMaiorNoPai(*origem, (*raiz)->info1->inicio);

                            Memoria *menor_pai;
                            menor_pai = buscaMenorNoPai2Infos(*origem, (*raiz)->info1->inicio);

                            if (auxpai == NULL || (auxpai != pai && menor_pai != NULL))
                            {
                                *maior = pai;
                                (*raiz)->numKeys = 0;
                                remove = -1;
                            }
                            else
                            {
                                if (auxpai->info1->inicio > (*raiz)->info1->inicio)
                                    info_pai = *(auxpai->info1);
                                else
                                    info_pai = *(auxpai->info2);

                                Memoria *avo;
                                avo = buscaNoPai(*origem, info_pai.inicio);
                                remove = MovimentoOnda(info_pai, (*raiz)->info1, avo, origem, &auxpai, maior, removeMemoria1);
                            }
                        }
                    }
                }
            }
            else if (info2)
                remove = removeMemoriaNaoFolha1(origem, *raiz, (*raiz)->info2, (*raiz)->center, (*raiz)->right, maior);
            else if (info1)
                remove = removeMemoriaNaoFolha1(origem, *raiz, (*raiz)->info1, (*raiz)->left, (*raiz)->center, maior);
        }
        else
        {
            if (info < (*raiz)->info1->inicio)
                remove = removeMemoria1(&(*raiz)->left, info, *raiz, origem, maior);
            else if ((*raiz)->numKeys == 1 || info < (*raiz)->info2->inicio)
                remove = removeMemoria1(&(*raiz)->center, info, *raiz, origem, maior);
            else
                remove = removeMemoria1(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return (remove);
}

int removeMemoria2(Memoria **raiz, int info, Memoria *pai, Memoria **origem, Memoria **maior)
{
    int remove = 0;

    if (*raiz != NULL)
    {
        int info1 = ehInfo1(**raiz, info);
        int info2 = ehInfo2(**raiz, info);

        if (info1 || info2)
        {
            remove = 1;
            if (ehFolha(*raiz))
            {
                if ((*raiz)->numKeys == 2)
                {
                    if (info1)
                        (*raiz)->info1 = (*raiz)->info2;

                    (*raiz)->numKeys = 1;
                }
                else
                {
                    if (pai == NULL)
                        no23free(raiz);
                    else
                    {
                        Memoria *auxpai;
                        Info info_pai;
                        if (*raiz == pai->center || (pai->numKeys == 2 && *raiz == pai->right))
                        {
                            auxpai = buscaNoPai(*origem, pai->info1->inicio);

                            if (*raiz == pai->center)
                                info_pai = *(pai->info1);
                            else
                                info_pai = *(pai->info2);

                            remove = MovimentoOnda(info_pai, (*raiz)->info1, auxpai, origem, &pai, maior, removeMemoria2);
                        }
                        else 
                        {
                            auxpai = buscaMenorNoPai(*origem, (*raiz)->info1->inicio);

                            Memoria *menor_pai;
                            menor_pai = buscaMenorNoPai2Infos(*origem, (*raiz)->info1->inicio);

                            Memoria *avo;
                            if (auxpai == NULL || (auxpai != pai && menor_pai != NULL))
                            {
                                remove = -1;
                                *maior = pai;
                            }
                            else
                            {
                                if (auxpai->numKeys == 2 && auxpai->info2->inicio < (*raiz)->info1->inicio)
                                    info_pai = *(auxpai->info2);
                                else
                                    info_pai = *(auxpai->info1);

                                avo = buscaNoPai(*origem, info_pai.inicio);
                                remove = MovimentoOnda(info_pai, (*raiz)->info1, avo, origem, &auxpai, maior, removeMemoria2);
                            }
                        }
                    }
                }
            }
            else if (info2)
                remove = removeMemoriaNaoFolha2(origem, *raiz, (*raiz)->info2, (*raiz)->right, (*raiz)->center, maior);
            else if (info1)
                remove = removeMemoriaNaoFolha2(origem, *raiz, (*raiz)->info1, (*raiz)->center, (*raiz)->left, maior);
        }
        else
        {
            if (info < (*raiz)->info1->inicio)
                remove = removeMemoria2(&(*raiz)->left, info, *raiz, origem, maior);
            else if ((*raiz)->numKeys == 1 || info < (*raiz)->info2->inicio)
                remove = removeMemoria2(&(*raiz)->center, info, *raiz, origem, maior);
            else
                remove = removeMemoria2(&(*raiz)->right, info, *raiz, origem, maior);
        }
    }
    return (remove);
}

int removeMemoria(Memoria **raiz, int info)
{
    Memoria *maior, *posicaoJuntar;
    int remove = removeMemoria1(raiz, info, NULL, raiz, &posicaoJuntar);

    if (remove == -1)
    {
        Info junctionValue = *no23MaiorInfo(posicaoJuntar);
        maior = NULL;
        remove = rebalancearMemoria(raiz, junctionValue.inicio, &maior);

        if (remove == -1)
        {
            Memoria *pai, *posicaoJuntar2;
            Info *input;
            pai = buscaNoPai(*raiz, junctionValue.inicio);

            if (ehInfo1(*posicaoJuntar, junctionValue.inicio))
                input = posicaoJuntar->center->info1;
            else
                input = posicaoJuntar->right->info1;

            remove = MovimentoOnda(junctionValue, input, pai, raiz, &posicaoJuntar, &posicaoJuntar2, removeMemoria2);

            if (remove == -1)
            {
                junctionValue = *(posicaoJuntar2->info1);
                pai = buscaNoPai(*raiz, junctionValue.inicio);
                remove = MovimentoOnda(junctionValue, posicaoJuntar2->left->info1, pai, raiz, &posicaoJuntar2, &posicaoJuntar, removeMemoria1);

                junctionValue = *no23MaiorInfo(posicaoJuntar);
                maior = NULL;
                remove = rebalancearMemoria(raiz, junctionValue.inicio, &maior);
            }
        }

        if (*raiz == NULL)
            *raiz = maior;
    }

    return (remove);
}

int rebalancearMemoria(Memoria **raiz, int info, Memoria **maior)
{
    int balanceou = 0;
    if (*raiz != NULL)
    {
        if (!ehFolha(*raiz))
        {
            if (info < (*raiz)->info1->inicio)
                balanceou = rebalancearMemoria(&((*raiz)->left), info, maior);
            else if ((*raiz)->numKeys == 1 || info < (*raiz)->info2->inicio)
            {
                if ((*raiz)->left->numKeys == 2 && !possivelRemover((*raiz)->center))
                    balanceou = -1;
                else
                    balanceou = rebalancearMemoria(&((*raiz)->center), info, maior);
            }
            else
            {
                if ((*raiz)->center->numKeys == 2 && !possivelRemover((*raiz)->right))
                    balanceou = -1;
                else
                    balanceou = rebalancearMemoria(&((*raiz)->right), info, maior);
            }

            if (balanceou != -1)
            {
                if ((*raiz)->numKeys == 1)
                    balanceou = balancear(raiz, (*raiz)->left, &((*raiz)->center), *(*raiz)->info1, maior);
                else if ((*raiz)->numKeys == 2)
                    balanceou = balancear(raiz, (*raiz)->center, &((*raiz)->right), *(*raiz)->info2, maior);
            }
        }
    }

    return (balanceou);
}