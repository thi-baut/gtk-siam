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
	int c = -1;
	gchar *temp;
	pGame->turn = 1;
	pGame->first_init = TRUE;
	temp = (gchar *) malloc(3*sizeof(gchar));
	pGame->pTempButton = (Button *) malloc(sizeof(Button));
	pGame->toggle_color = TRUE;
	pGame->lock_turn = -1;
	
	// Allocation de la mémoire pour les boutons
	for(i=0 ; i < 56; i++) {
		pGame->pBoardButton[i] = (Button *) malloc(sizeof(Button));
	}
	
	// On initialise le chrono à 0
	pGame->chrono = -1;
	
	// On intialise l'entier qui servira de round;
	pGame->round = 0;
	
	// Création de la fenêtre
	pGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pWindow), "GTK Siam - Plateau");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pWindow), 1000, 80E);
	
	g_signal_connect(pGame->pWindow, "destroy", G_CALLBACK (OnQuitBtn), pGame);

	// Labels
	pGame->pLabel[0] = gtk_label_new("Nom du jo1 : ");
	pGame->pLabel[4] = gtk_label_new("Nom du joueur 2 : igné");
	pGame->pLabel[1] = gtk_label_new("Chronomètre : désactivé");
	pGame->pLabel[2] = gtk_label_new("Mode : non renseign�	pGame->pLabel[3] = gtk_label_new("Tour de jeu : pas de partie en cours");
	pGame->pLabel[5] = gtk_label_new("Laisser la main : ");
	pGame->pPlayerLabel[0] = gtk_label_new("non renseigné");
	pGame->pPlayerLabel[1] = gtk_label_new("non renseigné");

	// Table de jeu
	for (i=0; i<35; i++){
	pGame->pBoardButton[i]->button = utton=gtk_button_new();
	}

	pGame->pTable = gtk_table_new(5, 5, T
#ifndef WIN32_parse("black", &pGame->black);
	gdk_color_parse("white", &pGame->white);
	gdk_color_parse("#392B20", &pGame->brown);
	gdk_color_parse("#2E2E2E", &pD0D0D0", &pGame->black_clicked);
	gdk_color_parse("#D0D0D0", &pGame->white_clicked);
	gdk_color_parse("#D0D0D0", &pGame->brown	
	// Créa#endif
	// Loading de l'image de welcome
	pGame->pStartImage = gtk_image_new_from_file("/splashscreen.png");
	
s sLoading de l'image de victoire
	pGame->pWinImage = gtk_image_new_from_file("/win.png");
	
s separator
	for(i=0;i<2;i++){
		pGame->pSeparator[i] = gtk_vseparator_new();
	}

	for( i= 0; i< 	
	// Numéro des boutons dans le GObject : pas de boucle, comme ça les chaînes sont allouées automatiquement :pdata(G_OBJECT(pGame->pBoardButton[0]->button), "number", "0");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[1]->button), "number", "1");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[2]->button), "number", "2");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[3]->button), "number", "3");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[4]->button), "number", "4");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[5]->button), "number", "5");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[6]->button), "number", "6");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[7]->button), "number", "7");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[8]->button), "number", "8");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[9]->button), "number", "9");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[10]->button), "number", "10");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[11]->button), "number", "11");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[12]->button), "number", "12");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[13]->button), "number", "13");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[14]->button), "number", "14");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[15]->button), "number", "15");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[16]->button), "number", "16");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[17]->button), "number", "17");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[18]->button), "number", "18");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[19]->button), "number", "19");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[20]->button), "number", "20");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[21]->button), "number", "21");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[22]->button), "number", "22");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[23]->button), "number", "23");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[24]->button), "number", "24");
	
	g_object_set	_data(G_OBJECT(pGame->pBoardButton[25]->button), "number", "25");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[26]->button), "number", "26");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[27]->button), "number", "27");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[28]->button), "number", "28");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[29]->button), "number", "29");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[30]->button), "number", "30");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[31]->button), "number", "31");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[32]->button), "number", "32");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[33]->button), "number", "33");
	g_object_set_data(G_OBJECT(pGame->pBoardButton[34]->button), "number", "34");
	
	// Couleurs	i<5; i++)
		for (j=0; j<5; j++) {
			c++;
			// On enregistre les coordonnées
			pGame->pBoardButton[c]->x = j;
			pGame->pBoardButton[c]->y = i;
			gtk_table_attach(GTK_TABLE(pGame->pTable), pGame->pBoardButton[c]->button,j, j+1, i, i+1, GTK_EXPAND  | GTK_FILL , GTK_FILL | GTK_EXPAND, 0, 0);
		}
	
	// Charge	
	// Chargement des pions vide du plateau
	for(i = 0; i < 35; i++) {
		if(pGame->first_init == FALSE)
			gtk_widget_destroy(pGame->pBoardButton[i]->image);
		pGame->pBoardButton[i]->piece = 'n';
		pGame->pBoardButton[i]->image = gtk_image_new_from_file("/empty.png");
		gtk_button_set_image(GTK_BUTTON(pGame->pBoardButton[i]->button), pGame->pBoardButton[i]->image);
	}e d'outils
	pGame->pToolbar = gtk_toolbar_new();
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_NEW, "Nouveau", NULL, G_CALLBACK(OnButtonNewGame), pGame, -1);
	gtk_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_OPEN,"Ouvrir", NULL, G_CALLBACK(OnButtonOpenGame), NULL,-1);
