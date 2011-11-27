#ifndef LIGNE
#define LIGNE

typedef struct _une_ligne
	{
	char *code; //Le nom de la ligne A, B .., M1, M2, T1...
	char *color; //La couleur de la ligne #RRGGBB
	float vitesse; //Vitesse moyenne des rames en km/h
	float intervalle; //Intervalle moyen entre 2 rames
	struct _une_ligne *suiv;
	} Une_ligne;

Une_ligne *lire_lignes(char *nom_fichier);

void afficher_lignes(Une_ligne *lligne);

void detruire_lignes(Une_ligne *lligne);

Une_ligne *chercher_ligne(Une_ligne *lligne, char *code);
#endif
