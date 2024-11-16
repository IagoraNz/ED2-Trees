#ifndef Q1_H
#define Q1_H

/*-----------------------------------------------------------------------------------------------------*/

/* ESTRUTAS DAS ÁRVORES E DEMAIS */

typedef struct ingptbst{
    char *palavra;
    struct ingptbst *dir,*esq;
} IngPTBST;

typedef struct info {
    char *palavra;
    IngPTBST *versaoIng;
    int unidade;
} Info;

typedef struct Arv23pt{
    Info info1;
    Info info2;
    struct Arv23pt *cen;
    struct Arv23pt *dir;
    struct Arv23pt *esq;
    int ninfos;
} Arv23PT;

/*-----------------------------------------------------------------------------------------------------*/

/* FUNÇÕES ADICIONAIS */

Arv23PT *criaNo(const Info *informacao, Arv23PT *filhoesq, Arv23PT *filhocen);
Arv23PT *adicionaChave(Arv23PT *no, const Info *informacao, Arv23PT *filho);
Arv23PT *quebraNo(Arv23PT **no, const Info *informacao, Info *promove, Arv23PT **filho);
int ehFolha(const Arv23PT *no);
Arv23PT *inserirArv23(Arv23PT **no, Info *informacao, Info *promove, Arv23PT **pai);
void freeTree(Arv23PT *no);

#endif