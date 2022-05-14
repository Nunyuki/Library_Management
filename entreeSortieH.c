#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "entreeSortieH.h"
#include "biblioH.h"

BiblioH* charger_n_entreesH(char* nomfic, int n){
  // Prend les n premières lignes d'un fichier et les stocke dans une bibliothèque

	FILE *f = fopen(nomfic,"r");
	if(f==NULL){
		return NULL;
	}
	
	char buffer[256];
	int num;
	char titre[256];
	char auteur[256];
	
	int i=0;
	BiblioH *b=creerbiblio(M);

	while(i<n && fgets(buffer,256,f)){
		sscanf(buffer, "%d %s %s\n",&num,titre,auteur);
		inserer(b,num,titre,auteur);
		i++;
	}

	fclose(f);
	return b;
}

void enregistrer_biblioH(BiblioH *b, char* nomfic){
	FILE *f=fopen(nomfic,"w");
	if(f==NULL){
		return;
	}

  if (b==NULL){
     return;
  }
 
  LivreH *l;
  for(int i=0;i<b->m;i++){ 
    l=b->T[i];
    if (l){
      while(l){
		    fprintf(f,"%d %s %s\n",l->num,l->titre,l->auteur);
		    l=l->suivant;
	    }
    }
  }

	fclose(f);
}