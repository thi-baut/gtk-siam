/*
 *  game.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 22/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

void ActionInGame(GtkWidget *pButton, MainWindow *pGame) {

	// Numéro de la case. Récupérée dans le champ adéquat dans le GObject pButton passé en argument du Callback
	static int number, number2;
	static gchar temp[150];
	gint i, c;
	gfloat resistance;
	gint i_tmp;
	gint j = 0;

	if(pGame->mode == 1) {

		switch(pGame->round) {
			
			case 0:
				printf("LOL");
				// Permet de savoir de quelle case du tableau de structures il s'agît.
				number = atoi(g_object_get_data(G_OBJECT(pButton), "number"));

				// Si la case de départ est vide, ne rien faire, c'est à dire laisser la variable pGame->round à 0
				// DANS LES AUTRES CAS, c'est à dire lorsque l'échange est possible
				if(pGame->pBoardSquare[number]->piece == 'n')
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous avez cliqué sur une case vide !");

				if(pGame->pBoardSquare[number]->piece != 'n') {
					
					/* PREPARATION DE L'ECHANGE */
					// On récupère le type de pion actuellement sur la case
					pGame->pTempButton->piece = pGame->pBoardSquare[number]->piece;

					// On récupère les autres variables
					pGame->pTempButton->r_left = pGame->pBoardSquare[number]->r_left;
					pGame->pTempButton->r_right = pGame->pBoardSquare[number]->r_right;
					pGame->pTempButton->r_top = pGame->pBoardSquare[number]->r_top;
					pGame->pTempButton->r_bottom = pGame->pBoardSquare[number]->r_bottom;
					pGame->pTempButton->force = pGame->pBoardSquare[number]->force;
					pGame->pTempButton->direction = pGame->pBoardSquare[number]->direction;

					sprintf(temp,"Coordonnées du pion sélectionné : x = %d et y = %d. C'est un pion %c orienté en %c.", pGame->pBoardSquare[number]->x, pGame->pBoardSquare[number]->y, pGame->pTempButton->piece, pGame->pTempButton->direction);
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);

					// Enfin on met la valeur round à 1 pour activer le mode case d'arrivée
					pGame->round = 1;
					// On active quand même ce mode dans le cas où on clique deux fois sur la même case.
				}
				break;

			case 1:
				// Permet de savoir de quelle case du tableau de structures il s'agît.
				number2 = atoi(g_object_get_data(G_OBJECT(pButton), "number"));

				if((pGame->turn % 2 == 0) & (pGame->pBoardSquare[number]->piece != 'r'))
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas bouger un pion adverse !");

				else if((pGame->turn % 2 != 0) & (pGame->pBoardSquare[number]->piece != 'e'))	
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas bouger un pion adverse !");

				// Cas de la rotation
				else if(number == number2) {
					
					// Variables temporaires pour le mini-menu
					GtkWidget *pPopup;
					GtkWidget *pLabel;
					GtkWidget *pVBox;
					GtkWidget *pButton[5];
					gint x; // Coordonnées de la souris
					gint y;
					gint win_x; // Taille de la fenêtre
					gint win_y;
					GdkDisplay *display = gdk_display_get_default();
					
					// Fenêtre + Boxes
					pPopup = gtk_window_new(GTK_WINDOW_POPUP);
					gtk_window_set_position(GTK_WINDOW(pPopup), GTK_WIN_POS_MOUSE);
					gtk_window_set_opacity(GTK_WINDOW(pPopup), 0.90);
					gtk_container_set_border_width(GTK_CONTAINER(pPopup), 6);
					gdk_display_get_pointer (display, NULL, &x, &y, NULL);
					
					pVBox = gtk_vbox_new(TRUE, 2);
					pLabel = gtk_label_new("Orientation :");
					pButton[0] = gtk_button_new_with_label("Gauche");
					pButton[1] = gtk_button_new_with_label("Droite");
					pButton[2] = gtk_button_new_with_label("Haut");
					pButton[3] = gtk_button_new_with_label("Bas");
					pButton[4] = gtk_button_new_with_label("Annuler");
					gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, TRUE, 0);
					
					// Affiche différents menus selon l'orientation actuelle du pion
					switch(pGame->pBoardSquare[number]->direction) {
						case 'r':
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[0], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[2], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[3], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[4], TRUE, TRUE, 0);
							break;
						case 'l':
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[1], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[2], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[3], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[4], TRUE, TRUE, 0);
							break;
						case 't':
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[0], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[1], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[3], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[4], TRUE, TRUE, 0);
							break;
						case 'b':
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[0], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[1], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[2], TRUE, TRUE, 0);
							gtk_box_pack_start(GTK_BOX(pVBox), pButton[4], TRUE, TRUE, 0);
							break;
					}
					gtk_container_add(GTK_CONTAINER(pPopup), pVBox);
					gtk_window_get_default_size(GTK_WINDOW(pPopup), &win_x, &win_y);
					gtk_window_move(GTK_WINDOW(pPopup), x+win_x/2, y+win_y/2);

					pGame->number = number; // Sauvegarde le numéro de la case pour l'exploiter dans les callbacks
					
					g_signal_connect(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(OnButtonLeft), pGame);
					g_signal_connect(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(OnButtonRight), pGame);
					g_signal_connect(G_OBJECT(pButton[2]), "clicked", G_CALLBACK(OnButtonTop), pGame);
					g_signal_connect(G_OBJECT(pButton[3]), "clicked", G_CALLBACK(OnButtonBottom), pGame);
					g_signal_connect_swapped(G_OBJECT(pButton[4]), "clicked", G_CALLBACK(gtk_widget_destroy), pPopup);
					
					gtk_widget_show_all(pPopup);
				}

				// Conditions qui empêchent l'échange et/ou la poussée
				else if(pGame->pBoardSquare[number]->piece == 'e' && number2 >= 30 && number2 < 35) 	
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas aller dans le camp adverse !");
				
				else if(pGame->pBoardSquare[number]->piece == 'r' && number2 >= 25 && number2 < 30)	
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas aller dans le camp adverse !");
				
				else if(((pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x > 1) || (pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x < -1)) && (number < 25 && (number2 > 5 || number2 < 20)) || NUMBER_CENTER)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement non autorisé !");
					
				else if(((pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y > 1) || (pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y < -1)) || NUMBER_CENTER)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement non autorisé !");
				
				else if((pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x == 1) && (pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y == 1) && number < 25)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !"); 

				else if((pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x == 1) && (pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y == -1) && number < 25)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !"); 
				
				else if((pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x == -1) && (pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y == 1) && number < 25)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !"); 
				
				else if((pGame->pBoardSquare[number2]->x - pGame->pBoardSquare[number]->x == -1) && (pGame->pBoardSquare[number2]->y - pGame->pBoardSquare[number]->y == -1) && number < 25)
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !"); 
				
				else if(((number >= 30 && number < 35) || (number >= 25 && number < 30)) && pGame->pBoardSquare[number2]->piece !='n')		
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Rentrée sur le plateau impossible");

				
				// Cas de l'échange, c'est à dire qu'on inverse deux pièces. Simple déplacement des pions en fait !
				else if (pGame->pBoardSquare[number2]->piece == 'n')  {

					// C'est ici que l'on vérifie que le sens du pion est correctement enregistré pour permettre le déplacement
					if((pGame->pBoardSquare[number]->x - pGame->pBoardSquare[number2]->x > 0) && (pGame->pBoardSquare[number]->direction != 'l') && pGame->pBoardSquare[number]->x != -1 && pGame->pBoardSquare[number]->x != 5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement !");

					else if((pGame->pBoardSquare[number]->x - pGame->pBoardSquare[number2]->x < 0) && (pGame->pBoardSquare[number]->direction != 'r') && pGame->pBoardSquare[number]->x != -1 && pGame->pBoardSquare[number]->x != 5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement !");

					else if((pGame->pBoardSquare[number]->y - pGame->pBoardSquare[number2]->y > 0) && (pGame->pBoardSquare[number]->direction != 't') && pGame->pBoardSquare[number]->x != -1 && pGame->pBoardSquare[number]->x != 5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement !");

					else if((pGame->pBoardSquare[number]->y - pGame->pBoardSquare[number2]->y < 0) && (pGame->pBoardSquare[number]->direction != 'b') && pGame->pBoardSquare[number]->x != -1 && pGame->pBoardSquare[number]->x != 5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement !");

					else {
						if(((pGame->turn) % 2) == 0) {
							strcpy(temp, "Tour de jeu : ");
							strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
							gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
						}
						else {
							strcpy(temp, "Tour de jeu : ");
							strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
							gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
						}
						
						// Échange des variables
						pGame->pBoardSquare[number]->piece = pGame->pBoardSquare[number2]->piece;
						pGame->pBoardSquare[number]->r_left = pGame->pBoardSquare[number2]->r_left;
						pGame->pBoardSquare[number]->r_right = pGame->pBoardSquare[number2]->r_right;
						pGame->pBoardSquare[number]->r_top = pGame->pBoardSquare[number2]->r_top;
						pGame->pBoardSquare[number]->r_bottom = pGame->pBoardSquare[number2]->r_bottom;
						pGame->pBoardSquare[number]->force = pGame->pBoardSquare[number2]->force;
						pGame->pBoardSquare[number]->direction = pGame->pBoardSquare[number2]->direction;

						pGame->pBoardSquare[number2]->piece = pGame->pTempButton->piece;
						pGame->pBoardSquare[number2]->r_left = pGame->pTempButton->r_left;
						pGame->pBoardSquare[number2]->r_right = pGame->pTempButton->r_right;
						pGame->pBoardSquare[number2]->r_top = pGame->pTempButton->r_top;
						pGame->pBoardSquare[number2]->r_bottom = pGame->pTempButton->r_bottom;
						pGame->pBoardSquare[number2]->force = pGame->pTempButton->force;
						pGame->pBoardSquare[number2]->direction = pGame->pTempButton->direction;

						// Si l'échange a été effectué, message dans la statusbar
						sprintf(temp, "Nouvelles coordonnées : x = %d et y = %d. C'est un pion %c orienté en %c", pGame->pBoardSquare[number2]->x, pGame->pBoardSquare[number2]->y, pGame->pBoardSquare[number2]->piece, pGame->pBoardSquare[number2]->direction);
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, temp);

						// On passe à l'autre joueur
						pGame->turn++%2;
					}
				}

				/* Cas de la poussée : /!\ Complexe /!\ */
				else{
					if(pGame->pBoardSquare[number]->piece == 'e')
						switch(pGame->pBoardSquare[number]->direction) {

							case 't':
								i = number;
								i_tmp = number;
								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->y <= 0) break;
									i = i-5;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'b':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance - pGame->pBoardSquare[i]->r_bottom;
											break;
										case 't':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_top;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number - 5*j;

								if(resistance > 0) {

									while(i-5 <= i_tmp) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->y == 0) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}

										// On parcoure dans l'autre sens
										i = i+5;

										if(i-5 >= 0) {
										pGame->pBoardSquare[i-5]->piece = pGame->pBoardSquare[i]->piece;
										pGame->pBoardSquare[i-5]->r_left = pGame->pBoardSquare[i]->r_left;
										pGame->pBoardSquare[i-5]->r_right = pGame->pBoardSquare[i]->r_right;
										pGame->pBoardSquare[i-5]->r_top = pGame->pBoardSquare[i]->r_top;
										pGame->pBoardSquare[i-5]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
										pGame->pBoardSquare[i-5]->force = pGame->pBoardSquare[i]->force;
										pGame->pBoardSquare[i-5]->direction = pGame->pBoardSquare[i]->direction;
										printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
										RefreshDisplay(pGame, i-5);

										}

										// C'est ce qu'il manquait
										if(i-5 == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}
									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'b':
								i = number;
								i_tmp = number;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->y == 4) break;
									i = i+5;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 't':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance - pGame->pBoardSquare[i]->r_top;
											break;
										case 'b':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_bottom;
											break;
									}
								}

								printf("\n\nLa valeur de j est %d", j);
								i = number + 5*j;

								if(resistance > 0) {

									while(i >= 0) {

										printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


										// Déplacement des pions
										if(pGame->pBoardSquare[i]->y == 4) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}

										if(i >= 0) {
											pGame->pBoardSquare[i]->piece = pGame->pBoardSquare[i-5]->piece;
											pGame->pBoardSquare[i]->r_left = pGame->pBoardSquare[i-5]->r_left;
											pGame->pBoardSquare[i]->r_right = pGame->pBoardSquare[i-5]->r_right;
											pGame->pBoardSquare[i]->r_top = pGame->pBoardSquare[i-5]->r_top;
											pGame->pBoardSquare[i]->r_bottom = pGame->pBoardSquare[i-5]->r_bottom;
											pGame->pBoardSquare[i]->force = pGame->pBoardSquare[i-5]->force;
											pGame->pBoardSquare[i]->direction = pGame->pBoardSquare[i-5]->direction;
											printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
											RefreshDisplay(pGame, i);
										}

										// C'est ce qu'il manquait
										if(i == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}
										// On parcoure dans l'autre sens
										i = i-5;
									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'r':
								i = number;
                                i_tmp = i;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->x >= 4) break;
									i = i+1;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'l':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance - pGame->pBoardSquare[i]->r_left;
											break;
										case 'r':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_left;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number + j;

								if(resistance > 0) {

									while(i-1 >= 0) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->x == 4) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}


										if(i >= 0) {
										pGame->pBoardSquare[i]->piece = pGame->pBoardSquare[i-1]->piece;
										pGame->pBoardSquare[i]->r_left = pGame->pBoardSquare[i-1]->r_left;
										pGame->pBoardSquare[i]->r_right = pGame->pBoardSquare[i-1]->r_right;
										pGame->pBoardSquare[i]->r_top = pGame->pBoardSquare[i-1]->r_top;
										pGame->pBoardSquare[i]->r_bottom = pGame->pBoardSquare[i-1]->r_bottom;
										pGame->pBoardSquare[i]->force = pGame->pBoardSquare[i-1]->force;
										pGame->pBoardSquare[i]->direction = pGame->pBoardSquare[i-1]->direction;
										printf("\nPi-1on %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
										RefreshDisplay(pGame, i);

										}

										// C'est ce qu'il manquait
										if(i == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}

                                        // On parcoure dans l'autre sens
										i = i-1;

									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'l':
								i = number;
								i_tmp = i;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->x <= 0) break;
									i = i-1;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'r':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance - pGame->pBoardSquare[i]->r_right;
											break;
										case 'l':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_right;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number - j;

								if(resistance > 0) {

									while(i <= i_tmp) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->x == 0) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}
                                        // On parcoure dans l'autre sens
                                        i = i+1;

										if(i-1 >= 0) {
										pGame->pBoardSquare[i-1]->piece = pGame->pBoardSquare[i]->piece;
										pGame->pBoardSquare[i-1]->r_left = pGame->pBoardSquare[i]->r_left;
										pGame->pBoardSquare[i-1]->r_right = pGame->pBoardSquare[i]->r_right;
										pGame->pBoardSquare[i-1]->r_top = pGame->pBoardSquare[i]->r_top;
										pGame->pBoardSquare[i-1]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
										pGame->pBoardSquare[i-1]->force = pGame->pBoardSquare[i]->force;
										pGame->pBoardSquare[i-1]->direction = pGame->pBoardSquare[i]->direction;
										printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i-1, pGame->pBoardSquare[i-1]->piece, pGame->pBoardSquare[i-1]->direction, pGame->pBoardSquare[i-1]->x, pGame->pBoardSquare[i-1]->y);
										RefreshDisplay(pGame, i-1);

										}

										// C'est ce qu'il manquait
										if(i-1 == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}

									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;
						}
                    if(pGame->pBoardSquare[number]->piece == 'r')
						switch(pGame->pBoardSquare[number]->direction) {
							case 't':
								i = number;
								i_tmp = number;
								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->y <= 0) break;
									i = i-5;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'b':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance - pGame->pBoardSquare[i]->r_bottom;
											break;
										case 't':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_top;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number - 5*j;

								if(resistance > 0) {

									while(i-5 <= i_tmp) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->y == 0) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}

										// On parcoure dans l'autre sens
										i = i+5;

										if(i-5 >= 0) {
										pGame->pBoardSquare[i-5]->piece = pGame->pBoardSquare[i]->piece;
										pGame->pBoardSquare[i-5]->r_left = pGame->pBoardSquare[i]->r_left;
										pGame->pBoardSquare[i-5]->r_right = pGame->pBoardSquare[i]->r_right;
										pGame->pBoardSquare[i-5]->r_top = pGame->pBoardSquare[i]->r_top;
										pGame->pBoardSquare[i-5]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
										pGame->pBoardSquare[i-5]->force = pGame->pBoardSquare[i]->force;
										pGame->pBoardSquare[i-5]->direction = pGame->pBoardSquare[i]->direction;
										printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
										RefreshDisplay(pGame, i-5);

										}

										// C'est ce qu'il manquait
										if(i-5 == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}
									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'b':
								i = number;
								i_tmp = number;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->y == 4) break;
									i = i+5;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 't':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance - pGame->pBoardSquare[i]->r_top;
											break;
										case 'b':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_bottom;
											break;
									}
								}

								printf("\n\nLa valeur de j est %d", j);
								i = number + 5*j;

								if(resistance > 0) {

									while(i >= 0) {

										printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


										// Déplacement des pions
										if(pGame->pBoardSquare[i]->y == 4) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}

										if(i >= 0) {
											pGame->pBoardSquare[i]->piece = pGame->pBoardSquare[i-5]->piece;
											pGame->pBoardSquare[i]->r_left = pGame->pBoardSquare[i-5]->r_left;
											pGame->pBoardSquare[i]->r_right = pGame->pBoardSquare[i-5]->r_right;
											pGame->pBoardSquare[i]->r_top = pGame->pBoardSquare[i-5]->r_top;
											pGame->pBoardSquare[i]->r_bottom = pGame->pBoardSquare[i-5]->r_bottom;
											pGame->pBoardSquare[i]->force = pGame->pBoardSquare[i-5]->force;
											pGame->pBoardSquare[i]->direction = pGame->pBoardSquare[i-5]->direction;
											printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
											RefreshDisplay(pGame, i);
										}

										// C'est ce qu'il manquait
										if(i == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}
										// On parcoure dans l'autre sens
										i = i-5;
									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'r':
								i = number;
                                i_tmp = i;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->x >= 4) break;
									i = i+1;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'l':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance - pGame->pBoardSquare[i]->r_left;
											break;
										case 'r':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_left;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number + j;

								if(resistance > 0) {

									while(i-1 >= 0) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->x == 4) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}


										if(i >= 0) {
										pGame->pBoardSquare[i]->piece = pGame->pBoardSquare[i-1]->piece;
										pGame->pBoardSquare[i]->r_left = pGame->pBoardSquare[i-1]->r_left;
										pGame->pBoardSquare[i]->r_right = pGame->pBoardSquare[i-1]->r_right;
										pGame->pBoardSquare[i]->r_top = pGame->pBoardSquare[i-1]->r_top;
										pGame->pBoardSquare[i]->r_bottom = pGame->pBoardSquare[i-1]->r_bottom;
										pGame->pBoardSquare[i]->force = pGame->pBoardSquare[i-1]->force;
										pGame->pBoardSquare[i]->direction = pGame->pBoardSquare[i-1]->direction;
										printf("\nPi-1on %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->direction, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
										RefreshDisplay(pGame, i);

										}

										// C'est ce qu'il manquait
										if(i == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}

                                        // On parcoure dans l'autre sens
										i = i-1;

									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;

							case 'l':
								i = number;
                                i_tmp = i;

								resistance = pGame->pBoardSquare[number]->force;
								while(pGame->pBoardSquare[i]->piece != 'n') {

									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);

									if(pGame->pBoardSquare[i]->x <= 0) break;
									i = i-1;
									j++;

									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardSquare[i]->direction) {
										case 'r':
											if(pGame->pBoardSquare[i]->piece == 'e')
												resistance = resistance - pGame->pBoardSquare[i]->r_right;
											break;
										case 'l':
											if(pGame->pBoardSquare[i]->piece == 'r')
												resistance = resistance + pGame->pBoardSquare[i]->force;
										default:
											if(pGame->pBoardSquare[i]->piece == 'm')
												resistance = resistance - pGame->pBoardSquare[i]->r_right;
											break;
									}
								}
								printf("\n\nLa valeur de j est %d", j);
								i = number - j;

								if(resistance > 0) {

									while(i <= i_tmp) {

									printf("\nLa valeur de i est %d et on a y = %d", i, pGame->pBoardSquare[i]->y);


									// Déplacement des pions
										if(pGame->pBoardSquare[i]->x == 0) {
											switch(pGame->pBoardSquare[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardSquare[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;

												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardSquare[c]->piece != 'n') c++;

													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça

													pGame->pBoardSquare[c]->piece = pGame->pBoardSquare[i]->piece;
													pGame->pBoardSquare[c]->r_left = pGame->pBoardSquare[i]->r_left;
													pGame->pBoardSquare[c]->r_right = pGame->pBoardSquare[i]->r_right;
													pGame->pBoardSquare[c]->r_top = pGame->pBoardSquare[i]->r_top;
													pGame->pBoardSquare[c]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
													pGame->pBoardSquare[c]->force = pGame->pBoardSquare[i]->force;
													pGame->pBoardSquare[c]->direction = pGame->pBoardSquare[i]->direction;

													// On s'assure que la case est "vidée"
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardSquare[i]->piece, pGame->pBoardSquare[i]->x, pGame->pBoardSquare[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardSquare[c]->piece, pGame->pBoardSquare[c]->x, pGame->pBoardSquare[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													OnWin(NULL, pGame);
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
												default:
													pGame->pBoardSquare[i]->piece = 'n';
													pGame->pBoardSquare[i]->r_left = 0;
													pGame->pBoardSquare[i]->r_right = 0;
													pGame->pBoardSquare[i]->r_top = 0;
													pGame->pBoardSquare[i]->r_bottom = 0;
													pGame->pBoardSquare[i]->force = 0;
													pGame->pBoardSquare[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}
                                        // On parcoure dans l'autre sens
                                        i = i+1;

										if(i-1 >= 0) {
										pGame->pBoardSquare[i-1]->piece = pGame->pBoardSquare[i]->piece;
										pGame->pBoardSquare[i-1]->r_left = pGame->pBoardSquare[i]->r_left;
										pGame->pBoardSquare[i-1]->r_right = pGame->pBoardSquare[i]->r_right;
										pGame->pBoardSquare[i-1]->r_top = pGame->pBoardSquare[i]->r_top;
										pGame->pBoardSquare[i-1]->r_bottom = pGame->pBoardSquare[i]->r_bottom;
										pGame->pBoardSquare[i-1]->force = pGame->pBoardSquare[i]->force;
										pGame->pBoardSquare[i-1]->direction = pGame->pBoardSquare[i]->direction;
										printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i-1, pGame->pBoardSquare[i-1]->piece, pGame->pBoardSquare[i-1]->direction, pGame->pBoardSquare[i-1]->x, pGame->pBoardSquare[i-1]->y);
										RefreshDisplay(pGame, i-1);

										}

										// C'est ce qu'il manquait
										if(i-1 == i_tmp) {
											pGame->pBoardSquare[i]->piece = 'n';
											pGame->pBoardSquare[i]->r_left = 0;
											pGame->pBoardSquare[i]->r_right = 0;
											pGame->pBoardSquare[i]->r_top = 0;
											pGame->pBoardSquare[i]->r_bottom = 0;
											pGame->pBoardSquare[i]->force = 0;
											pGame->pBoardSquare[i]->direction = 'n';
											break;
										}

									}
								}
								else	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Poussée impossible !");
								break;
						}
				
						pGame->turn++;
				}

				// On rafraîchit l'image :
				RefreshDisplay(pGame, number);

				// Si on est pas en mode "rotation". Un test est moins coûteux qu'un rechargement de l'image
				if(number != number2)
					RefreshDisplay(pGame, number2);

				// Signifie qu'on a cliqué sur le bouton d'arrivée - tout s'est déroulé correctement
				pGame->round = 0;
				
				break;

			default:
				break;
		}
	}
	
	
	// METTRE ICI LE CODE LORSQUE L'IA SERA COMMENCÉE - else if(mode == 1)

}

