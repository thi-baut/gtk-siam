/*
 *  init.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 14/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

void CreateGameWindow(MainWindow *pGame){

	// Allocation des variables (temporaires)
	int i;
	gchar *temp;
	
	// Tous les widgets temporaires : il n'est pas nécessaire qu'ils soient dans le structure pGame !!!
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pVBox;

	// Allocation dynamique de la structure "Bouton temporaire"
	temp = (gchar *) malloc(3*sizeof(gchar));
	pGame->pTempButton = (Button *) malloc(sizeof(Button));

	// Allocation de la mémoire pour les cases
	for(i=0 ; i < 35; i++)
		pGame->pBoardSquare[i] = (Button *) malloc(sizeof(Button));

	// On initialise la variable qui sera incrémentée chrono
	pGame->chrono = -1;
	
	// On prépare cette variable pour dire que le programme vient de démmarrer
	pGame->first_init = TRUE= 0;
	
	// Création de la fenêtre
	pGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pWindow), "GTK Siam - Plateau");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pWindo8, 1000, 80);
	
	g_signal_connect(pGame->pWindow, "destroy", G_CALLBACK (OnQuitBtn), pGame);

	// Labels
	pGame->pLabel[0] = gtk_label_new("Nom du jo1 : ");
	pGame->pLabel[4] = gtk_label_new("Nom du joueur 2 : igné");
	pGame->pLabel[1] = gtk_label_new("Chronomètre : désactivé");
	pGame->pLabel[2] = gtk_label_new("Mode : non renseign�	pGame->pLabel[3] = gtk_label_new("Tour de jeu : pas de partie en cours");
	pGame->pLabel[5] = gtk_label_new("Passer son tour : ");
	pGame->pPlayerLabel[0] = gtk_label_new("non renseigné");
	pGame->pPlayerLabel[1] = gtk_label_new("non renseigné");

	/* NE MARCHE PAS SUR WINDOWS, PROBLÈME DE LINKER */
#ifndef WIN32_parse("black", &pGame->black);
	gdk_color_parse("white", &pGame->white);
	gdk_color_parse("#392B20", &pGame->brown);
	gdk_color_parse("#2E2E2E", &pD0D0D0", &pGame->grey);
#endif
	
	// Loading de l'image de démarrage
	pGame->pStartImage = gtk_image_new_from_file("/splashscreen.png");

	// Barre d'outils
	pGame->pToolbar = gtk_toolbar_new(olbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"Ouvreau", NULL, G_CALLBACK(OnButtonNewGame), pGame, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"Ouvrir", NULL, G_CALLBACK(OnButtonOpenGame), NULL,-1);
pGame_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_SAVE, "Enregistrer", NULL, G_CALLBACK(OnButtonSaveGame), NULL, -1);pGamek_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_QUIT, "Quitter", NULL, G_CALLBACK(OnQuitBtn), pGame, -1);

	/* Insertio/ Taille des icones et style de la barre d'outils (icones seulement)
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(pGame->pToolbar), GTK_ICON_SIZE_BUTTON);
	gtk_toolbar_set_style(GTK_TOOLBAR(pGame->pToolbar), GTK_TOOLBAR_ICONS);

	// Menu
    pMenuBar = gtk_menu_bar_new();

	// Premier sous-menu
    pMenu = gtk_menu_new();

    pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW, NULL);
	g_signal_connect(G_OBJECT(uItem), "activate", G_CALLBACK(OnButtonNewGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGameMenu), pMenuItem);

    uItem = gtk_menuimage_menu_item_new_from_stock(GTK_STOCK_OPEN, NULLg_signal_connect(G_OBJECT(pGameItem), "activate", G_CALLBACK(OnButtonOpenGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGameMenu), pMenuItem);

    pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_SAVE, NULL);
	g_signal_connect(G_OBJECT(uItem), "activate", G_CALLBACK(OnButtonSaveGame), (MainWindow*) pGame);
 ame);
    gtk_menu_shell_append(GTK_MENU_SHELMenu), pMenuItem);

    pMenuItem = gtk_image_menu_item_new_from_stock(GTK_STOCK_CLOSE, NULL);
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnQuitBtn), pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_label("Partie");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

	// Second sous-menu
    pMenu = gtk_menu_new();
	
	pMenuItem = gtk_menu_item_new_with_label("Passer son tour");
	g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnSkipTurn), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);
	
    pMenuItem = gtk_menu_item_new_with_label("Déclarer forfait");
    g_signal_connect(G_OBJECT(pMenuItem), "activate", G_CALLBACK(OnButtonWithDrawal), (MainWindow*) pGame);     gtk_menu_shell_append(GTK_MENU_SHELL(pMenu), pMenuItem);

	pMenuItem = gtk_menu_item_new_with_label("Action");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItem);

    // Troisième sous-menu
    pMenu = gtk_menu_new();

	pMenuItem = gtk_menu_item_new_with_label("À propos de...");
    g_signal_connect(G_OBJECT(e->pMenuItem), "activate", G_CALLBACK(OnAbout), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELMenu), pMenuItem);
	
	e->pMenuItem = gtk_menu_item_new_with_label("Règles du jeu");
    g_signal_connect(G_OBJEC->pMenuItem), "activate", G_CALLBACK(OnGameRules), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELMenu), pMenuItem);

    pMenuItem = gtk_menu_item_new_with_label("?");
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pMenuItem), pMenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(pMenuBar), pMenuItemFALSE, 0);

	// Barre d'état
	pGame->pStatusBar = gtk_statusbar_new();
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "Bienvenue dans GTK-Siam, cliquez-sur \"Nouvelle partie\" pour commencer !");

	/* Ajouter les élà la fenêtre principale */

	// HBox
	pGame->pHBox = gtk_hbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pStartImage, TRUE, TRUE, 0);
	
	// VBox
	pVBox = gtk_vbox_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pMenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pGame->pToolbar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pGame->pHBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pGame->pStatusBar, FALSE, TRUE, 0);

	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pWindow), pVBox);
}

