#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auth.h"
#include "gestion.h"

#define MAX 100

int main() {
    Personne personnes[MAX];
    int compteur = 0;
    char role[10];

    printf("=== Connexion requise ===\n");
    int choix;
    printf("1. Se connecter\n2. Créer un compte utilisateur\nVotre choix: ");
    scanf("%d", &choix); getchar();

    if (choix == 2) {
        creerCompte();
        return 0;
    }

    if (!verifierConnexion(role)) {
        printf("Échec de la connexion\n");
        return 1;
    }

    printf("Connexion réussie en tant que [%s]\n", role);
    int option;

    do {
        printf("\n--- MENU ---\n");
        printf("1. Ajouter une personne\n");
        printf("2. Afficher les personnes\n");
        if (strcmp(role, "admin") == 0) {
            printf("3. Supprimer une personne\n");
            printf("4. Rechercher\n");
            printf("5. Trier (1=Nom, 2=Âge)\n");
            printf("6. Exporter vers fichier texte\n");
            printf("7. Sauvegarder\n");
            printf("8. Charger\n");
            printf("9. Quitter\n");
        } else {
            printf("3. Quitter\n");
        }

        printf("Choix: ");
        scanf("%d", &option); getchar();

        if (strcmp(role, "admin") == 0) {
            switch (option) {
                case 1: ajouter(personnes, &compteur); break;
                case 2: afficher(personnes, compteur); break;
                case 3: supprimer(personnes, &compteur); break;
                case 4: rechercher(personnes, compteur); break;
                case 5: {
                    int c;
                    printf("1. Nom\n2. Âge\n> ");
                    scanf("%d", &c); getchar();
                    trier(personnes, compteur, c);
                    break;
                }
                case 6: exporter(personnes, compteur, "liste.txt"); break;
                case 7: sauvegarder("personnes.bin", personnes, compteur); break;
                case 8: compteur = charger("personnes.bin", personnes); break;
            }
        } else {
            switch (option) {
                case 1: ajouter(personnes, &compteur); break;
                case 2: afficher(personnes, compteur); break;
            }
        }
    } while ((strcmp(role, "admin") == 0 && option != 9) || (strcmp(role, "user") == 0 && option != 3));

    return 0;
}
