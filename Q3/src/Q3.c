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

Memoria *quebraNo(Memoria **no, const Info *info, Info *promove, Memoria **filho)
{
    Memoria *maior;

    if (info->inicio > (*no)->info1->inicio)
    {
        *promove = *(*no)->info2;
        if (filho)
            maior = criarNo(info, (*no)->right, *filho);
        else
            maior = criarNo(info, (*no)->right, NULL);
    }
    else if (info->inicio > (*no)->info2->inicio)
    {
        *promove = *info;
        if (filho)
            maior = criarNo((*no)->info2, *filho, (*no)->right);
        else
            maior = criarNo((*no)->info2, NULL, (*no)->right);
    }
    else
    {
        *promove = *(*no)->info1;

        maior = criarNo((*no)->info2, (*no)->center, (*no)->right);

        if ((*no)->info1 == NULL)
        {
            (*no)->info1 = (Info *)malloc(sizeof(Info));
            if ((*no)->info1 == NULL)
                printf("Erro ao alocar memória para info1.\n");
        }

        *(*no)->info1 = *info;

        if (filho)
            (*no)->center = *filho;
        else
            (*no)->center = NULL;
    }

    (*no)->numKeys = 1;

    return (maior);
}

// Memory *insertTree23(Memory **node, Info *info, Info *promote, Memory **father)
Memoria *insereArv23(Memoria **no, Info *info, Info *promove, Memoria **noPai)
{
    Info promove1;
    Memoria *maiorNo = NULL;
    if (*no == NULL)
        *no = criarNo(info, NULL, NULL);

    else
    {
        if (ehFolha(*no))
        { 
            if ((*no)->numKeys == 1)
                *no = addKey(*no, info, NULL);
            else
            {
                maiorNo = quebraNo(no, info, promove, NULL);
                if (noPai == NULL)
                { 
                    *no = criarNo(promove, *no, maiorNo);
                    maiorNo = NULL;
                }
            }
        }
        else
        { 
            if (info->inicio < (*no)->info1->inicio)
                maiorNo = insereArv23(&((*no)->left), info, promove, no);
            else if ((*no)->numKeys == 1 || info->inicio < (*no)->info2->inicio)
                maiorNo = insereArv23(&((*no)->center), info, promove, no);
            else
                maiorNo = insereArv23(&((*no)->right), info, promove, no);
            if (maiorNo)
            {
                if ((*no)->numKeys == 1)
                {
                    *no = addKey(*no, promove, maiorNo);
                    maiorNo = NULL;
                }
                else
                {
                    maiorNo = quebraNo(no, promove, &promove1, &maiorNo);
                    if (noPai == NULL)
                    {
                        *no = criarNo(&promove1, *no, maiorNo);
                        maiorNo = NULL;
                    }
                }
            }
        }
    }

    return (maiorNo);
}

