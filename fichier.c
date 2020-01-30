 /* contient les fonctions de gestion de fichiers*/

 #include "includes.h"

 int compterMots(FILE *dico)
 {
     int nombreDeMots = 0 , caractereActuel;
     do
     {
         caractereActuel = fgetc(dico);
         if(caractereActuel == '\n')
            nombreDeMots++;

     } while(caractereActuel != EOF);

     return nombreDeMots;
 }

 void choisirMot(char *motSecret)
 {
     int nIemeMot , i;
     FILE *dico = NULL;
     dico = fopen("dicos//dico.txt" , "r");
     if(!dico)
     {
         fprintf(stderr , "le fichier dico.txt est absent");
         exit(EXIT_FAILURE);
     }

     nIemeMot = (rand()%compterMots(dico));
     rewind(dico);
     for(i = 0 ; i <= nIemeMot ; i++)
     {
         fgets(motSecret , 26 , dico);
     }

     fclose(dico);

 }
