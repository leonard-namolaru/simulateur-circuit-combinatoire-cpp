/*
 * CircuitException.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "CircuitException.hpp"

CircuitException::CircuitException(const string& message) : message{message} {

}

CircuitException::CircuitException() : message{"Une erreur s'est produite mais malheureusement le système n'est pas en mesure de fournir une description plus détaillée"} {

}

string CircuitException::getMessage() const {
	return message;
}

CircuitException::~CircuitException() {
}
