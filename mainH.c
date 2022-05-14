#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioH.h"
#include "entreeSortieH.h"


void menuH(){
  printf("*------------------------- Menu -----------------------------*\n");
  printf("0- Sortie du programme\n");
  printf("1- Affichage\n");
  printf("2- Insérer ouvrage\n");
  printf("3- Rechercher ouvrage par numéro\n");
  printf("4- Rechercher ouvrage par son titre\n");
  printf("5- Rechercher les ouvrages d'un même auteur\n");
  printf("6- Supprimer ouvrage\n");
  printf("7- Rechercher tous les ouvrages avec plusieurs exemplaires\n");
  printf("8- Fusionner deux bibliothèques\n");
  printf("9- Stocker la bibliothèque dans un fichier\n");
  printf("*-------------------------------------------------------------*\n");
}

int main (int argc, char** argv){
  BiblioH* b=charger_n_entreesH("Biblio.txt", 10);
  enregistrer_biblioH(b,"b.txt");

  int rep;
  char ligne[256];
  int num, n1, n2;
  char titre[256];
  char auteur[256];
  char f1[256];
  char f2[256];
  char nomb[256];
  LivreH *l;
  BiblioH *bb;

  do{
    menuH();
    printf("Que souhaitez-vous faire?\n");
    fgets(ligne, 256, stdin);
    sscanf(ligne, "%d\n", &rep);
    printf("\n");


    switch (rep){

      case 1:
        printf("Affichage de la bibliothèque :\n");
        afficher_biblioH(b);
        printf("\n");
        break;

      case 2:
        printf("Veuillez saisir le numero, le titre et l'auteur de l'ouvrage.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, " %d %s %s\n", &num, titre, auteur)==3){
          inserer(b,num,titre,auteur);
          printf("Ouvrage inséré.\n");
          printf("\n");
        } 
        else{
          printf("Erreur format\n");
          printf("\n");
        }
        break;

      case 3:
        printf("Veuillez saisir le numero de l'ouvrage.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, " %d\n", &num)==1){
          l=rech_numH(num, b);

          if (l==NULL){
            printf("L'ouvrage recherche n'existe pas.\n\n");
          } 
          else{
            printf("Ouvrage trouvé. Voici l'ouvrage correspondant. \n");
            afficher_livreH(l);
            printf("\n");
          } 
        }
        else{
          printf("Erreur format\n");
          printf("\n");
        }
        break;

      case 4: 
        printf("Veuillez saisir le titre de l'ouvrage.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, " %s\n", titre)==1){
          l=rech_titreH(titre, b);

          if(l==NULL){
            printf("L'ouvrage recherche n'existe pas.\n\n");
          }
          else{
            printf("Ouvrage trouvé. Voici l'ouvrage correspondant.\n");
            afficher_livreH(l);
            printf("\n");
          }    
        } 
        else{
          printf("Erreur format\n\n");
        }
        break;

      case 5: 
        printf("Veuillez saisir l'auteur des ouvrages.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, " %s\n", auteur)==1){
          bb=rech_auteurH(auteur, b);
          printf("Ouvrages trouvés.\n");
          printf("Voici une liste des ouvrages écrits par l'auteur %s : \n", auteur);
          afficher_biblioH(bb);
          printf("\n");
        }
        else{
          printf("Erreur format\n\n");
        }
        break;

      case 6:
        printf("Veuillez saisir l'ouvrage à supprimer.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, " %d %s %s\n", &num, titre, auteur)==3){
          supp_livreH(b, num, titre, auteur);
          printf("Ouvrage abandonné par l'utilisateur.\n\n");
        }
        else{
          printf("Erreur format\n\n");
        }
        break;

      case 7:
        printf("Voici une liste de tous les ouvrages avec plusieurs exemplaires de la bibliothèque.\n");
        bb=exemplaireH(b);
        afficher_biblioH(bb);
        printf("\n");
        break;

      case 8:
        printf("Vous souhaitez fusionner deux bibliothèques.\n");
        printf("Veulliez saisir le nom des fichiers dans lesquels sont stockés vos bibliothèques.\n");
        fgets(ligne,256,stdin);

        if(sscanf(ligne, "%s %s\n", f1, f2)==2){
          printf("Combien d'ouvrages souhaitez vous stockés dans chaque bibliothèque? Veuillez saisir deux nombres.\n");
          fgets(ligne, 256, stdin);
   
          if (sscanf(ligne, "%d %d\n", &n1,&n2)==2){
            BiblioH *b1= charger_n_entreesH(f1,n1);
            BiblioH *b2= charger_n_entreesH(f2,n2);
            fusion_biblioH(b1,b2);
            printf("Fusion réussie.\n\n");
            printf("Quel est le nom du fichier dans lequel seront stockés la nouvelle bibliothèque fusionnée?\n");
            fgets(ligne, 256, stdin);

            if (sscanf(ligne, "%s\n", nomb)==1){
              enregistrer_biblioH(b1,nomb);
              printf("Enregistrement avec succès.\n\n");
            }
            else{
              printf("Erreur dans l'enregistrement.\n\n");
            }
          }
          else{
            printf("Erreur dans la saisie.\n\n");
          }
        } 
        else{
          printf("Erreur dans la saisie des fichiers\n\n");
        }
        break;
        
      case 9: 
        printf("Veuillez saisir le nom du fichier dans lequel vous souhaitez stocké la bibliothèque utilisée actuellement.\n");
        fgets(ligne, 256, stdin);

        if (sscanf(ligne,"%s\n", nomb)==1){
          enregistrer_biblioH(b,nomb);
          printf("Enregistrement avec succès.\n\n");
        }
        else{
          printf("Erreur dans l'enregistrement.\n\n");
        }
        break;       
    }
  }while(rep!=0);
  printf("Merci, et au revoir.\n");

  return 0;
}