Memoria *buscaEspaco(Memoria *raiz, int quantEspaco)
{
    Memoria *resultado = NULL;

    if (raiz != NULL)
    {
        for (int i = 0; i < raiz->numKeys; i++)
        {
            Info *infoAtual = (i == 0) ? raiz->info1 : raiz->info2;

            if (infoAtual->status == LIVRE)
            {
                int espacoLivre = infoAtual->fim - infoAtual->inicio + 1;

                if (espacoLivre >= quantEspaco)
                    resultado = raiz;
            }
        }

        if (resultado == NULL)
        {
            resultado = buscaEspaco(raiz->left, quantEspaco);

            if (resultado == NULL)
                resultado = buscaEspaco(raiz->center, quantEspaco);

            if (resultado == NULL && raiz->numKeys == 2)
                resultado = buscaEspaco(raiz->right, quantEspaco);
        }
    }

    return (resultado);
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

int alocaEspaco(Memoria **raiz, int quantEspaco, int *return_inicio)
{
    Memoria *no = buscaEspaco(*raiz, quantEspaco);
    int tamEspaco = 0;

    if (no)
    {
        Info *infoDestino = NULL;
        int espacoLivre = 0;

        if (no->info1 && no->info1->status == LIVRE)
        {
            espacoLivre = no->info1->fim - no->info1->inicio + 1;
            if (espacoLivre >= quantEspaco)
                infoDestino = no->info1;
        }

        if (!infoDestino && no->info2 && no->info2->status == LIVRE)
        {
            espacoLivre = no->info2->fim - no->info2->inicio + 1;
            if (espacoLivre >= quantEspaco)
                infoDestino = no->info2;
        }

        if (infoDestino)
        {
            int novoEndOcupado = infoDestino->inicio + quantEspaco - 1;

            Info *novaInfoOcupada = criarInfo(infoDestino->inicio, novoEndOcupado, OCUPADO);
            *return_inicio = infoDestino->inicio;
            tamEspaco = espacoLivre;

            if (infoDestino == no->info1)
                no->info1 = novaInfoOcupada;
            else if (infoDestino == no->info2)
                no->info2 = novaInfoOcupada;

            if (espacoLivre > quantEspaco)
            {
                int restoInicio = novoEndOcupado + 1;
                int restoFim = infoDestino->fim;
                Info *remainingInfo = criarInfo(restoInicio, restoFim, LIVRE);
                Info promove;
                insereArv23(raiz, remainingInfo, &promove, NULL);
            }

            printf("Espaço alocado com sucesso.\n");
        }
        else
            printf("Espaço insuficiente na memória\n");
    }
    else
        printf("Espaço insuficiente na memória\n");

    return (tamEspaco);
}

void freeEspaco(Memoria *memoria, int inicio, int fim)
{
    if (memoria != NULL)
    {
        if (memoria->info1 != NULL && memoria->info1->inicio == inicio && memoria->info1->fim == fim)
            memoria->info1->status = 1;

        if (memoria->info2 != NULL && memoria->info2->inicio == inicio && memoria->info2->fim == fim)
            memoria->info2->status = 1;

        freeEspaco(memoria->left, inicio, fim);
        freeEspaco(memoria->center, inicio, fim);
        freeEspaco(memoria->right, inicio, fim);
    }
}

void mergeNosInicio(Memoria **raiz, int *return_inicio)
{
    if (raiz != NULL)
    {
        Memoria *atual = *raiz;

        if (atual->info1 && atual->info2)
        {
            if (atual->info1->status == atual->info2->status &&
                atual->info1->fim + 1 == atual->info2->inicio)
            {
                atual->info1->fim = atual->info2->fim;
                atual->numKeys--;

                *return_inicio = atual->info2->inicio;
            }
        }

        if (atual->left && atual->info1 &&
            atual->left->info2 &&
            atual->left->info2->status == atual->info1->status &&
            atual->left->info2->fim + 1 == atual->info1->inicio)
        {
            atual->left->info2->fim = atual->info1->fim;
            atual->numKeys--;

            *return_inicio = atual->info1->inicio;
        }

        if (atual->right && atual->info2 &&
            atual->right->info1 &&
            atual->info2->status == atual->right->info1->status &&
            atual->info2->fim + 1 == atual->right->info1->inicio)
        {
            atual->info2->fim = atual->right->info1->fim;
            atual->right->numKeys--;

            *return_inicio = atual->info2->inicio;
        }

        if (atual->left)
            mergeNosInicio(&atual->left, return_inicio);
        else if (atual->center)
            mergeNosInicio(&atual->center, return_inicio);
        else if (atual->right)
            mergeNosInicio(&atual->right, return_inicio);
    }
}

// ============================
// HARD CODING TÁ ERRADO NÃO PEGUEM
void mergeNosMeio(Memoria **raiz, int *aux1, int *aux2)
{
    if (raiz != NULL && *raiz != NULL)
    {
        Memoria *atual = *raiz;

        if (atual->info1 && atual->info2)
        {
            if (atual->info1->status == atual->info2->status &&
                atual->info1->fim + 1 == atual->info2->inicio)
            {
                *aux1 = atual->info1->inicio;
                *aux2 = atual->info2->inicio;
            }
            if (atual->info1->fim < atual->info2->fim && atual->info1->status == atual->info2->status)
                atual->info1->fim = atual->info2->fim;
        }

        if (atual->left)
            mergeNosMeio(&atual->left, aux1, aux2);

        if (atual->center)
            mergeNosMeio(&atual->center, aux1, aux2);

        if (atual->right)
            mergeNosMeio(&atual->right, aux1, aux2);
    }
}

void mergeNosFim(Memoria **raiz, int *return_inicio)
{
    if (raiz != NULL)
    {
        Memoria *atual = *raiz;

        if (atual->info2 && atual->right)
        {
            if (atual->info2->status == atual->right->info1->status &&
                atual->info2->fim + 1 == atual->right->info1->inicio)
            {
                atual->info2->fim = atual->right->info1->fim;
                atual->right->numKeys--;
                *return_inicio = atual->right->info1->inicio;
            }
        }

        if (atual->left && atual->info1)
        {
            if (atual->left->info2->status == atual->info1->status &&
                atual->left->info2->fim + 1 == atual->info1->inicio)
            {
                atual->left->info2->fim = atual->info1->fim;
                atual->numKeys--;

                *return_inicio = atual->info1->inicio;
            }
        }

        if (atual->left)
            mergeNosFim(&atual->left, return_inicio);
        else if (atual->center)
            mergeNosFim(&atual->center, return_inicio);
        else if (atual->right)
            mergeNosFim(&atual->right, return_inicio);
    }
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

static int ehInfo1(Memoria no, int info)
{
    return (info == no.info1->inicio);
}

static int ehInfo2(Memoria no, int info)
{
    return (no.numKeys == 2 && info == no.info2->inicio);
}

Memoria *criarNoRMV(Info info, Memoria *filhoEsq, Memoria *filhoCen)
{
    Memoria *no;
    no = alocarNo23();

    no->info1 = (Info *)malloc(sizeof(Info));
    if (no->info1 == NULL)
    {
        fprintf(stderr, "Erro ao alocar memória para info1\n");
        exit(EXIT_FAILURE);
    }

    *(no->info1) = info;

    no->left = filhoEsq;
    no->center = filhoCen;
    no->right = NULL;
    no->numKeys = 1;

    return (no);
}

Memoria *quebraNoRMV(Memoria *no, Info info, Info *promove, Memoria *maiorFilho)
{
    Memoria *maior;

    if (info.inicio > no->info2->inicio)
    {
        *promove = *(no->info2);
        maior = criarNoRMV(info, no->right, maiorFilho);
    }
    else if (info.inicio > no->info1->inicio)
    {
        *promove = info;
        maior = criarNoRMV(*(no->info2), maiorFilho, no->right);
    }
    else
    {
        *promove = *(no->info1);
        maior = criarNoRMV(*(no->info2), no->center, no->right);

        *(no->info1) = info;

        no->center = maiorFilho;
    }

    no->numKeys = 1;

    return (maior);
}

static Info no23MaiorInfo(Memoria *raiz)
{
    return (raiz->numKeys == 2 ? *(raiz->info2) : *(raiz->info1));
}

static Memoria *buscaMenorFilho(Memoria *raiz, Memoria **pai)
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

static Memoria *buscaMaiorFilho(Memoria *raiz, Memoria **pai, Info *maiorInfo)
{
    Memoria *filho;
    filho = raiz;

    while (!ehFolha(filho))
    {
        *pai = filho;
        if (filho->numKeys == 1)
            filho = filho->center;
        else
            filho = filho->right;
    }

    if (filho != NULL)
        *maiorInfo = no23MaiorInfo(filho);

    return (filho);
}

static Memoria *buscaNoPai(Memoria *raiz, int info)
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

static Memoria *buscaMaiorNoPai(Memoria *raiz, int info)
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

static Memoria *buscaMenorNoPai(Memoria *raiz, int info)
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

Memoria *insereMemoria(Memoria **raiz, Info info, Memoria *pai, Info *promove)
{
    Memoria *maior;
    maior = NULL;

    if (*raiz == NULL)
        *raiz = criarNoRMV(info, NULL, NULL);
    else
    {
        if (ehFolha(*raiz))
        {
            if ((*raiz)->numKeys == 1)
                noAddInfo(*raiz, info, NULL);
            else
            {
                maior = quebraNoRMV(*raiz, info, promove, NULL);
                if (pai == NULL)
                {
                    *raiz = criarNoRMV(*promove, *raiz, maior);
                    maior = NULL;
                }
            }
        }
        else
        {
            if (info.inicio < (*raiz)->info1->inicio)
                maior = insereMemoria(&((*raiz)->left), info, *raiz, promove);
            else if ((*raiz)->numKeys == 1 || info.inicio < (*raiz)->info2->inicio)
                maior = insereMemoria(&((*raiz)->center), info, *raiz, promove);
            else
                maior = insereMemoria(&((*raiz)->right), info, *raiz, promove);

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
                    maior = quebraNoRMV(*raiz, *promove, &promove_aux, maior);
                    *promove = promove_aux;
                    if (pai == NULL)
                    {
                        *raiz = criarNoRMV(promove_aux, *raiz, maior);
                        maior = NULL;
                    }
                }
            }
        }
    }

    return (maior);
}

