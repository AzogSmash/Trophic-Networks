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

        Nous avons choisi deux approches pour la simulation dynamique :
        
        - 1. Simulation avec des paramètres prédéfinis - Cette méthode utilise des valeurs prédéterminées pour No (population initiale),
        r (taux de croissance) et K (capacité de charge). Ces valeurs ont été établies à partir de recherches approfondies, notamment en 
        analysant les proportions relatives entre les différentes espèces. L'objectif est de reproduire au mieux la réalité, avec des
        paramètres qui se rapprochent autant que possible des conditions naturelles. 
        
        - 2. Simulation manuelle pour explorer différents scénarios - Cette méthode permet de modifier manuellement les paramètres No,
        K ou r afin d'examiner leur influence sur le résultat attendu. Elle offre la possibilité de simuler des extinctions ou des
        disparitions partielles de certaines espèces et d'observer leurs répercussions sur une période donnée. Cela permet d'évaluer
        l'importance relative d'une espèce dans un écosystème spécifique.







  
        
