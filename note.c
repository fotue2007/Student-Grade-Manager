#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "note.h"
#include "etudiant.h"
#include "matiere.h"

void saisirNote() {
    FILE *f = fopen("fnote.ing", "ab");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }

    Evaluation n;
    printf("Code matière : ");
    scanf("%s", n.code_matiere);

    if (!verifierMatiereExiste(n.code_matiere)) {
        printf("Erreur : La matière avec le code '%s' n'existe pas !\n", n.code_matiere);
        fclose(f);
        return;
    }

    printf("Matricule étudiant : ");
    scanf("%s", n.matricule);

    printf("Numéro de séquence (entre 1 et 6) : ");
    scanf("%d", &n.numero_sequence);
    if (n.numero_sequence < 1 || n.numero_sequence > 6) {
        printf("Erreur : La séquence doit être comprise entre 1 et 6 !\n");
        fclose(f);
        return;
    }

    printf("Note (entre 0 et 20) : ");
    scanf("%f", &n.note);
    if (n.note < 0 || n.note > 20) {
        printf("Erreur : La note doit être comprise entre 0 et 20 !\n");
        fclose(f);
        return;
    }

    fwrite(&n, sizeof(Evaluation), 1, f);
    fclose(f);
    printf("Note enregistrée avec succès !\n");
}

void afficherNotes() {
    FILE *f = fopen("fnote.ing", "rb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }

    Evaluation n;
    printf("\nListe des notes :\n");
    while (fread(&n, sizeof(Evaluation), 1, f)) {
        printf("Matricule étudiant : %s\n", n.matricule);
        printf("Code matière : %s\n", n.code_matiere);
        printf("Numéro de séquence : %d\n", n.numero_sequence);
        printf("Note : %.2f\n\n", n.note);
    }
    fclose(f);
}

void moyenneEtudiant() {
    char matricule[20];
    printf("Entrez le matricule de l'étudiant : ");
    scanf("%s", matricule);

    FILE *fNote = fopen("fnote.ing", "rb");
    if (fNote == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }

    Evaluation n;
    float somme = 0;
    int nbNotes = 0;

    while (fread(&n, sizeof(Evaluation), 1, fNote)) {
        if (strcmp(n.matricule, matricule) == 0) {
            somme += n.note;
            nbNotes++;
        }
    }
    fclose(fNote);

    if (nbNotes > 0) {
        float moyenne = somme / nbNotes;
        printf("Moyenne de l'étudiant %s : %.2f\n", matricule, moyenne);
    } else {
        printf("Aucune note trouvée pour l'étudiant %s\n", matricule);
    }
}

void modifierNote() {
    char matricule[20], codeMatiere[6];
    int sequence;
    printf("Entrez le matricule de l'étudiant : ");
    scanf("%s", matricule);
    printf("Entrez le code de la matière : ");
    scanf("%s", codeMatiere);
    printf("Entrez le numéro de séquence : ");
    scanf("%d", &sequence);

    FILE *f = fopen("fnote.ing", "rb+");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }

    Evaluation n;
    int found = 0;
    while (fread(&n, sizeof(Evaluation), 1, f)) {
        if ((strcmp(n.matricule, matricule) == 0) &&
            (strcmp(n.code_matiere, codeMatiere) == 0) &&
            (n.numero_sequence == sequence)) {
            found = 1;
            printf("Note actuelle : %.2f\n", n.note);
            printf("Entrez la nouvelle note : ");
            scanf("%f", &n.note);

            fseek(f, -sizeof(Evaluation), SEEK_CUR);
            fwrite(&n, sizeof(Evaluation), 1, f);
            printf("Note modifiée avec succès !\n");
            break;
        }
    }
    if (!found)
        printf("Aucune note trouvée pour cet étudiant, cette matière et cette séquence.\n");

    fclose(f);
}

void supprimerNote() {
    char matricule[20], codeMatiere[6];
    int sequence;
    printf("Entrez le matricule de l'étudiant : ");
    scanf("%s", matricule);
    printf("Entrez le code de la matière (5 caracteres) : ");
    scanf("%s", codeMatiere);
    printf("Entrez le numéro de séquence : ");
    scanf("%d", &sequence);

    FILE *f = fopen("fnote.ing", "rb");
    if (f == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }
    FILE *temp = fopen("temp.ing", "wb");
    if (temp == NULL) {
        printf("Erreur lors de la création du fichier temporaire !\n");
        fclose(f);
        return;
    }

    Evaluation n;
    int found = 0;
    while (fread(&n, sizeof(Evaluation), 1, f)) {
        if ((strcmp(n.matricule, matricule) == 0) &&
            (strcmp(n.code_matiere, codeMatiere) == 0) &&
            (n.numero_sequence == sequence)) {
            found = 1;
        } else {
            fwrite(&n, sizeof(Evaluation), 1, temp);
        }
    }
    fclose(f);
    fclose(temp);

    if (found) {
        remove("fnote.ing");
        rename("temp.ing", "fnote.ing");
        printf("Note supprimée avec succès !\n");
    } else {
        printf("Aucune note trouvée pour cet étudiant, cette matière et cette séquence.\n");
        remove("temp.ing");
    }
}

void procesVerbalEtudiant() {
    char matricule[20];
    printf("Entrez le matricule de l'étudiant : ");
    scanf("%s", matricule);

    FILE *fEtud = fopen("fetud.ing", "rb");
    if (fEtud == NULL) {
        printf("Erreur d'ouverture du fichier des étudiants !\n");
        return;
    }

    Etudiant e;
    int foundEtud = 0;
    while (fread(&e, sizeof(Etudiant), 1, fEtud)) {
        if (strcmp(e.matricule, matricule) == 0) {
            foundEtud = 1;
            break;
        }
    }
    fclose(fEtud);

    if (!foundEtud) {
        printf("Aucun étudiant trouvé avec le matricule %s\n", matricule);
        return;
    }

    printf("\n===== PROCES-VERBAL =====\n");
    printf("Matricule : %s\n", e.matricule);
    printf("Nom : %s\n", e.nom);
    printf("Filière : %s\n", e.filiere);
    printf("--------------------------\n");

    FILE *fNote = fopen("fnote.ing", "rb");
    if (fNote == NULL) {
        printf("Erreur d'ouverture du fichier des notes !\n");
        return;
    }

    Evaluation n;
    float somme = 0;
    int nbNotes = 0;
    while (fread(&n, sizeof(Evaluation), 1, fNote)) {
        if (strcmp(n.matricule, matricule) == 0) {
            printf("Matière : %s | Séquence : %d | Note : %.2f\n", n.code_matiere, n.numero_sequence, n.note);
            somme += n.note;
            nbNotes++;
        }
    }
    fclose(fNote);

    if (nbNotes > 0) {
        float moyenne = somme / nbNotes;
        printf("--------------------------\n");
        printf("Moyenne générale : %.2f\n", moyenne);
    } else {
        printf("Aucune note enregistrée pour cet étudiant.\n");
    }
}
