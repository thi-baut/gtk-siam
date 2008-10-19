/*
 *  main.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/2008.
 *  Copyright Fusion Studios 2008. All rights reserved.
 */

#include "library.h"
#include "menu.h"
#include "newgame.h"

int main (int argc, char **argv)
{
	
	// Initialisation de GTK+
	gtk_init(&argc, &argv);
	
	/* Structures */
	
	// Déclaration des structures
	MainWindow *pGame;
	
	// Allocation dynamique des structures
	pGame = (MainWindow *) malloc(sizeof(MainWindow));

	/* Création et paramétrage des fenêtres */
	
	// Fenêtre principale
	CreateGameWindow(pGame);
	
	
	/* Affichage de la fenêtre */
	//gtk_widget_show_all(pNewGame->pWindow);
	gtk_widget_show_all(pGame->pWindow);

	/* Boucle principale. */
	gtk_main();
	
	return 0;
}
