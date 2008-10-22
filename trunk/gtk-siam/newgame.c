/*
 *  newgame.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

void LoadBoard(MainWindow *pGame){
	
	gint i;
		
	// On s'occupe des montagnes
	for(i = 11; i <= 13; i++) {
		pGame->pBoardButton[i]->r_left = 0.9;
		pGame->pBoardButton[i]->r_right = 0.9;
		pGame->pBoardButton[i]->r_top = 0.9;
		pGame->pBoardButton[i]->r_bottom = 0.9;
	}
	
	// On enregistre les paramètres des pions hors-jeu
	// Éléphants
	for(i = 0; i < 5; i++) {
		pGame->pOutButton[i]->image = gtk_image_new_from_file("/elephant.png");
		pGame->pOutButton[i]->piece = 'e';
		pGame->pOutButton[i]->r_left = 0;
		pGame->pOutButton[i]->r_right = 0;
		pGame->pOutButton[i]->r_top = 0;
		pGame->pOutButton[i]->r_bottom = 0;
		pGame->pOutButton[i]->force = 1;
		pGame->pOutButton[i]->direction = 'r';
		gtk_button_set_image(GTK_BUTTON(pGame->pOutButton[i]->button), pGame->pOutButton[i]->image);
	}
	
	// Rhinocéros
	for(i = 5; i < 10; i++) {
		pGame->pOutButton[i]->image = gtk_image_new_from_file("/rhino.png");
		pGame->pOutButton[i]->piece = 'r';
		pGame->pOutButton[i]->r_left = 0;
		pGame->pOutButton[i]->r_right = 0;
		pGame->pOutButton[i]->r_top = 0;
		pGame->pOutButton[i]->r_bottom = 0;
		pGame->pOutButton[i]->force = 1;
		pGame->pOutButton[i]->direction = 'l';
		gtk_button_set_image(GTK_BUTTON(pGame->pOutButton[i]->button), pGame->pOutButton[i]->image);
	}
	
}

void InitGame(GtkWidget *pButton, MainWindow *pGame) {
	
	// Variables
	gchar *temp;
	gint i;
	
	// On enregistre le niveau de la partie
	pGame->level = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxLevel));
	
	// On enregistre les paramètres du chrono
	pGame->timer = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxTimer));
	
	// On enregistre le type de partie (J vs. CPU ou J vs. J)
	pGame->vs_cpu = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxCPU));
	
	// On enregistre le choix du joueur concernant les pions
	pGame->pion = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pion));
	
	// On enregistre le nom du joueur
	pGame->player_name = gtk_entry_get_text(GTK_ENTRY(pGame->pNewGameEntry));
	if(pGame->player_name[0] != '\0') {
		temp = (gchar *) malloc(strlen(pGame->player_name)*sizeof(gchar) + 16);
		strcpy(temp, "Nom du joueur : ");
		strcat(temp, pGame->player_name);
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[0]), temp); /* BUGUE JE NE SAIS PAS POURQUOI : RELOU ! */
	}
	
	// On (re)démarre le timer
	if(pGame->timer == TRUE && pGame->chrono != -1) {
		pGame->chrono = 0;
		timeout(pGame);
	}
	else if(pGame->timer == TRUE && pGame->chrono == -1) {
		timeout(pGame);
		g_timeout_add_seconds(1, (gpointer)timeout, (MainWindow *)pGame);
	}
	
	// On modifie le message de la barre d'outils
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "La partie a débuté, c'est à vous de jouer");
	
	// On modifie le plateau pour afficher les images
	for(i = 0; i < 5; i++)
	gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]), pGame->pImageRhino);
	
	/* Détruit la fenêtre (elle reçoit donc un signal "destroy") 
	C'est pourquoi on ne doit pas connecter le signal "destroy" de la fenêtre 
	( = plantage car essaierai de destroy un GtkWidget déjà détruit) */
	gtk_widget_destroy(pGame->pNewGameWindow);
}
