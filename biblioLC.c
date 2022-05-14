#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioLC.h"
#include <assert.h>

//Création de Livre
Livre *creer_livre(int num, char *titre, char *auteur){
  Livre *l=(Livre*)(malloc(sizeof(Livre)));
	if(l==NULL){
		printf("Erreur d'allocation");
		return NULL;
	}
	
  l->num=num;
  l->titre=strdup(titre);
  l->auteur= strdup(auteur);
  l->suiv=NULL;
  return l;
}

//Libération d'un Livre
void liberer_livre(Livre *l){
  Livre *tmp;
  while(l){
    free(l->titre);
    free(l->auteur);
    tmp=l->suiv;
    free(l);
    l=tmp;
  }
}

//Création Bibliothèque
Biblio *creer_biblio(){
  Biblio *b=(Biblio*)(malloc(sizeof(Biblio)));
  if(b==NULL){
		printf("Erreur d'allocation");
		return NULL;
	}
  b->L=NULL;
  return b;
}

//Libération d'une Bibliothèque
void liberer_biblio(Biblio* b){
  if(b==NULL){
    return;
  }
  //Libération de tous les Livres contenus dans la B
  liberer_livre(b->L);

  //Libération de la Bibliothèque
  free(b);
}

//Insérer un ouvrage avec son numéro, son titre et son auteur en tête de la Bibliothèque
void inserer_en_tete(Biblio* b, int num, char* titre, char* auteur){
  Livre* l=creer_livre(num,titre,auteur);

  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de Bibliothèque\n");
    liberer_livre(l);
    return;
  }

  //Teste l'existence de Livre dans la Bibliothèque
  if(b->L==NULL){
    b->L=l;
    return;
  }

  //Insère le nouvel ouvrage en tête de liste
  l->suiv=b->L;
  b->L=l;
}

//QUESTION 6

//Affichage d'un Livre
void afficher_livre(Livre *l){
  //Teste l'existence d'un Livre
  if(l==NULL){
    printf("Pas de livre\n");
    return;
  }
    printf("%d %s %s\n", l->num, l->titre, l->auteur);
}

//Affichage d'une Bibliothèque
void afficher_biblio(Biblio *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return;
  }

  Livre *l=b->L;
  //Teste l'existence de Livre dans la Bibliothèque
  if(l==NULL){
    //printf("Pas de Livre dans la Bibliothèque\n");
    return;
  }

  //Affichage des Livres de la Bibliothèque
  while(l){
    afficher_livre(l);
    l=l->suiv;
  }
}

//Recherche d'un ouvrage par son numéro
//Le numéro est unique pour chaque ouvrage
Livre *rech_num(int num, Biblio *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  Livre *l=b->L;
  //Teste l'existence de Livre dans la Bibliothèque
  if(l==NULL){
    //printf("Pas de Livre dans la Bibliothèque\n");
    return NULL;
  }

  //Recherche de l'ouvrage ayant le numéro correspondant
	while(l){ 
    if(l->num==num){
      return l;
    }
		l=l->suiv;
	}
  //printf("Le Livre n'existe pas.\n");
  return NULL;
}

//Recherche d'un ouvrage par son titre
//Renvoie le premier ouvrage possédant ce nom
Livre *rech_titre(char *titre, Biblio *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  Livre *l=b->L;
  //Teste l'existence de Livre dans la Bibliothèque
  if(l==NULL){
    printf("Pas de Livre dans la Bibliothèque\n");
    return NULL;
  }

  //Recherche de l'ouvrage ayant le titre correspondant
	while(l){ 
    if(strcmp(l->titre,titre)==0){
      return l;
    }
		l=l->suiv;
	}
  printf("Le Livre n'existe pas.\n");
  return NULL;
}

