/*
 * Outils.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "Outils.hpp"

/**
 * vector<string>* Outils::StringTokenizer(string str, string delim) : Diviser une chaîne en jetons.
 * Le string de l'argument delim est le délimiteur pour séparer les jetons. Le string délimiteur lui-même n'est pas traités comme un jeton.
 * La fonction renvoie un pointeur vers un vecteur avec tous les jetons.
 */
vector<string>* Outils::StringTokenizer(string str, string delim) {
	const size_t NOT_FOUND = -1;
	vector<string>* tokens = new vector<string>;

	size_t indexDelim = str.find(delim);
	while (indexDelim != NOT_FOUND) {
		string nextToken = str.substr(0, indexDelim);
		str = str.substr(indexDelim + 1);

		tokens->push_back(nextToken);
		indexDelim = str.find(delim);
	}

	tokens->push_back(str);

	return tokens;
}

/**
 * vector<string>* Outils::StringVectorTokenizer(vector<string>* strVecteur, string delim)
 * Diviser toutes les chaînes stockées dans un vecteur de chaînes en jetons.
 * La fonction renvoie un pointeur vers un vecteur avec tous les jetons.
 */
vector<string>* Outils::StringVectorTokenizer(vector<string>* strVecteur, string delim) {
	const size_t NOT_FOUND = -1;
	vector<string>* tokens = new vector<string>;
	size_t indexDelim;

	for(unsigned int i = 0 ; i < strVecteur->size() ; i++) {
		indexDelim = strVecteur->at(i).find(delim);
		while (indexDelim != NOT_FOUND) {
			string nextToken = strVecteur->at(i).substr(0, indexDelim);
			strVecteur->at(i) = strVecteur->at(i).substr(indexDelim + 1);

			if (nextToken.size() != 0)
				tokens->push_back(nextToken);
			indexDelim = strVecteur->at(i).find(delim);
		}
		if (strVecteur->at(i).size() != 0)
			tokens->push_back(strVecteur->at(i));
	}

	return tokens;
}

Outils::Outils(){

}
