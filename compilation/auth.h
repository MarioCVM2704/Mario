#ifndef AUTH_H
#define AUTH_H

#include <stdbool.h>

bool verifierConnexion(char *role);
void creerCompte();
char* hacherMotDePasse(const char *mdp, char *hashStr);

#endif
