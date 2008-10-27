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
	gint i = 0;
	gint resistance;
	
	if(pGame->vs_human == TRUE) {
	
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
				
			// On récupère les autres trucs
			pGame->pTempButton->r_left = pGame->pBoardButton[number]->r_left;
			pGame->pTempButton->r_right = pGame->pBoardButton[number]->r_right;
			pGame->pTempButton->r_top = pGame->pBoardButton[number]->r_top;
			pGame->pTempButton->r_bottom = pGame->pBoardButton[number]->r_bottom;
			pGame->pTempButton->force = pGame->pBoardButton[number]->force;
			pGame->pTempButton->direction = pGame->pBoardButton[number]->direction;

			sprintf(temp,"Coordonnées du pion sélectionné : x = %d et y = %d. C'est un pion %c orienté en %c.", pGame->pBoardButton[number]->x, pGame->pBoardButton[number]->y, pGame->pTempButton->piece, pGame->pTempButton->direction);
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
						pGame->pBoardButton[number]->direction = 'r';
						break;
					case 'b':
						pGame->pBoardButton[number]->direction = 'l';
						break;
					case 'l':
						pGame->pBoardButton[number]->direction = 't';
						break;
					case 'r':
						pGame->pBoardButton[number]->direction = 'b';
						break;
				}
			}
			
			
			else if((pGame->pBoardButton[number]->piece == 'e') && (number2>=30) && (number2<35))	{
			   
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
			
			else if((((number>=30) && (number<35)) || ((number>=25) && (number<30)))  && ((pGame->pBoardButton[number2]->piece !='n'))){
				
				gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Rentrée sur le plateau impossible");
				
			}

			// Cas de l'échange, c'est à dire qu'on inverse deux pièces. Simple déplacement des pions en fait !
			else if(pGame->pBoardButton[number2]->piece == 'n'){
				
			// C'est ici que l'on vérifie que le sens du pion est correctement enregistré pour permettre le déplacement
				if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x > 0) && (pGame->pBoardButton[number]->direction != 'l'))
				   gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
				   
				else if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x < 0) && (pGame->pBoardButton[number]->direction != 'r'))
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
						
				else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y > 0) && (pGame->pBoardButton[number]->direction != 't'))
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
								
				else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y < 0) && (pGame->pBoardButton[number]->direction != 'b'))
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
				
				else {
					pGame->pBoardButton[number]->piece = pGame->pBoardButton[number2]->piece;
					pGame->pBoardButton[number]->r_left = pGame->pBoardButton[number2]->r_left;
					pGame->pBoardButton[number]->r_right = pGame->pBoardButton[number2]->r_right;
					pGame->pBoardButton[number]->r_top = pGame->pBoardButton[number2]->r_top;
					pGame->pBoardButton[number]->r_bottom = pGame->pBoardButton[number2]->r_bottom;
					pGame->pBoardButton[number]->force = pGame->pBoardButton[number2]->force;
					pGame->pBoardButton[number]->direction = pGame->pBoardButton[number2]->direction;
			
					pGame->pBoardButton[number2]->piece = pGame->pTempButton->piece;
					pGame->pBoardButton[number2]->r_left = pGame->pTempButton->r_left;
					pGame->pBoardButton[number2]->r_right = pGame->pTempButton->r_right;
					pGame->pBoardButton[number2]->r_top = pGame->pTempButton->r_top;
					pGame->pBoardButton[number2]->r_bottom = pGame->pTempButton->r_bottom;
					pGame->pBoardButton[number2]->force = pGame->pTempButton->force;
					pGame->pBoardButton[number2]->direction = pGame->pTempButton->direction;
					
					// Si l'échange a été effectué, message dans la statusbar
					sprintf(temp, "Nouvelles coordonnées : x = %d et y = %d. C'est un pion %c orienté en %c", pGame->pBoardButton[number2]->x, pGame->pBoardButton[number2]->y, pGame->pBoardButton[number2]->piece, pGame->pBoardButton[number2]->direction);
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, temp);
				}
			}
			
			// Cas de la poussée : et là, c'est le drame.
			else {
				if(pGame->pBoardButton[number]->piece == 'e')
				switch(pGame->pBoardButton[number]->direction) {
					case 't':
						i = number;
						resistance = pGame->pBoardButton[number]->force;
						while(pGame->pBoardButton[i]->piece != 'n') {
							printf("Pion %d\n", i);
							printf("La force restante est de %d", resistance);
							if(pGame->pBoardButton[i]->y <= 0) break;
							i = i-5;
							// On soustrait les résistances
								switch(pGame->pBoardButton[i]->direction) {
									case 'r':
										if(pGame->pBoardButton[i]->piece == 'r' || pGame->pBoardButton[i]->piece == 'm')
											resistance = resistance - pGame->pBoardButton[i]->r_right;
										else if(pGame->pBoardButton[i]->piece == 'e')
											resistance = resistance + pGame->pBoardButton[i]->force;
										break;
									case 'l':
										if(pGame->pBoardButton[i]->piece == 'r' || pGame->pBoardButton[i]->piece == 'm')
											resistance = resistance - pGame->pBoardButton[i]->r_left;
										else if(pGame->pBoardButton[i]->piece == 'e')
											resistance = resistance + pGame->pBoardButton[i]->force;
										break;
									case 't':
										if(pGame->pBoardButton[i]->piece == 'r' || pGame->pBoardButton[i]->piece == 'm')
											resistance = resistance - pGame->pBoardButton[i]->r_top;
										else if(pGame->pBoardButton[i]->piece == 'e')
											resistance = resistance + pGame->pBoardButton[i]->force;
										break;
									case 'b':
										if(pGame->pBoardButton[i]->piece == 'r' || pGame->pBoardButton[i]->piece == 'm')
											resistance = resistance - pGame->pBoardButton[i]->r_bottom;
										else if(pGame->pBoardButton[i]->piece == 'e')
											resistance = resistance + pGame->pBoardButton[i]->force;
										break;
								}
						}
						break;
					case 'b':
						i = number;
						resistance = pGame->pBoardButton[number]->r_bottom;
						while(pGame->pBoardButton[i]->piece != 'n') {
							printf("Pion %d\n", i);
							if(pGame->pBoardButton[i]->y > 4) break;
							i = i+5;
						}
						break;
					case 'l':
						i = number;
						resistance = pGame->pBoardButton[number]->r_left;
						while(pGame->pBoardButton[i]->piece != 'n') {
							printf("Pion %d\n", i);
							if(pGame->pBoardButton[i]->x < 0) break;
							i = i-1;

						}
						break;
					case 'r':
						i = number;
						resistance = pGame->pBoardButton[number]->r_right;
						while(pGame->pBoardButton[i]->piece != 'n') {
							if(pGame->pBoardButton[i]->x > 4) break;
							printf("Pion %d\n", i);
							i = i+1;
						}
						break;
				}
			}
			
			// On rafraîchit l'image :
			switch(pGame->pBoardButton[number]->direction) {
					case 't':
						switch(pGame->pBoardButton[number]->piece) {
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								gtk_widget_destroy(pGame->pBoardButton[number]->image);
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'b':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-b.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-b.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'l':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-l.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-l.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'r':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-r.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-r.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					default:
					switch(pGame->pBoardButton[number]->piece) {
						case 'e':
							pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-r.png");
							break;
						case 'r':
							pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-r.png");
							break;
						case 'm':
							pGame->pBoardButton[number]->image = gtk_image_new_from_file("/mountain.png");
							break;
						default:
							pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
							break;
					}
					break;
				}
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
			
			if(number != number2) {
				switch(pGame->pBoardButton[number2]->direction) {
						gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number2]->image));
						gtk_widget_destroy(pGame->pBoardButton[number2]->image);
				case 't':
					switch(pGame->pBoardButton[number2]->piece) {
						case 'e':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant.png");
							break;
						case 'r':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino.png");
							break;
						default:
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
							break;
					}
					break;
				case 'b':
					switch(pGame->pBoardButton[number2]->piece) {
						case 'e':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-b.png");
							break;
						case 'r':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-b.png");
							break;
						default:
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
							break;
					}
					break;
				case 'l':
					switch(pGame->pBoardButton[number2]->piece) {
						case 'e':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-l.png");
							break;
						case 'r':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-l.png");
							break;
						default:
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
							break;
					}
					break;
				case 'r':
					switch(pGame->pBoardButton[number2]->piece) {
						case 'e':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-r.png");
							break;
						case 'r':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-r.png");
							break;
						default:
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
							break;
					}
					break;
				default:
					switch(pGame->pBoardButton[number2]->piece) {
						case 'e':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-r.png");
							break;
						case 'r':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-r.png");
							break;
						case 'm':
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/mountain.png");
							break;
						default:
							pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
							break;
						}
					break;
			}
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number2]->button), pGame->pBoardButton[number2]->image);
			}
			
			// Signifie qu'on a cliqué sur le bouton d'arrivée - tout s'est déroulé correctement
			pGame->round = 0;
			
		break;
			
		default:
		break;
	}
	}
	
	else if(pGame->vs_human == FALSE) {
		
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
					
					// On récupère les autres trucs
					pGame->pTempButton->r_left = pGame->pBoardButton[number]->r_left;
					pGame->pTempButton->r_right = pGame->pBoardButton[number]->r_right;
					pGame->pTempButton->r_top = pGame->pBoardButton[number]->r_top;
					pGame->pTempButton->r_bottom = pGame->pBoardButton[number]->r_bottom;
					pGame->pTempButton->force = pGame->pBoardButton[number]->force;
					pGame->pTempButton->direction = pGame->pBoardButton[number]->direction;
					
					sprintf(temp,"Coordonnées du pion sélectionné : x = %d et y = %d. C'est un pion %c orienté en %c.", pGame->pTempButton->x, pGame->pTempButton->y, pGame->pTempButton->piece, pGame->pTempButton->direction);
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
							pGame->pBoardButton[number]->direction = 'r';
							break;
						case 'b':
							pGame->pBoardButton[number]->direction = 'l';
							break;
						case 'l':
							pGame->pBoardButton[number]->direction = 't';
							break;
						case 'r':
							pGame->pBoardButton[number]->direction = 'b';
							break;
					}
				}
				
				
				else if((pGame->pBoardButton[number]->piece == 'e') && (number2>=30) && (number2<35))	{
					
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
				
				else if((((number>=30) && (number<35)) || ((number>=25) && (number<30)))  && ((pGame->pBoardButton[number2]->piece !='n'))){
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Rentrée sur le plateau impossible");
					
				}
				
				else {
					
					// C'est ici que l'on vérifie que le sens du pion est correctement enregistré pour permettre le déplacement
					if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x < 0) && (pGame->pBoardButton[number]->direction == 'l'))
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x > 0) && (pGame->pBoardButton[number]->direction == 'r'))
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y < 0) && (pGame->pBoardButton[number]->direction == 't'))
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y > 0) && (pGame->pBoardButton[number]->direction == 'b'))
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else {
						pGame->pBoardButton[number]->piece = pGame->pBoardButton[number2]->piece;
						pGame->pBoardButton[number]->r_left = pGame->pBoardButton[number2]->r_left;
						pGame->pBoardButton[number]->r_right = pGame->pBoardButton[number2]->r_right;
						pGame->pBoardButton[number]->r_top = pGame->pBoardButton[number2]->r_top;
						pGame->pBoardButton[number]->r_bottom = pGame->pBoardButton[number2]->r_bottom;
						pGame->pBoardButton[number]->force = pGame->pBoardButton[number2]->force;
						pGame->pBoardButton[number]->direction = pGame->pBoardButton[number2]->direction;
						
						pGame->pBoardButton[number2]->piece = pGame->pTempButton->piece;
						pGame->pBoardButton[number2]->r_left = pGame->pTempButton->r_left;
						pGame->pBoardButton[number2]->r_right = pGame->pTempButton->r_right;
						pGame->pBoardButton[number2]->r_top = pGame->pTempButton->r_top;
						pGame->pBoardButton[number2]->r_bottom = pGame->pTempButton->r_bottom;
						pGame->pBoardButton[number2]->force = pGame->pTempButton->force;
						pGame->pBoardButton[number2]->direction = pGame->pTempButton->direction;
						
						// Si l'échange a été effectué, message dans la statusbar
						sprintf(temp, "Nouvelles coordonnées : x = %d et y = %d. C'est un pion %c orienté en %c", pGame->pBoardButton[number2]->x, pGame->pBoardButton[number2]->y, pGame->pBoardButton[number2]->piece, pGame->pBoardButton[number2]->direction);
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, temp);
					}
					
					
				}
				
				// On rafraîchit l'image :
				switch(pGame->pBoardButton[number]->direction) {
					case 't':
						switch(pGame->pBoardButton[number]->piece) {
								gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number]->image));
								gtk_widget_destroy(pGame->pBoardButton[number]->image);
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'b':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-b.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-b.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'l':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-l.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-l.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					case 'r':
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-r.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-r.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
					default:
						switch(pGame->pBoardButton[number]->piece) {
							case 'e':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/elephant-r.png");
								break;
							case 'r':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/rhino-r.png");
								break;
							case 'm':
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/mountain.png");
								break;
							default:
								pGame->pBoardButton[number]->image = gtk_image_new_from_file("/empty.png");
								break;
						}
						break;
				}
				gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number]->button), pGame->pBoardButton[number]->image);
				
				if(number != number2) {
					switch(pGame->pBoardButton[number2]->direction) {
							gtk_image_clear(GTK_IMAGE(pGame->pBoardButton[number2]->image));
							gtk_widget_destroy(pGame->pBoardButton[number2]->image);
						case 't':
							switch(pGame->pBoardButton[number2]->piece) {
								case 'e':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant.png");
									break;
								case 'r':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino.png");
									break;
								default:
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
									break;
							}
							break;
						case 'b':
							switch(pGame->pBoardButton[number2]->piece) {
								case 'e':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-b.png");
									break;
								case 'r':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-b.png");
									break;
								default:
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
									break;
							}
							break;
						case 'l':
							switch(pGame->pBoardButton[number2]->piece) {
								case 'e':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-l.png");
									break;
								case 'r':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-l.png");
									break;
								default:
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
									break;
							}
							break;
						case 'r':
							switch(pGame->pBoardButton[number2]->piece) {
								case 'e':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-r.png");
									break;
								case 'r':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-r.png");
									break;
								default:
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
									break;
							}
							break;
						default:
							switch(pGame->pBoardButton[number2]->piece) {
								case 'e':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/elephant-r.png");
									break;
								case 'r':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/rhino-r.png");
									break;
								case 'm':
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/mountain.png");
									break;
								default:
									pGame->pBoardButton[number2]->image = gtk_image_new_from_file("/empty.png");
									break;
							}
							break;
					}
					gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[number2]->button), pGame->pBoardButton[number2]->image);
				}
				
				// Signifie qu'on a cliqué sur le bouton d'arrivée - tout s'est déroulé correctement
				pGame->round = 0;
				
				break;
				
			default:
				break;
		}
	}
	

}	