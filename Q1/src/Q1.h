#ifndef Q1_H
#define Q1_H

/*-----------------------------------------------------------------------------------------------------*/

/* ESTRUTAS DAS ÁRVORES E DEMAIS */

typedef struct unidades {
    int unidade;
    struct unidades *prox;
} Unidades;

typedef struct infobst {
    char *palavra;
    Unidades *unidades;
} InfoBST;

typedef struct ingptbst{
    InfoBST *info;
    struct ingptbst *dir,*esq;
} IngPTBST;

typedef struct info {
    char *palavra;
    IngPTBST *versaoIng;
} Info;

typedef struct Arv23pt{
    Info info1;
    Info info2;
    struct Arv23pt *cen, *dir, *esq;
    int ninfos;
} Arv23PT;

/*-----------------------------------------------------------------------------------------------------*/

/* FUNÇÕES ADICIONAIS */

void toupperString(char *string);
Arv23PT *criaNo(const Info informacao, Arv23PT *filhoesq, Arv23PT *filhocen);
void adicionaChave(Arv23PT *no, const Info informacao, Arv23PT *filho);
Arv23PT *quebraNo(Arv23PT *no, const Info informacao, Info *promove, Arv23PT **filho);
int ehFolha(const Arv23PT *no);
Arv23PT *inserirArv23(Arv23PT **no, const Info informacao, Info *promove, Arv23PT **pai);
void freeTree(Arv23PT *no);
void inserirunidade(Unidades **unidades, int unidade);
int insereArvBin(IngPTBST **raiz, InfoBST *info);

/*
    Funções Referente ao Item I
*/
void exibirEN(const IngPTBST *raiz);
int percorreLista(const Unidades *uni, int unidade);
void ExibirPalavrasUnidade(Arv23PT *raiz, int unidade);

/*
    Funções Referente ao Item II
*/
void ExibirPalavrasEN(Arv23PT *raiz, char *palavraPTBR);

/*
    Funções Referente ao Item III
*/
int onda(Info saindo, Info *entrada, Arv23PT *pai, Arv23PT **origem, Arv23PT **raiz, Arv23PT **maior, int (*funcao_remover)(Arv23PT **, char *, Arv23PT *, Arv23PT **, Arv23PT **));
int removivel(Arv23PT *raiz);
Arv23PT *buscarMenorFilho(Arv23PT *raiz, Arv23PT **pai);
Info maiorFilho(Arv23PT *raiz);
Arv23PT *buscarMaiorFilho(Arv23PT *raiz, Arv23PT **pai, Info *maiorValor);
void desalocaNo(Arv23PT **no);
void adicionarInfo(Arv23PT *no, Info info, Arv23PT *filhomaior);
Arv23PT *juntaNo(Arv23PT *filho1, Info info, Arv23PT *maior, Arv23PT **raiz);
int ehInfo1(const Arv23PT no, const char *palavra);
int ehInfo2(const Arv23PT no, const char *palavra);
Arv23PT *buscapai(Arv23PT *raiz, char *palavra);
Arv23PT *buscarMaiorPai(Arv23PT *raiz, char *palavra);
Arv23PT *buscarMaiorPai2Infos(Arv23PT *raiz, char *palavra);
Arv23PT *buscarMenorPai(Arv23PT *raiz, char *palavra);
Arv23PT *buscarMenorPai2Infos(Arv23PT *raiz, char *palavra);
void desalocarArv23(Arv23PT **raiz);
int removerNaoFolha1(Arv23PT **origem, Arv23PT *raiz, Info *info, Arv23PT *filho1, Arv23PT *filho2, Arv23PT **maior);
int removerNaoFolha2(Arv23PT **origem, Arv23PT *raiz, Info *info, Arv23PT *filho1, Arv23PT *filho2, Arv23PT **maior);
int Remover1Arv23(Arv23PT **raiz, char *palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior);
int Remover2Arv23(Arv23PT **raiz, char *palavra, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior);
int balanceamento(Arv23PT **raiz, Arv23PT *filho1, Arv23PT **filho2, Info info, Arv23PT **maior);
int Arv23Rebalancear(Arv23PT **raiz, char *palavra, Arv23PT **maior);
int Arv23Remover(Arv23PT **raiz, char *palavra);

/*
    Funções Referente ao Item IV
*/
int ehFolhaBST(const IngPTBST *raiz);
IngPTBST *soumFilho(IngPTBST *raiz);
IngPTBST *menorFilhoEsq(IngPTBST *raiz);
int removerBST(IngPTBST **raiz, const char *palavra);
int buscaBST(IngPTBST *raiz, int unidade);
void removerPTporUnidade(Arv23PT **raiz, char *palavra, int unidade);

#endif