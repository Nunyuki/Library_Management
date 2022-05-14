#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "biblioH.h"

//Recherche de la clé du Livre
int fonctionClef(char* auteur){
  int n = strlen(auteur);
  int s = 0;

  for(int i=0; i<n; i++){
    s+=auteur[i];
  }
  return s;
}

//Création d'un livre
LivreH *creerlivre(int num,char *titre,char *auteur){
  LivreH *l=(LivreH*)(malloc(sizeof(LivreH)));
  if (l==NULL){
    printf("Erreur d'allocation.\n");
    return NULL;
  }

  l->num=num;
  l->titre=strdup(titre);
  l->auteur= strdup(auteur);
  l->clef=fonctionClef(auteur);
  l->suivant=NULL;
  return l;
}

//Libération d'un Livre
void libererlivre(LivreH *l){
  LivreH *tmp;
  while (l){
    free(l->titre);
    free(l->auteur);
    tmp=l->suivant;
    free(l);
    l=tmp;
  }
}

//Création Bibliothèque
BiblioH *creerbiblio(int m){
  BiblioH* b=(BiblioH*)(malloc(sizeof(BiblioH)));
  LivreH **ht=malloc(m*sizeof(LivreH*));

  if(b==NULL){
		printf("Erreur d'allocation");
		return NULL;
	}
  
  b->nE=0;
  b->m=m;
  b->T=ht;

  //Initialisation de la table de hachage
  for(int i=0; i<m; i++) {
    ht[i] = NULL;
  }
  return b;
}

//Libération d'une Bibliothèque
void libererbiblio(BiblioH* b){
  if(b==NULL){
    return;
  } 

  //Libération de tous les Livres contenus dans chaque table de la Bibliothèque
  for(int i=0;i<b->m;i++){
    libererlivre(b->T[i]);
  }

  //Libération de la Bibliothèque
  free(b->T);
  free(b);
}

//Fonction de Hachage
int fonctionHachage(int cle, int m){
  float A = (sqrt(5)-1)/2.0;
  int res=(int)(m*(cle*A-(int)(cle*A)));
  return res;
}

//Insérer un ouvrage avec son numéro, son titre et son auteur en tête de la Bibliothèque
void inserer(BiblioH* b, int num, char* titre, char* auteur){
  LivreH *l=creerlivre(num, titre, auteur);
  
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de Bibliothèque\n");
    libererlivre(l);
    return;
  }

  int nh= fonctionHachage(l->clef,b->m);
  LivreH *ll = (b->T)[nh];

  //Teste l'existence de Livre dans la Bibliothèque
  if((b->T)[nh]==NULL){
    (b->T)[nh]=l;
    (b->nE)++;
    return;
  }

  //Insère le nouvel ouvrage en tête de liste
  l->suivant = ll;
  (b->T)[nh]=l;
  (b->nE)++;
}

//Affichage d'un Livre
void afficher_livreH(LivreH *l){
  //Teste l'existence d'un Livre
  if(l==NULL){
    printf("Pas de livre\n");
    return;
  }   
  printf("%d %s %s\n", l->num, l->titre, l->auteur);
}

//Affichage d'une Bibliothèque
void afficher_biblioH(BiblioH *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return;
  }

  LivreH *l;
  for(int i=0;i<b->m;i++){
    //Teste l'existence de Livre dans la table
    if((b->T)[i]){
      l=(b->T)[i];
      printf("case: %d\n",i);

      //Affichage des Livres de la Bibliothèque
      while(l){
        printf(" -->");
        afficher_livreH(l);
        l=l->suivant;
      }
    }
    else{
      printf("case: %d ----------\n",i);
    }
  }
}

//Recherche d'un ouvrage par son numéro
//Le numéro est unique pour chaque ouvrage
LivreH *rech_numH(int num, BiblioH *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  LivreH *l;
  for(int i=0;i<b->m;i++){
    l=b->T[i];
    //Recherche si le Livre est dans la table i
    //Recherche de l'ouvrage ayant le numéro correspondant
	  while(l){ 
      if(l->num==num){
        //printf("case: %d\n", i);
        return l;
      }
	   l=l->suivant;
    }
	}
  return NULL;
}
//Recherche d'un ouvrage par son titre
//Renvoie le premier ouvrage possédant ce nom
//Un titre un auteur unique
LivreH *rech_titreH(char *titre, BiblioH *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  LivreH *l;
  for(int i=0;i<b->m;i++){
    l=b->T[i];
    //Recherche de l'ouvrage ayant le titre correspondant dans la table i
	  while(l){ 
      if(strcmp(l->titre,titre)==0){
        printf("case: %d\n", i);
        return l;
      }
		  l=l->suivant;
	  }
  }
  return NULL;
}

