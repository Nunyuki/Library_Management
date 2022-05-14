#include <stdio.h>
#include "entreeSortieH.h"
#include "biblioLC.h"
#include "biblioH.h"
#include "entreeSortieLC.h"
#include <time.h>


int main(){

  // LISTE CHAINEE
  Biblio *bLC = charger_n_entrees("GdeBiblio.txt", 1000);

  // Livre présent
  clock_t ti1, tf1;
  float t1=0, t2=0, t3=0;
  int n; 
  for(int i=0; i<1000; i++){
    ti1= clock();
    Livre *l1= rech_num(675, bLC);
    tf1= clock();
    t1+= (float)(tf1 - ti1)/CLOCKS_PER_SEC;

    ti1= clock();
    Livre *l2= rech_titre("RYOCAUOLCAV", bLC);
    tf1= clock();
    t2+= (float)(tf1 - ti1)/CLOCKS_PER_SEC;

    ti1= clock();
    Biblio *b1= rech_auteur("mumjx", bLC);
    tf1= clock();
    liberer_biblio(b1);
    // printf("rech_auteur --> temps :%f s\n", (float)(tf1 - ti1)/CLOCKS_PER_SEC);
    t3+= (float)(tf1 - ti1)/CLOCKS_PER_SEC;

    n++;
    // 675 RYOCAUOLCAV mumjx 
  }
    printf("\nLivre présent | Liste chainée \n");
    printf("temps moyen rech_num: %f s\n", (float)t1/n);
    printf("temps moyen rech_titre: %f s\n", (float)t2/n);
    printf("temps moyen rech_auteur: %f s\n", (float)t3/n);
    printf("\n");
    
  // Livre absent
  t1=0; t2=0; t3=0; n=0;
  clock_t ti2, tf2;
  for(int i=0; i<1000; i++){
    ti2= clock();
    Livre *l1= rech_num(1000000, bLC);
    tf2= clock();
    t1+=(float)(tf2 - ti2)/CLOCKS_PER_SEC;
    

    ti2= clock();
    Livre *l2= rech_titre("RECHERCHE", bLC);
    tf2= clock();
    t2+=(float)(tf2 - ti2)/CLOCKS_PER_SEC;
    

    ti2= clock();
    Biblio *b1= rech_auteur("recherche", bLC);
    tf2= clock();
    t3+=(float)(tf2- ti2)/CLOCKS_PER_SEC;
    
    liberer_biblio(b1);
    n++;
  }
  printf("\nLivre asbent | Liste chainée \n");
  printf("temps moyen rech_num : %f s\n", (float)t1/n);
  printf("temps moyen rech_titre : %f s\n", (float)t2/n);
  printf("temps moyen rech_auteur : %f s\n", (float)t3/n);
  printf("\n");


  // TABLE DE HACHAGE
  int taille =1000;
  BiblioH *bH= charger_n_entreesH("GdeBiblio.txt", taille);

  t1=0; t2=0; t3=0; n=0;
  // Livre présent
  clock_t ti3, tf3;
  for(int i=0; i<1000; i++){
    ti3= clock();
    LivreH *l1= rech_numH(675, bH);
    tf3= clock();
    t1+= (float)(tf3 - ti3)/CLOCKS_PER_SEC;
    // printf("rech_num --> temps :%f s\n", (float)(tf3 - ti3)/CLOCKS_PER_SEC);

    ti3= clock();
    LivreH *l2= rech_titreH("RYOCAUOLCAV", bH);
    tf3= clock();
    t2+=(float)(tf3 - ti3)/CLOCKS_PER_SEC;
    // printf("rech_titre --> temps :%f s\n", (float)(tf3 - ti3)/CLOCKS_PER_SEC);

    ti3= clock();
    BiblioH *b1= rech_auteurH("mumjx", bH);
    tf3= clock();
    t3+=(float)(tf3 - ti3)/CLOCKS_PER_SEC;
    libererbiblio(b1);
    // printf("rech_auteur --> temps :%f s\n", (float)(tf3 - ti3)/CLOCKS_PER_SEC);

    n++;
    // 675 RYOCAUOLCAV mumjx 

  }
  printf("\nLivre present | Table de hachage de taille %d \n", taille);
  printf("temps moyen rech_numH : %f s\n", (float)t1/n);
  printf("temps moyen rech_titreH : %f s\n", (float)t2/n);
  printf("temps moyen rech_auteurH : %f s\n", (float)t3/n);
  printf("\n");
  

  // Livre absent
  t1=0; t2=0; t3=0; n=0;
  clock_t ti4, tf4;
  for(int i=0; i<1000; i++){
    ti4= clock();
    LivreH *l1= rech_numH(1000000, bH);
    tf4= clock();
    t1+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;
    

    ti4= clock();
    LivreH *l2= rech_titreH("RECHERCHE", bH);
    tf4= clock();
    t2+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;
    

    ti4= clock();
    BiblioH *b1= rech_auteurH("recherche", bH);
    tf4= clock();
    t3+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;
    
    libererbiblio(b1);
    n++;
  }
  printf("\nLivre asbent | Table de hachage de taille %d \n", taille);
  printf("temps moyen rech_numH : %f s\n", (float)t1/n);
  printf("temps moyen rech_titreH : %f s\n", (float)t2/n);
  printf("temps moyen rech_auteurH : %f s\n", (float)t3/n);
  printf("\n");


// MODIFICATION DE LA TAILLE DE LA TABLE DE HACHAGE

  int tailleH=10000;
  BiblioH *bH2=charger_n_entreesH("GdeBiblio.txt",tailleH);

    
  // Livre présent
  t1=0; t2=0; t3=0; n=0;
  for(int i=0; i<1000; i++){
    ti3= clock();
    LivreH *l1= rech_numH(675, bH);
    tf3= clock();
    t1+=(float)(tf3 - ti3)/CLOCKS_PER_SEC;
    

    ti3= clock();
    LivreH *l2= rech_titreH("RYOCAUOLCAV", bH);
    tf3= clock();
    t2+=(float)(tf3 - ti3)/CLOCKS_PER_SEC;
    
    ti3= clock();
    BiblioH *b1= rech_auteurH("mumjx", bH);
    tf3= clock();
    t3+=(float)(tf3 - ti3)/CLOCKS_PER_SEC;
    
    libererbiblio(b1);
    n++;
    // 675 RYOCAUOLCAV mumjx 

  }
  printf("\nLivre present | Table de hachage de taille %d \n", tailleH);
  printf("temps moyen rech_numH : %f s\n", (float)t1/n);
  printf("temps moyen rech_titreH : %f s\n", (float)t2/n);
  printf("temps moyen rech_auteurH : %f s\n", (float)t3/n);
  printf("\n");

  // Livre absent
  t1=0; t2=0; t3=0; n=0;
  for(int i=0; i<1000; i++){
    ti4= clock();
    LivreH *l1= rech_numH(1000000, bH);
    tf4= clock();
    t1+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;
    
    ti4= clock();
    LivreH *l2= rech_titreH("RECHERCHE", bH);
    tf4= clock();
    t2+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;


    ti4= clock();
    BiblioH *b1= rech_auteurH("recherche", bH);
    tf4= clock();
    t3+=(float)(tf4 - ti4)/CLOCKS_PER_SEC;

    
    libererbiblio(b1);
    n++;
  }
  printf("\nLivre absent | Table de hachage de taille %d \n", tailleH);
  printf("temps moyen rech_numH : %f s\n", (float)t1/n);
  printf("temps moyen rech_titreH : %f s\n", (float)t2/n);
  printf("temps moyen rech_auteurH : %f s\n", (float)t3/n);
  printf("\n");
  

  // RECHERCHES EXEMPLAIRE

  FILE *f = fopen("temps.txt","w");
    if (f == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
        return 1;
    }
  FILE *fH = fopen("tempsH.txt","w");
    if (fH == NULL) {
        printf("Erreur dans l'ouverture du fichier\n");
        return 1;
    }

    
  clock_t ti, tf, ti5, tf5;
  float temps, tempsH;

  for(int i=1000; i<50000; i=i+200){
    printf("%d\n",i);
    Biblio *bb= charger_n_entrees("GdeBiblio.txt",i);
    BiblioH *bbH= charger_n_entreesH("GdeBiblio.txt",i);

    ti = clock();
    Biblio *exb= exemplaire(bb);
    tf = clock();

    ti5 = clock();
    BiblioH *exbH= exemplaireH(bbH);
    tf5 = clock();

    temps = (float)(tf-ti)/CLOCKS_PER_SEC;
    tempsH = (float)(tf5-ti5)/CLOCKS_PER_SEC;
    fprintf(f, "%f\n",temps);
    fprintf(fH, "%f\n", tempsH);

    liberer_biblio(bb);
    liberer_biblio(exb);
    libererbiblio(bbH);
    libererbiblio(exbH);
    printf("done\n");

    }

  fclose(f);
  fclose(fH);
  return 0;
}
  