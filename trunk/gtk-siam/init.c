/*
 *  init.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 14/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "library.h"

void CreateGameWindow(MainWindow *pGame){

	int i;
	// Création de la fenêtre
	pGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pWindow), "GTK Siam - Plateau");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pWindow), 800, 600);
	//gtk_window_set_resizable(GTK_WINDOW(pGame->pWindow), FALSE);
	g_signal_connect(pGame->pWindow, "destroy", G_CALLBACK (OnQuitBtn), NULL);

	// Labels
	pGame->pLabel = gtk_label_new("Nom du joueur : non renseigné");
	pGame->pTimerLabel = gtk_label_new("Chronomètre : désactivé");

	// Table de jeu
	for (i=0; i<25; i++){
	pGame->pBoardButton[i]=gtk_button_new_with_label("bouton vide");
	}

	pGame->pTable = gtk_table_new(5, 5, TRUE);
/*
	for (i=0; i<5; i++){
        for (j=0; j<5; j++){
        gtk_table_attach(GTK_TABLE(pGame->pTable), pGame->pBoardButton[c++],j, j+1, i, i+1, GTK_EXPAND  | GTK_FILL , GTK_EXPAND, 0, 0);
        }
	}
*/

	// Barre d'outils
	pGame->pToolbar = gtk_toolbar_new();
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_NEW, "Nouveau", NULL, G_CALLBACK(OnNewGame), pGame, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"Ouvrir", NULL, G_CALLBACK(OnButtonOpenGame), NULL,-1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_SAVE, "Enregistrer", NULL, G_CALLBACK(OnButtonSaveGame), NULL, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_QUIT, "Quitter", NULL, G_CALLBACK(OnQuitBtn), NULL, -1);

	/* Insertion d'un espace */
	gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
	
	gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pLabel, "Nom du joueur", "Nom du joueur", -1);
	gtk_toolbar_append_space(GTK_TOOLBAR(pGame->pToolbar));
	gtk_toolbar_insert_widget(GTK_TOOLBAR(pGame->pToolbar), pGame->pTimerLabel, "Chronomètre", "Chronomètre", -1);
	
	/* Modification de la taille des icones */
	gtk_toolbar_set_icon_size(GTK_TOOLBAR(pGame->pToolbar), GTK_ICON_SIZE_BUTTON);
	/* Affichage uniquement des icones */
	gtk_toolbar_set_style(GTK_TOOLBAR(pGame->pToolbar), GTK_TOOLBAR_ICONS);


	// Menu
	/**** Creation du menu ****/

    /* ETAPE 1 */
    pGame->pMenuBar = gtk_menu_bar_new();
    /** premier sous-menu **/
    /* ETAPE 2 */
    pGame->pMenu = gtk_menu_new();
    /* ETAPE 3 */
    pGame->pMenuItem = gtk_menu_item_new_with_label("Nouvelle partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnNewGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Charger une partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonOpenGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Enregistrer la partie");
	g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonSaveGame), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnQuitBtn), (GtkWidget *) pGame->pWindow);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    /* ETAPE 4 */
    pGame->pMenuItem = gtk_menu_item_new_with_label("Partie");
    /* ETApGame->pE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);
    /* ETApGame->pE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);

	/** Second sous-menu **/
    /* ETApGame->pE 2 */
    pGame->pMenu = gtk_menu_new();
    /* ETApGame->pE 3 */
	pGame->pMenuItem = gtk_menu_item_new_with_label("Passer son tour");
    //g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnGameRules), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    pGame->pMenuItem = gtk_menu_item_new_with_label("Déclarer forfait");
    //g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnAbout), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    /* ETApGame->pE 4 */
    pGame->pMenuItem = gtk_menu_item_new_with_label("Action");
    /* ETApGame->pE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);
    /* ETApGame->pE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);


    /** Dernier sous-menu **/
    /* ETApGame->pE 2 */
    pGame->pMenu = gtk_menu_new();
    /* ETApGame->pE 3 */
	pGame->pMenuItem = gtk_menu_item_new_with_label("Règles du jeu");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnGameRules), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    pGame->pMenuItem = gtk_menu_item_new_with_label("A propos de...");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnAbout), (MainWindow*) pGame);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    /* ETApGame->pE 4 */
    pGame->pMenuItem = gtk_menu_item_new_with_label("?");
    /* ETApGame->pE 5 */
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(pGame->pMenuItem), pGame->pMenu);
    /* ETApGame->pE 6 */
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenuBar), pGame->pMenuItem);

	
	// Image

	for(i = 0; i < 25; i++) 
		pGame->pEventBoxes[i] = gtk_event_box_new();
	pGame->pBoard_White = gtk_image_new_from_file("/white.png");
	pGame->pBoard_Black = gtk_image_new_from_file("/black.png");
	pGame->pButton = gtk_button_new();
	GtkBorder* border;
	border = (GtkBorder *) malloc(sizeof(GtkBorder));
	border->left = 0;
	border->top = 0;
	border->right = 0;
	border->bottom = 0;
	//gtk_button_set_image(GTK_BUTTON(pGame->pButton), pGame->pBoard_Black);
	GdkColor color;
	gdk_color_parse ("black", &color);
	gtk_widget_modify_fg (pGame->pEventBoxes[0], GTK_STATE_NORMAL, &color);
	gtk_container_add(GTK_CONTAINER(pGame->pEventBoxes[0]), pGame->pButton);
	gtk_container_add(GTK_CONTAINER(pGame->pButton), pGame->pLabel);
	gtk_widget_set_name (pGame->pEventBoxes[0], "myapp-special-widget");

	gtk_table_attach(GTK_TABLE(pGame->pTable), pGame->pEventBoxes[0], 0, 1, 0, 1, GTK_FILL, GTK_FILL, 0,0);
	// g_object_set_data(G_OBJECT(pGame->pTable);
	// gtk_widget_modify_style(GTK_WIDGET(pGame->pButton), border);
	//gtk_button_set_relief(GTK_BUTTON(pGame->pButton), GTK_RELIEF_NONE);
	//gtk_button_set_focus_on_click(GTK_BUTTON(pGame->pButton), FALSE);
	

	// VBox
	pGame->pVBox = gtk_vbox_new(FALSE, 0);

	// Barre d'état
	pGame->pStatusBar = gtk_statusbar_new();
	/* PLUS TARD */

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
