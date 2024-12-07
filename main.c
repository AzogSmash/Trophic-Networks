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

void afficherReseau(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs, const char *nomEcosysteme, const char *climat) {
    printf("\n=========================================\n");
    printf("   Description du reseau trophique : %s\n", nomEcosysteme);
    printf("=========================================\n");
    printf("Climat : %s\n", climat);
    printf("\nListe des sommets (especes) :\n");
    for (int i = 0; i < nbSommets; i++) {
        printf("  [%d] %s\n", i, sommets[i].nom);
    }
    printf("\nListe des arcs (interactions) avec ponderations :\n");
    for (int i = 0; i < nbArcs; i++) {
        printf("  - %s -> %s : %.2f\n",
               sommets[arcs[i].source].nom,
               sommets[arcs[i].destination].nom,
               arcs[i].ponderation);
    }
    printf("=========================================\n");
    printf("\nAppuyez sur Entree pour continuer...\n");
    getchar();
    getchar();
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
// Fonction pour simuler la dynamique de population d'une espèce
void simulationPopulationSommet(Sommet *sommet, float N0, float r, float K, int iterations) {
    printf("\n--- Simulation pour l'espèce : %s ---\n", sommet->nom);
    printf("Population initiale (N0) : %.2f\n", N0);
    printf("Taux de croissance (r) : %.2f\n", r);
    printf("Capacité de charge (K) : %.2f\n", K);
    printf("Nombre d'itérations : %d\n\n", iterations);

    float N = N0; // Population initiale
    printf("Itération\tPopulation (N)\n");
    printf("--------------------------------\n");

    for (int t = 0; t <= iterations; t++) {
        printf("%d\t\t%.2f\n", t, N);
        N = N + r * N * (1 - N / K); // Équation logistique
        if (N < 0) {
            N = 0; // Extinction
            break;
        }
    }
}

// Intégration dans le menus
void simulationMenu(Sommet *sommets, int nbSommets) {
    int sommetIndex;
    float N0, r, K;
    int iterations;

    printf("\n--- Simulation de population ---\n");
    printf("Sélectionnez un sommet (0-%d) : ", nbSommets - 1);
    scanf("%d", &sommetIndex);

    if (sommetIndex >= 0 && sommetIndex < nbSommets) {
        printf("Entrez la population initiale (N0) : ");
        scanf("%f", &N0);
        printf("Entrez le taux de croissance (r) : ");
        scanf("%f", &r);
        printf("Entrez la capacité de charge (K) : ");
        scanf("%f", &K);
        printf("Entrez le nombre d'itérations : ");
        scanf("%d", &iterations);

        // Appel de la simulation pour l'espèce sélectionnée
        simulationPopulationSommet(&sommets[sommetIndex], N0, r, K, iterations);
    } else {
        printf("Sommet invalide.\n");
    }
}


void sousMenuReseau(const char *nomEcosysteme, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    int sousChoix;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("=========================================\n");
        printf("        Menu du reseau : %s\n", nomEcosysteme);
        printf("=========================================\n");
        printf("1. Verifier la connexite du reseau\n");
        printf("2. Afficher les details d'un sommet\n");
        printf("3. Calculer les statistiques du graphe\n");
        printf("4. Identifier les sommets particuliers\n");
        printf("5. Retour au menu principal\n");
        printf("=========================================\n");
        printf("Votre choix : ");
        scanf("%d", &sousChoix);

        switch (sousChoix) {
            case 1:
                printf(verifierConnexite(sommets, nbSommets, arcs, nbArcs) ? "\nLe graphe est connexe.\n" : "\nLe graphe n'est pas connexe.\n");
                break;
            case 2: {
                int sommetIndex;
                printf("\nSelectionnez un sommet (0-%d) : ", nbSommets - 1);
                scanf("%d", &sommetIndex);
                if (sommetIndex >= 0 && sommetIndex < nbSommets) {
                    predecessorsAndSuccessors(sommetIndex, sommets, nbSommets, arcs, nbArcs);
                } else {
                    printf("\nSommet invalide.\n");
                }
                break;
            }
            case 3:
                calculerComplexite(nbSommets, nbArcs);
                break;
            case 4:
                analyserGraphe(sommets, nbSommets, arcs, nbArcs);
                break;
            case 5:
                printf("\nRetour au menu principal...\n");
                break;
            default:
                printf("\nChoix invalide. Veuillez reessayer.\n");
        }

        if (sousChoix != 5) {
            printf("\nAppuyez sur Entree pour continuer...\n");
            getchar();
            getchar();
        }
    } while (sousChoix != 5);
}


void menuPrincipal() {
    int choix;

    do {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        printf("=========================================\n");
        printf("        Programme Trophic Networks       \n");
        printf("=========================================\n");
        printf("1. Explorer le reseau de la jungle\n");
        printf("2. Explorer le reseau marin\n");
        printf("3. Explorer le reseau de la savane\n");
        printf("4. Quitter le programme\n");
        printf("=========================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 3) {
            const char *fichiers[] = {"jungle.txt", "marin.txt", "savane.txt"};
            char nomEcosysteme[50], climat[50];
            Sommet *sommets = NULL;
            Arc *arcs = NULL;
            int nbSommets, nbArcs;

            // Lecture du graphe
            lireGraphe(fichiers[choix - 1], nomEcosysteme, climat, &sommets, &nbSommets, &arcs, &nbArcs);

            // Affichage direct des informations du réseau
            afficherReseau(sommets, nbSommets, arcs, nbArcs, nomEcosysteme, climat);

            // Accéder au sous-menu
            sousMenuReseau(nomEcosysteme, sommets, nbSommets, arcs, nbArcs);

            // Libérer la mémoire
            free(sommets);
            free(arcs);
        } else if (choix == 4) {
            printf("\nMerci d'avoir utilise le programme. Au revoir !\n");
        } else {
            printf("\nChoix invalide. Veuillez reessayer.\n");
        }

        if (choix != 4) {
            printf("\nAppuyez sur Entree pour revenir au menu principal...\n");
            getchar();
            getchar();
        }
    } while (choix != 4);
}


int main() {
    menuPrincipal();
    return 0;
}