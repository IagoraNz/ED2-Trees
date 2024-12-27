#ifndef Q1_H
#define Q1_H

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

int Arv23PT_remover1(Arv23PT **raiz, Info info, Arv23PT *pai, Arv23PT **origem, Arv23PT **maior);
int movimento_onda(Info saindo, Info *entrada, Arv23PT *pai, Arv23PT **origem, Arv23PT **raiz, Arv23PT **maior);

/*-----------------------------------------------------------------------------------------------------*/

#endif