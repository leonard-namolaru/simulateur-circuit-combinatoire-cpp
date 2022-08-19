/*
 * AndGate.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "AndGate.hpp"
#include "CircuitException.hpp"

/**
 * Constructeur.
 */
AndGate::AndGate(Gate *g1, Gate *g2) : Gate{"AND", false}
{
	// La longueur du nom d'une entree qui est aussi une entree du circuit est d'un caractere,
	// la longueur du nom d'une entree qui est une porte logique est de 3 caracteres.
	try {
		if(g1->getName().size() != g2->getName().size())
			throw CircuitException("Une porte logique peut avoir comme entrees deux entrees du circuit ou deux entrees qui sont des portes logiques. Mais il n'est pas possible dutiliser en meme temps une entree du premier type et une seconde entree du second type.");
	} catch(const CircuitException& circuitException) {
	cerr << circuitException.getMessage() << endl;
	exit(EXIT_FAILURE);
	}

    entrees->push_back(g1);
	entrees->push_back(g2);
}

bool AndGate::getValeurBooleenne() {
	valeurBooleenne = (this->getEntrees()->at(0)->getValeurBooleenne() && this->getEntrees()->at(1)->getValeurBooleenne());
	return valeurBooleenne;
}

AndGate::~AndGate()
{

}