//Recherche les ouvrages d'un même auteur
Biblio *rech_auteur(char *auteur, Biblio *b){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  Livre *l=b->L;
  //Teste l'existence de Livre dans la Bibliothèque
  if(l==NULL){
    printf("Pas de Livre dans la Bibliothèque\n");
    return NULL;
  }
  
  //Création d'une Bibliothèque dédiée à l'auteur
  Biblio *bb=creer_biblio();
  //Recherche tous les ouvrages de l'auteur et l'insère dans sa Bibliothèque
	while(l){ 
    if(strcmp(l->auteur,auteur)==0){
      inserer_en_tete(bb,l->num,l->titre,l->auteur);
    }
		l=l->suiv;
	}
  if(bb->L==NULL){
    printf("Aucun ouvrage de cet auteur\n");
    liberer_biblio(bb);
    return NULL;
  }
  return bb;
}

//Suppression d'un Livre dans la Bibliothèque
void supp_livre(Biblio *b, int num, char *titre, char *auteur){
  //Teste l'existence de la Bibliothèque
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return;
  }

  Livre *l=b->L;
  //Teste l'existence de Livre dans la Bibliothèque
  if(l==NULL){
    printf("Pas de Livre dans la Bibliothèque\n");
    return;
  }

  //Si l'ouvrage à supprimer est en première position
  if((l->num==num) && (strcmp(l->titre,titre)==0) && (strcmp(l->auteur,auteur)==0)){
    b->L = b->L->suiv;  
    free(l->titre);
    free(l->auteur);
    free(l);
    return;
  }

  //Si l'ouvrage à supprimer n'est pas en première position
  Livre *tmp;
	while(l){ 
    tmp=l->suiv;

    //L'ouvrage à suprrimer n'existe pas
    if(tmp==NULL){
      printf("L'ouvrage n'existe pas dans la Bibliothèque\n");
      liberer_livre(tmp);
      return;
    }

    //Ouvrage à supprimer trouver
    if((tmp->num==num) && (strcmp(tmp->titre,titre)==0) && (strcmp(tmp->auteur,auteur)==0)){
      l->suiv=l->suiv->suiv;
      free(tmp->titre);
      free(tmp->auteur);
      free(tmp);
      return;
    }
		l=l->suiv;
	}
}

//Fusion de deux Bibliothèques
void fusion_biblio(Biblio *b1, Biblio *b2){
    //Teste l'existence de la Bibliothèque 2
    if(b2==NULL){
        liberer_biblio(b2);
        return;
    }

    //Teste l'existence de la Bibliothèque 1
    if(b1==NULL){
        printf("La fusion est impossible\n");
        return;
    }

    int i=0;
    Livre *l1 = b1->L;
    Livre *l2 = b2->L;
  
      //Fusion des 2 Bibliothèques
      while(l1){
        l1->num=i;
        i++;
        l1=l1->suiv;
      }
      while(l2){
        inserer_en_tete(b1,i,l2->titre,l2->auteur);
        l2=l2->suiv;
        i++;
      }
      liberer_biblio(b2);

}

//Recherche des différents ouvrages possèdants plusieurs ouvrages
Biblio *exemplaire(Biblio *b){
  //Teste l'existence de la Bibliothèque  
  if(b==NULL){
    printf("Pas de bibliothèque\n");
    return NULL;
  }

  
  Livre *l1 = b->L;

  //Teste l'existence de Livre dans la Bibliothèque
  if(l1==NULL){
    printf("Pas de Livre dans la Bibliothèque\n");
    return NULL;
  }
  
  Livre *l2 ;
  Biblio *bb = creer_biblio();

  //Insertion des Livres ayant plusieurs exemplaires
  //Ne retire pas les Livres apparaissant plusieurs fois
  while (l1){
    l2 = l1->suiv;
    while (l2){
      if ((strcmp(l1->titre, l2->titre) == 0) && (strcmp(l1->auteur, l2->auteur) == 0)){
        inserer_en_tete(bb, l1->num, l1->titre, l1->auteur);
        inserer_en_tete(bb, l2->num, l2->titre, l2->auteur);
      }
      l2 = l2->suiv;
    }
    l1 = l1->suiv;
  }
  
  Biblio *bres=creer_biblio();
  Livre *l3 = bb->L;

  //Retire les Livres apparaissant plusieurs fois
  while(l3){
    if(rech_num(l3->num,bres)==NULL){
      inserer_en_tete(bres,l3->num,l3->titre,l3->auteur);
    }
    l3=l3->suiv;
  }
  liberer_biblio(bb);
  return bres;
}