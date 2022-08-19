/*
 * Circuit.cpp
 * Projet : Simulateur de circuit combinatoire - UE Langages a objets avances 2021 - 2022
 * M1 : Master Informatique fondamentale et appliquee - Universite de Paris.
 * @author AIT BENALI faycal, NAMOLARU leonard
 */
#include "Circuit.hpp"
#include "OrGate.hpp"
#include "XorGate.hpp"
#include "AndGate.hpp"
#include "OutputGate.hpp"
#include "Outils.hpp"

#include <iostream>
#include <fstream>
#include <map>

/**
 * void Circuit::changerValeursDesPortesEntree()
 * Une fonction qui permet de changer les valeurs booléennes des entrées du circuit (false par défaut).
 * La fonction parcours le vecteur des entrées du circuit et pour chacune elle présente à l'utilisateur
 * le nom de l'entrée à côté de la valeur booléenne courante. L'utilisateur est invité à entrer une valeur
 * booléenne (0 ou 1) pour chaque entrée. La fonction met alors à jour le vecteur qui stocke l'affichage du
 * circuit.
 */
void Circuit::changerValeursDesPortesEntree() {
	for(unsigned int i = 0 ; i < inputs->size() ; i++){
		cout << "Nom de l'entrée : " << inputs->at(i)->getName() << " ; Valeur : " << inputs->at(i)->getValeurBooleenne() << endl;
		cout << "Nouvelle valeur [1 / 0] : ";
		int tmp = inputs->at(i)->getValeurBooleenne();
		cin >> tmp;
		inputs->at(i)->setValeurBooleenne(tmp);
		cout << endl;
	}
	cout << endl;

	// La fonction met alors à jour le vecteur qui stocke l'affichage du circuit
	// la debut de chqaue ligne pour un input ressemble à ceci (par exemple) : a:0 -- (6 caractères)
	for(unsigned int i = 0 ; i < inputs->size() ; i++)
		affichageCircuit->at(i)->at(2) = to_string( inputs->at(i)->getValeurBooleenne() ).at(0); // to_string(int __val) ; char& string.at(size_type __n)
} // changerValeursDesPortesEntree()

/**
 * void Circuit::afficheCircuit() const
 * Une fonction qui parcours le vecteur qui mémorise l'affichage du circuit et l'affiche à l'écran.
 */
void Circuit::afficheCircuit() const {
	for(unsigned int i = 0 ; i < affichageCircuit->size() ; i++){ // Les lignes
		for(unsigned int j = 0 ; j < affichageCircuit->at(i)->size() ; j++){ // Les colonnes
			cout << affichageCircuit->at(i)->at(j);
		}
		cout << endl;
	}
	cout << endl;
} // afficheCircuit()

/**
 * string Circuit::afficherSousFormeTextuelle() const
 * Une fonction qui renvoie une chaîne de caractères qui représente le circuit.
 */
string Circuit::afficherSousFormeTextuelle() const {
	string str = ouputs->at(0)->getName(); // On commence par afficher le nom de la sortie
	str.append("=");
	str.append( ouputs->at(0)->getEntrees()->at(0)->getItineraireRecursif() );

	return str;
} // afficherSousFormeTextuelle()



void Circuit::sauvegarderCircuitDansFichier(const string& nomFichier) const {
	  string circuit = afficherSousFormeTextuelle();
	  ofstream fichier ( nomFichier.c_str() );
	  if (fichier.is_open()) {
		  fichier << circuit;
		  fichier.close();
	  }
	  else {
		  cerr << "Le fichier n'a pas pu être ouvert.";
	  }
}

Circuit* Circuit::relireCircuitQuiEstDansUnFichier(const string& nomFichier) {
	string expressionTextuelle = "";

	  ifstream fichier ( nomFichier.c_str() );
	  if (fichier.is_open()) {
		  fichier >> expressionTextuelle;
		  fichier.close();
	  }
	  else {
		  cerr << "Le fichier n'a pas pu être ouvert.";
		  return nullptr;
	  }

	return expressionTextuelleToCircuit(expressionTextuelle);
}