pGame_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_SAVE, "Enregistrer", NULL, G_CALLBACK(OnButtonSaveGame), NULL, -1);pGamek_toolbar_insert_stock(GTK_TOOLBAR(pGame->pToolbar), GTK_STOCK_QUIT, "Quitter", NULL, G_CALLBACK(OnQuitBtn), pGame, -1);

	/* Insertion d'un espace */
	gtk_toolbification de la taille des icones */
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
 ->pBoardButtoname);
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem pGame->pMenuItem = gtk_menu_item_new_with_label("Quitter");
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
    // gg_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(OnButtonWithDrawal), (MainWindow*) pGame);   gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
    
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
	
	//Vboxes 1 t 2
	
	pGame->pVBox1 = gtk_vbox_new(FALSE, 0);
	pGame->pVBox2 = gtk_vbox_new(FALSE, 0);
	
	// Hbox qui contient la totalité desboxes
	
	pGame->pHBox = gtk_hbox_new(FALSE, 0);

	// Barre d'état
	pGame->pStatusBar = gtk_statusbar_new();
	gtk_statusbar_push(GTK_STATUSBAR(pGame->pStatusBar), 1, "Bienvenue dans GTK-Siam, cliquez-sur \"Nouvelle partie\" pour commencer !");

	/* Ajouter les éléments aux fenêtres */

	// Fenêtre pGame
	
// VBox
	
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pMenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pToolbar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pHBox, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pStatusBar, FALSE, TRUE, 0);
	
	//5 boutons dans VBox1 et 5 boutons dans VBox 2 (de part et d'autre dela table)
	
	gtk_box_pack_start(GTK_BOX(pGame->pVBox1), pGame->pBoardButton[25]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox1), pGame->pBoardButton[26]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox1), pGame->pBoardButton[27]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox1), pGame->pBoardButton[28]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox1), pGame->pBoardButton[29]->button, TRUE, TRUE, 0);
	
	gtk_box_pack_start(GTK_BOX(pGame->pVBox2), pGame->pBoardButton[30]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox2), pGame->pBoardButton[31]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox2), pGame->pBoardButton[32]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox2), pGame->pBoardButton[33]->button, TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox2), pGame->pBoardButton[34]->button, TRUE	// HBox
	// On y colle une image
	gtk_box_pack_start(GTK_BOX(pGame->pHBox), pGame->pStartImage, TRUE, TRUE, 0);LSE, FALSE, 0);
	

	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pWindow), pG