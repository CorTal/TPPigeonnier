# Auteurs

CHEVALLIER Sullivan, TALARMAIN Corentin, LEBLOND Alexis

# Utilisation

1 - make all          <br />
2 - cd bin/           <br />
3 - ./solver -n <pigeons> -q <pigeonniers> || ./psolver -n <pigeons> -q <pigeonniers>

# TPPigeonnier

Notre projet permet de résoudre le problème du pigeonnier mais aussi de rejouter des contraintes si besoin dans le code, 
à partir du moment qu'elles respectent la signature de ces dernière.
Une première amélioration serait donc de généraliser plus les contraintes de manière à pouvoir en ajouter plus facilement et modéliser plus facilement d'autres problèmes.

# Parallélisation

Pour paralléliser le problème, nous avons utilisé OpenMP. La méthode a été assez simple, il nous a suffit de paralléliser la boucle principale du solveur. Pour ce faire, nous avons calculé le nombre total de matrices possible "nbSol". Ce nombre nous l'avons divisé par le nombre de coeurs pour obtenir "size", qui correspond au nombre de matrices à tester par coeur.