#ifndef ETUDIANT_H
#define ETUDIANT_H


typedef struct {
    char matricule[10];
    char nom[30];
    char date_naissance[11];
    char sexe[10];
    char filiere[20];
} Etudiant;

 int estBissextile(int annee);
 int DateValide(char *date);
 void saisirEtudiant();
 void afficherEtudiants();

 #endif
