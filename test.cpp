#include <iostream>
#include "utils.hpp"

using namespace std;

void count_message_f(char message[]) {

	int longeur = getlenchar(message);
	char tableau_symbole[50];
	int tableau_f[50];
	int tableau_parent[50];
	int tableau_enfant_gauche[50];
	int tableau_enfant_droit[50];
	int indexeurChar = 0;

	int i;
	for (i = 0; i < longeur ; i++) {

		//ajoute un symbole dans un tableau si il ne se trouve pas deja dedans
		//initialise un symbole et la frequene du symbole	
		if (isIn(tableau_symbole, message[i]) == false) {

			tableau_symbole[indexeurChar] = message[i];
			tableau_f[indexeurChar] = 0;
			tableau_parent[indexeurChar] = -1;
			tableau_enfant_gauche[indexeurChar] = -1;
			tableau_enfant_droit[indexeurChar] = -1;
			indexeurChar += 1;

		}

	}

	int lenght_tab_f = getlentabint(tableau_f);
	int lenght_tab_symb = getlenchar(tableau_symbole);

	int x;
	for(x = 0; x < longeur ; x++){
	
		int index = get_index_char(tableau_symbole, message[x], longeur);
		tableau_f[index] += 1;
	
	
	}



	//maintenant il faut rechercher les 2 indice avec la frequence la plus petite

	//fonction pour trouver le min ajouter a utils.cpp

	int idx_min_1 = 0;
	int idx_min_2 = 0;
	int f_min = 9999;

	// getlentabint fonctionne prob autre part
	cout << lenght_tab_f << endl;
	cout << lenght_tab_symb << endl;
	for (int m = 0; m < lenght_tab_symb ; m++) {
		int n ;
		for ( n = 0; n < lenght_tab_symb; n++) {
			if (m != n && (tableau_f[m] + tableau_f[n]) <= f_min ){
				
				f_min = tableau_f[m] + tableau_f[n];
				cout << "voci les differente valeur du minimum    :" << f_min << endl;
				idx_min_1 = m;
				idx_min_2 = n;
				
			}
		}

	}

	cout << "voici les 2 indice des nombre : " << endl;
	cout << idx_min_1 << "   et     " << idx_min_2 << endl;
	

	cout << "voici les valeurs" << endl << endl;
	cout << tableau_f[idx_min_1] << "    " << tableau_f[idx_min_2] << endl;
	cout << tableau_symbole[idx_min_1] << "      " << tableau_symbole[idx_min_2] << endl;





	// permet de print pour test

	for (int j = 0; j < indexeurChar; j++) {

		//cout << tableau_symbole[j] << "   " << tableau_f[j] << "   " << tableau_parent[j] << "    " << tableau_enfant_droit[j] << "    " << tableau_enfant_gauche[j] << endl;
		cout << tableau_symbole[j] << "   ";

	}
	
	cout << endl;
	for (int d = 0; d < indexeurChar; d++) {

		//cout << tableau_symbole[j] << "   " << tableau_f[j] << "   " << tableau_parent[j] << "    " << tableau_enfant_droit[j] << "    " << tableau_enfant_gauche[j] << endl;
		cout << tableau_f[d] << "   ";

	}


	
}

/// algo a l'air de fonctionner dans ulbzip
int main() {

	char text[1000] = "abbbbcddddeeeaaaslfjslsfslfjslaaaaaaaaef";

	count_message_f(text);




}