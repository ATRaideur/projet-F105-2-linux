#include <iostream>
#include "utils.hpp"




void huffman(char tableau_symbole[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], int tableau_f[MAX_NOEUDS], int tableau_parent[MAX_NOEUDS] , int tableau_enfant_gauche[MAX_NOEUDS], int tableau_enfant_droit[MAX_NOEUDS], int tab_length, const char *	 cheminArbre) {

	//cout << "voici la taille du tableau donner : " << tab_length << endl;

	//maintenant il faut rechercher les 2 indice avec la frequence la plus petite

	//fonction pour trouver le min ajouter a utils.cpp

	int idx_min_1 = 0;
	int idx_min_2 = 0;
	int f_min = 99999;

	// prendre minimum

	//il faut modifier les parent des 2 valeurs ajouter
	// il faut ajouter un nouveau noeud en indice de fin de liste qui est l'addition des 2 noeud orphelin
	// il faut faire cela jusque a ce qque la taille du denriner element de symbole est egale a la taille 
	// de la liste sans doublon

	int h ;
	const int inital_tab_lenght = tab_length;

	for(h = 0; h < inital_tab_lenght -1; h++){
	//cout << tab_length << endl;
	for (int m = 0; m < tab_length; m++) {
		int n;
		for (n = 0; n < tab_length; n++) {
			if (m != n && (tableau_f[m] + tableau_f[n]) <= f_min && (tableau_parent[m] == -1 && tableau_parent[n] == -1)){

				f_min = tableau_f[m] + tableau_f[n];
				idx_min_1 = m;
				idx_min_2 = n;
				
				//modification des parent

				
			}
		}

	}
	f_min = 9999;
	//cout << "voici les 2 indices min choisi : " << idx_min_1 << "  et " << idx_min_2 <<endl; 
	//cout << "voci la taille du tableau :  " << tab_length << endl;
	tableau_parent[idx_min_1] = tab_length;
	tableau_parent[idx_min_2] = tab_length;
	//tableau_symbole[indexeurChar] = temp_char;
	tableau_parent[tab_length] = -1;
	tableau_enfant_gauche[tab_length] = -1;
	tableau_enfant_droit[tab_length] = -1;
	tableau_f[tab_length] = tableau_f[idx_min_1] + tableau_f[idx_min_2];
	tableau_enfant_droit[tab_length] = idx_min_2;
	tableau_enfant_gauche[tab_length] = idx_min_1;



	// ici terminer la boucle for qui ecrit plusieur charactere
	int v;
	int total_lenght_symb_1 = getlenchar(tableau_symbole[idx_min_1]);
	for(v = 0; v < total_lenght_symb_1; v++){
	tableau_symbole[tab_length][v] = tableau_symbole[idx_min_1][v];
	}
	//cout << "voici la longueur du premier char  : "<<total_lenght_symb_1 << endl;
	int y;
	int total_lenght_symb_2 = getlenchar(tableau_symbole[idx_min_2]);
	//cout << "voici la longueur du deuxieme char  : "<<total_lenght_symb_2 << endl;

	int total = total_lenght_symb_2 + total_lenght_symb_1;
	//cout << "et voici le total : "<< total << endl;
	for(y = 0 ; y < total ; y++){
	tableau_symbole[tab_length][y + total_lenght_symb_1] = tableau_symbole[idx_min_2][y];
	}



	tab_length += 1;


	//cout << tableau_f[idx_min_1] << "    " << tableau_f[idx_min_2] << endl;
	//cout << tableau_symbole[idx_min_1] << "      " << tableau_symbole[idx_min_2] << endl;




	// permet de print pour test

	
	}

	for (int j = 0; j < tab_length; j++) {

		cout << tableau_symbole[j] << "   " << tableau_f[j] << "   " << tableau_parent[j] << "    " << tableau_enfant_droit[j] << "    " << tableau_enfant_gauche[j] << endl;


	}
	sauverArbre( cheminArbre, tableau_parent, tableau_enfant_gauche, tableau_enfant_droit, tableau_symbole, 2* inital_tab_lenght -1);
}
// enfant droit supprimer car non neccesaire vu que nous avons un arbre binaire
// il suffit d'un enfant et d'un else pour representer l'aute ca nous permet de avoir une variable en moins.
void abreACode(int parent[MAX_NOEUDS], 
	int enfantGauche[MAX_NOEUDS], 
	char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], 
	char (&code)[TAILLE_ALPHABET_ASCII][TAILLE_MAX_MOT_CODE]){
	

	int indexNoeud;

	for (indexNoeud = 0; indexNoeud < MAX_NOEUDS; indexNoeud++) {

		if (getlenchar(symboles[indexNoeud]) == 1) {

			// conversion du symbole en int pour indicage 
			int indexCode = static_cast<int>(symboles[indexNoeud][0]);
			const char* mot_code_convert = motCode(parent, enfantGauche, symboles, MAX_NOEUDS, *symboles[indexNoeud]).c_str();
			write_in_dict(code[indexCode], mot_code_convert);

		}
	}

}

