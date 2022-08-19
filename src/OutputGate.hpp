/*
 * OutputGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#ifndef OUTPUTGATE
#define OUTPUTGATE

#include <vector>
#include <iostream>
#include "Gate.hpp"
using namespace std;

class OutputGate : public Gate
{
public:
    OutputGate(const char nomOutputGate, Gate* g); // Constructeur.
    bool getValeurBooleenne() override;
    virtual ~OutputGate();
};

#endif
