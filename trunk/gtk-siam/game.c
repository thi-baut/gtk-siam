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
	gint i, c;
	gfloat resistance;
	gint i_tmp;
	gint j = 0;
	
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
							pGame->pBoardButton[number]->r_top = 0;
							pGame->pBoardButton[number]->r_right = 1;
							break;
						case 'b':
							pGame->pBoardButton[number]->direction = 'l';
							pGame->pBoardButton[number]->r_bottom = 0;
							pGame->pBoardButton[number]->r_left = 1;
							break;
						case 'l':
							pGame->pBoardButton[number]->direction = 't';
							pGame->pBoardButton[number]->r_left = 0;
							pGame->pBoardButton[number]->r_top = 1;
							break;
						case 'r':
							pGame->pBoardButton[number]->direction = 'b';
							pGame->pBoardButton[number]->r_right = 0;
							pGame->pBoardButton[number]->r_bottom = 1;
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
				
				else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==1 && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5) {
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
					
				}
				
				else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==-1 && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5){
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
					
				}
				
				else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==-1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==1 && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5){
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
					
				}
				
				else if((((pGame->pBoardButton[number2]->x)-(pGame->pBoardButton[number]->x))==-1) && ((pGame->pBoardButton[number2]->y)-(pGame->pBoardButton[number]->y))==-1 && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5){
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Déplacement en diagonale interdit !");	
					
				}

				
				else if((((number>=30) && (number<35)) || ((number>=25) && (number<30)))  && ((pGame->pBoardButton[number2]->piece !='n'))){
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Rentrée sur le plateau impossible");
					
				}
				
				else if((((pGame->turn) % 2) == 0) & (pGame->pBoardButton[number]->piece != 'r')) {
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas bouger un pion adverse");
					
				}
				
				else if((((pGame->turn) % 2) != 0) & (pGame->pBoardButton[number]->piece != 'e')) {
					
					gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Vous ne pouvez pas bouger un pion adverse");
					
				}
			
				
				// Cas de l'échange, c'est à dire qu'on inverse deux pièces. Simple déplacement des pions en fait !
				else if (pGame->pBoardButton[number2]->piece == 'n')  {

					
					// C'est ici que l'on vérifie que le sens du pion est correctement enregistré pour permettre le déplacement
					if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x > 0) && (pGame->pBoardButton[number]->direction != 'l') && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->x - pGame->pBoardButton[number2]->x < 0) && (pGame->pBoardButton[number]->direction != 'r') && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y > 0) && (pGame->pBoardButton[number]->direction != 't') && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else if((pGame->pBoardButton[number]->y - pGame->pBoardButton[number2]->y < 0) && (pGame->pBoardButton[number]->direction != 'b') && (pGame->pBoardButton[number]->x)>0 && (pGame->pBoardButton[number]->y)>5)
						gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 0, "Le pion n'est pas correctement orienté pour ce déplacement");
					
					else 	
					 {
						
						if(((pGame->turn) % 2) == 0) {
							
							gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), "Tour de jeu : Joueur 1");
														
						}
						
						else {							
							gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), "Tour de jeu : Joueur 2");
													
						}
				
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

		
						pGame->turn++;

					}
				}
				
				// Cas de la poussée : et là, c'est le drame.
				else {
					if(pGame->pBoardButton[number]->piece == 'e')
						switch(pGame->pBoardButton[number]->direction) {
							case 't':
								i = number;
								i_tmp = number;
								resistance = pGame->pBoardButton[number]->force;
								while(pGame->pBoardButton[i]->piece != 'n') {
									
									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);
									
									if(pGame->pBoardButton[i]->y <= 0) break;
									i = i-5;
									j++;
									
									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardButton[i]->direction) {
										case 'b':
											if(pGame->pBoardButton[i]->piece == 'r')
												resistance = resistance - pGame->pBoardButton[i]->r_bottom;
											break;
										case 't':
											if(pGame->pBoardButton[i]->piece == 'e')
												resistance = resistance + pGame->pBoardButton[i]->force;
										default:
											if(pGame->pBoardButton[i]->piece == 'm')
												resistance = resistance - pGame->pBoardButton[i]->r_top;
											break;
									}
								}
								printf("La valeur de j est %d", j);
								if(resistance > 0) {
									
									while(i-5 <= i_tmp) {
									
									// Déplacement des pions
										if(pGame->pBoardButton[i]->y == 0) {
											switch(pGame->pBoardButton[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardButton[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
												
												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardButton[c]->piece != 'n') c++;
													
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';

													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													printf("\nPartie terminée, vous avez gagné !");
													break;
												default:
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}
										
										printf("\nLa valeur de i est %d", i);

										if(i-5 >= 0) {
										pGame->pBoardButton[i-5]->piece = pGame->pBoardButton[i]->piece;
										pGame->pBoardButton[i-5]->r_left = pGame->pBoardButton[i]->r_left;
										pGame->pBoardButton[i-5]->r_right = pGame->pBoardButton[i]->r_right;
										pGame->pBoardButton[i-5]->r_top = pGame->pBoardButton[i]->r_top;
										pGame->pBoardButton[i-5]->r_bottom = pGame->pBoardButton[i]->r_bottom;
										pGame->pBoardButton[i-5]->force = pGame->pBoardButton[i]->force;
										pGame->pBoardButton[i-5]->direction = pGame->pBoardButton[i]->direction;
											
										printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->direction, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
										RefreshDisplay(pGame, i-5);

										}
										
										i = i+5; // On parcoure dans l'autre sens vu qu'on reprend la dernière valeur de i
									}
								}
								break;
							case 'b':
								
								resistance = pGame->pBoardButton[number]->force;
								i = number;
								while(pGame->pBoardButton[i]->piece != 'n') {
									
									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);
									
									if(pGame->pBoardButton[i]->y > 4) break;
									i = i+5;
									j++;
									
									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardButton[i]->direction) {
										case 't':
											if(pGame->pBoardButton[i]->piece == 'r')
												resistance = resistance - pGame->pBoardButton[i]->r_bottom;
											break;
										case 'b':
											if(pGame->pBoardButton[i]->piece == 'e')
												resistance = resistance + pGame->pBoardButton[i]->force;
										default:
											if(pGame->pBoardButton[i]->piece == 'm')
												resistance = resistance - pGame->pBoardButton[i]->r_top;
											break;
									}
								}
								i_tmp = i;
								printf("\nLa valeur de j est %d", j);
								if(resistance > 0) {
									
									while(i >= 0) {
										printf("\nPion %d", i+5);
										// Déplacement des pions
										if(pGame->pBoardButton[i+5]->y == 4) {
											switch(pGame->pBoardButton[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardButton[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i+5]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i+5]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i+5]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i+5]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i+5]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i+5]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i+5]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i+5, pGame->pBoardButton[i+5]->piece, pGame->pBoardButton[i+5]->x, pGame->pBoardButton[i+5]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
													
												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardButton[c]->piece != 'n') c++;
													
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i+5]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i+5]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i+5]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i+5]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i+5]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i+5]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i+5]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i+5, pGame->pBoardButton[i+5]->piece, pGame->pBoardButton[i+5]->x, pGame->pBoardButton[i+5]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													printf("\nPartie terminée, vous avez gagné !");
													break;
												default:
													pGame->pBoardButton[i+5+5]->piece = 'n';
													pGame->pBoardButton[i+5]->r_left = 0;
													pGame->pBoardButton[i+5]->r_right = 0;
													pGame->pBoardButton[i+5]->r_top = 0;
													pGame->pBoardButton[i+5]->r_bottom = 0;
													pGame->pBoardButton[i+5]->force = 0;
													pGame->pBoardButton[i+5]->direction = 'n';
													RefreshDisplay(pGame, i+5);
													break;
											}
										}
										
										printf("\nLa valeur de i est %d", i);
										
										if(i+5 <= 24) {
											pGame->pBoardButton[i+5]->piece = pGame->pBoardButton[i]->piece;
											pGame->pBoardButton[i+5]->r_left = pGame->pBoardButton[i]->r_left;
											pGame->pBoardButton[i+5]->r_right = pGame->pBoardButton[i]->r_right;
											pGame->pBoardButton[i+5]->r_top = pGame->pBoardButton[i]->r_top;
											pGame->pBoardButton[i+5]->r_bottom = pGame->pBoardButton[i]->r_bottom;
											pGame->pBoardButton[i+5]->force = pGame->pBoardButton[i]->force;
											pGame->pBoardButton[i+5]->direction = pGame->pBoardButton[i]->direction;
											
											printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->direction, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
											RefreshDisplay(pGame, i+5);
											
										}
										
										i = i-5; // On parcoure dans l'autre sens vu qu'on reprend la dernière valeur de i
									}
								}
								break;
								
							case 'l':
								i = number;
								i_tmp = number;
								resistance = pGame->pBoardButton[number]->r_left;
								while(pGame->pBoardButton[i]->piece != 'n') {
									
									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);
									
									if(pGame->pBoardButton[i]->x == 0) break;
									i = i-1;
									j++;
									
									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardButton[i]->direction) {
										case 'r':
											if(pGame->pBoardButton[i]->piece == 'r')
												resistance = resistance - pGame->pBoardButton[i]->r_right;
											break;
										case 'l':
											if(pGame->pBoardButton[i]->piece == 'e')
												resistance = resistance + pGame->pBoardButton[i]->force;
										default:
											if(pGame->pBoardButton[i]->piece == 'm')
												resistance = resistance - pGame->pBoardButton[i]->r_top;
											break;
									}
								}
								printf("\nLa valeur de j est %d", j);
								if(resistance > 0) {
									while(i-1 <= i_tmp) {

										// Déplacement des pions
										if(pGame->pBoardButton[i]->x == 0) {
											switch(pGame->pBoardButton[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardButton[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													
													printf("\n1) La case %d, contient %c", c, pGame->pBoardButton[c]->piece);
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
													
												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardButton[c]->piece != 'n') c++;
													
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													printf("\nPartie terminée, vous avez gagné !");
													break;
												default:
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}
										
										printf("\nLa valeur de i est %d", i);
										
										if(i-1 >= 0) {
											pGame->pBoardButton[i-1]->piece = pGame->pBoardButton[i]->piece;
											pGame->pBoardButton[i-1]->r_left = pGame->pBoardButton[i]->r_left;
											pGame->pBoardButton[i-1]->r_right = pGame->pBoardButton[i]->r_right;
											pGame->pBoardButton[i-1]->r_top = pGame->pBoardButton[i]->r_top;
											pGame->pBoardButton[i-1]->r_bottom = pGame->pBoardButton[i]->r_bottom;
											pGame->pBoardButton[i-1]->force = pGame->pBoardButton[i]->force;
											pGame->pBoardButton[i-1]->direction = pGame->pBoardButton[i]->direction;
											
											printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->direction, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
											RefreshDisplay(pGame, i-1);
											RefreshDisplay(pGame, i);
											
										}
										
										i = i+1; // On parcoure dans l'autre sens vu qu'on reprend la dernière valeur de i
									}
								}
								break;
								
							case 'r':
								i = number;
								resistance = pGame->pBoardButton[number]->r_right;
								while(pGame->pBoardButton[i]->piece != 'n') {
									
									printf("\nPion %d", i);
									printf("\nLa force restante est de %2f", resistance);
									
									if(pGame->pBoardButton[i]->x > 4) break;
									i = i+1;
									j++;
									
									// On soustrait les résistances des pions qui s'opposent au mouvement
									switch(pGame->pBoardButton[i]->direction) {
										case 'l':
											if(pGame->pBoardButton[i]->piece == 'r')
												resistance = resistance - pGame->pBoardButton[i]->r_left;
											break;
										case 'r':
											if(pGame->pBoardButton[i]->piece == 'e')
												resistance = resistance + pGame->pBoardButton[i]->force;
										default:
											if(pGame->pBoardButton[i]->piece == 'm')
												resistance = resistance - pGame->pBoardButton[i]->r_top;
											break;
									}
								}
								i_tmp = i;
								printf("\nLa valeur de j est %d", j);
								if(resistance > 0) {
									while(i+1 >= 0) {
										
										// Déplacement des pions
										if(pGame->pBoardButton[i]->x == 0) {
											switch(pGame->pBoardButton[i]->piece) {
												case 'e':
													// Doit checker si il y a une case libre (normalement oui...) dans la zone de garage des éléphants
													c = 25;
													while(c < 30 && pGame->pBoardButton[c]->piece != 'n') c++;
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													
													printf("\n1) La case %d, contient %c", c, pGame->pBoardButton[c]->piece);
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
													
												case 'r':
													c = 30;
													while(c < 35 && pGame->pBoardButton[c]->piece != 'n') c++;
													
													printf("\nUne case libre est la case %d", c);
													// Vu que le pion en question est en haut, on l'échange avec la case libre pour dégager tout ça
													
													pGame->pBoardButton[c]->piece = pGame->pBoardButton[i]->piece;
													pGame->pBoardButton[c]->r_left = pGame->pBoardButton[i]->r_left;
													pGame->pBoardButton[c]->r_right = pGame->pBoardButton[i]->r_right;
													pGame->pBoardButton[c]->r_top = pGame->pBoardButton[i]->r_top;
													pGame->pBoardButton[c]->r_bottom = pGame->pBoardButton[i]->r_bottom;
													pGame->pBoardButton[c]->force = pGame->pBoardButton[i]->force;
													pGame->pBoardButton[c]->direction = pGame->pBoardButton[i]->direction;
													
													// On s'assure que la case est "vidée"
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													
													printf("\n1) Pion %d est un %c aux coordonnées %d, %d", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
													printf("\n2) Pion %d est un %c aux coordonnées %d, %d\n", c, pGame->pBoardButton[c]->piece, pGame->pBoardButton[c]->x, pGame->pBoardButton[c]->y);
													RefreshDisplay(pGame, c);
													break;
												case 'm':
													// Si c'est ça, le joueur X a gagné
													printf("\nPartie terminée, vous avez gagné !");
													break;
												default:
													pGame->pBoardButton[i]->piece = 'n';
													pGame->pBoardButton[i]->r_left = 0;
													pGame->pBoardButton[i]->r_right = 0;
													pGame->pBoardButton[i]->r_top = 0;
													pGame->pBoardButton[i]->r_bottom = 0;
													pGame->pBoardButton[i]->force = 0;
													pGame->pBoardButton[i]->direction = 'n';
													RefreshDisplay(pGame, i);
													break;
											}
										}
										
										printf("\nLa valeur de i est %d", i);
										
										if(i+1 <= 24) {
											pGame->pBoardButton[i+1]->piece = pGame->pBoardButton[i]->piece;
											pGame->pBoardButton[i+1]->r_left = pGame->pBoardButton[i]->r_left;
											pGame->pBoardButton[i+1]->r_right = pGame->pBoardButton[i]->r_right;
											pGame->pBoardButton[i+1]->r_top = pGame->pBoardButton[i]->r_top;
											pGame->pBoardButton[i+1]->r_bottom = pGame->pBoardButton[i]->r_bottom;
											pGame->pBoardButton[i+1]->force = pGame->pBoardButton[i]->force;
											pGame->pBoardButton[i+1]->direction = pGame->pBoardButton[i]->direction;
											
											printf("\nPion %d est un %c dans le sens %c aux coordonnées %d, %d\n", i, pGame->pBoardButton[i]->piece, pGame->pBoardButton[i]->direction, pGame->pBoardButton[i]->x, pGame->pBoardButton[i]->y);
											RefreshDisplay(pGame, i+1);
											
										}
										
										i = i-1; // On parcoure dans l'autre sens vu qu'on reprend la dernière valeur de i
									}
								}
								break;
						}
				}
				
			
				// On rafraîchit l'image :
				RefreshDisplay(pGame, number);

				if(number != number2)
					RefreshDisplay(pGame, number2);
					
				// Signifie qu'on a cliqué sur le bouton d'arrivée - tout s'est déroulé correctement
				pGame->round = 0;
				
				break;
				
			default:
				break;
		}
	}
	
	/*
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
					// PREPARATION DE L'ECHANGE
					
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
	*/
	
}	

void RefreshDisplay(MainWindow *pGame, gint number) {
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
	
	
	
}