/**
 * Circuit(vector<InputGate*>* inputsCircuit, vector<Gate*>* gates, vector<OutputGate*>* ouputs) : Constructeur.
 * Le constructeur reçoit comme paramètre le vecteur des entrées, le vecteur des portes logiques et le vecteur des sorties.
 */
Circuit::Circuit(vector<InputGate*>* inputsCircuit, vector<Gate*>* gates, vector<OutputGate*>* ouputs)
: inputs{inputsCircuit}, ouputs{ouputs}, gates{gates}, affichageCircuit{new vector< vector<char>* >}, simulationPasParPas{new vector< vector<Gate*>* >} {

	try {
		if(ouputs->size() > 1)
			throw CircuitException("Bien qu'un circuit puisse être créé avec de nombreuses entrées, la limitation est que le circuit ne peut contenir qu'une seule sortie.");
	} catch(const CircuitException& circuitException) {
	cerr << circuitException.getMessage() << endl;
	exit(EXIT_FAILURE);
	}

	/**
	 * À l'intérieur du constructeur, nous remplissons deux vecteurs :
	 * 	vector< vector<char>* >* affichageCircuit : La représentation graphique du circuit.
	 * 	vector< vector<Gate*>* >* simulationPasParPas : Pour une utilisation future, lorsque l'utilisateur veut
	 * 	visualiser la vue pas à pas de l'évolution du flux d'informations dans le circuit,
	 * 	on stocke dans ce vecteur des pointeurs vers les portes logiques situées à chaque niveau de l'affichage du circuit.
	 */

	vector<Gate*>* portesLogiquesAvecEntreesQuiSontEntreesDuCircuit = ajoutInputs();
	simulationPasParPas->push_back(portesLogiquesAvecEntreesQuiSontEntreesDuCircuit);

	ajoutCheminsApresInputs(); // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')
	ajoutNomsOperationsLogiques(portesLogiquesAvecEntreesQuiSontEntreesDuCircuit);// Afficher les noms des opérations logiques
	ajoutCheminsApresOperationsLogiques(); // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')

	vector<Gate*>* portesLogiquesSuivantes = trouverLesPortesLogiquesSuivantes(portesLogiquesAvecEntreesQuiSontEntreesDuCircuit);
	vector<Gate*>* portesLogiquesPrecedentes = portesLogiquesAvecEntreesQuiSontEntreesDuCircuit;
	int level = 1, index = 1;
	while(portesLogiquesSuivantes->size() != 0) {
		simulationPasParPas->push_back(portesLogiquesSuivantes);

		if(portesLogiquesSuivantes->at(0)->getName().size() > 1)
			ajoutAsterisquesApresChemins(level);

		ajoutNomsOperationsLogiques(portesLogiquesSuivantes);// Afficher les noms des opérations logiques
		ajoutCheminsApresOperationsLogiques(); // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')

		level = level + (2 * index);
		index++;

		portesLogiquesPrecedentes = portesLogiquesSuivantes;
		portesLogiquesSuivantes = trouverLesPortesLogiquesSuivantes(portesLogiquesPrecedentes);
	} // while
} // Circuit()

Circuit::~Circuit()
{
	for(unsigned int i = 0 ; i < inputs->size() ; i++)
		delete inputs->at(i);

	for(unsigned int i = 0 ; i < gates->size() ; i++)
		delete gates->at(i);

	for(unsigned int i = 0 ; i < affichageCircuit->size() ; i++)
		delete affichageCircuit->at(i);

	delete inputs;
	delete gates;
	delete ouputs; // Une sortie du circuit doit être ajoutée à la fois au vecteur des portes logiques (gates) et au vecteur des sorties (ouputs).
	delete affichageCircuit;
}


/* **************** LA CONSTRUCTION DE L'AFFICHAGE DU CIRCUIT **************** */


/**
 * void Circuit::ajoutCheminsApresInputs()
 * Une methode qui recherche les positions des caractères '+' et '*' dans la dernière ligne du vecteur qui stocke l'affichage du circuit
 * et ajoute aux mêmes positions dans la ligne en dessous le caractère '|'
 */
