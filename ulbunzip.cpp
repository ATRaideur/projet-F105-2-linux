#include <iostream>
#include<stdio.h>

#include "utils.hpp"
using namespace std;

void decoderMessage(int parent[MAX_NOEUDS], 
	int enfantGauche[MAX_NOEUDS], 
	int enfantDroite[MAX_NOEUDS], 
	char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII],
	int nombreNoeuds, 
	char messageEncode[TAILLE_MAX_MESSAGE_ENCODE], 
	char (&message)[TAILLE_MAX_MESSAGE]) {
	
	int size = getlenchar(messageEncode);
	int indexRacine = get_index_n(parent,-1, nombreNoeuds);
	int indexNoeud = indexRacine;
	string messageDecode = "";
	
	const char* zero = "0";
	int bitIndexe;
	for(bitIndexe=0; bitIndexe<= size; bitIndexe = bitIndexe +1){
		if(messageEncode[bitIndexe] == zero[0]){
			indexNoeud = enfantGauche[indexNoeud];
		}
		else{
			indexNoeud = enfantDroite[indexNoeud];
		}

		if (getlenchar(symboles[indexNoeud])== 1){
			messageDecode += symboles[indexNoeud];
			indexNoeud = indexRacine;
		}

	}   

    //conversion et sauvegarde du message decoder dans "message":
	char* convertedstring = const_cast<char*>(messageDecode.c_str());
	sauverDansAdresseMemoire(message,convertedstring);

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
	static char messageEncode[TAILLE_MAX_MESSAGE_ENCODE];

	static int nombreNoeuds;
	static int parent[MAX_NOEUDS];
	static int enfantGauche[MAX_NOEUDS];
	static int enfantDroite[MAX_NOEUDS];
	static char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII];

	chargerTexte(cheminMessageEncode,messageEncode);
	chargerArbre(cheminArbre, parent, enfantGauche, enfantDroite, symboles,
		nombreNoeuds);
	decoderMessage(parent, enfantGauche, enfantDroite, symboles, nombreNoeuds,
		messageEncode, message);
	//j'ai modiffier ici car c'est message qui doit etre sauver dans chemin  et non messgeenccoder
	sauverFichierTexte(cheminMessage, message);

	return 0;
}