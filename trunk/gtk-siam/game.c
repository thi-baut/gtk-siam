/*
 *  game.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 22/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "library.h"

void ActionInGame(GtkWidget *pButton, MainWindow *pGame) {
	
	// Numéro de la case. Récupérée dans le champ adéquat dans le GObject pButton passé en argument du Callback
	static int number, number2;
	
	// Structure temporaire "Bouton"
	static Button *pTempButton;
	pTempButton = (Button *) malloc(sizeof(Button));
	
	switch(pGame->round) {
		case 0:
			// Permet de savoir de quelle case du tableau de structures il s'agît.
			number = atoi(g_object_get_data(G_OBJECT(pButton), "number"));
			// Signifie qu'on a cliqué sur le bouton de départ
			// Mémorise la case de départ
			// On enregistre les coordonnées du bouton dans les coordonnées temporaires
			pTempButton->x = pGame->pBoardButton[number]->x;
			pTempButton->y = pGame->pBoardButton[number]->y;
			
			// On récupère le pion actuellement sur la case
			pTempButton->piece = pGame->pBoardButton[number]->piece;

			pTempButton->r_left = pGame->pBoardButton[number]->r_left;
			pTempButton->r_right = pGame->pBoardButton[number]->r_right;
			pTempButton->r_top = pGame->pBoardButton[number]->r_top;
			pTempButton->r_bottom = pGame->pBoardButton[number]->r_bottom;
			pTempButton->force = pGame->pBoardButton[number]->force;
			pTempButton->direction = pGame->pBoardButton[number]->direction;
			pTempButton->color = pGame->pBoardButton[number]->color;

			printf("Bouton %d : x = %d et y = %d. C'est un pion %c et la case est de couleur %d\n", number, pTempButton->x, pTempButton->y, pTempButton->piece, pTempButton->color);

			// Enfin on met la valeur round à 1 pour activer le mode "case" d'arrivée
			pGame->round = 1;
		break;
			
		case 1:
			// Permet de savoir de quelle case du tableau de structures il s'agît.
			number2 = atoi(g_object_get_data(G_OBJECT(pButton), "number"));
			// Signifie qu'on a cliqué sur le bouton d'arrivée
			pGame->round = 0;
			
			printf("\nLe point de départ était %d : x = %d et y = %d. C'est un pion %c et la case est de couleur %d\n", number, pGame->pBoardButton[number]->x, pGame->pBoardButton[number]->y, pGame->pBoardButton[number]->piece, pGame->pBoardButton[number]->color);
			printf("Bouton d'arrivée %d : x = %d et y = %d. C'est un pion %c et la case est de couleur %d\n", number2, pGame->pBoardButton[number2]->x, pGame->pBoardButton[number2]->y, pGame->pBoardButton[number2]->piece, pGame->pBoardButton[number2]->color);
			
			
			// Echange des boutons !! BENTROC C'EST LÀ QUE TU RENTRES EN SCENE ;)
			// J'ai fait le code de "switche sans rien checker" - inspire toi pour les autres cas
			pGame->pBoardButton[number]->x = pGame->pBoardButton[number2]->x;
			pGame->pBoardButton[number]->y = pGame->pBoardButton[number2]->y;
			pGame->pBoardButton[number]->piece = pGame->pBoardButton[number2]->piece;
			pGame->pBoardButton[number]->r_left = pGame->pBoardButton[number2]->r_left;
			pGame->pBoardButton[number]->r_right = pGame->pBoardButton[number2]->r_right;
			pGame->pBoardButton[number]->r_top = pGame->pBoardButton[number2]->r_top;
			pGame->pBoardButton[number]->r_bottom = pGame->pBoardButton[number2]->r_bottom;
			pGame->pBoardButton[number]->force = pGame->pBoardButton[number2]->force;
			pGame->pBoardButton[number]->direction = pGame->pBoardButton[number2]->direction;
			pGame->pBoardButton[number]->color = pGame->pBoardButton[number2]->color;

			switch(pGame->pBoardButton[number]->piece) {
				case 'e':
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant.png");
					break;
				case 'r':
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino.png");
					break;
				case 'm':
					break;
				default:
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			
			pGame->pBoardButton[number2]->x = pTempButton->x;
			pGame->pBoardButton[number2]->y = pTempButton->y;
			pGame->pBoardButton[number2]->piece = pTempButton->piece;
			pGame->pBoardButton[number2]->r_left = pTempButton->r_left;
			pGame->pBoardButton[number2]->r_right = pTempButton->r_right;
			pGame->pBoardButton[number2]->r_top = pTempButton->r_top;
			pGame->pBoardButton[number2]->r_bottom = pTempButton->r_bottom;
			pGame->pBoardButton[number2]->force = pTempButton->force;
			pGame->pBoardButton[number2]->direction = pTempButton->direction;
			pGame->pBoardButton[number2]->color = pTempButton->color;

			switch(pGame->pBoardButton[number2]->piece) {
				case 'e':
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant.png");
					break;
				case 'r':
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino.png");
					break;
				case 'm':
					break;
				default:
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			
			// On rafraichît l'affichage : on "téléporte" les images
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number2]->button), pGame->pBoardButton[number2]->image);
			
		break;
			
		default:
		break;
	}
	
	g_free(pTempButton);
	
}