void Circuit::ajoutCheminsApresInputs(){
	int longueurLigne = affichageCircuit->at(0)->size(); // Longueur d'une ligne
	affichageCircuit->push_back( new vector<char>(longueurLigne, ' ') ); // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')

	int nombreDeLignes = affichageCircuit->size(); // Le nombre de lignes maintenant stockées dans le vecteur qui représente l'affichage du circuit.

	// Nous parcourons l'avant-dernière ligne de l'affichage (La dernière ligne avant la nouvelle ligne que nous venons d'ajouter)
	for(unsigned int i = 0 ; i < affichageCircuit->at(nombreDeLignes-2)->size() ; i++) {
		if(affichageCircuit->at(nombreDeLignes-2)->at(i) == '+' || affichageCircuit->at(nombreDeLignes-2)->at(i) == '*')
			affichageCircuit->at(nombreDeLignes - 1)->at(i) = '|';
	} // for

} // ajoutCheminsApresInputs()

/**
 * void Circuit::ajoutCheminsApresOperationsLogiques()
 * Ajout de chemins (caractères '|') après avoir affiché les noms de portes logiques.
 * Le nom d'une porte logique est toujours composé de 3 caractères. Nous plaçons toujours le chemin sous la lettre du milieu.
 */
void Circuit::ajoutCheminsApresOperationsLogiques(){
	unsigned int longueurLigne = affichageCircuit->at(0)->size();// Longueur d'une ligne
	affichageCircuit->push_back( new vector<char>(longueurLigne, ' ') ) ; // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')

	int nombreDeLignes = affichageCircuit->size(); // Le nombre de lignes maintenant stockées dans le vecteur qui représente l'affichage du circuit.

	// Nous parcourons la dernière ligne de l'affichage (La dernière ligne avant la nouvelle ligne que nous venons d'ajouter)
	for(unsigned int i = 0 ; i < affichageCircuit->at(nombreDeLignes-2)->size() ; i++) {

		if(affichageCircuit->at(nombreDeLignes-2)->at(i) >= 'A' && affichageCircuit->at(nombreDeLignes-2)->at(i) <= 'Z') {
			if ((i != 0) && (affichageCircuit->at(nombreDeLignes-2)->at(i - 1) >= 'A' && affichageCircuit->at(nombreDeLignes-2)->at(i - 1) <= 'Z')) {
				if ((i != longueurLigne - 1) && ( (affichageCircuit->at(nombreDeLignes-2)->at(i + 1) >= 'A' && affichageCircuit->at(nombreDeLignes-2)->at(i + 1) <= 'Z') || (affichageCircuit->at(nombreDeLignes-2)->at(i + 1) == '_') ))
					affichageCircuit->at(nombreDeLignes-1)->at(i) = '|';
			} // if
		} // if

	} // for
} // ajoutCheminsApresOperationsLogiques()

/**
 * void Circuit::ajoutNomsOperationsLogiques(const vector<Gate*>* portesLogiquesAjouterAffichage)
 * La fonction affiche les noms des portes logiques. Le nom d'une porte logique comportera toujours 3 caractères.
 */
void Circuit::ajoutNomsOperationsLogiques(const vector<Gate*>* portesLogiquesAjouterAffichage){
	int longueurLigne = affichageCircuit->at(0)->size();// Longueur d'une ligne

	affichageCircuit->push_back( new vector<char>(longueurLigne, ' ') ) ; // Ajouter une  ligne à l'affichage du circuit
	int NombreDeLignesDansAffichage = affichageCircuit->size(); // Le nombre de lignes de l'affichage du circuit, y compris la ligne nouvellement ajoutée
	unsigned int d = 0;
	for(unsigned int i = 0 ; (i < affichageCircuit->at(NombreDeLignesDansAffichage - 1)->size()) && (d < portesLogiquesAjouterAffichage->size()) ; i++ ){
		if (affichageCircuit->at(NombreDeLignesDansAffichage - 2)->at(i) == '|' && affichageCircuit->at(NombreDeLignesDansAffichage - 1)->at(i) == ' ') {
			affichageCircuit->at(NombreDeLignesDansAffichage - 1)->at(i) = portesLogiquesAjouterAffichage->at(d)->getName().at(0);
			if(portesLogiquesAjouterAffichage->at(d)->getName().size() > 1)  affichageCircuit->at(NombreDeLignesDansAffichage - 1)->at(i + 1) = portesLogiquesAjouterAffichage->at(d)->getName().at(1);
			if(portesLogiquesAjouterAffichage->at(d)->getName().size() > 2) affichageCircuit->at(NombreDeLignesDansAffichage - 1)->at(i + 2) = portesLogiquesAjouterAffichage->at(d)->getName().at(2);
			d++;

		} // if
	} // for
} // ajoutNomsOperationsLogiques()

