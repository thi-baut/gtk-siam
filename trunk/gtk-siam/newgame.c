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
	
	// On s'occupe de toutes les cases
	for(i = 0; i < 35; i++) {
		pGame->pBoardButton[i]->piece = 'n';
		pGame->pBoardButton[i]->r_left = 0;
		pGame->pBoardButton[i]->r_right = 0;
		pGame->pBoardButton[i]->r_top = 0;
		pGame->pBoardButton[i]->r_bottom = 0;
		pGame->pBoardButton[i]->force = 0;
		pGame->pBoardButton[i]->direction = 'n';
		pGame->pBoardButton[i]->image = gtk_image_new();
	}
	
#ifndef WIN32
	for( i= 0; i< 25; i++) {
		// Couleurs des boutons
		switch(i%2) {
			case 0:
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_NORMAL, &pGame->black);
				if(pGame->toggle_color == TRUE) {
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->black_clicked);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->black_clicked);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_SELECTED, &pGame->black_clicked);
				}
				else {
					gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->black);
					gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->black);
					gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_SELECTED, &pGame->black);
				}
				break;
			case 1:
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_NORMAL, &pGame->white);
				if(pGame->toggle_color == TRUE) {
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->white_clicked);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->white_clicked);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_SELECTED, &pGame->white_clicked);
				}
				else {
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->white);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->white);
				gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_SELECTED, &pGame->white);
				}
				break;
		}
	}
	
	// Couleurs des boutons out
	for(i = 25; i < 35; i++) {
		gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_NORMAL, &pGame->brown);
		if(pGame->toggle_color == TRUE) {
		gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->brown_clicked);
		gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->brown_clicked);
		gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->brown_clicked);
		}
		else {
			gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_PRELIGHT, &pGame->brown);
			gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_ACTIVE, &pGame->brown);
			gtk_widget_modify_bg (pGame->pBoardButton[i]->button, GTK_STATE_SELECTED, &pGame->brown);
		}
	}
#endif
	
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
		pGame->pBoardButton[i]->r_right = 1; // A 1 car le pion est en r au début
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
		pGame->pBoardButton[i]->image = gtk_image_new_from_file("/rhino-l.png");
		pGame->pBoardButton[i]->piece = 'r';
		pGame->pBoardButton[i]->r_left = 1; // A 1 voir au dessus
		pGame->pBoardButton[i]->r_right = 0;
		pGame->pBoardButton[i]->r_top = 0;
		pGame->pBoardButton[i]->r_bottom = 0;
		pGame->pBoardButton[i]->force = 1;
		pGame->pBoardButton[i]->direction = 'l';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]->button), pGame->pBoardButton[i]->image);

		pGame->pBoardButton[i]->y = i-30; // Signifie que le pion est hors plateau
		pGame->pBoardButton[i]->x = 5;

	}
	
	for(i = 0; i < 35; i++) {
		RefreshDisplay(pGame, i);
	}

}
void InitGame(GtkWidget *pButton, MainWindow *pGame) {

	// Variables
	gchar temp[60];
	gchar temp2[60];
	gint i;
	
	// On enregistre les paramètres du chrono
	pGame->timer = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxTimer));

	// On enregistre le type de partie (J vs. CPU ou J vs. J)
	pGame->mode = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxCPU));

	// On enregistre le choix du joueur concernant les pions
	pGame->pion = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxAnimal));
	
	// On enregistre le choix du joueur concernant les pions
	pGame->toggle_color = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxToggle));

	// On enregistre le nom du joueur
	pGame->player_name[0] = gtk_entry_get_text(GTK_ENTRY(pGame->pNewGameEntry[0]));
	strcpy(temp, pGame->player_name[0]);
	strcpy(temp2,"Tour de jeu : ");
	strcat(temp2, pGame->player_name[0]);
	gtk_label_set_text(GTK_LABEL(pGame->pPlayerLabel[0]), temp);
	gtk_label_set_text(GTK_LABEL(pGame->pLabel[3]), temp2);
	
	pGame->player_name[1] = gtk_entry_get_text(GTK_ENTRY(pGame->pNewGameEntry[1]));
	strcpy(temp, pGame->player_name[1]);
	gtk_label_set_text(GTK_LABEL(pGame->pPlayerLabel[1]), temp);


	if(pGame->mode == FALSE)
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[2]), "Mode : Humain vs. CPU");

	else if(pGame->mode == TRUE)
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[2]), "Mode : Humain vs. Humain");

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
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "La partie a débuté, c'est à vous de jouer !");

	// On applique les callbacks pour tous les boutons
	if(pGame->first_init == TRUE) {
		for(i = 0; i < 35; i++) {
		g_signal_connect(G_OBJECT(pGame->pBoardButton[i]->button), "clicked", G_CALLBACK(ActionInGame), pGame);
		}
		
		//Hbox
		gtk_container_remove(GTK_CONTAINER(pGame->pHBox), pGame->pStartImage);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pVBox1, FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pSeparator[0], FALSE, FALSE, 15);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pTable, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pSeparator[1], FALSE, FALSE, 15);
		gtk_box_pack_end(GTK_BOX(pGame->pHBox), pGame->pVBox2, FALSE, FALSE, 0);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[0], "Nom du joueur 1", "Nom du joueur 1", -1);
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pPlayerLabel[0], "Nom du joueur 1", "Nom du joueur 1", -1);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[4], "Nom du joueur 2", "Nom du joueur 2", -1);
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pPlayerLabel[1], "Nom du joueur 1", "Nom du joueur 1", -1);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[1], "Chronomètre", "Chronomètre", -1);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[2], "Mode", "Mode", -1);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[3], "Tour", "Tour", -1);
		gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
		gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[5], "Tour", "Tour", -1);
		gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_GOTO_LAST, "Passer le tour", NULL, G_CALLBACK(OnSkipTurn), pGame, -1);
		gtk_widget_show_all(pGame->pWindow);
		
		pGame->first_init = FALSE;
	}
	
	/* Détruit la fenêtre (elle reçoit donc un signal "destroy")
	C'est pourquoi on ne doit pas connecter le signal "destroy" de la fenêtre
	( = plantage car essaierai de destroy un GtkWidget déjà détruit) */
	if(pGame->player_name[0][0] == '\0' || pGame->player_name[1][0] == '\0') {
		GtkWidget *pDialog;
		pDialog = gtk_message_dialog_new(GTK_WINDOW(pGame->pNewGameWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_OK, "Vous n'avez pas entré les noms correctement !");
		gtk_window_set_position(GTK_WINDOW(pDialog), GTK_WIN_POS_CENTER);
		gtk_window_set_title(GTK_WINDOW(pDialog), "GTK-Siam - Erreur");
		gtk_dialog_run(GTK_DIALOG(pDialog));
		gtk_widget_destroy(pDialog);
		gtk_widget_destroy(pGame->pNewGameWindow);
		OnButtonNewGame(NULL, pGame);
	}
	else {
		
		gtk_widget_destroy(pGame->pNewGameWindow);
		
		// Sinon, on opère les modifications visuelles
		// On charge le plateau
		LoadBoard(pGame);
	}
}
