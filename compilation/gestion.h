#ifndef GESTION_H
#define GESTION_H

#include <stdbool.h>
#define MAX 100

typedef struct {
    char nom[50];
    int age;
} Personne;

void ajouter(Personne *tab, int *n);
void afficher(Personne *tab, int n);
void supprimer(Personne *tab, int *n);
void sauvegarder(const char *nomFichier, Personne *tab, int n);
int charger(const char *nomFichier, Personne *tab);
void rechercher(Personne *tab, int n);
void trier(Personne *tab, int n, int critere);
void exporter(Personne *tab, int n, const char *fichierTxt);

#endif