void RefreshDisplay(MainWindow *pGame, gint number) {
	switch(pGame->pBoardSquare[number]->direction) {
		case 't':
			switch(pGame->pBoardSquare[number]->piece) {
					gtk_image_clear(GTK_IMAGE(pGame->pBoardSquare[number]->image));
					gtk_widget_destroy(pGame->pBoardSquare[number]->image);
				case 'e':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/elephant.png");
					break;
				case 'r':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/rhino.png");
					break;
				default:
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			break;
		case 'b':
			switch(pGame->pBoardSquare[number]->piece) {
				case 'e':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/elephant-b.png");
					break;
				case 'r':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/rhino-b.png");
					break;
				default:
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			break;
		case 'l':
			switch(pGame->pBoardSquare[number]->piece) {
				case 'e':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/elephant-l.png");
					break;
				case 'r':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/rhino-l.png");
					break;
				default:
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			break;
		case 'r':
			switch(pGame->pBoardSquare[number]->piece) {
				case 'e':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/elephant-r.png");
					break;
				case 'r':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/rhino-r.png");
					break;
				default:
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			break;
		default:
			switch(pGame->pBoardSquare[number]->piece) {
				case 'e':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/elephant-r.png");
					break;
				case 'r':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/rhino-r.png");
					break;
				case 'm':
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/mountain.png");
					break;
				default:
					pGame->pBoardSquare[number]->image = gtk_image_new_from_file("/empty.png");
					break;
			}
			break;
	}
	gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[number]->button), pGame->pBoardSquare[number]->image);

}

void OnWin(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	// Variables
	GtkWidget *pVBox;
	GtkWidget *pHBox;
	GtkWidget *pButtonNewGame;
	GtkWidget *pButtonExit;
	GtkWidget *pLabel;
	GtkWidget *pImage;
	gchar temp[40];
	
	// Fenêtre
	pGame->pVictoryWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pVictoryWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pVictoryWindow), "Victoire !");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pVictoryWindow), 500, 500);
	gtk_container_set_border_width(GTK_CONTAINER(pGame->pVictoryWindow), 25);
	
	// Boutons
	pButtonNewGame = gtk_button_new_with_label("Nouvelle Partie");
	pButtonExit = gtk_button_new_with_label("Quitter");

	// Image
	pImage = gtk_image_new_from_file("/win.png");
	
	if(pGame->turn %2 == 0) {
		sprintf(temp, "Bien joué %s, vous avez gagné !", gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		pLabel = gtk_label_new(temp);
	}
	else {
		sprintf(temp, "Bien joué %s, vous avez gagné !", gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		pLabel = gtk_label_new(temp);
	}
	
	// Boxes
	pVBox = gtk_vbox_new(FALSE,15);
	pHBox = gtk_hbox_new(TRUE,0);
				
	gtk_box_pack_start(GTK_BOX(pVBox), pLabel, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pHBox), pButtonExit, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pHBox), pButtonNewGame, TRUE, TRUE, 5);
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox, TRUE, TRUE, 0);
	
	// On accroche la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pVictoryWindow), pVBox);
	
	// Signaux des boutons
	g_signal_connect(G_OBJECT(pButtonExit), "clicked", gtk_main_quit, NULL);
	g_signal_connect(G_OBJECT(pButtonNewGame), "clicked", G_CALLBACK(OnDestroyWinWindow), (MainWindow*) pGame);
	
	gtk_widget_show_all(pGame->pVictoryWindow);
}

