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
	/* Paramètre la langue et les signes utilisés par GTK+ (meilleur pour le multi-plateforme) */
	gtk_set_locale();
	
	/* Initialisation de GTK+ */
	gtk_init(&argc, &argv);

	/* Déclaration et allocation de la structure principale */
	MainWindow *pGame;
	pGame = (MainWindow *) malloc(sizeof(MainWindow));

	/* Création et paramétrage des fenêtres */
	CreateGameWindow(pGame);
	
	/* Affichage de la fenêtre */
	gtk_widget_show_all(pGame->pWindow);

	/* Boucle principale. */
	gtk_main();
	
	return 0;
}
