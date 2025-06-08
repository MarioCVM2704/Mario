#include <stdio.h>
#include <string.h>
#include "gestion.h"

// Ajouter une personne
void ajouter(Personne *tab, int *n) {
    if (*n >= MAX) {
        printf("Liste pleine.\n");
        return;
    }

    printf("Nom : ");
    fgets(tab[*n].nom, sizeof(tab[*n].nom), stdin);
    tab[*n].nom[strcspn(tab[*n].nom, "\n")] = 0;

    printf("Âge : ");
    while (scanf("%d", &tab[*n].age) != 1 || tab[*n].age < 0 || tab[*n].age > 130) {
        printf("Âge invalide. Réessayez : ");
        while (getchar() != '\n');
    }
    getchar(); // Consommer le \n

    (*n)++;
    printf("✅ Personne ajoutée avec succès.\n");
}

// Afficher la liste
void afficher(Personne *tab, int n) {
    if (n == 0) {
        printf("Aucune personne enregistrée.\n");
        return;
    }

    printf("\n--- Liste des personnes ---\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s, %d ans\n", i + 1, tab[i].nom, tab[i].age);
    }
}

// Supprimer une personne
void supprimer(Personne *tab, int *n) {
    if (*n == 0) {
        printf("Aucune personne à supprimer.\n");
        return;
    }

    char nomASupprimer[50];
    printf("Nom de la personne à supprimer : ");
    fgets(nomASupprimer, sizeof(nomASupprimer), stdin);
    nomASupprimer[strcspn(nomASupprimer, "\n")] = 0;

    int trouve = 0;
    for (int i = 0; i < *n; i++) {
        if (strcmp(tab[i].nom, nomASupprimer) == 0) {
            for (int j = i; j < *n - 1; j++) {
                tab[j] = tab[j + 1];
            }
            (*n)--;
            printf("✅ %s a été supprimé(e).\n", nomASupprimer);
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("❌ Aucun nom correspondant trouvé.\n");
    }
}

// Sauvegarder dans un fichier binaire
void sauvegarder(const char *nomFichier, Personne *tab, int n) {
    FILE *f = fopen(nomFichier, "wb");
    if (!f) {
        perror("Erreur de sauvegarde");
        return;
    }
    fwrite(tab, sizeof(Personne), n, f);
    fclose(f);
    printf("💾 Données sauvegardées dans %s\n", nomFichier);
}

// Charger depuis un fichier binaire
int charger(const char *nomFichier, Personne *tab) {
    FILE *f = fopen(nomFichier, "rb");
    if (!f) {
        perror("Erreur de chargement");
        return 0;
    }
    int n = fread(tab, sizeof(Personne), MAX, f);
    fclose(f);
    printf("📂 %d personnes chargées depuis %s\n", n, nomFichier);
    return n;
}

// Rechercher une personne
void rechercher(Personne *tab, int n) {
    int choix;
    printf("Rechercher par :\n1. Nom\n2. Âge\nVotre choix : ");
    scanf("%d", &choix); getchar();

    if (choix == 1) {
        char nom[50];
        printf("Nom à rechercher : ");
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = 0;

        int trouve = 0;
        for (int i = 0; i < n; i++) {
            if (strcmp(tab[i].nom, nom) == 0) {
                printf("🔍 Trouvé : %s, %d ans\n", tab[i].nom, tab[i].age);
                trouve = 1;
            }
        }
        if (!trouve)
            printf("Aucune personne trouvée avec ce nom.\n");
    } else if (choix == 2) {
        int age;
        printf("Âge à rechercher : ");
        scanf("%d", &age); getchar();

        int trouve = 0;
        for (int i = 0; i < n; i++) {
            if (tab[i].age == age) {
                printf("🔍 %s, %d ans\n", tab[i].nom, tab[i].age);
                trouve = 1;
            }
        }
        if (!trouve)
            printf("Aucune personne trouvée avec cet âge.\n");
    } else {
        printf("Choix invalide.\n");
    }
}

// Trier par nom ou âge
void trier(Personne *tab, int n, int critere) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            int swap = 0;
            if (critere == 1 && strcmp(tab[i].nom, tab[j].nom) > 0) {
                swap = 1;
            } else if (critere == 2 && tab[i].age > tab[j].age) {
                swap = 1;
            }

            if (swap) {
                Personne temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }
    printf("✅ Liste triée avec succès.\n");
}

// Exporter vers fichier texte
void exporter(Personne *tab, int n, const char *fichierTxt) {
    FILE *f = fopen(fichierTxt, "w");
    if (!f) {
        perror("Erreur lors de l'export");
        return;
    }

    fprintf(f, "--- Liste des personnes ---\n");
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d. %s, %d ans\n", i + 1, tab[i].nom, tab[i].age);
    }
    fclose(f);
    printf("📤 Liste exportée dans %s\n", fichierTxt);
}
