/*
 *  newgame.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

void InitGame(GtkWidget *pButton, MainWindow *pGame) {
	
	// Variables
	gchar *temp;
	
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
	if(pGame->timer == TRUE) {
		// On arrête le chrono (voir la procédure adéquate, vous comprendrez !) 
		pGame->chrono = 0;
		g_timeout_add_seconds(1, (gpointer)timeout, (MainWindow *)pGame);
	}
	
	// On modifie le message de la barre d'outils
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "La partie a débutée, c'est à vous de jouer");
	
	/* Détruit la fenêtre (elle reçoit donc un signal "destroy") 
	C'est pourquoi on ne doit pas connecter le signal "destroy" de la fenêtre 
	( = plantage car essaierai de destroy un GtkWidget déjà détruit) */
	gtk_widget_destroy(pGame->pNewGameWindow);
	
}