/**
 * vector<Gate*>* Circuit::trouverLesPortesLogiquesSuivantes(const vector<Gate*>* portesLogiquesPrecedentes)
 * Lors de la construction de l'affichage du circuit, à chaque étape on utilise les portes logiques de l'étape précédente de l'affichage
 * afin de repérer les portes logiques suivantes (on cherche quelles portes logiques reçoivent en entrées les portes logiques de
 * l'étape précédente). Si la fonction renvoie un vecteur vide, cela signifie que nous avons atteint la fin du circuit.
 */
vector<Gate*>* Circuit::trouverLesPortesLogiquesSuivantes(const vector<Gate*>* portesLogiquesPrecedentes){
	vector<Gate*>* portesLogiquesSuivantes = new vector<Gate*>;

	for(unsigned int i = 0 ; i < gates->size() ; i++ ){ // On parcours par le vecteur avec toutes les portes logiques
		bool check = true;
		// Pour chaque porte logique, nous parcourons le vecteur qui comprend les entrées de cette porte logique
		for(unsigned int j = 0 ; j < gates->at(i)->getEntrees()->size() ; j++) {
			bool found = false;
			// On vérifie si cette porte logique a une entrée qui est en fait une porte logique du niveau précédent du circuit
			for(unsigned int k = 0 ; k < portesLogiquesPrecedentes->size() ; k++) {
				if(portesLogiquesPrecedentes->at(k) == gates->at(i)->getEntrees()->at(j))
					found = true;
			} // for(k)

			if(!found) check = false;
		} // for(j)
		if(check) portesLogiquesSuivantes->push_back(gates->at(i));
	} // for(i)
	return portesLogiquesSuivantes;
} // trouverLesPortesLogiquesSuivantes()


