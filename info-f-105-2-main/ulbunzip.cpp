#include <iostream>
#include<stdio.h>

#include "utils.hpp"
using namespace std;

void decoderMessage(int parent[MAX_NOEUDS], 
	int enfantGauche[MAX_NOEUDS], 
	int enfantDroite[MAX_NOEUDS], 
	char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII],
	int nombreNoeuds, 
	unsigned char messageEncode[TAILLE_MAX_MESSAGE_ENCODE], 
	char (&message)[TAILLE_MAX_MESSAGE]) {
	
	int j;
	const int MAX_SIZE = getLenUnsignedChar(messageEncode); 
	int* tableau_decimale = new int[MAX_SIZE];
	char* messageBinaire = new char[MAX_SIZE * 8];
	for(j =0; j<= MAX_SIZE; j++){
		tableau_decimale[j] = (int)messageEncode[j];
		//cout << "voci la taille des char : " <<MAX_SIZE << endl;
		//cout << "voici le tableau en decimale :" <<tableau_decimale[j] << endl;
			}

	int k;
	int i;
	int compteur = 0;
	int temp_valeur = 0;
	for (i = 0; i < MAX_SIZE; i++){
		temp_valeur = tableau_decimale[i];
		for (k =0 ; k < 8; k++){
			if(temp_valeur >= expo(2, 7 - k)) {
					messageBinaire[compteur] = '1';
					temp_valeur -= expo(2, 7 - k);
					compteur += 1;
				}
			else{
				messageBinaire[compteur] = '0';
				compteur += 1; 
			}
		}


	}
	
	for(int p = 0; p < MAX_SIZE * 8; p++){
	//cout << messageBinaire[p]  << endl;

	}

		



	int indexRacine = get_index_n(parent,-1, nombreNoeuds);
	int indexNoeud = indexRacine;
	int messageIndex = 0;

	int bitIndexe;
	for(bitIndexe=0; bitIndexe<= MAX_SIZE * 8 - 1; bitIndexe = bitIndexe +1){
		if(messageBinaire[bitIndexe] == '0'){
			indexNoeud = enfantGauche[indexNoeud];
		}
		else{
			indexNoeud = enfantDroite[indexNoeud];
		}

		if (getlenchar(symboles[indexNoeud])== 1){
			message[messageIndex] = symboles[indexNoeud][0];
			indexNoeud = indexRacine;
			messageIndex++;
		}

	}   

delete[] messageBinaire;
delete[] tableau_decimale;
}



int main(int argc, char *argv[]) {
	const char *cheminMessage;
	const char *cheminArbre;
	const char *cheminMessageEncode;
	if (argc == 4) {
		cheminMessageEncode = argv[1];
		cheminArbre = argv[2];
		cheminMessage = argv[3];
	}
	else {
		std::cerr << "ulbunzip doit prendre obligatoirement les 3 arguments " 
			          "cheminMessageEcode cheminArbre cheminMessage " << std::endl;
		return 1;
	}
	static char message[TAILLE_MAX_MESSAGE];
	unsigned char* messageEncode = new unsigned char[TAILLE_MAX_MESSAGE_ENCODE];
	int* nombreNoeuds = new int;
	int* parent = new int[MAX_NOEUDS];
	int* enfantGauche = new int[MAX_NOEUDS];
	int* enfantDroite = new int[MAX_NOEUDS];
	static char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII];

	chargerTexteBis(cheminMessageEncode,messageEncode);
	chargerArbre(cheminArbre, parent, enfantGauche, enfantDroite, symboles,
		nombreNoeuds[0]);
	decoderMessage(parent, enfantGauche, enfantDroite, symboles, nombreNoeuds[0],
		messageEncode, message);
	//j'ai modiffier ici car c'est message qui doit etre sauver dans chemin  et non messgeenccoder
	sauverFichierTexte(cheminMessage, message);


	delete[] messageEncode;
	delete nombreNoeuds;
	delete[] parent;
	delete[] enfantDroite;
	delete[] enfantGauche;
	return 0;
}