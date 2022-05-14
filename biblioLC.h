#ifndef BIBLIOLC_H
#define BIBLIOLC_H

typedef struct livre {
  int num ;
  char * titre ;
  char * auteur ;
  struct livre * suiv ;
} Livre ;

typedef struct { /* Tete fictive */
  Livre * L ; /* Premier element */
} Biblio ;

Livre* creer_livre(int num, char* titre, char* auteur);
void liberer_livre(Livre* l);
Biblio* creer_biblio();
void liberer_biblio(Biblio* b);
void inserer_en_tete(Biblio* b,int num,char* titre,char* auteur);

// Question 1.6
void afficher_livre(Livre *l);
void afficher_biblio(Biblio *b);

Livre *rech_num(int num, Biblio *b);
Livre *rech_titre(char *titre, Biblio *b);
Biblio *rech_auteur(char *auteur, Biblio *b); 

void supp_livre(Biblio *b, int num, char *titre, char *auteur);
void fusion_biblio(Biblio *b1, Biblio *b2);
Biblio *exemplaire(Biblio *b);

#endif 