/*
 * CircuitException.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef EXCEPTION
#define EXCEPTION
#include<iostream>
using namespace std;

class CircuitException {
private:
	string message;
public:
	CircuitException(const string& message);
	CircuitException();
	virtual ~CircuitException();
	string getMessage() const;
};

#endif /* EXCEPTION */
