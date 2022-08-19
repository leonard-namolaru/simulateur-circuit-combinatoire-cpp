/*
 * InputGate.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "InputGate.hpp"
#include "CircuitException.hpp"

/**
 * Constructeur.
 */
InputGate::InputGate(const char nomInputGate) : Gate{std::string(1,nomInputGate), false } {
	// Le nom dune entree (InputGate) ne peut etre que une lettre minuscule.
	try {
		if(nomInputGate < 'a' || nomInputGate > 'z')
			throw CircuitException("Le nom dune entree (InputGate) ne peut etre que une lettre minuscule. Une tentative a apparemment ete faite pour utiliser un autre caractere a cette fin");
	} catch(const CircuitException& circuitException) {
	cerr << circuitException.getMessage() << endl;
	exit(EXIT_FAILURE);
	}
}

bool InputGate::getValeurBooleenne() {
	return valeurBooleenne;
}

void InputGate::setValeurBooleenne(bool valeurBool){
	valeurBooleenne = valeurBool;
}


InputGate::~InputGate()
{

}
