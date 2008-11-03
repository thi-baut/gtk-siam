/*
 *  menu.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 Fusion Studios. All rights reserved.
 *
 */

#include "library.h"

void OnButtonNewGame(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	/* Création de la nouvelle fenêtre */
	pGame->pNewGameWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pNewGameWindow), GTK_WIN_POS_MOUSE);
	gtk_window_set_title(GTK_WINDOW(pGame->pNewGameWindow), "GTKSiam - Nouvelle partie");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pNewGameWindow), 400, 200);
	gtk_window_set_resizable(GTK_WINDOW(pGame->pNewGameWindow), FALSE);

	// Labels
	pGame->pNewGameLabel[0] = gtk_label_new("Niveau :");
	pGame->pNewGameLabel[1] = gtk_label_new("Temps limité :");
	pGame->pNewGameLabel[2] = gtk_label_new("Partie :");
	pGame->pNewGameLabel[3] = gtk_label_new("Animal :");
	pGame->pNewGameLabel[4] = gtk_label_new("Nom du joueur :");
	
	// Zone de saisie
	pGame->pNewGameEntry = gtk_entry_new_with_max_length(30);
	
	// Listes déroulantes
	pGame->pComboBoxLevel = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxLevel), "Facile");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxLevel), "Moyen");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxLevel), "Difficile");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxLevel), 0);

	pGame->pComboBoxTimer = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxTimer), "Désactivé");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxTimer), "Activé");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxTimer), 0);
	   
	pGame->pComboBoxCPU = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxCPU), "Un joueur (Humain vs. CPU)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxCPU), "Deux joueurs (Humain vs. Humain");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxCPU), 1);
	
	pGame->pComboBoxAnimal = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxAnimal), "Hippopotame (gris)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxAnimal), "Éléphant (blanc)");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxAnimal), 0);
	
	// Boutons
	pGame->pNewGameButton[0] = gtk_button_new_with_label("Nouvelle partie");
	pGame->pNewGameButton[1] = gtk_button_new_with_label("Annuler");
	
	// VBox
	pGame->pNewGameVBox = gtk_vbox_new(TRUE, 0);
	
	// HBoxs
	pGame->pNewGameHBox[0] = gtk_hbox_new(FALSE, 10);
	pGame->pNewGameHBox[1] = gtk_hbox_new(FALSE, 10);
	pGame->pNewGameHBox[2] = gtk_hbox_new(FALSE, 10);
	pGame->pNewGameHBox[3] = gtk_hbox_new(FALSE, 10);
	pGame->pNewGameHBox[4] = gtk_hbox_new(FALSE, 10);
	pGame->pNewGameHBox[5] = gtk_hbox_new(FALSE, 10);
	
	// Séparateur horizontale
	pGame->pNewGameHSeparator = gtk_hseparator_new();
	
	
	/* Ajouter les éléments à la fenêtre */
	
	// HBoxs
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[0]), pGame->pNewGameLabel[0], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[0]), pGame->pComboBoxLevel, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[1]), pGame->pNewGameLabel[1], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[1]), pGame->pComboBoxTimer, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[2]), pGame->pNewGameLabel[2], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[2]), pGame->pComboBoxCPU, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[3]), pGame->pNewGameLabel[3], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pGame->pNewGameHBox[3]), pGame->pComboBoxAnimal, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[4]), pGame->pNewGameLabel[4], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pGame->pNewGameHBox[4]), pGame->pNewGameEntry, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameHBox[5]), pGame->pNewGameButton[0], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pGame->pNewGameHBox[5]), pGame->pNewGameButton[1], TRUE, TRUE, 10);
	
	// VBox
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[0], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[1], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[2], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[3], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[4], FALSE, FALSE, 0);
	gtk_box_pack_start(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHSeparator, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(pGame->pNewGameVBox), pGame->pNewGameHBox[5], FALSE, FALSE, 0);
	
	// Accrochage de la VBox dans la fenêtre
	gtk_container_add(GTK_CONTAINER(pGame->pNewGameWindow), pGame->pNewGameVBox);
	
	/* Connexion des signaux */
	g_signal_connect(G_OBJECT(pGame->pNewGameButton[0]), "clicked", G_CALLBACK(InitGame), pGame);
	g_signal_connect_swapped(G_OBJECT(pGame->pNewGameButton[1]), "clicked", G_CALLBACK(gtk_widget_destroy), pGame->pNewGameWindow);
	// Swapped signifie qu'on inverse les arguments envoyés : la fonction gtk_widget_destroy appellée en callback reçoit donc pGame->pNewGameWindow pour son seul argument.
	
	gtk_widget_show_all(pGame->pNewGameWindow);
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

