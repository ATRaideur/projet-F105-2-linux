#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cstdio>

#include "utils.hpp"

using namespace std;

int chargerTexte(const char* cheminMessage, char* texte) {
    ifstream f(cheminMessage);

    if (f) {
        stringstream buffer;
        buffer << f.rdbuf();
        string tmp = buffer.str();
        strcpy(texte, tmp.c_str());
        return 0;
    }
    else {
        fprintf(stderr, "Fichier %s ne peut pas être ouvert\n", cheminMessage);
        return 1;
    }
}

int chargerArbre(const char* chemin, int* parent, int* gauche, int* droite, char symboles[][TAILLE_ALPHABET_ASCII], int& nombreNoeuds) {
    FILE* fichier = fopen(chemin, "r");
    bool continuer = true;
    unsigned int longueur;

    nombreNoeuds = 0;

    if (fichier == nullptr) {
        perror("Ouverture du fichier avec l'arbre");
        return 1;
    }

    while (continuer) {
        if (fscanf(fichier, "%d,%d,%d,%u,", &parent[nombreNoeuds], &gauche[nombreNoeuds],
            &droite[nombreNoeuds], &longueur) != 4) {
            fclose(fichier);

            if (ferror(fichier)) {
                cerr << "Impossible de lire l'entièreté du document." << endl;
                return 1;
            }
            else {
                return 0;
            }
        }

        if (fread(symboles[nombreNoeuds], sizeof(char), longueur, fichier) != longueur) {
            cerr << "Impossible de lire l'entièreté du document." << endl;
            fclose(fichier);
            return 1;
        }

        fgetc(fichier); // Lire le '\n' à la fin de la ligne

        symboles[nombreNoeuds][longueur] = '\0';

        ++nombreNoeuds;
    }

    fclose(fichier);
    return 0;
}

int sauverArbre(const char* chemin, int* parent, int* gauche, int* droite, char symboles[][TAILLE_ALPHABET_ASCII], int nombreNoeuds) {
    FILE* fichier = fopen(chemin, "w");

    if (fichier == nullptr) {
        perror("Ouverture du fichier avec l'arbre");
        return 1;
    }

    for (int i = 0; i < nombreNoeuds; i++) {
        fprintf(fichier, "%d,%d,%d,%lu,%s\n", parent[i], gauche[i], droite[i], strlen(symboles[i]), symboles[i]);
    }

    fclose(fichier);
    return 0;
}

int sauverFichierTexte(const char* cheminTexte, char* texte) {

    ofstream out(cheminTexte);
    if (out) {
        out.write((char*)texte, strlen(texte));
        out.close();
        return 0;
    }
    else {
        fprintf(stderr, "Fichier %s ne peut pas être ouvert\n",
            cheminTexte);
        return 1;
    }
}


int get_index_n(int array[], int n, int size){

    int i;
    int index = 0;
    for (i=0; i<=size; i = i + 1){
        if (array[i] == n) index = i;
        
   }
   return index;

}



int getlenchar(char* charactere){

    int len = 0;
    char end[2] = {"\0"};
    while (charactere[len] != end[0]) len ++ ;
    return len;
}

int getlentabint(int* tabint) {
  int len = 0;
    while (tabint[len] != 0) len++;
    return len;

}


int sauverDansAdresseMemoire(char* message, char* other){

    int i;
    int size = getlenchar(other);
    for (i=0; i<=size; i = i + 1){
        (message[i] = other[i]);
        
}
 return 0;
}




bool isIn(char suite_charactere[], char charactere) {

    int i;
    int longeur = getlenchar(suite_charactere);
    for (i = 0; i < longeur; i++) {
        if (suite_charactere[i] == charactere) {
            return true;
        }
    }
    return false;

}

string motCode(int parent[MAX_NOEUDS],
    int enfantGauche[MAX_NOEUDS],
    char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII],
    int nombreNoeuds, char  symbole_cible){

    string codeSymbole = "";
    // permet de trouver l'indice de la feuille contenant le symbole chercher
    int indexNoeud;
    for (indexNoeud = 0; indexNoeud < nombreNoeuds; indexNoeud++){
        if ((getlenchar(symboles[indexNoeud]) == 1) &&  (* symboles[indexNoeud] == symbole_cible))
            break;
        
    }

    char bit;

    int True = 0;
    while (True == 0) {

        indexNoeud = parent[indexNoeud];
        if (isIn(symboles[enfantGauche[indexNoeud]],symbole_cible)){

            bit = '0';

        }
        
        else {
            bit = '1';
        }
    codeSymbole = bit + codeSymbole;

        if (parent[indexNoeud] == -1) {
            True = 1;
    }
    }

    return codeSymbole;



}


void write_in_dict(char* dict, const char * value) {

    strcpy(dict, value);

}


int get_index_char(char array[], char charactere, int size) {

    int i;
    int index = 0;
    for (i = 0; i <= size; i++) {
        if (array[i] == charactere) index = i;

    }
    return index;
}

int get_index_char_2d(char array[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], char charactere, int size) {

    int i;
    int index = 0;
    for (i = 0; i <= size; i++) {
        if (array[i][0] == charactere) index = i;

    }
    return index;
}

bool isIn_2d(char suite_charactere[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], char charactere, int longeur) {

    int i;
    for (i = 0; i < longeur; i++) {
        if (suite_charactere[i][0] == charactere) {
            return true;
        }
    }
    return false;

}
