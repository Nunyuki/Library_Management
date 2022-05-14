#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioH.h"
#include "entreeSortieH.h"
#include <assert.h>

int main (int argc, char** argv){

//Charger n Livre d'un fichier
  printf("\n------------Charger Livres------------\n");
  //n première lignes
  BiblioH *charger1=charger_n_entreesH("Biblio.txt",4);
  afficher_biblioH(charger1);
  printf("\n");

  //si nombre de Livres inférieur à n
  BiblioH *charger2=charger_n_entreesH("Biblio.txt",10);
  afficher_biblioH(charger2);

//Ecrire une Bibliothèque dans un fichier
  printf("\n----------Ecrire Bibliothèque----------\n");
  enregistrer_biblioH(charger1,"testH1.txt");
  enregistrer_biblioH(charger2,"testH2.txt");

  //Libération des Livres
  libererbiblio(charger1);
  libererbiblio(charger2);

//Recherche de la clé
  printf("-----------Recherche Clé-----------\n");
  int a=fonctionClef("a");
  int z=fonctionClef("z");
  //assert((z-a)==25);
  printf("clé de a:%d\n",a);
  printf("clé de z:%d\n",z);

//Création de Livre
  printf("\n----------Création de Livre----------\n");  
  LivreH *l=NULL;
  afficher_livreH(l);

  LivreH *ll=creerlivre(0,"TEST", "code");
  afficher_livreH(ll);

//Création de Bibliothèque
  printf("\n-------Création de Bibliothèque------\n");
  BiblioH *bb=NULL;
  afficher_biblioH(bb);
  
  BiblioH *b= creerbiblio(M);
  afficher_biblioH(b);

//Fonction de Hachage
  printf("\n-------Fonction Hashage------\n");
  assert(fonctionHachage(0,b->m)==0);
  int h = fonctionHachage(666,b->m);
  printf("clé: %d, taille m: %d, n°hashage: %d\n",666,b->m,h);

//Insertion Livre
  printf("\n----------Insertion de Livre----------\n");
  inserer(bb,1, "INSERER", "test1");
  afficher_biblioH(bb);

  inserer(b,1, "INSERER1", "test1");
  inserer(b,2, "INSERER2", "test2");
  afficher_biblioH(b);

  //Libération des Livres
  libererlivre(l);
  libererlivre(ll);

  //Libération ds Bibliothèques
  libererbiblio(b);
  libererbiblio(bb);

//Recherche un Livre par son numéro
  printf("\n-----------Recherche Numéro-----------\n");
  BiblioH *rech0 = NULL;
  BiblioH *rech1 = creerbiblio(M);
  BiblioH *rech2 = creerbiblio(M);
  
  inserer(rech2,1, "RECHERCHE1", "num1");
  inserer(rech2,2, "RECHERCHE2", "num2");
  inserer(rech2,3, "RECHERCHE3", "3num");
  inserer(rech2,5, "RECHERCHE3", "nu3m");
  inserer(rech2,6, "RECHERCHE3", "num3");
  inserer(rech2,4, "RECHERCHE4", "num4");
  afficher_biblioH(rech2);
  printf("\n");
  
  //Les différents cas où un Livre n'est pas retourné
  assert(rech_numH(1,rech0)==NULL);
  assert(rech_numH(1,rech1)==NULL);
  assert(rech_numH(10,rech2)==NULL);

  //Livre en tête d'une table
  LivreH *l1= creerlivre(1,"RECHERCHE1","num1");
  assert(rech_numH(1,rech2)->num==l1->num);
  afficher_livreH(l1);

  //Livre dans le corps d'une table
  LivreH *l2 = creerlivre(5,"RECHERCHE3","nu3m");
  assert(rech_numH(5,rech2)->num==l2->num);
  afficher_livreH(l2);

  //Livre à la fin d'une table
  LivreH *l3 = creerlivre(3,"RECHERCHE3","3num");
  assert(rech_numH(3,rech2)->num==l3->num);
  afficher_livreH(l3);

  //Libération des Livres
  libererlivre(l1);
  libererlivre(l2);
  libererlivre(l3);

//Recherche un Livre par son titre
  printf("\n-----------Recherche Titre-----------\n");
  //Les différents cas où un Livre n'est pas retourné
  assert(rech_titreH("RECHERCHE1",rech0)==NULL);
  assert(rech_titreH("RECHERCHE1",rech1)==NULL);
  assert(rech_titreH("RECHERCHE5",rech2)==NULL);

  //Livre en tête d'une table
  LivreH *ll1= creerlivre(6,"RECHERCHE3","num3");
  assert(strcmp(rech_titreH("RECHERCHE3",rech2)->titre,ll1->titre)==0);
  afficher_livreH(ll1);

  //Livre dans le corps d'une table
  LivreH *ll2 = creerlivre(5,"RECHERCHE3","nu3m");
  assert(strcmp(rech_titreH("RECHERCHE3",rech2)->titre,ll2->titre)==0);
  afficher_livreH(ll2);

  //Livre à la fin d'une table
  LivreH *ll3 = creerlivre(3,"RECHERCHE3","3num");
  assert(strcmp(rech_titreH("RECHERCHE3",rech2)->titre,ll3->titre)==0);
  afficher_livreH(ll3);  

  //Libération des Livres
  libererlivre(ll1);
  libererlivre(ll2);
  libererlivre(ll3);

//Recherche les différents Livres d'un auteur
  printf("\n-----------Recherche Auteur-----------\n");
  inserer(rech2,5, "RECHERCHE5", "num4");
  inserer(rech2,6, "RECHERCHE6", "num3");
  inserer(rech2,7, "RECHERCHE7", "num4");
  
  //Le cas où la Bibliothèque n'est pas retournée
  assert(rech_auteurH("num1",rech0)==NULL);

  //Les cas où une bibliothèque vide est retournée
  assert(rech_auteurH("num1",rech1)==NULL);
  assert(rech_auteurH("num5",rech2)==NULL);
  
  //Un seul livre
  BiblioH *bl1= rech_auteurH("num1",rech2);
  afficher_biblioH(bl1);
  printf("\n");

  //Plusieurs Livres
  BiblioH *bl2= rech_auteurH("num4",rech2);
  afficher_biblioH(bl2);  
  
  //Libération des Bibliothèques
  libererbiblio(bl1);
  libererbiblio(bl2);

//Supression d'un ouvrage
  printf("\n-----------Suppression Livre-----------\n");
  //Aucun Livre n'est supprimé
  supp_livreH(rech0,0,"RECHERCHE0","num1");
  supp_livreH(rech1,0,"RECHERCHE0","num1");
  supp_livreH(rech2,0,"RECHERCHE0","num1");

  afficher_biblioH(rech2);
  printf("\n");
  
  //Livre à supprimer en tête d'une table
  supp_livreH(rech2,6,"RECHERCHE6","num3");
  
  //Livre à supprimer dans le corps d'une table
  supp_livreH(rech2,5,"RECHERCHE3","nu3m");
  
  //Livre à supprimer en fin de table
  supp_livreH(rech2,3,"RECHERCHE3","3num"); 

  //Livre à supprimer dans une table unique
  supp_livreH(rech2,1,"RECHERCHE1","num1");
  afficher_biblioH(rech2);

//Fusion de deux Bibliothèques
  printf("\n---------Fusion Bibliothèques---------\n");
  //Bibliothèque rech0 vide
  fusion_biblioH(rech2,rech0);
  afficher_biblioH(rech2);
  printf("\n");
  
  //Bibliothèque rech0 vide
  fusion_biblioH(rech0,rech2);
  afficher_biblioH(rech0);
  printf("\n");

  //Fusion de deux Bibliothèques non vide
  BiblioH *fusio= creerbiblio(M);
  inserer(fusio,1,"FUSION1","fus_0_1");
  inserer(fusio,2,"FUSION2","fus_0_2");
  afficher_biblioH(fusio);
  printf("\n");
  fusion_biblioH(rech2,fusio);
  afficher_biblioH(rech2);

//Recherche les différents exemplaires
  printf("\n--------Recherche Exemplaires--------\n");
  inserer(rech2,6, "RECHERCHE5", "num4");
  inserer(rech2,7, "RECHERCHE5", "num4");
  inserer(rech2,8, "RECHERCHE5", "num4");
  afficher_biblioH(rech2);
  printf("\n");

  //Pas d'exemplaire possible
  assert(exemplaireH(rech0)==NULL);
  assert(exemplaireH(rech1)==NULL);
  printf("\n");

  //Bibliothèque ayant des exemplaires
  BiblioH *exempl=exemplaireH(rech2);
  printf("\n");
  afficher_biblioH(exempl);
  
  //Libération des Bibliothèques
  libererbiblio(rech0);
  libererbiblio(rech1);
  libererbiblio(rech2);
  libererbiblio(exempl);
}