void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame){ // FUCKED UP because of un bug qui fait chier (gdb error quand on exploite des variable de pGame)
	
	GtkWidget *pFileSelection;
	GtkWidget *pParent;
	gchar *sChemin;
	FILE* pSave;
	
	pParent = GTK_WIDGET(pGame);
	
	printf("%c",pGame->pBoardButton[0]->piece);
	
	/* Creation de la fenetre de selection */
	pFileSelection = gtk_file_chooser_dialog_new("Choisir un endroit où sauver la partie...", GTK_WINDOW(pParent), GTK_FILE_CHOOSER_ACTION_SAVE, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_OK, NULL);
    /* On limite les actions a cette fenetre */
    gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
	
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
		case GTK_RESPONSE_OK:
			/* Recuperation du chemin */
			sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
			g_free(sChemin);
			pSave = fopen(sChemin, "wb+");
		
			
			break;
			
			default:
			break;
    }
	
    gtk_widget_destroy(pFileSelection);
}

void OnButtonWithDrawal(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	/* Fenêtre popup forfait */
	
	GtkWidget *pWithDrawalWindow;
	GtkWidget *pWithDrawalButton[2];
	GtkWidget *pWithDrawalLabel;
	GtkWidget *pWithDrawalVBox;
	GtkWidget *pWithDrawalHBox;
	
	pWithDrawalWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWithDrawalWindow), 400, 200);
	gtk_window_set_title(GTK_WINDOW(pWithDrawalWindow), "Déclarer forfait ?");
	gtk_window_set_position(GTK_WINDOW(pWithDrawalWindow), GTK_WIN_POS_CENTER);
	g_signal_connect(G_OBJECT(pWithDrawalWindow),"destroy",G_CALLBACK(gtk_widget_hide_all),NULL);
	
	pWithDrawalVBox = gtk_vbox_new(TRUE, 10);
	pWithDrawalHBox = gtk_hbox_new(TRUE, 10);
	
	pWithDrawalLabel = gtk_label_new("Qu'est-ce que vous êtes ?");
	gtk_box_pack_start(GTK_BOX(pWithDrawalVBox), pWithDrawalLabel, TRUE, TRUE, 10);
	
	pWithDrawalButton[0] = gtk_button_new_with_label("Un loser...");
	gtk_box_pack_start(GTK_BOX(pWithDrawalHBox), pWithDrawalButton[0], TRUE, TRUE, 10);
	
	pWithDrawalButton[1] = gtk_button_new_with_label("Un gagnant !");
	gtk_box_pack_start(GTK_BOX(pWithDrawalHBox), pWithDrawalButton[1], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pWithDrawalVBox), pWithDrawalHBox, TRUE, TRUE, 10);
	
	gtk_container_add(GTK_CONTAINER(pWithDrawalWindow), pWithDrawalVBox);
	
	g_signal_connect(G_OBJECT(pWithDrawalButton[0]),"clicked",G_CALLBACK(gtk_main_quit),NULL);
	
	g_signal_connect_swapped(G_OBJECT(pWithDrawalButton[1]),"clicked",G_CALLBACK(gtk_widget_destroy), pWithDrawalWindow);

	gtk_widget_show_all(pWithDrawalWindow);
	
}