void encoderMessage(char code[TAILLE_ALPHABET_ASCII][TAILLE_MAX_MOT_CODE], 
	char message[TAILLE_MAX_MESSAGE], 
	char (&messageEncode)[TAILLE_MAX_MESSAGE_ENCODE]) {

	//string 	messageEncodage = "";
	char* messageCoder = new char[1000];
	int messageCoderIndex = 0; // Compteur pour "messageCoder"
	int i;
	for(i = 0; i < getlenchar(message) ; i++){
		int charactereInt = static_cast<int>(message[i]); // Convertir le caractère en entier
		
		if (*code[charactereInt] != '1' && *code[charactereInt] != '0'){
		cout << "vous avez inseré un mauvais charactére"<< endl;
		}
		
		//messageEncodage += code[charactereInt];

		for(int j = 0; j < getlenchar(code[charactereInt]); j++){
		messageCoder[messageCoderIndex] = code[charactereInt][j];
		cout << messageCoder[messageCoderIndex];
		//cout << messageCoder << endl;
		messageCoderIndex += 1;
		}



	}
	// conversion du string car fonction "sauverDandAdresseMemoire" a besoin d'un char
	//char* convertedstring = const_cast<char*>(messageEncodage.c_str());
	//sauverDansAdresseMemoire(messageEncode, convertedstring);
	cout << messageCoderIndex << endl;

	for(int l =0; l< messageCoderIndex; l++){
	messageEncode[l] = messageCoder[l] ;
	}

	delete[] messageCoder;

}


int main(int argc, char *argv[]) {
	const char *cheminMessage;
	const char *cheminArbre;
	const char *cheminMessageEncode;
   
	if (argc == 4) {
		cheminMessage = argv[1];
		cheminArbre = argv[2];
		cheminMessageEncode = argv[3];
	} else {
      std::cerr << "ulbzip doit prendre obligatoirement les 3 arguments "
                   "cheminMessage cheminArbre cheminMessageEcode" << std::endl;
		return 1;
	}
   
	static char message[TAILLE_MAX_MESSAGE];
	static char messageEncode[TAILLE_MAX_MESSAGE_ENCODE];

	static int nombreNoeuds;
	static int parent[MAX_NOEUDS];
	static int enfantGauche[MAX_NOEUDS];
	static int enfantDroite[MAX_NOEUDS];
	static char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII];
	static char code[TAILLE_ALPHABET_ASCII][TAILLE_MAX_MOT_CODE];

	chargerTexte(cheminMessage,message);


	////////////////////////////

	int longeur = getlenchar(message);
	char tableau_symbole[MAX_NOEUDS][TAILLE_ALPHABET_ASCII];
	int tableau_f[MAX_NOEUDS];
	int tableau_parent[MAX_NOEUDS];
	int tableau_enfant_gauche[MAX_NOEUDS];
	int tableau_enfant_droit[MAX_NOEUDS];
	int indexeurChar = 0;

	int i;
	for (i = 0; i < longeur; i++) {

		//ajoute un symbole dans un tableau si il ne se trouve pas deja dedans
		//initialise un symbole et la frequene du symbole
		if (isIn_2d(tableau_symbole, message[i], indexeurChar) == false) {

			tableau_symbole[indexeurChar][0] = message[i];
			tableau_f[indexeurChar] = 0;
			tableau_parent[indexeurChar] = -1;
			tableau_enfant_gauche[indexeurChar] = -1;
			tableau_enfant_droit[indexeurChar] = -1;
			indexeurChar += 1;
		
		}

	}


	int x;
	for (x = 0; x < longeur; x++) {

		int index = get_index_char_2d(tableau_symbole, message[x], indexeurChar);
		tableau_f[index] += 1;


	}
	///////////////////////////////////////////

	huffman(tableau_symbole, tableau_f, tableau_parent, tableau_enfant_gauche, tableau_enfant_droit, indexeurChar, cheminArbre);
	chargerArbre(cheminArbre, parent, enfantGauche, enfantDroite, symboles,nombreNoeuds);
	abreACode(parent, enfantGauche, symboles, code);
	encoderMessage(code, message, messageEncode);
	sauverFichierTexte(cheminMessageEncode, messageEncode);
	return 0;
}
