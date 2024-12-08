

#include "reseau_trophique.h"

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
    system("cls");
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
    visite[sommet] = 1; // Marque le sommet comme visité

    // Parcourir tous les arcs pour trouver les voisins du sommet actuel
    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].source == sommet) {
            int voisin = arcs[i].destination;
            if (!visite[voisin]) {
                dfs(voisin, visite, arcs, nbArcs, nbSommets); // Explorer le voisin
            }
        } else if (arcs[i].destination == sommet) {
            // Si le graphe est non orienté, considérer aussi les arcs inverses
            int voisin = arcs[i].source;
            if (!visite[voisin]) {
                dfs(voisin, visite, arcs, nbArcs, nbSommets); // Explorer le voisin
            }
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
        N = N + r * N * (1 - N / K); // Équation phare pour la dynamique de population
        if (N < 0) {
            N = 0; // Extinction
            break;
        }
    }
}


// Fonction pour simuler la dynamique des populations dans tout le réseau trophique
void simulationDynamique(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs, int iterations) {
    int choixSimulation;

    // Demander à l'utilisateur de choisir le type de simulation
    printf("\n--- Choisissez le mode de simulation ---\n");
    printf("1. Saisie manuelle des paramètres\n");
    printf("2. Utiliser des paramètres predefinis\n");
    printf("Votre choix : ");
    scanf("%d", &choixSimulation);

    // Declaration des tableaux de paramètres
    float *populations = (float *)malloc(nbSommets * sizeof(float));
    float *tauxCroissance = (float *)malloc(nbSommets * sizeof(float));
    float *capaciteCharge = (float *)malloc(nbSommets * sizeof(float));

    if (!populations || !tauxCroissance || !capaciteCharge) {
        printf("Erreur : allocation memoire pour les paramètres.\n");
        exit(1);
    }

    // Initialisation des paramètres
    if (choixSimulation == 1) {
        printf("\n--- Saisie manuelle des paramètres ---\n");
        for (int i = 0; i < nbSommets; i++) {
            printf("Entrez la population initiale pour l'espece '%s' : ", sommets[i].nom);
            scanf("%f", &populations[i]);
            if (populations[i] < 0) populations[i] = 0;  // Pas de valeurs negatives

            printf("Entrez le taux de croissance (r) pour l'espece '%s' : ", sommets[i].nom);
            scanf("%f", &tauxCroissance[i]);

            printf("Entrez la capacite de charge (K) pour l'espece '%s' : ", sommets[i].nom);
            scanf("%f", &capaciteCharge[i]);
        }
    } else if (choixSimulation == 2) {
        printf("\n--- Paramètres predefinis appliques ---\n");
        float valeursPopulations[] = {100, 50, 200, 150, 80, 70, 90, 120, 300, 250};
        float valeursTauxCroissance[] = {0.1, 0.05, 0.15, 0.2, 0.12, 0.08, 0.1, 0.09, 0.07, 0.06};
        float valeursCapaciteCharge[] = {500, 300, 700, 600, 400, 350, 450, 550, 800, 750};

        for (int i = 0; i < nbSommets; i++) {
            populations[i] = valeursPopulations[i % 10];
            tauxCroissance[i] = valeursTauxCroissance[i % 10];
            capaciteCharge[i] = valeursCapaciteCharge[i % 10];

            printf("  %s : Pop=%.2f, r=%.2f, K=%.2f\n", 
                   sommets[i].nom, populations[i], tauxCroissance[i], capaciteCharge[i]);
        }
    } else {
        printf("\nChoix invalide. Retour au menu precedent.\n");
        free(populations);
        free(tauxCroissance);
        free(capaciteCharge);
        return;
    }

    // Ouvrir le fichier de donnees pour Gnuplot
    FILE *fichierDonnees = fopen("simulation_data.txt", "w");
    if (!fichierDonnees) {
        printf("Erreur : Impossible de creer le fichier de donnees.\n");
        free(populations);
        free(tauxCroissance);
        free(capaciteCharge);
        return;
    }

    // Ajouter les entêtes au fichier de donnees
    fprintf(fichierDonnees, "Iteration");
    for (int i = 0; i < nbSommets; i++) {
        fprintf(fichierDonnees, "\t%s", sommets[i].nom);
    }
    fprintf(fichierDonnees, "\n");

    // Simulation des iterations
    for (int t = 0; t <= iterations; t++) {
        fprintf(fichierDonnees, "%d", t);

        for (int i = 0; i < nbSommets; i++) {
            fprintf(fichierDonnees, "\t%.2f", populations[i]);
        }
        fprintf(fichierDonnees, "\n");

        // Mise à jour des populations selon la dynamique logistique
        for (int i = 0; i < nbSommets; i++) {
            populations[i] += tauxCroissance[i] * populations[i] *
                              (1 - populations[i] / capaciteCharge[i]);
            if (populations[i] < 0) populations[i] = 0; // eviter des valeurs negatives
        }

        // Appliquer les interactions trophiques
        for (int i = 0; i < nbArcs; i++) {
            int source = arcs[i].source;
            int destination = arcs[i].destination;

            // Impact de la predation (pondere par l'arc)
            float impact = arcs[i].ponderation * populations[source];
            populations[destination] -= impact;
            if (populations[destination] < 0) populations[destination] = 0;

    // Libération des mémoires
    free(populations);
    free(tauxCroissance);
    free(capaciteCharge);

    printf("\n--- Fin de la simulation ---\n");
}


void afficherGraphiqueDot(const char *fichierDot) {
    char commande[256];
    snprintf(commande, sizeof(commande), "start %s", fichierDot);
    system(commande);
}
void calculerDemiDegres(int sommetIndex, Arc *arcs, int nbArcs, int *demiDegreEntrant, int *demiDegreSortant) {
    *demiDegreEntrant = 0;
    *demiDegreSortant = 0;

    for (int i = 0; i < nbArcs; i++) {
        if (arcs[i].destination == sommetIndex) {
            (*demiDegreEntrant)++;
        }
        if (arcs[i].source == sommetIndex) {
            (*demiDegreSortant)++;
        }
    }
}
void sousMenuDemiDegres(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    int sommetIndex;
    printf("\n--- Calcul des demi-degres ---\n");
    printf("Selectionnez un sommet (0-%d) : ", nbSommets - 1);
    scanf("%d", &sommetIndex);

    if (sommetIndex >= 0 && sommetIndex < nbSommets) {
        int demiDegreEntrant, demiDegreSortant;
        calculerDemiDegres(sommetIndex, arcs, nbArcs, &demiDegreEntrant, &demiDegreSortant);

        printf("\n--- Demi-degres pour l'espece : %s ---\n", sommets[sommetIndex].nom);
        printf("Demi-degre entrant : %d\n", demiDegreEntrant);
        printf("Demi-degre sortant : %d\n", demiDegreSortant);
    } else {
        printf("\nSommet invalide.\n");
    }

    printf("\nAppuyez sur Entrée pour continuer...\n");
    getchar();
    getchar();
}



void sousMenuReseau(const char *nomEcosysteme, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs) {
    int sousChoix;

    do {
        system("cls"); // Nettoyer l'écran pour Windows

        printf("=========================================\n");
        printf("        Menu du reseau : %s\n", nomEcosysteme);
        printf("=========================================\n");
        printf("1. Verifier la connexite du reseau\n");
        printf("2. Afficher les details d'un sommet\n");
        printf("3. Calculer les statistiques du graphe\n");
        printf("4. Identifier les sommets particuliers\n");
        printf("5. Lancer la simulation\n");
        printf("6. Calculer les demi-degres d'un sommet\n");
        printf("7. Retour au menu principal\n");
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
                printf("\nEntrez le nombre d'iterations pour la simulation : ");
                int iterations;
                 scanf("%d", &iterations);
                 simulationDynamique(sommets, nbSommets, arcs, nbArcs, iterations);
            break;
            case 6:
                sousMenuDemiDegres(sommets, nbSommets, arcs, nbArcs);
                break;

            case 7:
                printf("\nRetour au menu principal...\n");
                break;
            default:
                printf("\nChoix invalide. Veuillez reessayer.\n");
        }

        if (sousChoix != 7) {
            printf("\nAppuyez sur Entree pour continuer...\n");
            getchar();
            getchar();
        }
    } while (sousChoix != 7);
}

void menuPrincipal() {
    int choix;

    do {
        system("cls"); // Nettoyer l'écran pour Windows

        printf("=========================================\n");
        printf("        Programme Trophic Networks       \n");
        printf("=========================================\n");
        printf("1. Explorer le reseau de la jungle\n");
        printf("2. Explorer le reseau marin\n");
        printf("3. Explorer le reseau de la savane\n");
        printf("4. Charger un reseau depuis un fichier\n");
        printf("5. Quitter le programme\n");
        printf("=========================================\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix >= 1 && choix <= 4) {
            const char *fichiers[] = {"jungle.txt", "marin.txt", "savane.txt"};
            const char *fichiersDot[] = {"jungle.dot", "marin.dot", "savane.dot"};
            char cheminFichier[100], cheminFichierDot[100], nomEcosysteme[50], climat[50];
            Sommet *sommets = NULL;
            Arc *arcs = NULL;
            int nbSommets, nbArcs;

            if (choix == 4) {
                // Option pour charger un fichier personnalisé
                printf("\nEntrez le chemin du fichier a charger : ");
                scanf("%s", cheminFichier);
                printf("\nEntrez le chemin du fichier DOT associe : ");
                scanf("%s", cheminFichierDot);
            } else {
                // Fichiers prédéfinis
                strcpy(cheminFichier, fichiers[choix - 1]);
                strcpy(cheminFichierDot, fichiersDot[choix - 1]);
            }

            // Lecture du graphe
            lireGraphe(cheminFichier, nomEcosysteme, climat, &sommets, &nbSommets, &arcs, &nbArcs);

            // Affichage des informations textuelles du réseau
            afficherReseau(sommets, nbSommets, arcs, nbArcs, nomEcosysteme, climat);

            // Affichage graphique du fichier DOT
            afficherGraphiqueDot(cheminFichierDot);

            // Accéder au sous-menu
            sousMenuReseau(nomEcosysteme, sommets, nbSommets, arcs, nbArcs);

            // Libérer la mémoire
            free(sommets);
            free(arcs);
        } else if (choix == 5) {
            printf("\nMerci d'avoir utilise le programme. Au revoir !\n");
        } else {
            printf("\nChoix invalide. Veuillez reessayer.\n");
        }

        if (choix != 5) {
            printf("\nAppuyez sur Entree pour revenir au menu principal...\n");
            getchar();
            getchar();
        }
    } while (choix != 5);
}
