# Auteurs

CHEVALLIER Sullivan, TALARMAIN Corentin, LEBLOND Alexis

# Utilisation

1 - bash perf.sh <br />
2 - Si d'autres tests veulent être effectués, veuillez modifier les fichiers satisfiables et insatisfiables dans le dossier /bin qui correspondent aux contraintes. <br />
3 	- Edition des contraintes c correspond à contrainte
	-Le chiffre suivant à la valeur minimale de la contrainte
	-Le chiffre suivant à la valeur maximale de la contrainte 
	-Le dernier chiffre par exemple pour les pigeons correspond aux nombres de pigeons disponibles.
# TPPigeonnier

Notre projet permet de résoudre le problème du pigeonnier mais aussi de rajouter des contraintes si besoin dans le code, 
à partir du moment qu'elles respectent la signature nécessaire par la structure.
Une première amélioration serait donc de généraliser plus les contraintes de manière à pouvoir en ajouter plus facilement et modéliser plus facilement d'autres problèmes.

# Parallélisation

Pour paralléliser le problème, nous avons utilisé OpenMP. La méthode a été assez simple, il nous a suffit de paralléliser la boucle principale du solver. Pour ce faire, nous avons calculé le nombre total de matrices possible "nbSol". Ce nombre nous l'avons divisé par le nombre de coeurs pour obtenir "size", qui correspond au nombre de matrices à tester par coeur.