void InitGame(GtkWidget *pButton, MainWindow *pGame) {
	
	// Variables
	gchar temp[60];
	gchar temp2[60];
	gint i;
	
	// Widgets temporaires
	GtkWidget *pSeparator[2];
	GtkWidget *pVBox[2];
	
	// On enregistre les paramètres du chrono
	pGame->timer = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxTimer));
	
	// On enregistre le type de partie (J vs. CPU ou J vs. J)
	pGame->mode = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxCPU));
	
	// On enregistre le choix du joueur concernant les pions
	pGame->toggle_color = gtk_combo_box_get_active(GTK_COMBO_BOX(pGame->pComboBoxToggle));
	
	// C'est le joueur 1 qui commence
	pGame->turn = 1;
	
	// On intialise l'entier qui servira de round;
	pGame->round = 0;
	
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
	
	if(pGame->mode == 0)
		gtk_label_set_text(GTK_LABEL(pGame->pLabel[2]), "Mode : Humain vs. CPU");
	else
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

	if(pGame->first_init == TRUE) {
		
		// Séparateurs
		for(i=0;i<2;i++)
			pSeparator[i] = gtk_vseparator_new();
		
		// VBox
		pVBox[0] = gtk_vbox_new(FALSE, 0);
		pVBox[1] = gtk_vbox_new(FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[0]), pGame->pBoardSquare[25]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[0]), pGame->pBoardSquare[26]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[0]), pGame->pBoardSquare[27]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[0]), pGame->pBoardSquare[28]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[0]), pGame->pBoardSquare[29]->button, TRUE, TRUE, 0);
		
		gtk_box_pack_start(GTK_BOX(pVBox[1]), pGame->pBoardSquare[30]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[1]), pGame->pBoardSquare[31]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[1]), pGame->pBoardSquare[32]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[1]), pGame->pBoardSquare[33]->button, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pVBox[1]), pGame->pBoardSquare[34]->button, TRUE, TRUE, 0);
		
		// HBox
		gtk_container_remove(GTK_CONTAINER(pGame->pHBox), pGame->pStartImage);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pVBox[0], FALSE, FALSE, 0);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pSeparator[0], FALSE, FALSE, 15);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pTable, TRUE, TRUE, 0);
		gtk_box_pack_start(GTK_BOX(pGame->pHBox), pSeparator[1], FALSE, FALSE, 15);
		gtk_box_pack_end(GTK_BOX(pGame->pHBox), pVBox[1], FALSE, FALSE, 0);
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
	ar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"OuvrGOTO_LAST, "Passer le tour", NULL, G_CALLBACK(OnSkipTurn), pGame, -1);
		gtk_widget_show_all(pGame->pWindow);
		
		pGame->first_init = FALSE;
	}
	
	else {
		for(i = 0; i < 35; i++) {
			gtk_widget_destroy(pGame->pBoardSquare[i]->image);
			pGame->pBoardSquare[i]->piece = 'n';
			pGame->pBoardSquare[i]->piece = 'n';
			pGame->pBoardSquare[i]->r_left = 0;
			pGame->pBoardSquare[i]->r_right = 0;
			pGame->pBoardSquare[i]->r_top = 0;
			pGame->pBoardSquare[i]->r_bottom = 0;
			pGame->pBoardSquare[i]->force = 0;
			pGame->pBoardSquare[i]->direction = 'n';
			pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/empty.png");
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
		}
		// On s'occupe des montagnes
		for(i = 11; i <= 13; i++) {
			gtk_widget_destroy(pGame->pBoardSquare[i]->image);
			pGame->pBoardSquare[i]->piece = 'm';
			pGame->pBoardSquare[i]->r_left = 0.9;
			pGame->pBoardSquare[i]->r_right = 0.9;
			pGame->pBoardSquare[i]->r_top = 0.9;
			pGame->pBoardSquare[i]->r_bottom = 0.9;
			pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/mountain.png");
			pGame->pBoardSquare[i]->force = 0;
			pGame->pBoardSquare[i]->direction = 'n';
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
		}
			
		// On enregistre les paramètres des pions hors-jeu
		// Éléphants
		for(i = 25; i < 30; i++) {
			gtk_widget_destroy(pGame->pBoardSquare[i]->image);
			pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/elephant-r.png");
			pGame->pBoardSquare[i]->piece = 'e';
			pGame->pBoardSquare[i]->r_left = 0;
			pGame->pBoardSquare[i]->r_right = 1; // A 1 car le pion est en r au début
			pGame->pBoardSquare[i]->r_top = 0;
			pGame->pBoardSquare[i]->r_bottom = 0;
			pGame->pBoardSquare[i]->force = 1;
			pGame->pBoardSquare[i]->direction = 'r';
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
			
			pGame->pBoardSquare[i]->x = -1; // Signifie que le pion est hors plateau
			pGame->pBoardSquare[i]->y = i-25;
		}
			
		// Rhinocéros
		for(i = 30; i < 35; i++) {
			gtk_widget_destroy(pGame->pBoardSquare[i]->image);
			pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/rhino-l.png");
			pGame->pBoardSquare[i]->piece = 'r';
			pGame->pBoardSquare[i]->r_left = 1; // A 1 voir au dessus
			pGame->pBoardSquare[i]->r_right = 0;
			pGame->pBoardSquare[i]->r_top = 0;
			pGame->pBoardSquare[i]->r_bottom = 0;
			pGame->pBoardSquare[i]->force = 1;
			pGame->pBoardSquare[i]->direction = 'l';
			gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
	
			pGame->pBoardSquare[i]->y = i-30; // Signifie que le pion est hors plateau
			pGame->pBoardSquare[i]->x = 5;
		}
			
		RefreshDisplay(pGame, i);
		}
	
	
	// On modifie le message de la barre d'outils
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "La partie a débuté, c'est à vous de jouer !");
	
	gtk_widget_destroy(pGame->pNewGameWindow);
}

