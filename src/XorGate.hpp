/*
 * XorGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef XORGATE
#define XORGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"

using namespace std;

class XorGate : public Gate
{
public:
    XorGate(Gate *g1, Gate *g2); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~XorGate();
};

#endif
