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

    // Lecture du nom de l'écosystème et du climat
    fgets(nomEcosysteme, 50, fichier);
    nomEcosysteme[strcspn(nomEcosysteme, "\n")] = '\0';
    fgets(climat, 50, fichier);
    climat[strcspn(climat, "\n")] = '\0';

    // Lecture du nombre de sommets et d'arcs
    fscanf(fichier, "%d %d\n", nbSommets, nbArcs);

    // Allocation mémoire pour les sommets et les arcs
    *sommets = (Sommet *)malloc(*nbSommets * sizeof(Sommet));
    *arcs = (Arc *)malloc(*nbArcs * sizeof(Arc));

    // Lecture des sommets
    for (int i = 0; i < *nbSommets; i++) {
        fgets((*sommets)[i].nom, 50, fichier);
        (*sommets)[i].nom[strcspn((*sommets)[i].nom, "\n")] = '\0'; // Retirer le saut de ligne
    }

    // Lecture des arcs
    for (int i = 0; i < *nbArcs; i++) {
        fscanf(fichier, "%d %d %f\n", &(*arcs)[i].source, &(*arcs)[i].destination, &(*arcs)[i].ponderation);
    }

    fclose(fichier);
}

// Fonction pour afficher les informations sur le réseau trophique
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

// Fonction pour afficher les prédécesseurs et successeurs d'un sommet
void predecessorsAndSuccessors(int sommetIndex, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    printf("\n--- Informations sur le sommet : %s ---\n", sommets[sommetIndex].nom);

    // Liste des prédécesseurs
    printf("Predecesseurs :\n");
    int hasPredecessors = 0;
    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].destination == sommetIndex) {
            printf("  - %s\n", sommets[arcs[i].source].nom);
            hasPredecessors = 1;
        }
    }
    if (!hasPredecessors) {
        printf("  Aucun\n");
    }

    // Liste des successeurs
    printf("Successeurs :\n");
    int hasSuccessors = 0;
    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].source == sommetIndex) {
            printf("  - %s\n", sommets[arcs[i].destination].nom);
            hasSuccessors = 1;
        }
    }
    if (!hasSuccessors) {
        printf("  Aucun\n");
    }
}

// Fonction pour calculer la complexité du graphe
void calculerComplexite(int nbSommets, int nbArcs) {
    printf("\n--- Statistiques du graphe ---\n");
    printf("Nombre d'especes : %d\n", nbSommets);
    printf("Nombre de liaisons : %d\n", nbArcs);

    // Densité de liaison = arcs / (sommets * (sommets - 1))
    float densite = (float) nbArcs / (nbSommets * (nbSommets - 1));
    printf("Densite de liaison : %.2f\n", densite);
}

// Fonction pour analyser les caractéristiques particulières du graphe
void analyserGraphe(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    int *predCount = (int *)calloc(nbSommets, sizeof(int)); // Compte les prédécesseurs
    int *succCount = (int *)calloc(nbSommets, sizeof(int)); // Compte les successeurs

    // Parcourir les arcs pour remplir les compteurs
    for (int i = 0; i < nbArcs; i++) {
        predCount[arcs[i].destination]++; // La destination a un prédateur
        succCount[arcs[i].source]++;      // La source a une proie
    }

    // 1. Producteurs primaires
    printf("\n--- Producteurs primaires ---\n");
    int found = 0;
    for (int i = 0; i < nbSommets; i++) {
        if (succCount[i] == 0) {
            printf("  - %s\n", sommets[i].nom);
            found = 1;
        }
    }
    if (!found) printf("  Aucun\n");

    // 2. Super-prédateurs
    printf("\n--- Super-predateurs ---\n");
    found = 0;
    for (int i = 0; i < nbSommets; i++) {
        if (predCount[i] == 0) {
            printf("  - %s\n", sommets[i].nom);
            found = 1;
        }
    }
    if (!found) printf("  Aucun\n");

    // 3. Une seule source de nourriture
    printf("\n--- Especes avec une seule source de nourriture ---\n");
    found = 0;
    for (int i = 0; i < nbSommets; i++) {
        if (succCount[i] == 1) {
            printf("  - %s\n", sommets[i].nom);
            found = 1;
        }
    }
    if (!found) printf("  Aucune\n");

    // 4. Proies partagées
    printf("\n--- Proies partagees par plusieurs predateurs ---\n");
    found = 0;
    for (int i = 0; i < nbSommets; i++) {
        int predatorCount = 0;
        for (int j = 0; j < nbArcs; j++) {
            if (arcs[j].destination == i) {
                predatorCount++;
            }
        }
        if (predatorCount >= 2) {
            found = 1;
            printf("%s est consomme par :\n", sommets[i].nom);
            for (int j = 0; j < nbArcs; j++) {
                if (arcs[j].destination == i) {
                    printf("  - %s\n", sommets[arcs[j].source].nom);
                }
            }
        }
    }
    if (!found) printf("  Aucune\n");


    free(predCount);
    free(succCount);
}
// Fonction DFS pour explorer les sommets atteignables
void dfs(int sommet, int *visite, Arc *arcs, int nbArcs, int nbSommets) {
    visite[sommet] = 1; // Marquer le sommet comme visité
    for (int i = 0; i < nbArcs; i++) {
        // Si l'arête part du sommet courant et mène à un sommet non visité
        if (arcs[i].source == sommet && !visite[arcs[i].destination]) {
            dfs(arcs[i].destination, visite, arcs, nbArcs, nbSommets);
        }
    }
}