vector<Gate*>* Circuit::ajoutInputs(){

	// Corrélation entre le nom d'un input avec le numéro de la ligne de ce input dans le vecteur de l'affichage.
	map<char,int> correlationEntreNomInputAvecNumeroLigneDansAffichage;
	for(unsigned int i = 0 ; i < inputs->size() ; i++) // Nous parcourons le vecteur qui inclut les entrées (inputs)
		correlationEntreNomInputAvecNumeroLigneDansAffichage.insert( make_pair(inputs->at(i)->getName().at(0), i));

	vector<Gate*>* portesLogiquesAvecEntreesQuiSontEntreesDuCircuit = new vector<Gate*>;
	// Le nombre d'entrées des portes logiques qui sont aussi des entrées du circuit
	int nombreEntreesPortesLogiquesQuiSontEntreesDuCircuit = 0;
	for(unsigned int i = 0 ; i < gates->size() ; i++){
		bool check = false;
		for(unsigned int j = 0 ; j < gates->at(i)->getEntrees()->size() ; j++) {

			// Si le nom dun Gate est de longeur 1, c'est un InputGate
			if(gates->at(i)->getEntrees()->at(j)->getName().size() == 1){
				check = true;
				nombreEntreesPortesLogiquesQuiSontEntreesDuCircuit++;
			}
		} // for(j)

		if(check) portesLogiquesAvecEntreesQuiSontEntreesDuCircuit->push_back(gates->at(i));
	} // for(i)

	// la debut de chqaue ligne pour un input ressemble à ceci (par exemple) : a:0 -- (6 caractères)
	const int NB_CHAR_AU_DEBUT_CHAQUE_LIGNE = 6; // Le nombre de caractères qui apparaissent toujours au début de chaque ligne d'un input
	int longueurLigneAffichage = NB_CHAR_AU_DEBUT_CHAQUE_LIGNE + nombreEntreesPortesLogiquesQuiSontEntreesDuCircuit*2;

	for(unsigned int i = 0 ; i < inputs->size() ; i++){ // Nous parcourons le vecteur qui inclut les entrées (inputs)
		affichageCircuit->push_back(new vector<char>(longueurLigneAffichage, '-')); // Pour chaque entrée, nous ajoutons une nouvelle ligne à l'affichage

		// La ligne commence par afficher le nom de l'entrée, sa valeur booléenne ainsi que quelques caractères supplémentaires pour l'affichage

		affichageCircuit->at(i)->at(0) = inputs->at(i)->getName().at(0); // Chaque ligne d'entrée commence par l'affichage du nom de l'entrée
		affichageCircuit->at(i)->at(1) =  ':'; // Après le nom d'entrée, nous affichons le caractère ':'

		// Après le caractère ':', on présente la valeur booléenne initiale
		// Nous obtenons la valeur booléenne en tant que int, nous transformons l'int en string,
		// puis en utilisant la méthode at() nous obtenons ce nombre en tant que caractère (char) afin qu'il puisse être ajouté au vecteur d'affichage qui se compose de caractères
		affichageCircuit->at(i)->at(2) =   to_string( inputs->at(i)->getValeurBooleenne() ).at(0); // to_string(int __val) ; char& string.at(size_type __n)

		affichageCircuit->at(i)->at(3) =  ' '; // Ajout d'un espace vide à l'affichage
		affichageCircuit->at(i)->at(4) =  '-'; // Ajout du caractère '-' à l'affichage
		affichageCircuit->at(i)->at(5) =  '-'; // Ajout du caractère '-' à l'affichage
	}

	/* Nous voulons dessiner une trajectoire de départ pour l'entrée.
	 * Dans l'itinéraire, nous ajouterons le caractère '*' en fonction du nombre de portes logiques qui reçoivent l'entrée actuelle en input.
	 * Le caractère '+' est en fait un point qui permet le passage pour d'autres entrées
	 */

	int positionProchainAsterisque = NB_CHAR_AU_DEBUT_CHAQUE_LIGNE; // La position du prochain astérisque
	for(unsigned int i = 0 ; i < portesLogiquesAvecEntreesQuiSontEntreesDuCircuit->size() && positionProchainAsterisque < longueurLigneAffichage; i++) {
		for(unsigned int j = 0 ; j < portesLogiquesAvecEntreesQuiSontEntreesDuCircuit->at(i)->getEntrees()->size(); j++) {

			// Si le nom dun Gate est de longeur 1, c'est un InputGate
			if(portesLogiquesAvecEntreesQuiSontEntreesDuCircuit->at(i)->getEntrees()->at(j)->getName().size() == 1) {
				char name = portesLogiquesAvecEntreesQuiSontEntreesDuCircuit->at(i)->getEntrees()->at(j)->getName().at(0);
				affichageCircuit->at(correlationEntreNomInputAvecNumeroLigneDansAffichage.at(name))->at(positionProchainAsterisque) = '*';
				positionProchainAsterisque += 2;
			} // if

		} // for
	} // for

	for(unsigned int i = 1 ; i < affichageCircuit->size() ; i++) {
		for(unsigned int j = 0; j < affichageCircuit->at(i)->size() ; j++) {
			if(affichageCircuit->at(i - 1)->at(j) == '+' || affichageCircuit->at(i - 1)->at(j) == '*')
				affichageCircuit->at(i)->at(j) = '+';
		}
	}

	return portesLogiquesAvecEntreesQuiSontEntreesDuCircuit;
} // ajoutInputs()

