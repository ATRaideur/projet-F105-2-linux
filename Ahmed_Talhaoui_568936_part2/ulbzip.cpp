#include <iostream>
#include "utils.hpp"



void huffman(char tableau_symbole[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], int tableau_f[MAX_NOEUDS], int tableau_parent[MAX_NOEUDS] , int tableau_enfant_gauche[MAX_NOEUDS], int tableau_enfant_droit[MAX_NOEUDS], int tab_length, const char *	 cheminArbre) {

	//initialisations de valeurs sentinels .
	int idx_min_1 = 0;
	int idx_min_2 = 0;
	int f_min = 99999;


	// longeur du tableau inital.
	const int inital_tab_lenght = tab_length;

	int h ;
	//boucle qui pose tout les nouveau : noeud arbres avec 0 ou 2 enfants = 2*n - 1
	//on a deja n dans tableau donc boucle : longeur du tableau pour le * 2 et - 1
	for(h = 0; h < inital_tab_lenght -1; h++){

	for (int m = 0; m < tab_length; m++) {
		int n;
		for (n = 0; n < tab_length; n++) {
			//recherche des 2 minimums orphelins dans le tableau
			if (m != n && (tableau_f[m] + tableau_f[n]) <= f_min && (tableau_parent[m] == -1 && tableau_parent[n] == -1)){
				
				//permet de trouver la frequence des mot minimum 
				f_min = tableau_f[m] + tableau_f[n];
				idx_min_1 = m;
				idx_min_2 = n;
								
			}
		}

	}
	//remise de la valeurs sentinel a defaut.
	f_min = 9999;


	//initialisation des nouveau noeud parents
	//et modification des parent des noeud orphelins
	tableau_parent[idx_min_1] = tab_length;
	tableau_parent[idx_min_2] = tab_length;
	tableau_parent[tab_length] = -1;
	tableau_enfant_gauche[tab_length] = -1;
	tableau_enfant_droit[tab_length] = -1;
	tableau_f[tab_length] = tableau_f[idx_min_1] + tableau_f[idx_min_2];
	tableau_enfant_droit[tab_length] = idx_min_2;
	tableau_enfant_gauche[tab_length] = idx_min_1;



	// permet de concaterner dans le tableau les symbole du min 1
	int v;
	int total_lenght_symb_1 = getlenchar(tableau_symbole[idx_min_1]);
	for(v = 0; v < total_lenght_symb_1; v++){
		tableau_symbole[tab_length][v] = tableau_symbole[idx_min_1][v];
	}

	int y;
	int total_lenght_symb_2 = getlenchar(tableau_symbole[idx_min_2]);
	int total = total_lenght_symb_2 + total_lenght_symb_1;
	// permet de concaterner dans le tableau les symbole du min 2
	for(y = 0 ; y < total ; y++){
		tableau_symbole[tab_length][y + total_lenght_symb_1] = tableau_symbole[idx_min_2][y];
	}
	tab_length += 1; //permet d'agrandir le tableau de 1 case a chaque iteration
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

        if (indexNoeud >= MAX_NOEUDS) {
            break;
        }

        if (symboles[indexNoeud] == NULL) {
            continue;
        }

        if (getlenchar(symboles[indexNoeud]) == 1) {

            // conversion du symbole en int pour indicage 
            int indexCode = static_cast<int>(symboles[indexNoeud][0]);

            if (indexCode < 0 || indexCode >= TAILLE_ALPHABET_ASCII) {
                continue;
            }

            if (getlenchar(symboles[indexNoeud]) <= 0) {
                continue;
            }

            if (&code[indexCode] == NULL) {
                continue;
            }

            const char* mot_code_convert = motCode(parent, enfantGauche, symboles, MAX_NOEUDS, *symboles[indexNoeud]).c_str();
            write_in_dict(code[indexCode], mot_code_convert);
        }
    }
}


void encoderMessage(char code[TAILLE_ALPHABET_ASCII][TAILLE_MAX_MOT_CODE], 
	char message[TAILLE_MAX_MESSAGE], 
	unsigned char (messageEncode)[TAILLE_MAX_MESSAGE_ENCODE]) {

	unsigned char* messageCoder = new unsigned char[TAILLE_MAX_MESSAGE];
	int messageCoderIndex = 0; // Compteur pour "messageCoder"
	int i;
	//erit tout les bit dans le unsigned char : messageCoder
	for(i = 0; i < getlenchar(message) ; i++){
		int charactereInt = static_cast<int>(message[i]); // Convertir le caractère en entier
		
		if (*code[charactereInt] != '1' && *code[charactereInt] != '0'){
		}
		

		for(int j = 0; j < getlenchar(code[charactereInt]); j++){
			if(code[charactereInt][j] == '1' || code[charactereInt][j] == '0'){
		messageCoder[messageCoderIndex] = code[charactereInt][j];

		messageCoderIndex += 1;
		}
		}
	}

	int indexeur_bit = 0;
	int valeur_binaire = 0b00000000;
	int compteur_bits = 7;
	int l;

	for( l =0; l< messageCoderIndex ; l++){
		if(messageCoder[l] == '1'){
			if (compteur_bits == 8) compteur_bits -= 1; 
			valeur_binaire += expo(2, (compteur_bits));

		}

		compteur_bits -= 1;
		if (compteur_bits < 0){

			compteur_bits = 7;

			messageEncode[indexeur_bit] = valeur_binaire ;

			cout << indexeur_bit << endl;
			indexeur_bit += 1;
			valeur_binaire = 0b00000000;

			
			}



	}

	if ((l == messageCoderIndex) && (compteur_bits != 0) ){
			messageEncode[indexeur_bit]  = valeur_binaire;

			int surplus = compteur_bits + 1;
			messageEncode[indexeur_bit + 1] = surplus;


			}


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
   
	char* message = new char[TAILLE_MAX_MESSAGE];
	unsigned char* messageEncode = new unsigned char[TAILLE_MAX_MESSAGE_ENCODE];
	int* nombreNoeuds = new int;
	int* parent = new int[MAX_NOEUDS];
	int* enfantGauche = new int[MAX_NOEUDS];
	int* enfantDroite = new int[MAX_NOEUDS];
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
	chargerArbre(cheminArbre, parent, enfantGauche, enfantDroite, symboles,nombreNoeuds[0]);
	abreACode(parent, enfantGauche, symboles, code);
	encoderMessage(code, message, messageEncode);
	sauverFichierTexteBis(cheminMessageEncode, messageEncode, 1130);

	delete[] message;
	delete[] messageEncode;
	delete nombreNoeuds;
	delete[] parent;
	delete[] enfantDroite;
	delete[] enfantGauche;
 	return 0;
}