/* PROCÉDURE À MODIFIER POUR PLUS DE STYLE */
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	GtkWidget *pWindowAbout;
	GtkWidget *pScrollbar;
	GtkWidget *pLabel;
	GtkWidget *pImage[3];
	GtkWidget *pVBox;
	
	pImage[0] = gtk_image_new_from_file("/regle1.png");
	pImage[1] = gtk_image_new_from_file("/regle2.png");
	pImage[2] = gtk_image_new_from_file("/regle3.png");
	
	pWindowAbout = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(pWindowAbout), 580, 850);
	gtk_window_set_title(GTK_WINDOW(pWindowAbout), "Règles du jeu");
	gtk_window_set_position(GTK_WINDOW(pWindowAbout), GTK_WIN_POS_CENTER_ALWAYS);
	g_signal_connect(G_OBJECT(pWindowAbout),"destroy",G_CALLBACK(gtk_widget_hide_all),NULL);
	
	pScrollbar = gtk_scrolled_window_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(pWindowAbout), pScrollbar);
	
	pLabel = gtk_label_new("Règles du jeu :\n\nChaque joueur choisit son animal.\nLes joueurs joueront à tour de rôle.\nAu début du jeu les animaux sont disposés à l'extérieur du plateau et les blocs de rochers au centre du plateau.\nLes éléphants blancs, animaux sacrés dans le royaume de SIAM commenceront à jouer.\n\nLes joueurs ne pourront jouer à chaque tour de jeu qu'un seul de leur animal et ne faire qu'une des 5 actions suivantes :\n- Entrer un de ses animaux sur le plateau\n- Se déplacer sur une case libre\n- Changer l'orientation de son animal sans changer de case\n- Sortir un de ses animaux disposés sur une case extérieure\n- Se déplacer en poussant d'autres pièces disposées sur le plateau\n\nEntrer un de ses animaux sur le plateau :\nVous devez entrer un de vos animaux par l'une des cases extérieures.\nDeux cas peuvent se présenƒter :\n- la case est libre et dans ce cas vous pouvez placer votre animal en l'orientant dans la direction de votre choix\n- la case est occupée et vous pouvez sous certaines conditions rentrer en effectuant un poussée (voir \"se déplacer en poussant\").\n\nSe déplacer sur une case libre :\n\nVous ne pouvez vous déplacer que d'une seule case et de façon orthogonale (déplacement en diagonale interdit).\nL'orientation de votre animal n'importe pas sur la direction de votre déplacement.\nTout en vous déplaçant, vous pouvez à votre guise changer l'orientation de votre animal\n\nChanger l'orientation de son animal sans chanter de case :\nVous pouvez changer l'orientation de votre animal sur sa case, ce coup compte comme un tour de jeu.\n\nSortir un de ses animaux disposé sur une case extérieure :\nVous pouvez sortir du plateau et à tout moment un de vos animaux disposé sur une case extérieure, ce coup compte comme un tour de jeu.\nL'animal sorti pourra être réutilisé et revenir sur le plateau à tout moment.\n\nSe déplacer en poussant d'autres pièces disposées sur le plateau :\nLorsque la case ou vous voulez vous rendre est occupée par une pièce (éléphant, rhinocéros ou rochers), vous pouvez sous certaines conditions effectuer une poussée :\n- Vous ne pouvez pousser que dans une seule direction : vers l'avant de votre animal.\n- Un animal peut pousser un rocher, deux animaux orientés dans la bonne direction peuvent pousser deux rochers, et trois animaux orientés dans la bonne direction peuvent pousser trois.\n- Un animal ne peut pousser un autre animal qui lui fait face (peu importe à qui appartient l'animal).\n  En effet, rhinos et éléphants ont la même force de poussée ; pour pouvoir pousser, il faut qu'il y ait donc une majorité d'animaux qui poussent dans la même direction.\nPrécision : un de vos animaux peut empêcher votre poussée, un animal adverse peut aider votre poussée.\n- Un animal peut pousser autant d'animaux que possible si ceux-ci ne sont pas orientés dans la direction opposée.\n- Vous pouvez pousser en entrant une pièce sur le plateau.\n- Pour résoudre des situations de poussée plus compliquées, il suffit de regarder les animaux qui se neutralisent et de voir si ceux qui restent sont en nombre suffisant pour pousser des rochers.\n- Lorsqu'un rocher est expulsé la partie est terminée mais attention le gagnant est le joueur qui est le plus proche du rocher et dans le même sens de poussée.\n- Un animal expulsé hors du plateau n'est pas éliminé ; il est récupéré et peut être joué à tout moment.\n- Pendant une poussée, aucun animal ne peut changer d'orientation.");
	
	// VBox
	pVBox = gtk_vbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage[0], TRUE, TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pVBox), pImage[1], TRUE, TRUE, 0);
	gtk_box_pack_end(GTK_BOX(pVBox), pImage[2], TRUE, TRUE, 0);
	
	gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(pScrollbar), pVBox);
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

void OnQuitBtn(GtkWidget* widget, MainWindow *pGame){
	
    GtkWidget *pQuestion;
	
    /* Création de la boîte de dialogue de type OUI-NON */
	// GTK_DIALOG_DESTROY_WITH_PARENT veut dire que si l'application se ferme, cette fenêtre est détruitre aussi
	// GTK_MESSAGE_WARNING c'est le petit icône de point d'exclamation
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(pGame->pWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Voulez vous vraiment quitter le jeu ?");
	gtk_window_set_position(GTK_WINDOW(pQuestion), GTK_WIN_POS_MOUSE);
	
    /* Affichage et attente d'une réponse, ceci n'est pas une boucle infinie :) */
    switch(gtk_dialog_run(GTK_DIALOG(pQuestion)))
    {
        case GTK_RESPONSE_YES:
            // OUI : On détruit la fenêtre et on quitte l'application
            gtk_widget_destroy(pQuestion);
			gtk_main_quit();
            break;
        case GTK_RESPONSE_NO:
            // NON : On détruit la fenêtre et on ré-affiche le fenêtre principale
            gtk_widget_destroy(pQuestion);
			gtk_widget_show_all(pGame->pWindow);
            break;
		default:
			break;
    }
}
