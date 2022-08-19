/*
 * Gate.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "Gate.hpp"
#include "XnorGate.hpp"
#include "XorGate.hpp"
#include "OrGate.hpp"
#include "AndGate.hpp"
#include "NorGate.hpp"
#include "NandGate.hpp"
#include <map>

/**
 * Constructeur 1.
 */
Gate::Gate(const string& nomGate, bool valeurBooleenne) : nomGate{nomGate}, entrees{new vector<Gate*>}, valeurBooleenne{valeurBooleenne}
{

}

/**
 * Constructeur 2.
 */
Gate::Gate(const string& nomGate) : nomGate{nomGate}, entrees{new vector<Gate*>}, valeurBooleenne{false}
{

}


vector<Gate*>* Gate::getEntrees() const{
	return entrees;
}

string Gate::getName() const {
	return nomGate;
}

bool Gate::getValeurBooleenne() {
	return valeurBooleenne;
}

string Gate::getItineraireRecursif() const {
	string str = this->getName();

	if(this->getEntrees()->size() > 0)  {
		str.append("(");
		str.append( this->getEntrees()->at(0)->getItineraireRecursif() );
	}

	if(this->getEntrees()->size() > 1)  {
		str.append( "," );
		str.append( this->getEntrees()->at(1)->getItineraireRecursif() );
	}

	if(this->getEntrees()->size() > 0)  {
		str.append(")");

	}

   return str;
}

Gate* Gate::getGateByName(const string& name, Gate* input1, Gate* input2) {
	Gate* gate = nullptr;
	map<string, int> mapOfGates = {
	        {"xor",1},
			{"XOR",1},
			{"OR",2},
			{"OR_",2},
	        {"or",2},
	        {"or_",2},
			{"AND",3},
	        {"and",3},
			{"NOR",4},
	        {"nor",4},
			{"XNO",5},
	        {"xno",5},
			{"XNOR",5},
	        {"xnor",5},
			{"NAN",6},
	        {"nan",6},
			{"NAND",6},
	        {"nand",6}
	};

	if(mapOfGates.count(name) == 0)
		return nullptr;

	switch(mapOfGates.at(name)) {
		case 1:
				gate = new XorGate(input1, input2);
				break;
		case 2:
				gate = new OrGate(input1, input2);
				break;
		case 3:
				gate = new AndGate(input1, input2);
				break;
		case 4:
				gate = new NorGate(input1, input2);
				break;
		case 5:
				gate = new XnorGate(input1, input2);
				break;
		case 6:
				gate = new NandGate(input1, input2);
				break;
	} // switch

	return gate;
}

Gate::~Gate()
{

}