//Recherche les ouvrages d'un même auteur
BiblioH *rech_auteurH(char *auteur, BiblioH *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  //Recherche de la table où l'auteur est stocké
  int c= fonctionClef(auteur);
  int ht= fonctionHachage(c,M);
  BiblioH *bb=creerbiblio(M);
  LivreH *l=b->T[ht];

  //Recherche tous les ouvrages de l'auteur et l'insère dans sa Bibliothèque
	while(l){ 
    if(strcmp(l->auteur,auteur)==0){
      inserer(bb,l->num,l->titre,l->auteur);
    }
		l=l->suivant;
	}

  if(bb->T[ht]){
    printf("Case de l'auteur: %d\n",ht);
  }
  //Aucun Livre de cet auteur
  else{
    libererbiblio(bb);
    return NULL;
  }
  return bb;
}

//Suppression d'un Livre dans la Bibliothèque
void supp_livreH(BiblioH *b, int num, char *titre, char *auteur){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return ;
  }

  //Recherche de la table où l'auteur est stocké
  int c= fonctionClef(auteur);
  int ht= fonctionHachage(c,M);
  LivreH *l=b->T[ht];

  //Teste l'existence de Livre dans la table
  if(l==NULL){
    printf("Pas de Livre dans la Bibliothèque\n");
    return;
  }
  
  //Si l'ouvrage à supprimer est en première position
  if((l->num==num) && (strcmp(l->titre,titre)==0) && (strcmp(l->auteur,auteur)==0)){
    b->T[ht] = b->T[ht]->suivant;
    free(l->titre);
    free(l->auteur);
    free(l);
    return;
  }

  //Si l'ouvrage à supprimer n'est pas en première position
  LivreH *tmp;
	while(l){ 
    tmp=l->suivant;

    //L'ouvrage à suprrimer n'existe pas
    if(tmp==NULL){
      printf("L'ouvrage n'existe pas dans la Bibliothèque\n");
      libererlivre(tmp);
      return;
    }

    //Ouvrage à supprimer trouver
    if((tmp->num==num) && (strcmp(tmp->titre,titre)==0) && (strcmp(tmp->auteur,auteur)==0)){
      l->suivant=l->suivant->suivant;
      free(tmp->titre);
      free(tmp->auteur);
      free(tmp);
      return;
    }
		l=l->suivant;
	}
}

//Fusion de deux Bibliothèques
void fusion_biblioH(BiblioH *b1, BiblioH *b2){
  //Teste l'existence de la Bibliothèque 2
  if(b2==NULL){
    libererbiblio(b2);
     return;
  }

  //Teste l'existence de la Bibliothèque 1
  if(b1==NULL){
    printf("La fusion est impossible\n");
    return;
  }

  int j=0;
  LivreH *l1;
  LivreH *l2;

  //Fusion des 2 Bibliothèques
  for(int i=0;i<b1->m;i++){
    l1=(b1->T)[i];
    l2=(b2->T)[i];

    while(l1){
      l1->num=j;
      j++;
      l1=l1->suivant;
    }
    while(l2){
      inserer(b1,j,l2->titre,l2->auteur);
      l2=l2->suivant;
      j++;
    }
  }  
  libererbiblio(b2);
}

//Recherche des différents ouvrages possèdants plusieurs ouvrages
BiblioH* exemplaireH(BiblioH* b) {
  //Teste l'existence de la Bibliothèque  
  if(b==NULL){
    //printf("Pas de bibliothèque\n");
    return NULL;
  }
  
  BiblioH* bb = creerbiblio(b->m);
  for(int i=0; i<b->m; i++) {
    LivreH* l1 = b->T[i];
   
    while(l1) {
      LivreH* l2 = b->T[i];
      int k = 1;
      
      //Recherche dans la nouvelle Bibliothèque si le numéro regardé est dedans
      if ( rech_numH(l1->num,bb) == NULL ) { 
        while(l2) {

        if( (strcmp(l1->titre,l2->titre)==0) && (l1->num != l2->num) ) {
          inserer(bb,l2->num,l2->titre,l2->auteur);

          //insérer l'ouvrage qui a des exemplaires
          if(k) {
            inserer(bb,l1->num,l1->titre,l1->auteur);
            k = 0;
          }
        } 
        l2 = l2->suivant;
      }
   }
  l1 = l1->suivant;
  }
}

  //Vérifie si bb contient des ouvrages
  int n=0;
  for(int j=0;j<b->m;j++){
      if(b->T[j]){
    n++;
    }
  }

  if(n==0){
    libererbiblio(bb);
    return NULL;
  }
  return bb;
}