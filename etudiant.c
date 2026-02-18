#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"

//controle sur la date
 int estBissextile(int annee)
 {
     return((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0));
 }

 int DateValide(char *date)
 {
     int jour,mois,annee;
     //verifier le format de la date
     if(sscanf(date,"%d/%d/%d",&jour,&mois,&annee) != 3)
        return 0;//format date incorrect
     //verifier les valeurs des mois ,des jours et annee
     if(mois < 1 || mois > 12 || jour < 1 || annee < 1)
        return 0;

     //nombre jours par mois
     int jourParMois[] = {31,28,31,30,31,30,31,31,30,31,30,31};

     if(mois == 2 && estBissextile(annee))
        jourParMois[1] = 29;

     //verifier si le jour est valide
     if(jour > jourParMois[mois - 1])
        return 0;

    return 1;//date valide
 }

void saisirEtudiant() {
    FILE *f = fopen("fetud.ing", "ab");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants !\n");
        return;
    }

    Etudiant e;
    printf("Matricule : ");
    scanf("%s", e.matricule);
    printf("Nom et prenoms : ");
    scanf("%s",e.nom);

    do{
        printf("Date de naissance (JJ/MM/AAAA) : ");
        scanf("%s", e.date_naissance);
        if(DateValide(e.date_naissance) == 0)
            printf("Erreur ! Date invalide ! Veillez entrez date naissance correcte \n");
    }while(DateValide(e.date_naissance) == 0);



    printf("Sexe : ");
    scanf("%s", e.sexe);
    printf("Filière : ");
    scanf("%s", e.filiere);

    fwrite(&e, sizeof(Etudiant), 1, f);
    fclose(f);
    printf("Etudiant enregistré avec succès !\n");
}

void afficherEtudiants() {
    FILE *f = fopen("fetud.ing", "rb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants !\n");
        return;
    }

    Etudiant e;
    printf("\nListe des étudiants :\n");
    while (fread(&e, sizeof(Etudiant), 1, f)) {
        printf("Matricule : %s\n", e.matricule);
        printf("Nom : %s\n", e.nom);
        printf("Date de naissance : %s",e.date_naissance);
        printf("Sexe : %s\n", e.sexe);
        printf("Filière : %s\n\n", e.filiere);
    }
    fclose(f);
}



