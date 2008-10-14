/*
 *  menu.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "library.h"

gboolean OnNewGame(GtkWidget *pMenUItem, MainWindow *pGame) {

	GtkWidget *pWindow;
	GtkWidget *pLabel[4];
	GtkWidget *pButton[2];
	GtkWidget *pRadioButton[7];
	GtkWidget *pEntry;
	GtkWidget *pVBox;
	GtkWidget *pHBox[5];
	
	pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pWindow), "GTKSiam - Nouvelle partie");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 400, 200);
	g_signal_connect(pWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	// Labels
	pLabel[0] = gtk_label_new("Niveau :");
	pLabel[1] = gtk_label_new("Temps limité :");
	pLabel[2] = gtk_label_new("Partie :");
	pLabel[3] = gtk_label_new("Nom du joueur :");
	
	// Zone de saisie
	pEntry = gtk_entry_new_with_max_length(30);
	
	// Boutons
	pRadioButton[0] = gtk_radio_button_new_with_label(NULL, "Facile");
	pRadioButton[1] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadioButton[0]), "Moyen");
	pRadioButton[2] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadioButton[0]), "Difficile");
	pRadioButton[4] = gtk_radio_button_new_with_label(NULL, "désactivé");
	pRadioButton[3] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadioButton[4]), "activé");
	pRadioButton[5] = gtk_radio_button_new_with_label(NULL, "Deux joueurs");
	pRadioButton[6] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pRadioButton[5]), "Contre l'ordinateur");
	pButton[0] = gtk_button_new_with_label("Nouvelle partie");
	pButton[1] = gtk_button_new_with_label("Annuler");
	
	// VBox
	pVBox = gtk_vbox_new(TRUE, 10);
	
	// HBox
	pHBox[0] = gtk_hbox_new(FALSE, 10);
	pHBox[1] = gtk_hbox_new(FALSE, 10);
	pHBox[2] = gtk_hbox_new(FALSE, 10);
	pHBox[3] = gtk_hbox_new(FALSE, 10);
	pHBox[4] = gtk_hbox_new(FALSE, 10);
	
	
	/* Ajouter les éléments à la fenêtre */
	
	// HBoxs
	gtk_box_pack_start(GTK_BOX(pHBox[0]), pLabel[0], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pHBox[0]), pRadioButton[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(pHBox[0]), pRadioButton[1], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pHBox[0]), pRadioButton[2], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pHBox[1]), pLabel[1], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pHBox[1]), pRadioButton[3], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pHBox[1]), pRadioButton[4], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pHBox[2]), pLabel[2], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pHBox[2]), pRadioButton[5], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pHBox[2]), pRadioButton[6], FALSE, FALSE, 10);
	
	gtk_box_pack_start(GTK_BOX(pHBox[3]), pLabel[3], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pHBox[3]), pEntry, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pHBox[4]), pButton[0], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pHBox[4]), pButton[1], TRUE, TRUE, 10);
	
	// VBox
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox[0], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox[1], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox[2], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pVBox), pHBox[3], TRUE, TRUE, 2);
	gtk_box_pack_end(GTK_BOX(pVBox), pHBox[4], TRUE, TRUE, 2);
	
	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
	
	/* Connexion des signaux */
	g_signal_connect_swapped(G_OBJECT(pButton[0]), "clicked", G_CALLBACK(gtk_widget_hide_all), pWindow);
	g_signal_connect_swapped(G_OBJECT(pButton[1]), "clicked", G_CALLBACK(gtk_widget_hide_all), pWindow);
	
	gtk_widget_show_all(pWindow);
	
	return 0;
}

void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame){
	GtkWidget *pFileSelection;
	GtkWidget *pParent;
	gchar *sChemin;
	
	pParent = GTK_WIDGET(pGame);
	
	/* Creation de la fenetre de selection */
	pFileSelection = gtk_file_chooser_dialog_new("Ouvrir une partie existante...", GTK_WINDOW(pParent), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_OK, NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
	
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
		case GTK_RESPONSE_OK:
			/* Recuperation du chemin */
			sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
			g_free(sChemin);
			break;
			
		default:
			break;
    }
    gtk_widget_destroy(pFileSelection);
}

