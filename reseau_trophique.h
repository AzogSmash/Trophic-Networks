//
// Created by matte on 07/12/2024.
//

#ifndef RESEAU_TROPHIC_RESEAU_TROPHIQUE_H
#define RESEAU_TROPHIC_RESEAU_TROPHIQUE_H
//bibliotheque
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure
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
void lireGraphe(const char *nomFichier, char *nomEcosysteme, char *climat, Sommet **sommets, int *nbSommets, Arc **arcs, int *nbArcs);

// Fonction pour afficher le réseau trophique
void afficherReseau(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs, const char *nomEcosysteme, const char *climat);

// Fonction pour afficher les prédécesseurs et successeurs d'un sommet
void predecessorsAndSuccessors(int sommetIndex, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs);

// Fonction pour calculer la complexité du graphe
void calculerComplexite(int nbSommets, int nbArcs);

// Fonction pour analyser les caractéristiques particulières du graphe
void analyserGraphe(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs);

// Fonction DFS pour explorer les sommets atteignables
void dfs(int sommet, int *visite, Arc *arcs, int nbArcs, int nbSommets);

// Fonction pour vérifier la connexité du graphe
int verifierConnexite(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs);

// Fonction pour simuler la dynamique de population d'une espèce
void simulationPopulationSommet(Sommet *sommet, float N0, float r, float K, int iterations);

// Fonction (kais) pour simuler la dynamique de population
void simulationDynamique(Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs, int iterations)
// Intégration dans le menu
void simulationMenu(Sommet *sommets, int nbSommets);

// Fonction pour afficher un graphique DOT
void afficherGraphiqueDot(const char *fichierDot);

// Sous-menu pour explorer le réseau trophique
void sousMenuReseau(const char *nomEcosysteme, Sommet *sommets, int nbSommets, Arc *arcs, int nbArcs);
void menuPrincipal();
#endif //RESEAU_TROPHIC_RESEAU_TROPHIQUE_H
