/*
 *  main.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/2008.
 *  Copyright Fusion Studios 2008. All rights reserved.
 */

#include "library.h"
#include "menu.h"
#include "newgame.h"

int main (int argc, char **argv)
{
	
	// Initialisation de GTK+
	gtk_init(&argc, &argv);
	
	/* Structures */
	
	// Déclaration des structures
	MainWindow *pGame;
	NewGameWindow *pNewGame;
	App *pApp;
	
	// Allocation dynamique des structures
	pGame = (MainWindow *) malloc(sizeof(MainWindow));
	pNewGame = (NewGameWindow *) malloc(sizeof(NewGameWindow));
	pApp = (App *) malloc(sizeof(App));
	
	// Pointeurs (sert juste pour le bouton nouvelle partie)
	pApp->pGame = pGame;
	pApp->pNewGame = pNewGame;


	/* Création et paramétrage des fenêtres */
	
	// Fenêtre "Nouvelle partie"
	pNewGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	//gtk_window_set_position(GTK_WINDOW(pNewGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pNewGame->pWindow), "GTKSiam - Nouvelle partie");
	gtk_window_set_default_size(GTK_WINDOW(pNewGame->pWindow), 400, 200);
	g_signal_connect(pNewGame->pWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	
	// Fenêtre du jeu
	pGame->pWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pWindow), "GTKSiam - Partie");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pWindow), 800, 600);
	gtk_window_set_resizable(GTK_WINDOW(pGame->pWindow), FALSE);
	g_signal_connect(pGame->pWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	

	/* Paramétrages des GTKWidgets */
	
	// Fenêtre pNewGame
	// Labels
	pNewGame->pLabel[0] = gtk_label_new("Niveau :");
	pNewGame->pLabel[1] = gtk_label_new("Temps limité :");
	pNewGame->pLabel[2] = gtk_label_new("Partie :");
	pNewGame->pLabel[3] = gtk_label_new("Nom du joueur :");
	
	// Zone de saisie
	pNewGame->pEntry = gtk_entry_new_with_max_length(30);

	// Boutons
	pNewGame->pRadioButton[0] = gtk_radio_button_new_with_label(NULL, "Facile");
	pNewGame->pRadioButton[1] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pNewGame->pRadioButton[0]), "Moyen");
	pNewGame->pRadioButton[2] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pNewGame->pRadioButton[0]), "Difficile");
	pNewGame->pRadioButton[4] = gtk_radio_button_new_with_label(NULL, "désactivé");
	pNewGame->pRadioButton[3] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pNewGame->pRadioButton[4]), "activé");
	pNewGame->pRadioButton[5] = gtk_radio_button_new_with_label(NULL, "Deux joueurs");
	pNewGame->pRadioButton[6] = gtk_radio_button_new_with_label_from_widget(GTK_RADIO_BUTTON(pNewGame->pRadioButton[5]), "Contre l'ordinateur");
	pNewGame->pButton[0] = gtk_button_new_with_label("Nouvelle partie");
	pNewGame->pButton[1] = gtk_button_new_with_label("Quitter");
	
	// VBox
	pNewGame->pVBox = gtk_vbox_new(TRUE, 10);
	
	// HBox
	pNewGame->pHBox[0] = gtk_hbox_new(FALSE, 10);
	pNewGame->pHBox[1] = gtk_hbox_new(FALSE, 10);
	pNewGame->pHBox[2] = gtk_hbox_new(FALSE, 10);
	pNewGame->pHBox[3] = gtk_hbox_new(FALSE, 10);
	pNewGame->pHBox[4] = gtk_hbox_new(FALSE, 10);
	
	
	/* Ajouter les éléments aux fenêtres */
	
	// Fenêtre pNewGame
	
	// HBoxs
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[0]), pNewGame->pLabel[0], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[0]), pNewGame->pRadioButton[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[0]), pNewGame->pRadioButton[1], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGame->pHBox[0]), pNewGame->pRadioButton[2], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[1]), pNewGame->pLabel[1], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[1]), pNewGame->pRadioButton[3], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGame->pHBox[1]), pNewGame->pRadioButton[4], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[2]), pNewGame->pLabel[2], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[2]), pNewGame->pRadioButton[5], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGame->pHBox[2]), pNewGame->pRadioButton[6], FALSE, FALSE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[3]), pNewGame->pLabel[3], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGame->pHBox[3]), pNewGame->pEntry, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGame->pHBox[4]), pNewGame->pButton[0], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGame->pHBox[4]), pNewGame->pButton[1], TRUE, TRUE, 10);
	
	// VBox
	gtk_box_pack_start(GTK_BOX(pNewGame->pVBox), pNewGame->pHBox[0], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pNewGame->pVBox), pNewGame->pHBox[1], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pNewGame->pVBox), pNewGame->pHBox[2], TRUE, TRUE, 2);
	gtk_box_pack_start(GTK_BOX(pNewGame->pVBox), pNewGame->pHBox[3], TRUE, TRUE, 2);
	gtk_box_pack_end(GTK_BOX(pNewGame->pVBox), pNewGame->pHBox[4], TRUE, TRUE, 2);
	
	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pNewGame->pWindow), pNewGame->pVBox);
	
	/* Connexion des signaux */
	g_signal_connect(G_OBJECT(pNewGame->pButton[0]), "clicked", G_CALLBACK (OnButtonNewGame), pNewGame);
	g_signal_connect(G_OBJECT(pNewGame->pButton[1]), "clicked", G_CALLBACK (gtk_main_quit), pApp);
	
	
	// Fenêtre principale
	
	// Labels
	pGame->pLabel = gtk_label_new("Nom du joueur"); // à coder, doit prendre une chaîne qui a été récupérée auparavant dans la fenêtre NewGame
	
	// Table de jeu
	pGame->pTable = gtk_table_new(5, 5, TRUE);
	
	// Menu
	/**** Creation du menu ****/
	
    /* ETAPE 1 */
    pGame->pMenuBar = gtk_menu_bar_new();
    /** premier sous-menu **/
    /* ETAPE 2 */
    pGame->pMenu = gtk_menu_new();
    /* ETAPE 3 */
    pGame->pMenuItem = gtk_menu_item_new_with_label("Nouvelle partie");
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
	
    pGame->pMenuItem = gtk_menu_item_new_with_label("Charger une partie");
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);
	
    pGame->pMenuItem = gtk_menu_item_new_with_label("Enregistrer la partie");
    gtk_menu_shell_append(GTK_MENU_SHELL(pGame->pMenu), pGame->pMenuItem);

    pGame->pMenuItem = gtk_menu_item_new_with_label("Quitter");
    g_signal_connect(G_OBJECT(pGame->pMenuItem), "activate", G_CALLBACK(gtk_main_quit), (MainWindow*) pGame);
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
	
	
	// VBox
	pGame->pVBox = gtk_vbox_new(FALSE, 10);
	
	// Barre d'état
	pGame->pStatusBar = gtk_statusbar_new();
	/* PLUS TARD */
	
	/* Ajouter les éléments aux fenêtres */
	
	// Fenêtre pGame
	// VBox
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pMenuBar, FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pVBox), pGame->pTable, TRUE, TRUE, 0);
	gtk_box_pack_end(GTK_BOX(pGame->pVBox), pGame->pStatusBar, FALSE, TRUE, 0);
	
	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pWindow), pGame->pVBox);
	
	/* Connexion des signaux */
	//g_signal_connect(G_OBJECT(pNewGame->pButton[0]), "clicked", G_CALLBACK (OnButtonNewGame), pNewGame);
	//g_signal_connect(G_OBJECT(pNewGame->pButton[1]), "clicked", G_CALLBACK (gtk_main_quit), pApp);
	
	
	
	
	
	/* Affichage de la fenêtre */
	gtk_widget_show_all(pNewGame->pWindow);
	gtk_widget_show_all(pGame->pWindow);

	/* Boucle principale. */
	gtk_main();

	/* Destruction de la fenêtre */
	gtk_widget_destroy(pNewGame->pWindow);
	gtk_widget_destroy(pGame->pWindow);
	
	return 0;
}
