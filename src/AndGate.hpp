/*
 * AndGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef ANDGATE
#define ANDGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"

using namespace std;

class AndGate : public Gate{
public:
    AndGate(Gate *p1, Gate *p2); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~AndGate();
};

#endif