// Fonction pour vérifier la connexité du graphe
int verifierConnexite(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    int *visite = (int *)calloc(nbSommets, sizeof(int)); // Tableau de visite pour les sommets

    // Lancer DFS à partir du sommet 0
    dfs(0, visite, arcs, nbArcs, nbSommets);

    // Vérifier si tous les sommets ont été visités
    for (int i = 0; i < nbSommets; i++) {
        if (!visite[i]) {
            free(visite);
            return 0; // Si un sommet n'est pas visité, le graphe n'est pas connexe
        }
    }

    free(visite);
    return 1; // Si tous les sommets ont été visités, le graphe est connexe
}

// Menu principal
void menuPrincipal() {
    int choix;

    do {
        system("cls");
        printf("\n Menu Principal \n");
        printf("1. Reseau de la jungle\n");
        printf("2. Reseau marin\n");
        printf("3. Reseau de la savane\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 3) {
            const char *fichiers[] = {"C:\\Trophic-Networks\\jungle.txt", "C:\\Trophic-Networks\\marin.txt", "C:\\Trophic-Networks\\savane.txt"};
            char nomEcosysteme[50], climat[50];
            Sommet *sommets = NULL;
            Arc *arcs = NULL;
            int nbSommets, nbArcs;

            lireGraphe(fichiers[choix - 1], nomEcosysteme, climat, &sommets, &nbSommets, &arcs, &nbArcs);

            int sousChoix;
            do {
                system("cls");
                printf("\n--- %s ---\n", nomEcosysteme);
                printf("1. Afficher le reseau\n");
                printf("2. Connexite du sommet \n");
                printf("3. Informations sur un sommet\n");
                printf("4. Statistiques du graphe\n");
                printf("5. Sommets particuliers\n");
                printf("6. Retour au menu principal\n");
                printf("Votre choix : ");
                scanf("%d", &sousChoix);

                switch (sousChoix) {
                    case 1:
                        afficherReseau(sommets, nbSommets, arcs, nbArcs, nomEcosysteme, climat);
                        break;
                    case 2: {
                        if (verifierConnexite(sommets, nbSommets, arcs, nbArcs)) {
                            printf("Le graphe est connexe.\n");
                        } else {
                            printf("Le graphe n'est pas connexe.\n");
                        }
                        break;
                    }


                    case 3: {
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
                    case 4:
                        calculerComplexite(nbSommets, nbArcs);
                        break;
                    case 5:
                        analyserGraphe(sommets, nbSommets, arcs, nbArcs);
                        break;
                    case 6:
                        printf("Retour au menu principal...\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                }
                if (sousChoix != 6) {
                    printf("\nAppuyez sur une touche pour revenir !");
                    getchar();
                    getchar();
                }
            } while (sousChoix != 6);

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