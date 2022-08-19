/*
 * InputGate.hpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */

#ifndef INPUTGATE
#define INPUTGATE

#include "Gate.hpp"
#include "CircuitException.hpp"
#include <vector>
#include <iostream>

using namespace std;

class InputGate : public Gate{
public:
    InputGate(const char nomInputGate); // Constructeur.
    bool getValeurBooleenne() override;
    void setValeurBooleenne(bool valeurBool);
    virtual ~InputGate();
};

#endif
