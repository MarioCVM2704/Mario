#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"
#include "utils.h"

bool verifierConnexion(char *role) {
    FILE *f = fopen("comptes.txt", "r");
    if (!f) {
        perror("Fichier comptes introuvable");
        return false;
    }

    char username[50], password[50], hashInput[65], ligne[120];
    printf("Nom d'utilisateur: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Mot de passe: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hacherMotDePasse(password, hashInput);

    while (fgets(ligne, sizeof(ligne), f)) {
        char user[50], hashStored[65], roleTemp[10];
        sscanf(ligne, "%s %s %s", user, hashStored, roleTemp);

        if (strcmp(user, username) == 0 && strcmp(hashStored, hashInput) == 0) {
            strcpy(role,roleTemp);
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

void creerCompte() {
    FILE *f = fopen("comptes.txt", "a");
    if (!f) {
        perror("Erreur ouverture fichier comptes");
        return;
    }

    char username[50], password[50], hashStr[65];
    printf("Créer un nouveau compte utilisateur\nNom d'utilisatuer: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Mot de passe: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    hacherMotDePasse(password, hashStr);
    fprintf(f, "%s %s user\n", username, hashStr);
    fclose(f);

    printf("Compte créé avec succés!\n");
}