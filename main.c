#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Fonction pour lire un graphe depuis un fichier texte
void lireGraphe(const char *nomFichier, char *nomEcosysteme, char *climat, Sommet **sommets, int *nbSommets, Arc **arcs, int *nbArcs) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        exit(1);
    }

    // Lecture du nom de l'ecosysteme et du climat
    fgets(nomEcosysteme, 50, fichier);
    nomEcosysteme[strcspn(nomEcosysteme, "\n")] = '\0';  // Retirer le saut de ligne
    fgets(climat, 50, fichier);
    climat[strcspn(climat, "\n")] = '\0';  // Retirer le saut de ligne

    // Lecture du nombre de sommets et d'arcs
    fscanf(fichier, "%d %d\n", nbSommets, nbArcs);

    // Allocation memoire pour les sommets et les arcs
    *sommets = (Sommet *)malloc(*nbSommets * sizeof(Sommet));
    *arcs = (Arc *)malloc(*nbArcs * sizeof(Arc));

    // Lecture des sommets
    for (int i = 0; i < *nbSommets; i++) {
        fgets((*sommets)[i].nom, 50, fichier);
        (*sommets)[i].nom[strcspn((*sommets)[i].nom, "\n")] = '\0';  // Retirer le saut de ligne
    }

    // Lecture des arcs
    for (int i = 0; i < *nbArcs; i++) {
        fscanf(fichier, "%d %d %f\n", &(*arcs)[i].source, &(*arcs)[i].destination, &(*arcs)[i].ponderation);
    }

    fclose(fichier);
}

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
// Fonction pour afficher les predecesseurs et successeurs d'un sommet
void predecessorsAndSuccessors(int sommetIndex, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    printf("\n--- Informations sur le sommet : %s ---\n", sommets[sommetIndex].nom);

    // Liste des predecesseurs
    printf("Predecesseurs :\n");
    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].destination == sommetIndex) {
            printf("  - %s\n", sommets[arcs[i].source].nom);
        }
    }

    // Liste des successeurs
    printf("Successeurs :\n");
    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].source == sommetIndex) {
            printf("  - %s\n", sommets[arcs[i].destination].nom);
        }
    }
}
// Fonction pour calculer la complexite du graphe
void calculerComplexite(int nbSommets, int nbArcs) {
    printf("\n--- Statistiques du graphe ---\n");
    printf("Nombre d'especes : %d\n", nbSommets);
    printf("Nombre de liaisons : %d\n", nbArcs);

    // Densite de liaison = arcs / (sommets * (sommets - 1))
    float densite = (float) nbArcs / (nbSommets * (nbSommets - 1));
    printf("Densite de liaison : %.2f\n", densite);
}
// Menu principal
void menuPrincipal() {
    int choix;

    do {
        printf("\n--- Menu Principal ---\n");
        printf("1. Reseau de la jungle\n");
        printf("2. Reseau marin\n");
        printf("3. Reseau de la savane\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 3) {
            // Chargement du fichier correspondant
            const char *fichiers[] = {"jungle.txt", "marin.txt", "savane.txt"};
            char nomEcosysteme[50], climat[50];
            Sommet *sommets = NULL;
            Arc *arcs = NULL;
            int nbSommets, nbArcs;

            lireGraphe(fichiers[choix - 1], nomEcosysteme, climat, &sommets, &nbSommets, &arcs, &nbArcs);

            // Sous-menu
            int sousChoix;
            do {
                printf("\n--- %s ---\n", nomEcosysteme);
                printf("1. Afficher le reseau\n");
                printf("2. Informations sur un sommet\n");
                printf("3. Statistiques du graphe\n");
                printf("4. Retour au menu principal\n");
                printf("Votre choix : ");
                scanf("%d", &sousChoix);

                switch (sousChoix) {
                    case 1:
                        afficherReseau(sommets, nbSommets, arcs, nbArcs, nomEcosysteme, climat);
                        break;
                    case 2: {
                        int sommetIndex;
                        printf("Selectionnez un sommet (0-%d) : ", nbSommets - 1);
                        scanf("%d", &sommetIndex);
                        if (sommetIndex >= 0 && sommetIndex < nbSommets) {
                            predecessorsAndSuccessors(sommetIndex, sommets, nbSommets, arcs, nbArcs);
                        } else {
                            printf("Sommet invalide.\n");
                        }
                        break;
                    }
                    case 3:
                        calculerComplexite(nbSommets, nbArcs);
                        break;
                    case 4:
                        printf("Retour au menu principal...\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
            } while (sousChoix != 4);

            // Liberation de la memoire
            free(sommets);
            free(arcs);
        } else if (choix == 4) {
            printf("Au revoir !\n");
        } else {
            printf("Choix invalide.\n");
        }
    } while (choix != 4);
}
int main() {
   menuPrincipal();
    return 0;
}