/*
 * OutputGate.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "OutputGate.hpp"
#include "CircuitException.hpp"

/**
 * Constructeur.
 */
OutputGate::OutputGate(const char nomOutputGate, Gate* g) : Gate{std::string(1,nomOutputGate), false}
{
	// Le nom dune sortie (OutputGate) ne peut etre que une lettre majuscule.
	try {
		if(nomOutputGate < 'A' || nomOutputGate > 'Z')
			throw CircuitException("Le nom dune sortie (OutputGate) ne peut etre que une lettre majuscule. Une tentative a apparemment ete faite pour utiliser un autre caractere a cette fin.");
	} catch(const CircuitException& circuitException) {
		cerr << circuitException.getMessage() << endl;
		exit(EXIT_FAILURE);
	}
	entrees->push_back(g);
}

bool OutputGate::getValeurBooleenne() {
	valeurBooleenne = this->getEntrees()->at(0)->getValeurBooleenne();
	return valeurBooleenne;
}

OutputGate::~OutputGate()
{

}
