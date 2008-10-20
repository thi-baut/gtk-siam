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

	int i,j;
	int c = 0;
	GdkColor black;
	GdkColor white;
	GdkColor black_clicked;
	GdkColor white_clicked;
	
	// Création de la fenêtre
	pGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pWindow), "GTK Siam - Plateau");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pWindow), 800, 800);
	//gtk_window_set_resizable(GTK_WINDOW(pGame->pWindow), FALSE);
	g_signal_connect(pGame->pWindow, "destroy", G_CALLBACK (OnQuitBtn), pGame);

	// Labels
	pGame->pLabel[0] = gtk_label_new("Nom du joueur : non renseigné");
	pGame->pLabel[1] = gtk_label_new("Chronomètre : désactivé");

	// Table de jeu
	for (i=0; i<25; i++){
	pGame->pBoardButton[i]=gtk_button_new();
	}

	pGame->pTable = gtk_table_new(5, 5, TRUE);
	
	GtkBorder* border;
	border = (GtkBorder *) malloc(sizeof(GtkBorder));
	border->left = 0;
	border->top = 0;
	border->right = 0;
	border->bottom = 0;

	gdk_color_parse("black", &black);
	gdk_color_parse("white", &white);
	gdk_color_parse("#2E2E2E", &black_clicked);
	gdk_color_parse("#E8E8E8", &white_clicked);

	//g_object_set_data(G_OBJECT(pGame->pTable);
	for( i= 0; i< 25; i++) {
		
		switch(i%2) {
			case 0:
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_NORMAL, &black);
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_PRELIGHT, &black);
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_ACTIVE, &black_clicked);
				break;
			case 1:
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_NORMAL, &white);
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_PRELIGHT, &white);
				gtk_widget_modify_bg (pGame->pBoardButton[i], GTK_STATE_ACTIVE, &white_clicked);
				break;
		}
		
		//gtk_button_set_relief(GTK_BUTTON(pGame->pBoardButton[i]), GTK_RELIEF_NONE);
		gtk_button_set_focus_on_click(GTK_BUTTON(pGame->pBoardButton[i]), FALSE);
	}
	for (i=0; i<5; i++){
        for (j=0; j<5; j++){
        gtk_table_attach(GTK_TABLE(pGame->pTable), pGame->pBoardButton[c++],j, j+1, i, i+1, GTK_EXPAND  | GTK_FILL , GTK_FILL | GTK_EXPAND, 0, 0);
        }
	}

	// Barre d'outils
	pGame->pToolbar = gtk_toolbar_new();
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_NEW, "Nouveau", NULL, G_CALLBACK(OnButtonNewGame), pGame, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"Ouvrir", NULL, G_CALLBACK(OnButtonOpenGame), NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_SAVE, "Enregistrer", NULL, G_CALLBACK(OnButtonSaveGame), NULL, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_QUIT, "Quitter", NULL, G_CALLBACK(OnQuitBtn), pGame, -1);

	/* Insertion d'un espace */
	gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
	
	gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[0], "Nom du joueur", "Nom du joueur", -1);
	gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
	gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel[1], "Chronomètre", "Chronomètre", -1);
	
	/* Modification de la taille des icones */
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(pGame->pToolbar), GTK_ICON_SIZE_BUTTON);
	/* Affichage uniquement des icones */
	gtk_toolbar_set_style(GTK_TOOLBAR(pGame->pToolbar), GTK_TOOLBAR_ICONS);

	
	/* Creation du menu */
    pGame->pMenuBar = gtk_menu_bar_new();
   
	// Premier sous-menu
    pGame->pMenu = gtk_menu_new();

    pGame->pMenuItem = gtk_menu_item_new_with_label("Nouvelle partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonNewGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Charger une partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonOpenGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Enregistrer la partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonSaveGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnQuitBtn), pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Partie");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);

	// Second sous-menu
    pGame->pMenu = gtk_menu_new();
	pGame->pMenuItem = gtk_menu_item_new_with_label("Passer son tour");
	// g_signal_connect à rajouter
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    pGame->pMenuItem = gtk_menu_item_new_with_label("Déclarer forfait");
    // g_signal_connect à rajouter
	
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    
	pGame->pMenuItem = gtk_menu_item_new_with_label("Action");
	
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);
	
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);


    // Dernier sous-menu
    pGame->pMenu = gtk_menu_new();

	pGame->pMenuItem = gtk_menu_item_new_with_label("Règles du jeu");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnGameRules), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    pGame->pMenuItem = gtk_menu_item_new_with_label("A propos de...");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnAbout), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("?");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);

	
	// VBox
	pGame->pVBox = gtk_vbox_new(FALSE, 0);

	// Barre d'état
	pGame->pStatusBar = gtk_statusbar_new();
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "Bienvenue dans GTK-Siam, cliquez-sur \"Nouvelle partie\" pour commencer !");

	/* Ajouter les éléments aux fenêtres */

	// Fenêtre pGame
	// VBox
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pMenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pToolbar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pTable, TRUE, TRUE, 0);
	gtk_box_pack_end(GTK_BOX(pGame->pVBox), pGame->pStatusBar, FALSE, TRUE, 0);

	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pWindow), pGame->pVBox);


}
