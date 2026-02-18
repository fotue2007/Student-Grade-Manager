#ifndef MATIERE_H
#define MATIERE_H

typedef struct {
    char code[6]; // 5 caractères + '\0'
    char nom[50];
    int credit;
} Matiere;

void saisirMatiere();
void afficherMatieres();
int verifierMatiereExiste(const char *codeMatiere);

 #endif

