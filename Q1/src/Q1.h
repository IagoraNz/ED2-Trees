#ifndef Q1_H
#define Q1_H

/*-----------------------------------------------------------------------------------------------------*/

/* ESTRUTAS DAS ÁRVORES E DEMAIS */

typedef struct arv23pt { // Árvore 2-3 para as palavras em português
    char *word;
    char *word2;
    struct arv23pt *esq;
    struct arv23pt *meio;
    struct arv23pt *dir;
    int ninfos;
} Arv23pt;

typedef struct eng {
    char *word; // Palavra em inglês
    Arv23pt *equipt; // Palavras equivalentes em português
    int unidade; // Unidade a qual a palavra pertence
} Eng;

typedef struct engbst { // Árvore binária de busca para as palavras em inglês
    Eng *info;
    struct engbst *esq;
    struct engbst *dir;
} EngBST;

/*-----------------------------------------------------------------------------------------------------*/

#endif