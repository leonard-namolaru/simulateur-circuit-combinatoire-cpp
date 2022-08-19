/*
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avanccs 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
### Simulateur de circuit combinatoire ###

############################## Compilation ##############################
lenny@DESKTOP-DMJ749K:/mnt/c/Users/lenny/git/projet-cpp$ ls
Debug  Diagramme_de_classes.png  README.md  Raport_Projet.pdf  src

lenny@DESKTOP-DMJ749K:/mnt/c/Users/lenny/git/projet-cpp$ cd src
lenny@DESKTOP-DMJ749K:/mnt/c/Users/lenny/git/projet-cpp/src$ make all

R�sultat attendu :

g++ --std=c++11 -Wall -c Gate.cpp
g++ --std=c++11 -Wall -c Circuit.cpp
g++ --std=c++11 -Wall -c CircuitException.cpp
g++ --std=c++11 -Wall -c main.cpp
g++ --std=c++11 -Wall -c Outils.cpp
g++ --std=c++11 -Wall -c AndGate.cpp
g++ --std=c++11 -Wall -c InputGate.cpp
g++ --std=c++11 -Wall -c OrGate.cpp
g++ --std=c++11 -Wall -c OutputGate.cpp
g++ --std=c++11 -Wall -c XorGate.cpp
g++ --std=c++11 -Wall -c NandGate.cpp
g++ --std=c++11 -Wall -c NorGate.cpp
g++ --std=c++11 -Wall -c XnorGate.cpp
g++ --std=c++11 -Wall -o mr Gate.o Circuit.o CircuitException.o main.o Outils.o AndGate.o InputGate.o OrGate.o OutputGate.o XorGate.o NandGate.o NorGate.o XnorGate.o


############################## Ex�cution ##############################
lenny@DESKTOP-DMJ749K:/mnt/c/Users/lenny/git/projet-cpp/src$ make test

R�sultat attendu :

**** MENU : SIMULATEUR DE CIRCUIT COMBINATOIRE ***
1- Afficher le circuit
2- Simulation en mode pas a pas
3- Changer les valeurs des portes d'entree
4- Afficher sous forme textuelle
5- Synthetiser un circuit a partir d'une expression textuelle
6- Sauvegarder un circuit dans un fichier
7- Relire un circuit qui est dans un fichier
8- Quitter
Votre choix :

############################## Le menu ##############################

Si vous tapez 1 directement apr�s la premi�re ex�cution du programme, 
cela affichera le cicruit correspondant au code existant dans le main.ccp servant juste d'affichage standard � l'utilisateur au d�marage de l'application.
L'utilisateur pourra ainsi voir les fonctionnalt�s du programme meme sans creation de circuit au pr�alable.

Pour d�marer la simulation en mode pas � pas , tapez 2.
Cela affichera l'evolution de l'information au fur et � mesur de son passage par les portes logiques.
En tapant 2 directement apr�s l'�x�cution du programme , le logiciel lance la simulation du circuit existant. 

Pour changer les valeurs des portes d'entr�e tapez 3.
Ensuite, pour chaque entr�e , le programme affiche l'ancienne valeur sous la forme suivante :
Nom de l'entr�e : " NOM D'ENTR�E"  ; Valeur : "VALEUR DE L'ENTR�E" 
Le programme demande ensuite � l'utilisateur de rentrer une nouvelle valeur ( soit 0 , soit 1 ).

Pour Afficher le circruit sous forme textuelle tapez 4.
En tapant 4 directement apr�s l'�x�cution du programme cette option renvoie le chaine suivante, qui correspond au circuit  existant:

A=AND(OR_(XOR(OR_(a,b),AND(a,b)),AND(OR_(c,d),AND(c,d))),XOR(OR_(AND(e,f),AND(a,b)),XOR(OR_(a,f),OR_(d,f))))  

Pour synth�tiser un circuit � partir d'une expression textuelle, tapez 5.
On aura alors � donner l'expression textuelle du circuit qu'on voudrait cr�er (cf. Exemples)

Pour sauvegarder un circuit dans un fichier, tapez 6.
La cha�ne sera enregistr�e dans un fichier nomm� circuit.txt dans le meme dossier.
Si le fichier n'existe pas, le syst�me le cr�era. S'il existe, le contenu pr�c�dent sera �cras�.

Pour relire un circuit qui est dans un fichier tapez 7 

############################## Exemples : synthetiser un circuit a partir d'une expression textuelle ##############################
Expression textuelle : option 5 du menu -> ENSUITE, Affichage : option 1 du menu

Expression textuelle : A=and(a,b)
Affichage :
b:0 ----*-
a:0 --*-+-
      | |
      AND
       |
       A
       
Expression textuelle : A=or(and(a,b),and(c,d))
Affichage :
d:0 ----*-----
c:0 --*-+-----
b:0 --+-+---*-
a:0 --+-+-*-+-
      | | | |
      AND AND
       |   |
       ** **
        | |
        OR_
         |
         A
         
         
Expression textuelle : A=xor(or(and(a,b),and(c,d)),nor(or(e,f),nand(g,k)))
Affichage :
k:0 ----*-------------
g:0 --*-+-------------
f:0 --+-+---*---------
e:0 --+-+-*-+---------
d:0 --+-+-+-+---*-----
c:0 --+-+-+-+-*-+-----
b:0 --+-+-+-+-+-+---*-
a:0 --+-+-+-+-+-+-*-+-
      | | | | | | | |
      NAN OR_ AND AND
       |   |   |   |
       ** **   ** **
        | |     | |
        NOR     OR_
         |       |
         **** ****
            | |
            XOR
             |
             A
                          
Expression textuelle :  A=and(xor(or(and(a,b),and(c,d)),nor(or(e,f),nand(g,k))),xor(or(and(z,y),and(x,w)),nor(or(u,v),nand(p,q))))
Affichage :
q:0 ----*-----------------------------
p:0 --*-+-----------------------------
v:0 --+-+---*-------------------------
u:0 --+-+-*-+-------------------------
w:0 --+-+-+-+---*---------------------
x:0 --+-+-+-+-*-+---------------------
y:0 --+-+-+-+-+-+---*-----------------
z:0 --+-+-+-+-+-+-*-+-----------------
k:0 --+-+-+-+-+-+-+-+---*-------------
g:0 --+-+-+-+-+-+-+-+-*-+-------------
f:0 --+-+-+-+-+-+-+-+-+-+---*---------
e:0 --+-+-+-+-+-+-+-+-+-+-*-+---------
d:0 --+-+-+-+-+-+-+-+-+-+-+-+---*-----
c:0 --+-+-+-+-+-+-+-+-+-+-+-+-*-+-----
b:0 --+-+-+-+-+-+-+-+-+-+-+-+-+-+---*-
a:0 --+-+-+-+-+-+-+-+-+-+-+-+-+-+-*-+-
      | | | | | | | | | | | | | | | |
      NAN OR_ AND AND NAN OR_ AND AND
       |   |   |   |   |   |   |   |
       ** **   ** **   ** **   ** **
        | |     | |     | |     | |
        NOR     OR_     NOR     OR_
         |       |       |       |
         **** ****       **** ****
            | |             | |
            XOR             XOR
             |               |
             ******** ********
                    | |
                    AND
                     |
                     A