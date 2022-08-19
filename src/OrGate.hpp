/*
 * OrGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef ORGATE
#define ORGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"

using namespace std;

class OrGate : public Gate
{
public:
    OrGate(Gate *g1, Gate *g2); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~OrGate();
};

#endif
