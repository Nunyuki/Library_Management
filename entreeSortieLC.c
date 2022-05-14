#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "entreeSortieLC.h"
#include "biblioLC.h"

// Prend les n premières lignes d'un fichier et les stocke dans une bibliothèque
Biblio* charger_n_entrees(char* nomfic, int n){
	FILE *f = fopen(nomfic,"r");
  //Teste l'existence du fichier
	if(f==NULL){
		return NULL;
	}

  //Variable où l'on stock les numéros, titres et auteurs lus
	char buffer[256];
	int num;
	char titre[256];
	char auteur[256];
	
	int i=0;
	Biblio *b=creer_biblio();

  //Charge n lignes
  //Ou s'arrête lorsque il n'y a plus d'ouvrage dans le fichier
	while(i<n && fgets(buffer,256,f)){
		sscanf(buffer, "%d %s %s\n",&num,titre,auteur);
		inserer_en_tete(b,num,titre,auteur);
		i++;
	}
	fclose(f);
	return b;
}

//Ecriture d'une Bibliothèque dans un fichier
void enregistrer_biblio(Biblio *b, char* nomfic){
	FILE *f=fopen(nomfic,"w");
  //Teste l'existence du fichier
	if(f==NULL){
		return;
	}
  
  //Teste l'existence de la Bibliothèque
  if (b==NULL){
     return;
  }

  //Ecriture de la Bibliothèque dans un fichier
	Livre *l=b->L;
	while(l){
		fprintf(f,"%d %s %s\n",l->num,l->titre,l->auteur);
		l=l->suiv;
	}

	fclose(f);
}