#ifndef Q1_H
#define Q1_H

/*-----------------------------------------------------------------------------------------------------*/

/* ESTRUTAS DAS ÁRVORES E DEMAIS */

typedef struct ingptbst{
    char *palavra;
    int unidade;
    struct ingptbst *dir,*esq;
} IngPTBST;

typedef struct info {
    char *palavra;
    IngPTBST *versaoIng;
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

Arv23PT * criaNo(Info info, Arv23PT * pi, Arv23PT * arv23_pt);
Arv23PT *inserirArv23(Arv23PT **no, Info informacao, Info *promove, Arv23PT **pai);
void freeTree(Arv23PT *no);

#endif