void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame){
	GtkWidget *pFileSelection;
	GtkWidget *pParent;
	gchar *sChemin;
	
	pParent = GTK_WIDGET(pGame);
	
	/* Creation de la fenetre de selection */
	pFileSelection = gtk_file_chooser_dialog_new("Choisir un endroit où sauver la partie...", GTK_WINDOW(pParent), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_OK, NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
	
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
		case GTK_RESPONSE_OK:
			/* Recuperation du chemin */
			sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
			g_free(sChemin);
			break;
			
		default:
			break;
    }
    gtk_widget_destroy(pFileSelection);
}

void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame) {
	GtkWidget *pWindowAbout;
	GtkWidget *pScrollbar;
	GtkWidget *pLabel;
	//GtkWidget *pDialog;
	
	pWindowAbout = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWindowAbout), 300, 400);
	gtk_window_set_title(GTK_WINDOW(pWindowAbout), "Règles du jeu");
	g_signal_connect(G_OBJECT(pWindowAbout),"destroy",G_CALLBACK(gtk_widget_hide_all),NULL);
	
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(pWindowAbout), pScrollbar);
	
	pLabel = gtk_label_new("Règles du jeu :\n\nChaque joueur choisit son animal.\nLes joueurs joueront à tour de rôle.\nAu début du jeu les animaux sont disposés à l'extérieur du plateau et les blocs de rochers au centre du plateau.\nLes éléphants blancs, animaux sacrés dans le royaume de SIAM commenceront à jouer.\n\nLes joueurs ne pourront jouer à chaque tour de jeu qu'un seul de leur animal et ne faire qu'une des 5 actions suivantes :\n- Entrer un de ses animaux sur le plateau\n- Se déplacer sur une case libre\n- Changer l'orientation de son animal sans changer de case\n- Sortir un de ses animaux disposés sur une case extérieure\n- Se déplacer en poussant d'autres pièces disposées sur le plateau\n\nEntrer un de ses animaux sur le plateau :\nVous devez entrer un de vos animaux par l'une des cases extérieures.\nDeux cas peuvent se présenƒter :\n- la case est libre et dans ce cas vous pouvez placer votre animal en l'orientant dans la direction de votre choix\n- la case est occupée et vous pouvez sous certaines conditions rentrer en effectuant un poussée (voir \"se déplacer en poussant\").\n\nSe déplacer sur une case libre :\n\nVous ne pouvez vous déplacer que d'une seule case et de façon orthogonale (déplacement en diagonale interdit).\nL'orientation de votre animal n'importe pas sur la direction de votre déplacement.\nTout en vous déplaçant, vous pouvez à votre guise changer l'orientation de votre animal\n\nChanger l'orientation de son animal sans chanter de case :\nVous pouvez changer l'orientation de votre animal sur sa case, ce coup compte comme un tour de jeu.\n\nSortir un de ses animaux disposé sur une case extérieure :\nVous pouvez sortir du plateau et à tout moment un de vos animaux disposé sur une case extérieure, ce coup compte comme un tour de jeu.\nL'animal sorti pourra être réutilisé et revenir sur le plateau à tout moment.\n\nSe déplacer en poussant d'autres pièces disposées sur le plateau :\nLorsque la case ou vous voulez vous rendre est occupée par une pièce (éléphant, rhinocéros ou rochers), vous pouvez sous certaines conditions effectuer une poussée :\n- Vous ne pouvez pousser que dans une seule direction : vers l'avant de votre animal.\n- Un animal peut pousser un rocher, deux animaux orientés dans la bonne direction peuvent pousser deux rochers, et trois animaux orientés dans la bonne direction peuvent pousser trois.\n- Un animal ne peut pousser un autre animal qui lui fait face (peu importe à qui appartient l'animal).\n  En effet, rhinos et éléphants ont la même force de poussée ; pour pouvoir pousser, il faut qu'il y ait donc une majorité d'animaux qui poussent dans la même direction.\nPrécision : un de vos animaux peut empêcher votre poussée, un animal adverse peut aider votre poussée.\n- Un animal peut pousser autant d'animaux que possible si ceux-ci ne sont pas orientés dans la direction opposée.\n- Vous pouvez pousser en entrant une pièce sur le plateau.\n- Pour résoudre des situations de poussée plus compliquées, il suffit de regarder les animaux qui se neutralisent et de voir si ceux qui restent sont en nombre suffisant pour pousser des rochers.\n- Lorsqu'un rocher est expulsé la partie est terminée mais attention le gagnant est le joueur qui est le plus proche du rocher et dans le même sens de poussée.\n- Un animal expulsé hors du plateau n'est pas éliminé ; il est récupéré et peut être joué à tout moment.\n- Pendant une poussée, aucun animal ne peut changer d'orientation.");
	
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pLabel);
	gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(pScrollbar), GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
	
	gtk_widget_show_all(pWindowAbout);

	//pDialog = gtk_message_dialog_new(GTK_WINDOW(pGame->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "Règles du jeu :\n\nChaque joueur choisit son animal.\nLes joueurs joueront à tour de rôle.\nAu début du jeu les animaux sont disposés à l'extérieur du plateau et les blocs de rochers au centre du plateau.\nLes éléphants blancs, animaux sacrés dans le royaume de SIAM commenceront à jouer.\n\nLes joueurs ne pourront jouer à chaque tour de jeu qu'un seul de leur animal et ne faire qu'une des 5 actions suivantes :\n- Entrer un de ses animaux sur le plateau\n- Se déplacer sur une case libre\n- Changer l'orientation de son animal sans changer de case\n- Sortir un de ses animaux disposés sur une case extérieure\n- Se déplacer en poussant d'autres pièces disposées sur le plateau\n\nEntrer un de ses animaux sur le plateau :\nVous devez entrer un de vos animaux par l'une des cases extérieures.\nDeux cas peuvent se présenƒter :\n- la case est libre et dans ce cas vous pouvez placer votre animal en l'orientant dans la direction de votre choix\n- la case est occupée et vous pouvez sous certaines conditions rentrer en effectuant un poussée (voir \"se déplacer en poussant\").\n\nSe déplacer sur une case libre :\n\nVous ne pouvez vous déplacer que d'une seule case et de façon orthogonale (déplacement en diagonale interdit).\nL'orientation de votre animal n'importe pas sur la direction de votre déplacement.\nTout en vous déplaçant, vous pouvez à votre guise changer l'orientation de votre animal\n\nChanger l'orientation de son animal sans chanter de case :\nVous pouvez changer l'orientation de votre animal sur sa case, ce coup compte comme un tour de jeu.\n\nSortir un de ses animaux disposé sur une case extérieure :\nVous pouvez sortir du plateau et à tout moment un de vos animaux disposé sur une case extérieure, ce coup compte comme un tour de jeu.\nL'animal sorti pourra être réutilisé et revenir sur le plateau à tout moment.\n\nSe déplacer en poussant d'autres pièces disposées sur le plateau :\nLorsque la case ou vous voulez vous rendre est occupée par une pièce (éléphant, rhinocéros ou rochers), vous pouvez sous certaines conditions effectuer une poussée :\n- Vous ne pouvez pousser que dans une seule direction : vers l'avant de votre animal.\n- Un animal peut pousser un rocher, deux animaux orientés dans la bonne direction peuvent pousser deux rochers, et trois animaux orientés dans la bonne direction peuvent pousser trois.\n- Un animal ne peut pousser un autre animal qui lui fait face (peu importe à qui appartient l'animal).\n  En effet, rhinos et éléphants ont la même force de poussée ; pour pouvoir pousser, il faut qu'il y ait donc une majorité d'animaux qui poussent dans la même direction.\nPrécision : un de vos animaux peut empêcher votre poussée, un animal adverse peut aider votre poussée.\n- Un animal peut pousser autant d'animaux que possible si ceux-ci ne sont pas orientés dans la direction opposée.\n- Vous pouvez pousser en entrant une pièce sur le plateau.\n- Pour résoudre des situations de poussée plus compliquées, il suffit de regarder les animaux qui se neutralisent et de voir si ceux qui restent sont en nombre suffisant pour pousser des rochers.\n- Lorsqu'un rocher est expulsé la partie est terminée mais attention le gagnant est le joueur qui est le plus proche du rocher et dans le même sens de poussée.\n- Un animal expulsé hors du plateau n'est pas éliminé ; il est récupéré et peut être joué à tout moment.\n- Pendant une poussée, aucun animal ne peut changer d'orientation.");
	//gtk_dialog_run(GTK_DIALOG(pDialog));
	//gtk_widget_destroy(pDialog);
	
}
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame) {
	GtkWidget *pDialog;
	
	pDialog = gtk_message_dialog_new(GTK_WINDOW(pGame->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "GTK-Siam\nMade on a \nCopyright © 2008 Fusion Studios\n\nCrédits :\nThibaut Diehl\nGabriel Féron\nBenoît Trocmé");
	gtk_dialog_run(GTK_DIALOG(pDialog));
	gtk_widget_destroy(pDialog);
	
}
