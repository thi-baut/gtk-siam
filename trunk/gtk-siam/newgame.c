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
	// On s'occupe de tous les pions
	for(i = 0; i < 35; i++) {
		pGame->pBoardButton[i]->piece = 'n';
		pGame->pBoardButton[i]->image = gtk_image_new();
	}
	
	// On s'occupe des montagnes
	for(i = 11; i <= 13; i++) {
		pGame->pBoardButton[i]->piece = 'm';
		pGame->pBoardButton[i]->r_left = 0.9;
		pGame->pBoardButton[i]->r_right = 0.9;
		pGame->pBoardButton[i]->r_top = 0.9;
		pGame->pBoardButton[i]->r_bottom = 0.9;
		pGame->pBoardButton[i]->image = gtk_image_new_from_file("/mountain.png");
		pGame->pBoardButton[i]->force = 0;
		pGame->pBoardButton[i]->direction = 'n';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]->button), pGame->pBoardButton[i]->image);
	}
	
	// On enregistre les paramètres des pions hors-jeu
	// Éléphants
	for(i = 25; i < 30; i++) {
		pGame->pBoardButton[i]->image = gtk_image_new_from_file("/elephant-r.png");
		pGame->pBoardButton[i]->piece = 'e';
		pGame->pBoardButton[i]->r_left = 0;
		pGame->pBoardButton[i]->r_right = 0;
		pGame->pBoardButton[i]->r_top = 0;
		pGame->pBoardButton[i]->r_bottom = 0;
		pGame->pBoardButton[i]->force = 1;
		pGame->pBoardButton[i]->direction = 'r';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]->button), pGame->pBoardButton[i]->image);
		pGame->pBoardButton[i]->x = -1; // Signifie que le pion est hors plateau
		pGame->pBoardButton[i]->y = i-25;
	}
	
	// Rhinocéros
	for(i = 30; i < 35; i++) {
		pGame->pBoardButton[i]->image = gtk_image_new_from_file("/rhino-r.png");
		pGame->pBoardButton[i]->piece = 'r';
		pGame->pBoardButton[i]->r_left = 0;
		pGame->pBoardButton[i]->r_right = 0;
		pGame->pBoardButton[i]->r_top = 0;
		pGame->pBoardButton[i]->r_bottom = 0;
		pGame->pBoardButton[i]->force = 1;
		pGame->pBoardButton[i]->direction = 'l';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]->button), pGame->pBoardButton[i]->image);
		pGame->pBoardButton[i]->y = i-30; // Signifie que le pion est hors plateau
		pGame->pBoardButton[i]->x = 5;
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
	pGame->pion = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxAnimal));
	
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
	
	// On applique les callbacks pour tous les boutons
	for(i = 0; i < 35; i++) {
		g_signal_connect(G_OBJECT(pGame->pBoardButton[i]->button), "clicked", G_CALLBACK(ActionInGame), pGame);
	}
	
	/* Détruit la fenêtre (elle reçoit donc un signal "destroy") 
	C'est pourquoi on ne doit pas connecter le signal "destroy" de la fenêtre 
	( = plantage car essaierai de destroy un GtkWidget déjà détruit) */
	gtk_widget_destroy(pGame->pNewGameWindow);
}
