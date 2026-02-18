
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matiere.h"

int verifierMatiereExiste(const char *codeMatiere) {
    FILE *f = fopen("fmatiere.ing", "rb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des matières !\n");
        return 0;
    }

    Matiere m;
    while (fread(&m, sizeof(Matiere), 1, f)) {
        if (strcmp(m.code, codeMatiere) == 0) {
            fclose(f);
            return 1; // Existe
        }
    }
    fclose(f);
    return 0; // N'existe pas
}
void saisirMatiere() {
    FILE *f = fopen("fmatiere.ing", "ab");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des matières !\n");
        return;
    }

    Matiere m;
    printf("Code matière (5 caractères) : ");
    scanf("%s", m.code);
    printf("Nom de la matière : ");
    scanf("%s", m.nom);
    printf("Nombre de crédits : ");
    scanf("%d", &m.credit);

    fwrite(&m, sizeof(Matiere), 1, f);
    fclose(f);
    printf("Matière enregistrée avec succès !\n");
}

void afficherMatieres() {
    FILE *f = fopen("fmatiere.ing", "rb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des matières !\n");
        return;
    }

    Matiere m;
    printf("\nListe des matières :\n");
    while (fread(&m, sizeof(Matiere), 1, f)) {
        printf("Code : %s\n", m.code);
        printf("Nom : %s\n", m.nom);
        printf("Crédit : %d\n\n", m.credit);
    }
    fclose(f);
}
