#ifndef NOTE_H
#define NOTE_H

typedef struct {
    char code_matiere[6];
    char matricule[20];
    int numero_sequence;
    float note;
} Evaluation;
void saisirNote();
void afficherNotes();
void moyenneEtudiant();
void modifierNote();
void supprimerNote();
void procesVerbalEtudiant();
#endif
