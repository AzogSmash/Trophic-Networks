#include <stdio.h>
#include <stdlib.h>

// Structure pour un sommet
typedef struct {
    char nom[50];
} Sommet;

// Structure pour un arc
typedef struct {
    int source;
    int destination;
    float ponderation;
} Arc;
// Fonction pour afficher les informations sur le reseau trophique
void afficherReseau(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs, const char *nomEcosysteme, const char *climat) {
    printf("\n--- Description du reseau trophique : %s ---\n", nomEcosysteme);
    printf("Climat : %s\n", climat);
    printf("Liste des sommets (especes) :\n");
    for (int i = 0; i < nbSommets; i++) {
        printf("  - %s\n", sommets[i].nom);
    }
    printf("\nListe des arcs (interactions) avec ponderations :\n");
    for (int i = 0; i < nbArcs; i++) {
        printf("  - %s -> %s : %.1f\n",
               sommets[arcs[i].source].nom,
               sommets[arcs[i].destination].nom,
               arcs[i].ponderation);
    }
}


int main() {

    return 0;
}