void LoadBoard(MainWindow *pGame) {
	
	// Variables
	gint i, j, c = -1;
		
	// Plateau (+ boutons)
	pGame->pTable = gtk_table_new(5, 5, TRUE);
		
	for (i=0; i<35; i++)
		pGame->pBoardSquare[i]->button = gtk_button_new();
		
	// On applique les callbacks pour tous les boutons
	if(pGame->first_init == TRUE) {
		for(i = 0; i < 35; i++) {
			g_signal_connect(G_OBJECT(pGame->pBoardSquare[i]->button), "clicked", G_CALLBACK(ActionInGame), pGame);
		}
		i<5; i++)
		for (j=0; j<5; j++) {
			c++;
			// On enregistre les coordonnées
			pGame->pBoardButton[c]->xSquare[c]->x = j;
			pGame->pBoardSquare[c]->y = i;
			gtk_table_attach(GTK_TABLE(pGame->pTable), pGame->pBoardSquarej, j+1, i, i+1, GTK_EXPAND  | GTK_FILL , GTK_FILL | GTK_EXPAND, 0, 0);
		}
	
	// Charge		
	// Numéro des boutons dans le GObject : pas de boucle, comme ça les chaînes sont allouées automatiquement :pdata(G_OBJECT(pGame->pBoardButton[0]->buttSquare[0]->button), "number", "0");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[1]->button), "number", "1");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[2]->button), "number", "2");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[3]->button), "number", "3");
	g_object_set_data(G_OBJECT(pGame->pBoardSquarenumber", "4");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[5]->buttSquare[5]->button), "number", "5");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[6]->button), "number", "6");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[7]->button), "number", "7");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[8]->button), "number", "8");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[9]->button), "number", "9");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[10]->button), "number", "10");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[11]->button), "number", "11");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[12]->button), "number", "12");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare"number", "13");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[14]->butSquare[14]->button), "number", "14");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[15]->button), "number", "15");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[16]->button), "number", "16");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare"number", "17");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[18]->butSquare[18]->button), "number", "18");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[19]->button), "number", "19");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[20]->button), "number", "20");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[21]->button), "number", "21");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[22]->button), "number", "22");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[23]->button), "number", "23");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[24]->button), "number", "24");
	
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[25]->button), "number", "25");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare "number", "26");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[27]->buSquare[27]->button), "number", "27");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[28]->button), "number", "28");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[29]->button), "number", "29");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare "number", "30");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[31]->buSquare[31]->button), "number", "31");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[32]->button), "number", "32");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[33]->button), "number", "33");
	g_object_set_data(G_OBJECT(pGame->pBoardSquare[34]->button), "number", "34");
	}	
	
	// Chargement des pions vide du plateau
	for(i = 0; i < 35; i++) {
		pGame->pBoardSquare[i]->piece = 'n';
		pGame->pBoardSquare[i]->piece = 'n';
		pGame->pBoardSquare[i]->r_left = 0;
		pGame->pBoardSquare[i]->r_right = 0;
		pGame->pBoardSquare[i]->r_top = 0;
		pGame->pBoardSquare[i]->r_bottom = 0;
		pGame->pBoardSquare[i]->force = 0;
		pGame->pBoardSquare[i]->direction = 'n';
		pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/empty.png");
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
	}
	
