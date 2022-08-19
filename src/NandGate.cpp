/*
 * NandGate.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "NandGate.hpp"
#include "CircuitException.hpp"

/**
 * Constructeur.
 */
NandGate::NandGate(Gate *g1, Gate *g2) : Gate{"NAN", false} // Le nom d'une porte logique comportera toujours 3 caractères.
{
	// La longueur du nom d'une entrée qui est aussi une entrée du circuit est d'un caractère,
	// la longueur du nom d'une entrée qui est une porte logique est de 3 caractères.
	try {
		if(g1->getName().size() != g2->getName().size())
			throw CircuitException("Une porte logique peut avoir comme entrées deux entrées du circuit ou deux entrées qui sont des portes logiques. Mais il n'est pas possible de transférer une entrée du premier type et une seconde entrée du second type.");
	} catch(const CircuitException& circuitException) {
	cerr << circuitException.getMessage() << endl;
	exit(EXIT_FAILURE);
	}

    entrees->push_back(g1);
	entrees->push_back(g2);
}

bool NandGate::getValeurBooleenne() {
	valeurBooleenne = (!(this->getEntrees()->at(0)->getValeurBooleenne() && this->getEntrees()->at(1)->getValeurBooleenne()));
	return valeurBooleenne;
}

NandGate::~NandGate()
{

}
