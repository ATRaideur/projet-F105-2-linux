import sys
from utils import chargerFichierTexte, sauverArbre
import numpy as np

def trouverNoeudsMerger(f, parent,nNoeuds):
	"""
	fonction qui retourne l'index des 2 noeuds orphelins qui vont avoir comme 
	parent le noeud qui va être ajouté à cette itération.
	
	- f est une liste qui encode le nombre d'occurences des symboles 
	(voir énoncé).
	- parent est une liste qui encode l'index des noeuds parents.
	- nNoeuds est un entier qui indique le nombre de noeuds dans le graphe à 
	l'itération où la fonction trouverNoeudMerger est appelée.
	
	"""
	# trouve l'index des noeuds orphelins et le stocke dans un tableau numpy. 	
	idxOrphelins = np.where(np.array(parent[:nNoeuds]) == -1)[0]

	# S'il n'y a que deux noeuds orphelins, on retourne ceux là	
	if len(idxOrphelins) == 2:
		return idxOrphelins[0], idxOrphelins[1]
	
	# sinon on trouve ceux avec la valeur minimum de f en faisant une 
	# partition de la liste. Ca aurait pu être implémenté également avec 2 
	# boucles (une pour trouver le premier noeud et la deuxième pour le deuxième noeud) 
	else:
		
		# tableau numpy qui contient les fréquences des noeuds orphelins
		fOrphelins = np.array(f)[idxOrphelins] 

		# Partition de fOrphelins avec le deuxième élément et on garde l'index 
		#  des deux premières entrées de la partition 
		a = np.argpartition(fOrphelins, 2)[:2]

		# retourne l'index de 2 noeuds orphelins avec f minimum
		return idxOrphelins[a[0]], idxOrphelins[a[1]]

def creerAbreHuffman(message):
	"""
	Fonction qui construit un arbre préfixe optimal pour le message donné en 
	entrée avec l'algorithme de Huffman.
	"""

	# Compte les symboles dans dans le message dans un dictionaire et 
	# le reformatte en 2 listes. 
	compteSymboles = dict()
	for symbole in message:
		compteSymboles[symbole] = compteSymboles.get(symbole,0)+1
	symboles, f = map(list, zip(*compteSymboles.items()))

	# initialise d'autres variables et alloue également la mémoire nécéssaire 
	# pour symboles et f.
	nombreFeuilles = len(symboles)
	nNoeudsAbreFinal = 2*nombreFeuilles-1
	symboles += [""]*(nombreFeuilles-1)
	f += [0]*(nombreFeuilles-1) 
	parent = [-1]*nNoeudsAbreFinal
	enfantGauche = [-1]*nNoeudsAbreFinal
	enfantDroite = [-1]*nNoeudsAbreFinal	

	# Algorithme de Huffman
	for i in range(nombreFeuilles-1):

		# index du noeud qui va être ajouté à cette itération	
		indexNouveauNoeud = nombreFeuilles+i

		# trouve ses deux neuds enfants
		idxNoeud1, idxNoeud2 = trouverNoeudsMerger(f, parent,indexNouveauNoeud)

		# Ajoute le noeud parent en mettant à jour les différentes variables 
		# représentant l'arbre 
		parent[idxNoeud1] = indexNouveauNoeud
		parent[idxNoeud2] = indexNouveauNoeud
		symboles[indexNouveauNoeud] = symboles[idxNoeud1]+symboles[idxNoeud2]
		enfantGauche[indexNouveauNoeud] = idxNoeud1
		enfantDroite[indexNouveauNoeud] = idxNoeud2
		f[indexNouveauNoeud] = f[idxNoeud1] + f[idxNoeud2]
	
	arbre = (parent, enfantGauche, enfantDroite, symboles)
	return arbre


if __name__ == '__main__': 
	cheminMessage = sys.argv[1]
	cheminArbre = sys.argv[2]

	message = chargerFichierTexte(cheminMessage)
	arbre = creerAbreHuffman(message)
	sauverArbre(arbre, cheminArbre)