#ifndef WIN32
	for( i= 0; i< 25; i++) {
		// Couleurs des boutons
		switch(i%2) {
			case 0:
				gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_NORMAL, &pGame->black);
				if(pGame->toggle_color == TRUE) {
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->grey);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->grey);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_SELECTED, &pGame->grey);
				}
				else {
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->black);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->black);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_SELECTED, &pGame->black);
				}
				break;
			case 1:
				gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_NORMAL, &pGame->white);
				if(pGame->toggle_color == TRUE) {
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->grey);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->grey);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_SELECTED, &pGame->grey);
				}
				else {
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->white);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->white);
					gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_SELECTED, &pGame->white);
				}
				break;
		}
	}
	
	// Couleurs des boutons out
	for(i = 25; i < 35; i++) {
		gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_NORMAL, &pGame->brown);
		if(pGame->toggle_color == TRUE) {
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->grey);
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->grey);
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->grey);
		}
		else {
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_PRELIGHT, &pGame->brown);
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_ACTIVE, &pGame->brown);
			gtk_widget_modify_bg (pGame->pBoardSquare[i]->button, GTK_STATE_SELECTED, &pGame->brown);
		}
	}
#endif
	
	// On s'occupe des montagnes
	for(i = 11; i <= 13; i++) {
		gtk_widget_destroy(pGame->pBoardSquare[i]->image);
		pGame->pBoardSquare[i]->piece = 'm';
		pGame->pBoardSquare[i]->r_left = 0.9;
		pGame->pBoardSquare[i]->r_right = 0.9;
		pGame->pBoardSquare[i]->r_top = 0.9;
		pGame->pBoardSquare[i]->r_bottom = 0.9;
		pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/mountain.png");
		pGame->pBoardSquare[i]->force = 0;
		pGame->pBoardSquare[i]->direction = 'n';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
	}
	
	// On enregistre les paramètres des pions hors-jeu
	// Éléphants
	for(i = 25; i < 30; i++) {
		gtk_widget_destroy(pGame->pBoardSquare[i]->image);
		pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/elephant-r.png");
		pGame->pBoardSquare[i]->piece = 'e';
		pGame->pBoardSquare[i]->r_left = 0;
		pGame->pBoardSquare[i]->r_right = 1; // A 1 car le pion est en r au début
		pGame->pBoardSquare[i]->r_top = 0;
		pGame->pBoardSquare[i]->r_bottom = 0;
		pGame->pBoardSquare[i]->force = 1;
		pGame->pBoardSquare[i]->direction = 'r';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
		
		pGame->pBoardSquare[i]->x = -1; // Signifie que le pion est hors plateau
		pGame->pBoardSquare[i]->y = i-25;
		
	}
	
	// Rhinocéros
	for(i = 30; i < 35; i++) {
		gtk_widget_destroy(pGame->pBoardSquare[i]->image);
		pGame->pBoardSquare[i]->image = gtk_image_new_from_file("/rhino-l.png");
		pGame->pBoardSquare[i]->piece = 'r';
		pGame->pBoardSquare[i]->r_left = 1; // A 1 voir au dessus
		pGame->pBoardSquare[i]->r_right = 0;
		pGame->pBoardSquare[i]->r_top = 0;
		pGame->pBoardSquare[i]->r_bottom = 0;
		pGame->pBoardSquare[i]->force = 1;
		pGame->pBoardSquare[i]->direction = 'l';
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardSquare[i]->button), pGame->pBoardSquare[i]->image);
		
		pGame->pBoardSquare[i]->y = i-30; // Signifie que le pion est hors plateau
		pGame->pBoardSquare[i]->x = 5;
		
	}
}