/*
 *  timer.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 20/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

gboolean timeout(MainWindow *pGame) {
	
	// On incrémente le chrono
	pGame->chrono++;

	// Deux chaînes temporaires qui sont réallouées à chaque fois (ça trace, on s'en fous)
	gchar *temp;
	gchar *temp2;
	temp = (gchar *) malloc(25*sizeof(gchar));	temp2 = (gchar *) malloc(5*sizeof(gchar));
	
	strcpy(temp,"Chronomètre : ");
	sprintf(temp2, "%02d:%02d", pGame->chrono/60, pGame->chrono%61);
	strcat(temp, temp2);
    
	// On modifie le label
	gtk_label_set_text(GTK_LABEL(pGame->pLabel[1]), temp);
	
    return TRUE; // Ce return permet de dire à GTK qu'il continue à éxécuter la fonction normalement à l'intervalle désiré
}
