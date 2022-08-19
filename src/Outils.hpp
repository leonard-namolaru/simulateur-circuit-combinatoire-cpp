/*
 * Outils.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef OUTILS
#define OUTILS

#include <iostream>
#include <vector>
#include "Gate.hpp"

using namespace std;

/**
 * Afin de ne pas trop charger la classe Circuit,
 * certaines fonctions auxiliaires ont été définies dans cette classe comme méthodes "static".
 */
class Outils {
private:
	Outils();
public:
	// Diviser une chaîne en jetons.
	static vector<string>* StringTokenizer(string str, string delim);

	// Diviser toutes les chaînes stockées dans un vecteur de chaînes en jetons.
	static vector<string>* StringVectorTokenizer(vector<string>* strVecteur, string delim);
};

#endif /* OUTILS */
