                                                        RESEAUX TROPHIQUE



Ce projet consiste à analyser et modéliser des réseaux trophiques en utilisant des graphes pour représenter les interactions
entre différentes espèces dans un écosystème. Le programme permet de charger des réseaux à partir de fichiers texte, d'afficher
des informations sur les espèces, de vérifier la connexité du réseau, et de simuler la dynamique des populations.



## PREREQUIS:

    -Langage : C
    -Plugin sur Clion : DOT language 


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

  ## Fonctionnalités
  
       La modélisation des réseaux trophiques pour divers écosystèmes, tels que l'Amazonie, l'Océanie et la savane africaine, permet d'analyser les dynamiques 
      de population et leurs impacts écologiques. Cette approche utilise une équation de croissance logistique pour simuler les variations de population.


   ## Sources 

     - [Dépôt GitHub](https://github.com/AzogSmash/Trophic-Networks)
    - [Documentation en ligne sur Graphviz](https://dreampuf.github.io/GraphvizOnline/)
    - [FishBase](https://www.fishbase.se/)
    - [Globalbi] https://www.globalbioticinteractions.org/




















  
        
