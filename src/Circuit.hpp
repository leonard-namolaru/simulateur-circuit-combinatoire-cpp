/*
 * Circuit.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef CIRCUIT
#define CIRCUIT

#include "Gate.hpp"
#include <vector>
#include <iostream>
#include "InputGate.hpp"
#include "OutputGate.hpp"

using namespace std;

class Circuit
{
private:
	/* **** DATA **** */
	vector<InputGate*>* inputs;
	vector<OutputGate*>* ouputs;
	vector<Gate*>* gates;
	vector< vector<char>* >* affichageCircuit;
	vector< vector<Gate*>* >* simulationPasParPas;

	/* **** LA CONSTRUCTION DE L'AFFICHAGE DU CIRCUIT **** */
	vector<Gate*>* ajoutInputs();
	void ajoutCheminsApresInputs();
	void ajoutNomsOperationsLogiques(const vector<Gate*>* portesLogiquesAjouterAffichage);
	void ajoutCheminsApresOperationsLogiques();
	void ajoutAsterisquesApresChemins(unsigned int level);
	vector<Gate*>* trouverLesPortesLogiquesSuivantes(const vector<Gate*>* portesLogiquesPrecedentes);
public:
    Circuit(vector<InputGate*>* inputsCircuit, vector<Gate*>* gates, vector<OutputGate*>* ouputs);
    static Circuit* relireCircuitQuiEstDansUnFichier(const string& nomFichier);
    static Circuit* expressionTextuelleToCircuit(const string& expressionTextuelle);
    virtual ~Circuit();

    void changerValeursDesPortesEntree();// Permet de changer les valeurs booléennes des entrées du circuit (false par défaut)
    void simulation(); // Simulation en mode pas à pas

    void afficheCircuit()  const;
    string afficherSousFormeTextuelle() const; // Renvoie une chaîne de caractères qui représente le circuit.
    void sauvegarderCircuitDansFichier(const string& nomFichier) const;
};

#endif
