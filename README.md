                                                        RESEAUX TROPHIQUE



Ce projet consiste à analyser et modéliser des réseaux trophiques en utilisant des graphes pour représenter les interactions
entre différentes espèces dans un écosystème. Le programme permet de charger des réseaux à partir de fichiers texte, d'afficher
des informations sur les espèces, de vérifier la connexité du réseau, et de simuler la dynamique des populations.



## PREREQUIS:

    -Langage : C
    -Plugin sur Clion : DOT language 
    -gnuplot

## Installation de Gnuplot

### Installation sous Windows
1. Rendez-vous sur le site officiel de Gnuplot : [http://www.gnuplot.info](http://www.gnuplot.info).
2. Téléchargez le fichier d'installation pour Windows (`gnuplot-x.x.x-win64-mingw.exe`).
3. Lancez l'installateur et suivez les étapes :
   - Acceptez les termes de la licence.
   - Sélectionnez le répertoire d'installation (par défaut, `C:\Program Files\gnuplot`).
   - Assurez-vous que l'option "Add Gnuplot to PATH" est cochée.
4. Vérifiez l'installation :
   - Ouvrez un terminal (PowerShell ou CMD).
   - Tapez `gnuplot` et appuyez sur Entrée. Si Gnuplot s'ouvre, l'installation a réussi.


##  CHOIX DES FORMATS DES FICHIERS
  
    -.txt
        Le format .txt a été notamment été choisi pour sa simplicité et sa lisibilité : il est simple a comprendre et a manipuler.
        Ainsi l'utilisateur peut facilement créer un fichier texte pour créer son propre réseau.
        De plus le fichier texte va être facilement lisible avec les bibliothèque de base contrairement à d'autres formats comme
        JSON ou XML.les fichiers texte peuvent être directement lus et écrits avec des fonctions de base en C comme fgets(),
        fscanf(), et fprintf(). cela simplifie grandement le programme.

    -.dot
        Le format .dot a été choisi comme langage graphique et pour décrire les graphes pour sa comptabilité avec le plugin "DOT language".
        Ce format permet ainsi de rendre visuel et encore plus compréhensible les reséaux trophique. De plus il permet de rajouter des
        couleurs pour marquer certaine caractéristique comme les niveaux trophiques et d'ajouter des élgende pour rendre encore plus
        simple la compréhesion du réseau


##  SIMULATION DYNAMIQUE

        Nous avons choisi deux approches pour la simulation dynamique : 
        
        1. Simulation avec des paramètres prédéfinis - Cette méthode utilise des valeurs prédéterminées
        pour No (population initiale), r (taux de croissance) et K (capacité de charge). Ces valeurs ont
        été établies à partir de recherches approfondies. Par exemple, pour K, nous avons pris en compte 
        la disponibilité des ressources nécessaires à chaque espèce, comme la biomasse des producteurs
        primaires ou l’espace disponible pour les grands prédateurs. Pour r, nous nous sommes basés sur
        des données biologiques, telles que les taux de reproduction observés, les cycles de vie des espèces,
        et leur capacité à se réguler dans des conditions naturelles. L'objectif est de reproduire au mieux
        la réalité, avec des paramètres qui reflètent les dynamiques écologiques naturelles.
        
        
        2. Simulation manuelle pour explorer différents scénarios - Cette méthode permet de modifier
        manuellement les paramètres No, K ou r afin d'examiner leur influence sur le résultat attendu.
        Par exemple, en augmentant K pour une espèce prédatrice, on pourrait simuler une augmentation 
        des ressources disponibles, comme une abondance soudaine de proies. Inversement, en réduisant r
        pour un producteur primaire, on pourrait modéliser l’impact de conditions environnementales
        défavorables, comme une sécheresse. Cette approche offre également la possibilité de simuler
        des extinctions ou des disparitions partielles de certaines espèces pour observer leurs 
        répercussions sur une période donnée. Cela permet d'évaluer l'importance relative d'une
        espèce dans un écosystème spécifique et de visualiser des effets tels que des cascades trophiques
        ou des oscillations dans les populations.

  ## FONCTIONNALITE
  
       La modélisation des réseaux trophiques pour divers écosystèmes, tels que l'Amazonie, l'Océanie et la savane africaine, permet d'analyser les dynamiques 
      de population et leurs impacts écologiques. Cette approche utilise une équation de croissance logistique pour simuler les variations de population.


 ## SOURCES

      - [Dépôt GitHub](https://github.com/AzogSmash/Trophic-Networks) : Ce dépôt est utilisé pour la gestion collaborative du projet, le suivi des versions, et pour partager le code avec le jury ou les évaluateurs.
      - [Documentation en ligne sur Graphviz](https://dreampuf.github.io/GraphvizOnline/) : Utilisée pour visualiser rapidement les fichiers DOT générés par le programme, permettant une vérification et une présentation claire des réseaux trophiques.
      - [FishBase](https://www.fishbase.se/) : Fournit des données biologiques et écologiques précises sur les espèces marines, utilisées pour valider les pondérations et les relations entre prédateurs et proies dans le réseau marin.
      - [Globalbiotic Interactions (GloBI)](https://www.globalbioticinteractions.org/) : Base de données interactive pour explorer les interactions trophiques et valider les graphes utilisés dans les simulations.
      - [CProgramming.com](https://www.cprogramming.com) : Tutoriels détaillés pour la programmation en C.
      - [Learn-C.org](https://www.learn-c.org) : Apprentissage interactif pour le langage C.
      - [GeeksforGeeks - Algorithmes de graphes](https://www.geeksforgeeks.org/graph-data-structure-and-algorithms/) : Références sur les algorithmes liés aux graphes.
      - [TutorialsPoint - Programmation C](https://www.tutorialspoint.com/cprogramming/index.htm) : Explications sur la gestion des fichiers et la mémoire.
      - [Gnuplot Official Site](http://www.gnuplot.info) : Documentation officielle pour les graphiques dynamiques.
      - [Graphviz Official Site](https://graphviz.org) : Documentation sur l'utilisation des fichiers DOT.
      - [Stack Overflow](https://stackoverflow.com) : Communauté pour résoudre des problèmes spécifiques en C.
      - [GitHub - Projets similaires](https://github.com) : Pour rechercher des implémentations similaires en open source.
      - [Reddit - r/C_Programming](https://www.reddit.com/r/C_Programming/) : Discussions et retours d'expérience sur la programmation en C.





















  
        
