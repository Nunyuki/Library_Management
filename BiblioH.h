#ifndef BIBLIOH_H
#define BIBLIOH_H

#define M 20

typedef struct livreh{
    int clef;
    int num ;
    char * titre ;
    char * auteur ;
    struct livreh *suivant;
} LivreH;

typedef struct table{
    int nE;
    int m;
    LivreH **T;
} BiblioH;

int fonctionClef(char* auteur);
LivreH* creerlivre(int num,char* titre,char* auteur);
void libererlivre(LivreH* l);
BiblioH* creerbiblio(int m);
void libererbiblio(BiblioH* b);
int fonctionHachage(int cle, int m);

void inserer(BiblioH* b, int num, char* titre, char* auteur);
void afficher_livreH(LivreH *l);
void afficher_biblioH(BiblioH *b);

LivreH *rech_numH(int num, BiblioH *b);
LivreH *rech_titreH(char *titre, BiblioH *b);
BiblioH *rech_auteurH(char *auteur, BiblioH *b);

void supp_livreH(BiblioH *b, int num, char *titre, char *auteur);
void fusion_biblioH(BiblioH *b1, BiblioH *b2);
BiblioH *exemplaireH(BiblioH *b);

#endif