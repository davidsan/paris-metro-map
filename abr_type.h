#ifndef ABR_TYPE
#define ABR_TYPE

/* includes */

#include "liste.h"

/* types */

typedef struct _un_nabr
	{
	Un_truc *truc; //La station
	struct _un_nabr *g; //Fils gauche strictement inferieur
	struct _un_nabr *d; //Fils droit
	} Un_nabr;

/* fonctions de manipulation d abr de stations*/
#endif
