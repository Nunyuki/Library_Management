#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioLC.h"
#include "entreeSortieLC.h"
#include <assert.h>

int main (){

//Charger n Livre d'un fichier
  printf("\n------------Charger Livres------------\n");
  //n première lignes
  Biblio *charger1=charger_n_entrees("Biblio.txt",4);
  afficher_biblio(charger1);
  printf("\n");

  //si nombre de Livres inférieur à n
  Biblio *charger2=charger_n_entrees("Biblio.txt",10);
  afficher_biblio(charger2);

//Ecrire une Bibliothèque dans un fichier
  printf("\n----------Ecrire Bibliothèque----------\n");
  enregistrer_biblio(charger1,"Test1.txt");
  enregistrer_biblio(charger2,"Test2.txt");

  //Libération des Livres
  liberer_biblio(charger1);
  liberer_biblio(charger2);
  
//Création de Livre
  printf("\n----------Création de Livre----------\n");  
  Livre *l=NULL;
  afficher_livre(l);

  Livre *ll=creer_livre(0,"TEST", "code");
  afficher_livre(ll);
  
//Création de Bibliothèque
  printf("\n-------Création de Bibliothèque------\n");
  Biblio *bb=NULL;
  afficher_biblio(bb);
  
  Biblio *b= creer_biblio();
  afficher_biblio(b);
  
//Insertion Livre
  printf("\n----------Insertion de Livre----------\n");
  inserer_en_tete(bb,1, "INSERER", "test1");
  afficher_biblio(bb);

  inserer_en_tete(b,1, "INSERER1", "test1");
  afficher_biblio(b);

  //Libération des Livres
  liberer_livre(l);
  liberer_livre(ll);

  //Libération ds Bibliothèques
  liberer_biblio(b);
  liberer_biblio(bb);

//Recherche un Livre par son numéro
  printf("\n-----------Recherche Numéro-----------\n");
  Biblio *rech0 = NULL;
  Biblio *rech1 = creer_biblio();
  Biblio *rech2 = creer_biblio();
  
  inserer_en_tete(rech2,1, "RECHERCHE1", "num1");
  inserer_en_tete(rech2,2, "RECHERCHE2", "num2");
  inserer_en_tete(rech2,3, "RECHERCHE3", "num3");
  inserer_en_tete(rech2,4, "RECHERCHE4", "num4");

  //Les différents cas où un Livre n'est pas retourné
  assert(rech_num(1,rech0)==NULL);
  assert(rech_num(1,rech1)==NULL);
  assert(rech_num(5,rech2)==NULL);

  //Livre en tête
  Livre *l1= creer_livre(1,"RECHERCHE1","num1");
  assert(rech_num(1,rech2)->num==l1->num);
  afficher_livre(l1);

  //Livre dans le corps
  Livre *l2 = creer_livre(2,"RECHERCHE2","num2");
  assert(rech_num(2,rech2)->num==l2->num);
  afficher_livre(l2);

  //Livre à la fin
  Livre *l3 = creer_livre(4,"RECHERCHE4","num4");
  assert(rech_num(4,rech2)->num==l3->num);
  afficher_livre(l3);

  //Libération des Livres
  liberer_livre(l1);
  liberer_livre(l2);
  liberer_livre(l3);

//Recherche un Livre par son titre
  printf("\n-----------Recherche Titre-----------\n");
  //Les différents cas où un Livre n'est pas retourné
  assert(rech_titre("RECHERCHE1",rech0)==NULL);
  assert(rech_titre("RECHERCHE1",rech1)==NULL);
  assert(rech_titre("RECHERCHE5",rech2)==NULL);

  //Livre en tête
  Livre *ll1= creer_livre(1,"RECHERCHE1","num1");
  assert(strcmp(rech_titre("RECHERCHE1",rech2)->titre,ll1->titre)==0);
  afficher_livre(ll1);

  //Livre dans le corps
  Livre *ll2 = creer_livre(2,"RECHERCHE2","num2");
  assert(strcmp(rech_titre("RECHERCHE2",rech2)->titre,ll2->titre)==0);
  afficher_livre(ll2);

  //Livre à la fin
  Livre *ll3 = creer_livre(4,"RECHERCHE4","num4");
  assert(strcmp(rech_titre("RECHERCHE4",rech2)->titre,ll3->titre)==0);
  afficher_livre(ll3);  

  //Libération des Livres
  liberer_livre(ll1);
  liberer_livre(ll2);
  liberer_livre(ll3);

//Recherche les différents Livres d'un auteur
  printf("\n-----------Recherche Auteur-----------\n");
  inserer_en_tete(rech2,5, "RECHERCHE5", "num4");
  inserer_en_tete(rech2,6, "RECHERCHE6", "num3");
  inserer_en_tete(rech2,7, "RECHERCHE7", "num4");
  
  
  //Les différents cas où la Bibliothèque n'est pas retournée
  assert(rech_auteur("num1",rech0)==NULL);
  assert(rech_auteur("num1",rech1)==NULL);
  assert(rech_auteur("num5",rech2)==NULL);

  //Un seul livre
  Biblio *bl1= rech_auteur("num1",rech2);
  afficher_biblio(bl1);

  //Plusieurs Livres
  Biblio *bl2= rech_auteur("num4",rech2);
  afficher_biblio(bl2);  
  
  //Libération des Bibliothèques
  liberer_biblio(bl1);
  liberer_biblio(bl2);
  
//Supression d'un ouvrage
  printf("\n-----------Suppression Livre-----------\n");
  //Aucun Livre n'est supprimé
  supp_livre(rech0,0,"RECHERCHE0","num1");
  supp_livre(rech1,0,"RECHERCHE0","num1");
  supp_livre(rech2,0,"RECHERCHE0","num1");

  afficher_biblio(rech2);
  printf("\n");
  
  //Livre à supprimer en tête
  supp_livre(rech2,7,"RECHERCHE7","num4");
  afficher_biblio(rech2);
  printf("\n");
  
  //Livre à supprimer dans le corps
  supp_livre(rech2,4,"RECHERCHE4","num4");
  afficher_biblio(rech2);
  printf("\n");
  
  //Livre à supprimer en fin
  supp_livre(rech2,1,"RECHERCHE1","num1");
  afficher_biblio(rech2);

//Fusion de deux Bibliothèques
  printf("\n---------Fusion Bibliothèques---------\n");
  //Bibliothèque rech0 vide
  fusion_biblio(rech2,rech0);
  afficher_biblio(rech2);
  printf("\n");
  
  //Bibliothèque rech0 vide
  fusion_biblio(rech0,rech2);
  afficher_biblio(rech0);
  printf("\n");

  //Fusion de deux Bibliothèques non vide
  Biblio *fusio= creer_biblio();
  inserer_en_tete(fusio,1,"FUSION1","fus1");
  inserer_en_tete(fusio,2,"FUSION2","fus2");
  fusion_biblio(rech2,fusio);
  afficher_biblio(rech2);
  
//Recherche les différents exemplaires
  printf("\n--------Recherche Exemplaires--------\n");
  inserer_en_tete(rech2,6, "RECHERCHE5", "num4");
  inserer_en_tete(rech2,7, "RECHERCHE5", "num4");
  inserer_en_tete(rech2,8, "RECHERCHE5", "num4");
  afficher_biblio(rech2);
  printf("\n");

  //Pas d'exemplaire possible
  assert(exemplaire(rech0)==NULL);
  assert(exemplaire(rech1)==NULL);
  printf("\n");

  //Bibliothèque ayant des exemplaires
  Biblio *exempl=exemplaire(rech2);
  printf("\n");
  afficher_biblio(exempl);
  
  //Libération des Bibliothèques
  liberer_biblio(rech0);
  liberer_biblio(rech1);
  liberer_biblio(rech2);
  liberer_biblio(exempl);
}