void Circuit::ajoutAsterisquesApresChemins(unsigned int level){
	unsigned int longueurLigne = affichageCircuit->at(0)->size();// Longueur d'une ligne
	affichageCircuit->push_back( new vector<char>(longueurLigne, ' ') ) ; // Ajouter une nouvelle ligne à l'affichage du circuit pour stocker des chemins (caractères '|')

	int nombreDeLignes = affichageCircuit->size(); // Le nombre de lignes maintenant stockées dans le vecteur qui représente l'affichage du circuit.
	bool alternance = false;
	vector<int> memo;

	for(unsigned int i = 0 ; i < affichageCircuit->at( affichageCircuit->size() -2 )->size() ; i++) {
		unsigned int j, count;
		if( affichageCircuit->at( affichageCircuit->size() -2 )->at(i) == '|' ){
			if(alternance){
				alternance = false;
				affichageCircuit->at( affichageCircuit->size() -1 )->at(i) = '*';
				for(j = i - 1, count = 0 ; count < level && j > 0 ; j--, count++)
					affichageCircuit->at( affichageCircuit->size() -1 )->at(j) = '*';
				memo.push_back(j + 1);
			} else {
				alternance = true;
				affichageCircuit->at( affichageCircuit->size() -1 )->at(i) = '*';
				for(j = i + 1, count = 0 ; count < level && j < longueurLigne ; j++, count++)
					affichageCircuit->at( affichageCircuit->size() -1 )->at(j) = '*';
				memo.push_back(j - 1);
			}
		}
	}

	affichageCircuit->push_back( new vector<char>(longueurLigne, ' ') ) ; // Ajouter une  ligne à l'affichage du circuit
	nombreDeLignes = affichageCircuit->size(); // Le nombre de lignes maintenant stockées dans le vecteur qui représente l'affichage du circuit.
	for(unsigned int i = 0 ; i < memo.size() ; i++)
		affichageCircuit->at(nombreDeLignes - 1)->at(memo.at(i)) = '|';
} // ajoutAsterisquesApresChemins()


/**
 * Simulation en mode pas à pas
 */
void Circuit::simulation() {
	cout << endl;

	cout << "**********************************************************************************************************************" << endl;
	cout << "Bonjour et bienvenue au simulateur de circuit combinatoire !" << endl;
	cout <<	"La simulation sera effectuée en mode pas à pas, c’est-à-dire qu’à chaque pas l’information franchit au plus une porte," << endl;
	cout <<	"et durant toutes les étapes vous pourrez voir dans l’affichage la progression de l’information" << endl;
	cout << "**********************************************************************************************************************" << endl;

	cout << endl;

	unsigned int nbInputs =  inputs->size();
	for(unsigned int i = 0 ; i < nbInputs ; i++){
		for(unsigned int j = 0 ; j < affichageCircuit->at(i)->size() ; j++){
			cout << affichageCircuit->at(i)->at(j);
		}
		cout << endl;
	}
	cout << endl;

	cout << "**********************************************************************************************************************" << endl;
	for(unsigned i = 0 ; i < inputs->size() ; i++)
		cout << inputs->at(i)->getName() << " : " << inputs->at(i)->getValeurBooleenne() << "     ";
	cout << endl;
	cout << "**********************************************************************************************************************" << endl;

	unsigned int position = nbInputs;
	for(unsigned int numeroDePas = 0 ; numeroDePas < simulationPasParPas->size() ; numeroDePas++) {

		for(unsigned int i = position ; i < position + 2 && i < affichageCircuit->size() ; i++){
			for(unsigned int j = 0 ; j < affichageCircuit->at(i)->size() ; j++){
				cout << affichageCircuit->at(i)->at(j);
			}
			cout << endl;
		}


		unsigned int stop = 1;
		for(unsigned int i = 0 ; i < simulationPasParPas->at(numeroDePas)->size() ; i++) {
			cout << "**********************************************************************************************************************" << endl;
			for(unsigned int j = 0  ; (j < stop) && (stop <=  simulationPasParPas->at(0)->size()) ; j++) {
					if(simulationPasParPas->at(numeroDePas)->at(j)->getEntrees()->size() > 1)
						cout << simulationPasParPas->at(numeroDePas)->at(j)->getName() << "(" << simulationPasParPas->at(numeroDePas)->at(j)->getEntrees()->at(0)->getName() << "," <<  simulationPasParPas->at(numeroDePas)->at(j)->getEntrees()->at(1)->getName() << ") : " << simulationPasParPas->at(numeroDePas)->at(j)->getValeurBooleenne() << "     ";
					else
						cout << simulationPasParPas->at(numeroDePas)->at(j)->getName() << " = " << simulationPasParPas->at(numeroDePas)->at(j)->getValeurBooleenne() << "     ";
			}
			cout << endl;
			cout << "**********************************************************************************************************************" << endl;
			stop++;
		}
		cout << endl;
		position = position + 4;
	}

}

