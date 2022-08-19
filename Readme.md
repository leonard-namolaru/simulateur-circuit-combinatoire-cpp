# Projet UE Langages à objets avancés (Université Paris Cité, M1) - Simulateur de circuit combinatoire en C++ #
AIT BENALI faycal, NAMOLARU leonard

## Description ##
Un ensemble de types/fonctions permettant de créer un circuit combinatoire, 
c’est-à-dire un circuit sans boucle comprenant des portes logiques (AND, OR, NOR, etc) reliées ensembles par des « fils ». 
L’entrée du circuit est représentée par un ensemble de portes chacune représentant une variable booléenne nommée.

## Fonctionnalités ##
- Affichage du circuit sous une une forme agréable en mode texte (pas d’interface graphique)
- La simulation s’effectue en mode pas à pas, c’est-à-dire qu’à chaque pas l’information franchit au plus une porte, et il est possible de voir dans l’affichage la progression de l’information. 
- Affichage sous forme textuelle de la sortie à l’aide des variables d’entrée : Par exemple :A = xor(or(a, b), and(a, b)
- Autres fonctionnalités : sauver un circuit dans un fichier et le relire.

**Vous trouverez plus d'informations sur l'exécution et l'utilisation du projet dans le fichier `readme.txt`**