int removeMemoriaNaoFolha1(Memoria **origem, Memoria *raiz, Info *info, Memoria *filho1, Memoria *filho2, Memoria **maior)
{
    int remove;
    Memoria *filho, *pai;
    Info info_filho;

    pai = raiz;

    filho = buscaMaiorFilho(filho1, &pai, &info_filho);

    if (filho->numKeys == 2)
    {
        *info = info_filho;
        filho->numKeys = 1;
    }
    else
    {
        filho = buscaMenorFilho(filho2, &pai);
        remove = MovimentoOnda(*(filho->info1), info, pai, origem, &filho, maior, removeMemoria1);
    }

    return (remove);
}

int removeMemoriaNaoFolha2(Memoria **origem, Memoria *raiz, Info *info, Memoria *filho1, Memoria *filho2, Memoria **maior)
{
    int remove;
    Memoria *filho, *pai;
    Info info_filho;

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
        remove = MovimentoOnda(info_filho, info, pai, origem, &filho, maior, removeMemoria2);
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
        Info valorJuntar = no23MaiorInfo(posicaoJuntar); 
        maior = NULL;
        remove = rebalancearMemoria(raiz, valorJuntar.inicio, &maior);

        if (remove == -1)
        {
            Memoria *pai, *posicaoJuntar2;
            Info *input;
            pai = buscaNoPai(*raiz, valorJuntar.inicio);

            if (ehInfo1(*posicaoJuntar, valorJuntar.inicio))
                input = posicaoJuntar->center->info1;
            else
                input = posicaoJuntar->right->info1;

            remove = MovimentoOnda(valorJuntar, input, pai, raiz, &posicaoJuntar, &posicaoJuntar2, removeMemoria2);

            if (remove == -1)
            {
                valorJuntar = *(posicaoJuntar2->info1);
                pai = buscaNoPai(*raiz, valorJuntar.inicio);
                remove = MovimentoOnda(valorJuntar, posicaoJuntar2->left->info1, pai, raiz, &posicaoJuntar2, &posicaoJuntar, removeMemoria1);

                valorJuntar = no23MaiorInfo(posicaoJuntar);
                maior = NULL;
                remove = rebalancearMemoria(raiz, valorJuntar.inicio, &maior);
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