Circuit* Circuit::expressionTextuelleToCircuit(const string& expressionTextuelle) {
	const size_t NOT_FOUND = -1;

	size_t indiceDeSigneEgal = expressionTextuelle.find("=");
	if(indiceDeSigneEgal == NOT_FOUND)
		return nullptr;

	string expressionPortesLogiques = expressionTextuelle.substr(indiceDeSigneEgal + 1);
	string nomOutput = expressionTextuelle.substr(0, indiceDeSigneEgal);

	vector<string>* tokens = Outils::StringTokenizer(std::string(expressionPortesLogiques), ",");
	vector<string>* tokens2 = Outils::StringVectorTokenizer(tokens, "(");
	vector<string>* listePortesLogiquesEtEntrees = Outils::StringVectorTokenizer(tokens2, ")");

	vector<InputGate*>* inputsVector = new vector<InputGate*>;
	vector<Gate*>* gatesVector = new vector<Gate*>;
	vector<OutputGate*>* outputsVector = new vector<OutputGate*>;

	map<string, string> tableauNomsInputs;
	for(int i = listePortesLogiquesEtEntrees->size() - 1 ; i >= 0  ; i--) {
		string gateName = listePortesLogiquesEtEntrees->at(i);
		if(gateName.size() == 1){

			if( tableauNomsInputs.count(gateName) == 0) {
				inputsVector->push_back( new InputGate(gateName.at(0)) );
				tableauNomsInputs.insert( make_pair(gateName,"") );
			}

		} else {
			int vectorSize = listePortesLogiquesEtEntrees->size();
			if((i + 2 < vectorSize) && (listePortesLogiquesEtEntrees->at(i + 1).size() == 1 && listePortesLogiquesEtEntrees->at(i + 2).size() == 1)){
					int numInputs = inputsVector->size();
					InputGate* input1 = inputsVector->at(numInputs - 1);
					InputGate* input2 = inputsVector->at(numInputs - 2);
					Gate* gate = Gate::getGateByName(gateName, input1, input2);
					gatesVector->push_back( gate );
			} else {
				int level = 1;
				bool stop = false;
				for(unsigned int j = i + 1 ; j < listePortesLogiquesEtEntrees->size() && stop == false ; j++) {
					if( listePortesLogiquesEtEntrees->at(j).size() == 1 )
						stop = true;
					else
						level*=2;
				}
				level--;

				try {
					if(level > 15)
						throw CircuitException("Le circuit est trop grand (trop de niveaux).");
				} catch(const CircuitException& circuitException) {
				cerr << circuitException.getMessage() << endl;
				exit(EXIT_FAILURE);
				}

				int numGates = gatesVector->size();
				Gate* input1 = gatesVector->at(numGates - 1);
				Gate* input2 = gatesVector->at(((numGates - 1))-level);
				Gate* gate = Gate::getGateByName(gateName, input1, input2);
				gatesVector->push_back( gate );
			} // else
		} // else
	} // for

	OutputGate* output = new OutputGate( nomOutput.at(0), gatesVector->at(gatesVector->size() - 1) );
	gatesVector->push_back( output );
	outputsVector->push_back(output);

	return new Circuit(inputsVector, gatesVector, outputsVector);
}
