/*
 * NandGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef NANDGATE
#define NANDGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"
using namespace std;

class NandGate : public Gate{
public:
    NandGate(Gate *p1, Gate *p2); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~NandGate();
};

#endif
