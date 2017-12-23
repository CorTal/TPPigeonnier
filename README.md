# Auteurs

CHEVALLIER Sullivan, TALARMAIN Corentin, LEBLOND Alexis

# Utilisation

1 - bash perf.sh
2 - Si d'autre tests veulent être effectué veuillez modifier les fichier satisfiable et insatisfiable dans le dossier /bin qui correspondent aux contraintes.
3 - Edition des contrainte c correspond à contrainte le chiffre suivant la valeur minimum de la contrainte, le chiffre suivant la valeur maximum de la contrainte et le dernier chiffre par exemple pour les pigeons correspond aux nombres de pigeon disponible.
# TPPigeonnier

Notre projet permet de résoudre le problème du pigeonnier mais aussi de rejouter des contraintes si besoin dans le code, 
à partir du moment qu'elles respectent la signature de ces dernière.
Une première amélioration serait donc de généraliser plus les contraintes de manière à pouvoir en ajouter plus facilement et modéliser plus facilement d'autres problèmes.

# Parallélisation

Pour paralléliser le problème, nous avons utilisé OpenMP. La méthode a été assez simple, il nous a suffi de paralléliser la boucle principale du solver. Pour ce faire, nous avons calculé le nombre total de matrices possible "nbSol". Ce nombre nous l'avons divisé par le nombre de coeurs pour obtenir "size", qui correspond au nombre de matrices à tester par coeur.
