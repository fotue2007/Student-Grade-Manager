#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "etudiant.h"
#include "matiere.h"
#include "note.h"


// Définition des structures





void menu() {
    int choix;

    do {
        printf("\n===== MENU =====\n");
        printf("1 - Saisie etudiant\n");
        printf("2 - Liste etudiants\n");
        printf("3 - Saisie matiere\n");
        printf("4 - Liste matieres\n");
        printf("5 - Saisie note\n");
        printf("6 - Afficher notes\n");
        printf("7 - Moyenne d'un etudiant\n");
        printf("8 - Modifier note\n");
        printf("9 - Supprimer note\n");
        printf("10 - Proces-verbal d'un etudiant\n");
        printf("11 - Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: saisirEtudiant(); break;
            case 2: afficherEtudiants(); break;
            case 3: saisirMatiere(); break;
            case 4: afficherMatieres(); break;
            case 5: saisirNote(); break;
            case 6: afficherNotes(); break;
            case 7: moyenneEtudiant(); break;
            case 8: modifierNote(); break;
            case 9: supprimerNote(); break;
            case 10: procesVerbalEtudiant(); break;
            case 11: printf("Au revoir !\n"); break;
            default: printf("Choix invalide, réessayez.\n");
        }

    } while (choix != 11);
}

int main() {
    menu();
    return 0;
}
