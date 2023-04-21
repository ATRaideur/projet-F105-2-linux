using namespace std;

#define MAX_NOEUDS 255
#define TAILLE_ALPHABET_ASCII 256
#define TAILLE_MAX_FICHIER_ARBRE 100000

#define TAILLE_MAX_MESSAGE 200000
#define TAILLE_MAX_MOT_CODE 25
#define TAILLE_MAX_MESSAGE_ENCODE ((TAILLE_MAX_MESSAGE) * (TAILLE_MAX_MOT_CODE))


/**
 * Charge le fichier texte cheminMessage dans texte.
 * @return: True si le fichier a pu être ouvert, sinon retourne False.
 **/
int chargerTexte(const char *cheminMessage, char * texte);

/**
 * Lit le fichier cheminArbre, le parse et extrait les variables parent, 
 * gauche (l'enfant de gauche), droite et symboles.
 **/
int chargerArbre(const char* chemin, int* parent, int* gauche, int* droite, char symboles[][TAILLE_ALPHABET_ASCII], int& nombreNoeuds);

/**
 * Sauve texte dans le fichier cheminTexte.
 **/
int sauverFichierTexte(const char* cheminTexte, char * texte);

int sauverFichierTexteBis(const char* cheminTexte, unsigned char* texte);



/**
 * permet d'avoir l'indice d'un element dans un tableaux
 * utiliser ceci pour la taille : int size = sizeof(array)/sizeof(array[0]);
 * en O(n)
 **/
int get_index_n(int array[], int n, int size);



/**
 * permet d'avoir la longeur d'un mot.
 * en O(n)
 **/
int getlenchar(char* charactere);


/**
 * permet d'ecrire dans message
 * en O(n)
 **/
int sauverDansAdresseMemoire(char* message, char* other);



/**
 * permet de verifier si un charactere est dans un tableau de char
 * en O(n)
 **/
bool isIn(char suite_charactere[], char charactere);



/**
 * permet de de convertir un symbole en code.
 **/
string motCode(int parent[MAX_NOEUDS],
    int enfantGauche[MAX_NOEUDS],
    char symboles[MAX_NOEUDS][TAILLE_ALPHABET_ASCII],
    int nombreNoeuds, char symbole_cible);


/**
 * permet d'assigner une cle sur un charactere a une valeur.
 * en bref (permet seulment d'ecrire a un indice dans un tableau)
 **/
void write_in_dict(char *dict, const char* value);


int chargerArbre(const char* chemin, int* parent, int* gauche, int* droite, char symboles[][TAILLE_ALPHABET_ASCII], int& nombreNoeuds);

int get_index_char(char array[], char charactere, int size);

int getlentabint(int* tabint);

int get_index_char_2d(char array[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], char charactere, int size);

bool isIn_2d(char suite_charactere[MAX_NOEUDS][TAILLE_ALPHABET_ASCII], char charactere, int longeur);

int sauverArbre(const char* chemin, int* parent, int* gauche, int* droite, char symboles[][TAILLE_ALPHABET_ASCII], int nombreNoeuds);

int expo(int base, int exp);

int chargerTexteBis(const char* cheminMessage, unsigned char* texte);

int getLenUnsignedChar(unsigned char* charactere);

int chargerTexteTers(const char* cheminMessage, char* texte);