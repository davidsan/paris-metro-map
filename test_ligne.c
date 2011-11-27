#include <stdio.h>
#include "ligne.h"

int main(int argc, char *argv[])
	{
	Une_ligne *liste_lignes = NULL;

	if (argc != 2)
		{
		fprintf(stderr, "Usage : test_ligne fichier_lignes\n");
		return 1;
		}
	
	if ((liste_lignes = lire_lignes(argv[1])) == NULL)
		{
		fprintf(stderr, "Erreur : Lecture fichier lignes\n");
		return 1;
		}
	
	afficher_lignes(liste_lignes);

	detruire_lignes(liste_lignes);

	return 1;
	}
