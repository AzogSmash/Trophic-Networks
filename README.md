                                                        RESEAUX TROPHIQUE



Ce projet consiste à analyser et modéliser des réseaux trophiques en utilisant des graphes pour représenter les interactions
entre différentes espèces dans un écosystème. Le programme permet de charger des réseaux à partir de fichiers texte, d'afficher
des informations sur les espèces, de vérifier la connexité du réseau, et de simuler la dynamique des populations.



PREREQUIS:

    -Langage : C
    -Plugin sur Clion : DOT language 


  CHOIX DES FORMATS DES FICHIERS
  
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


  SIMULATION DYNAMIQUE

        On a donc choisi deux possibilité pour la simulation dynamique : 
                           - On peut soit faire une simulation avec des valeurs de No ( Population initiale ), r ( Taux de croissance ) et K ( Capacité de charge ) prédéfinies. Ces valeurs on les a determinées en faisant des recherches par exemple pour la population initiale on a chercher le rapport entre chaque espéce. Ce sont donc des valeurs qui essaye de reproduire la réalité au mieux.
                           - On peut aussi le faire de facon manuelle afin de tester des paramete No, k ou r qui pourrait donc influencer le resultat " attendue ".
  
        