void OnDestroyWinWindow (GtkWidget *pMenuItem, MainWindow *pGame) {
	
	// Ce programme permet juste de detruire la fenetre de victoire et de créer une nouvelle partie
	gtk_widget_destroy(pGame->pVictoryWindow);
	OnButtonNewGame(NULL, pGame);
	
}

void OnSkipTurn(GtkWidget *pButton, MainWindow* pGame) {
	
	// On passe la main à l'autre joueur
	pGame->turn++%2;
	gchar temp[150];
	
	if(((pGame->turn) % 2) == 0) {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	else {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
}

void OnButtonRight(GtkWidget *pButton, MainWindow *pGame) {
	
	gchar temp[48];
	GtkWidget *pWindow = gtk_widget_get_parent(gtk_widget_get_parent(pButton));
	if(pGame->pBoardSquare[pGame->number]->direction != 'r') {
	pGame->pBoardSquare[pGame->number]->direction = 'r';
	pGame->pBoardSquare[pGame->number]->r_top = 0;
	pGame->pBoardSquare[pGame->number]->r_right = 1;
	pGame->pBoardSquare[pGame->number]->r_left = 0;
	pGame->pBoardSquare[pGame->number]->r_bottom = 0;
	RefreshDisplay(pGame, pGame->number);
	sprintf(temp,"Le pion %d a été orienté vers la droite.", pGame->number);
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);
	pGame->turn++%2;
	}
	else
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion est déjà orienté vers la droite !");
	
	if(((pGame->turn) % 2) == 0) {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	else {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	gtk_widget_destroy(pWindow);
}

void OnButtonLeft(GtkWidget *pButton, MainWindow *pGame) {
	gchar temp[48];
	GtkWidget *pWindow = gtk_widget_get_parent(gtk_widget_get_parent(pButton));
	if(pGame->pBoardSquare[pGame->number]->direction != 'l') {
		pGame->pBoardSquare[pGame->number]->direction = 'l';
		pGame->pBoardSquare[pGame->number]->r_top = 0;
		pGame->pBoardSquare[pGame->number]->r_right = 0;
		pGame->pBoardSquare[pGame->number]->r_left = 1;
		pGame->pBoardSquare[pGame->number]->r_bottom = 0;
		RefreshDisplay(pGame, pGame->number);
		sprintf(temp,"Le pion %d a été orienté vers la gauche.", pGame->number);
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);
		pGame->turn++%2;
	}
	else
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion est déjà orienté vers la gauche !");
	
	if(((pGame->turn) % 2) == 0) {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	else {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	gtk_widget_destroy(pWindow);
}

void OnButtonTop(GtkWidget *pButton, MainWindow *pGame) {
	gchar temp[48];
	GtkWidget *pWindow = gtk_widget_get_parent(gtk_widget_get_parent(pButton));
	if(pGame->pBoardSquare[pGame->number]->direction != 't') {
		pGame->pBoardSquare[pGame->number]->direction = 't';
		pGame->pBoardSquare[pGame->number]->r_top = 1;
		pGame->pBoardSquare[pGame->number]->r_right = 0;
		pGame->pBoardSquare[pGame->number]->r_left = 0;
		pGame->pBoardSquare[pGame->number]->r_bottom = 0;
		RefreshDisplay(pGame, pGame->number);
		sprintf(temp,"Le pion %d a été orienté vers le haut.", pGame->number);
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);
		pGame->turn++%2;
	}
	else
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion est déjà orienté vers le haut !");
	
	if(((pGame->turn) % 2) == 0) {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	else {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	gtk_widget_destroy(pWindow);
}

void OnButtonBottom(GtkWidget *pButton, MainWindow *pGame) {
	gchar temp[48];
	GtkWidget *pWindow = gtk_widget_get_parent(gtk_widget_get_parent(pButton));
	if(pGame->pBoardSquare[pGame->number]->direction != 'b') {
		pGame->pBoardSquare[pGame->number]->direction = 'b';
		pGame->pBoardSquare[pGame->number]->r_top = 0;
		pGame->pBoardSquare[pGame->number]->r_right = 0;
		pGame->pBoardSquare[pGame->number]->r_left = 0;
		pGame->pBoardSquare[pGame->number]->r_bottom = 1;
		RefreshDisplay(pGame, pGame->number);
		sprintf(temp,"Le pion %d a été orienté vers le bas.", pGame->number);
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, temp);
		pGame->turn++%2;
	}
	else
		gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion est déjà orienté vers le bas !");
	
	if(((pGame->turn) % 2) == 0) {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	else {
		strcpy(temp, "Tour de jeu : ");
		strcat(temp, gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp);
	}
	
	gtk_widget_destroy(pWindow);
}
