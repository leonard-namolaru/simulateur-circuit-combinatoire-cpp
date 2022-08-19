/*
 * NorGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef NORGATE
#define NORGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"

using namespace std;

class NorGate : public Gate
{
public:
    NorGate(Gate *g1, Gate *g2); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~NorGate();
};

#endif
