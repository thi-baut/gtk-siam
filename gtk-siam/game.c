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
	static gchar temp[150];
	int i;
	
	
	switch(pGame->round) {
		case 0:
			// Permet de savoir de quelle case du tableau de structures il s'agît.
			number = atoi(g_object_get_data(G_OBJECT(pButton), "number"));
			
			// Si la case de départ est vide, ne rien faire, c'est à dire laisser la variable pGame->round à 0
			// DANS LES AUTRES CAS, c'est à dire lorsque l'échange est possible
			if(pGame->pBoardButton[number]->piece == 'n')
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous avez cliqué sur une case vide !");
			
			if(pGame->pBoardButton[number]->piece != 'n') {
			/* PREPARATION DE L'ECHANGE */
			
			// On récupère le pion actuellement sur la case
			pGame->pTempButton->piece = pGame->pBoardButton[number]->piece;
			printf("La pièce contient : %c", pGame->pTempButton->piece);
			
			// On récupère les autres trucs
			pGame->pTempButton->r_left = pGame->pBoardButton[number]->r_left;
			pGame->pTempButton->r_right = pGame->pBoardButton[number]->r_right;
			pGame->pTempButton->r_top = pGame->pBoardButton[number]->r_top;
			pGame->pTempButton->r_bottom = pGame->pBoardButton[number]->r_bottom;
			pGame->pTempButton->force = pGame->pBoardButton[number]->force;
			pGame->pTempButton->direction = pGame->pBoardButton[number]->direction;

			sprintf(temp,"Coordonnées : x = %d et y = %d. C'est un pion %c.", pGame->pTempButton->x, pGame->pTempButton->y, pGame->pTempButton->piece);
			gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);
				
			// Enfin on met la valeur round à 1 pour activer le mode case d'arrivée
			pGame->round = 1;
			// On active quand même ce mode dans le cas où on clique deux fois sur la même case. Mais on n'a pas copié toutes les variables pour rien !
			}
		break;
			
		case 1:
			// Permet de savoir de quelle case du tableau de structures il s'agît.
			number2 = atoi(g_object_get_data(G_OBJECT(pButton), "number"));

			if(number == number2) {
				switch(pGame->pBoardButton[number]->direction) {
					case 't':
						// On le tourne de 90¬∞ sans non trigo
						pGame->pBoardButton[number]->direction = 'r';
						// On modifie son image
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-r.png");
								break;
							case 'r':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-r.png");
								break;
						}
						// On rafra√Æchit l'image
						gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
						break;
					case 'b':
						pGame->pBoardButton[number]->direction = 'l';
						// On modifie son image
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-l.png");
								break;
							case 'r':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-l.png");
								break;
						}
						// On rafra√Æchit l'image
						gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
						break;
					case 'l':
						pGame->pBoardButton[number]->direction = 't';
						// On modifie son image
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant.png");
								break;
							case 'r':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino.png");
								break;
						}
						// On rafra√Æchit l'image
						gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
						break;
					case 'r':
						pGame->pBoardButton[number]->direction = 'b';
						// On modifie son image
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image)); // Lib√®re la m√©moire sinon √ßa chie :)
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-b.png");
								break;
							case 'r':
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-b.png");
								break;
						}
						// On rafra√Æchit l'image
						gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
						break;
				}
			}
			
			
			if((pGame->pBoardButton[number]->piece == 'e') && (number2>=30) && (number2<35))	{
			   
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas aller dans le camp adverse !");
			   
			   }
			
			else if((pGame->pBoardButton[number]->piece == 'r') && (number2>=25) && (number2<30))	{
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas aller dans le camp adverse !");
				
			}
			
			else if(((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))>1)) || (((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))<-1)) {
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez vous déplacer que d'une case par tour !");
				
			}
			
			else if(((((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))>1)) || (((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))<-1)) {
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez vous déplacer que d'une case par tour !");
				
			}
			
			else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==1){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
				
			}
			
			else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==-1){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
				
			}
			
			else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==-1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==1){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
				
			}
			
			else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==-1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==-1){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
				
			}
			
			else if((((number>=30) && (number<35)) || ((number>=25) && (number<30)))  && ((pGame->pBoardButton[number2]->piece!='n'))){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Rentrée sur le plateau impossible");
				
			}
			
			else {
			pGame->pBoardButton[number]->piece = pGame->pBoardButton[number2]->piece;
			pGame->pBoardButton[number]->r_left = pGame->pBoardButton[number2]->r_left;
			pGame->pBoardButton[number]->r_right = pGame->pBoardButton[number2]->r_right;
			pGame->pBoardButton[number]->r_top = pGame->pBoardButton[number2]->r_top;
			pGame->pBoardButton[number]->r_bottom = pGame->pBoardButton[number2]->r_bottom;
			pGame->pBoardButton[number]->force = pGame->pBoardButton[number2]->force;
			pGame->pBoardButton[number]->direction = pGame->pBoardButton[number2]->direction;
		

			switch(pGame->pBoardButton[number]->piece) {
				case 'e':
					gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant.png");
					break;
				case 'r':
					gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino.png");
					break;
				case 'm':
					break;
				default:
					gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
					pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			
			pGame->pBoardButton[number2]->piece = pGame->pTempButton->piece;
			
			pGame->pBoardButton[number2]->r_left = pGame->pTempButton->r_left;
			pGame->pBoardButton[number2]->r_right = pGame->pTempButton->r_right;
			pGame->pBoardButton[number2]->r_top = pGame->pTempButton->r_top;
			pGame->pBoardButton[number2]->r_bottom = pGame->pTempButton->r_bottom;
			pGame->pBoardButton[number2]->force = pGame->pTempButton->force;
			pGame->pBoardButton[number2]->direction = pGame->pTempButton->direction;

			switch(pGame->pBoardButton[number2]->piece) {
				case 'e':
					//gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number2]->image));
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant.png");
					printf("\nLe pion %d qui est un %c aura l'image éléphant", number2, pGame->pBoardButton[number2]->piece);
					break;
				case 'r':
					//gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number2]->image));
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino.png");
					printf("\nLe pion %d qui est un %c aura l'image rhino", number2, pGame->pBoardButton[number2]->piece);
					break;
				case 'm':
					break;
				default:
					gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number2]->image));
					pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
					printf("\nLe pion %d qui est un %c aura l'image montagne", number2, pGame->pBoardButton[number2]->piece);
					break;
			}
			
			// On rafraichît l'affichage : on "téléporte" les images
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number2]->button), pGame->pBoardButton[number2]->image);
				
			// Si l'échange a été effectué, message dans la statusbar
			sprintf(temp, "Nouvelles coordonnées : x = %d et y = %d. C'est un pion %c.", pGame->pBoardButton[number2]->x, pGame->pBoardButton[number2]->y, pGame->pBoardButton[number2]->piece);
			gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, temp);
			}
			
			// Signifie qu'on a cliqué sur le bouton d'arrivée - tout s'est déroulé correctement
			pGame->round = 0;
			
		break;
			
		default:
		break;
	}
}
