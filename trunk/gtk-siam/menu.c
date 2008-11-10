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
	
	// Widgets
	GtkWidget *pNewGameLabel[5];
	GtkWidget *pNewGameButton[2];
	
	GtkWidget *pNewGameVBox;
	GtkWidget *pNewGameHBox[6];
	GtkWidget *pNewGameHSeparator;
	
	// Fenêtre
	pGame->pNewGameWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(pGame->pNewGameWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(pGame->pNewGameWindow), "GTK Siam - Nouvelle partie");
	gtk_window_set_default_size(GTK_WINDOW(pGame->pNewGameWindow), 400, 200);
	gtk_window_set_resizable(GTK_WINDOW(pGame->pNewGameWindow), FALSE);
	
	// Labels
	pNewGameLabel[0] = gtk_label_new("Temps limité :");
	pNewGameLabel[1] = gtk_label_new("Partie :");
	pNewGameLabel[2] = gtk_label_new("Nom du joueur 1 :");
	pNewGameLabel[3] = gtk_label_new("Nom du joueur 2 :");
	pNewGameLabel[4] = gtk_label_new("Surlignage des boutons :");
	
	// Zones de saisie
	pGame->pNewGameEntry[0] = gtk_entry_new_with_max_length(30);
	gtk_entry_set_text(GTK_ENTRY(pGame->pNewGameEntry[0]), "Joueur_1");
	pGame->pNewGameEntry[1] = gtk_entry_new_with_max_length(30);
	gtk_entry_set_text(GTK_ENTRY(pGame->pNewGameEntry[1]), "Joueur_2");
	
	// Listes déroulantes
	pGame->pComboBoxTimer = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxTimer), "Désactivé");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxTimer), "Activé");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxTimer), 0);
	
	pGame->pComboBoxCPU = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxCPU), "Un joueur (Humain vs. CPU)");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxCPU), "Deux joueurs (Humain vs. Humain)");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxCPU), 1);
	
	pGame->pComboBoxToggle = gtk_combo_box_new_text();
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxToggle), "Désactivé");
	gtk_combo_box_append_text(GTK_COMBO_BOX(pGame->pComboBoxToggle), "Activé");
	gtk_combo_box_set_active(GTK_COMBO_BOX(pGame->pComboBoxToggle), 1);
	
	// Boutons
	pNewGameButton[0] = gtk_button_new_with_label("Nouvelle partie");
	pNewGameButton[1] = gtk_button_new_with_label("Annuler");
	
	// Séparateur horizontale
	pNewGameHSeparator = gtk_hseparator_new();
	
	// HBox
	pNewGameHBox[0] = gtk_hbox_new(FALSE, 10);
	pNewGameHBox[1] = gtk_hbox_new(FALSE, 10);
	pNewGameHBox[2] = gtk_hbox_new(FALSE, 10);
	pNewGameHBox[3] = gtk_hbox_new(FALSE, 10);
	pNewGameHBox[4] = gtk_hbox_new(FALSE, 10);
	pNewGameHBox[5] = gtk_hbox_new(FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[0]), pNewGameLabel[0], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[0]), pGame->pComboBoxTimer, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[1]), pNewGameLabel[1], FALSE, FALSE, 10);
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[1]), pGame->pComboBoxCPU, TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[2]), pNewGameLabel[2], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGameHBox[2]), pGame->pNewGameEntry[0], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[3]), pNewGameLabel[3], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGameHBox[3]), pGame->pNewGameEntry[1], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[4]), pNewGameButton[0], TRUE, TRUE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGameHBox[4]), pNewGameButton[1], TRUE, TRUE, 10);
	
	gtk_box_pack_start(GTK_BOX(pNewGameHBox[5]), pNewGameLabel[4], FALSE, FALSE, 10);
	gtk_box_pack_end(GTK_BOX(pNewGameHBox[5]), pGame->pComboBoxToggle, TRUE, TRUE, 10);
	
	// VBox
	pNewGameVBox = gtk_vbox_new(TRUE, 0);
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHBox[1], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHBox[0], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHBox[5], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHBox[2], FALSE, FALSE, 1);
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHBox[3], FALSE, FALSE, 1);
	
	gtk_box_pack_start(GTK_BOX(pNewGameVBox), pNewGameHSeparator, FALSE, FALSE, 0);
	gtk_box_pack_end(GTK_BOX(pNewGameVBox), pNewGameHBox[4], FALSE, FALSE, 0);
	
	// Accrochage de la VBox dans la fenêtre+
	gtk_container_set_border_width(GTK_CONTAINER(pGame->pNewGameWindow), 25);
	gtk_container_add(GTK_CONTAINER(pGame->pNewGameWindow), pNewGameVBox);
	
	// Connexion des signaux
	g_signal_connect(G_OBJECT(pNewGameButton[0]), "clicked", G_CALLBACK(InitGame), pGame);
	g_signal_connect_swapped(G_OBJECT(pNewGameButton[1]), "clicked", G_CALLBACK(gtk_widget_destroy), pGame->pNewGameWindow);
	// Swapped signifie qu'on inverse les arguments envoyés : la fonction gtk_widget_destroy appellée en callback reçoit donc pGame->pNewGameWindow pour son seul argument.
	
	gtk_widget_show_all(pGame->pNewGameWindow);
}

void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame){
	
	GtkWidget *pFileSelection;
	GtkWidget *pParent;
	gchar *sChemin;
	FILE* pSave;
	gchar info [500];
	gchar *info2;
	gint i;
	
	pParent = GTK_WIDGET(pGame);
	
	/* Creation de la fenetre de selection */
	pFileSelection = gtk_file_chooser_dialog_new("Ouvrir une partie existante...", GTK_WINDOW(pParent), GTK_FILE_CHOOSER_ACTION_OPEN, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_OK, NULL);
	/* On limite les actions a cette fenetre */
	gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
	
	/* Filtre de sélection de fichier */
	
	GtkFileFilter *filter = gtk_file_filter_new();
	gtk_file_filter_add_pattern(filter, "*.siam");
	gtk_file_chooser_set_filter (GTK_FILE_CHOOSER(pFileSelection), filter);
	
	/* Affichage fenetre */
	switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
	{
		case GTK_RESPONSE_OK:
			/* Recuperation du chemin */
			sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
			pSave = fopen(sChemin, "r");
			
			fscanf(pSave,"%s", info);
			
			info2 = strtok(info, ":");
			
			gtk_label_set_text(GTK_LABEL(pGame->pPlayerLabel[0]), info2);
			info2 = strtok(NULL, ":");
			gtk_label_set_text(GTK_LABEL(pGame->pPlayerLabel[1]), info2);
			info2 = strtok(NULL, ":");
			
			for(i=0;i<35;i++){
				
				pGame->pBoardSquare[i]->piece = info2[0];
				info2 = strtok(NULL, ":");
				pGame->pBoardSquare[i]->direction = info2[0];
				info2 = strtok(NULL, ":");
				pGame->pBoardSquare[i]->force = atoi(info2);
				info2 = strtok(NULL, ":");
				
				switch (pGame->pBoardSquare[i]->direction) {
						
					case 'r' :
						
						pGame->pBoardSquare[i]->r_left = 0;
						pGame->pBoardSquare[i]->r_right = 1;
						pGame->pBoardSquare[i]->r_top = 0;
						pGame->pBoardSquare[i]->r_bottom = 0;
						
						break;
						
					case 'l' :
						
						pGame->pBoardSquare[i]->r_left = 1;
						pGame->pBoardSquare[i]->r_right = 0;
						pGame->pBoardSquare[i]->r_top = 0;
						pGame->pBoardSquare[i]->r_bottom = 0;
						
						break;
						
					case 't' :
						
						pGame->pBoardSquare[i]->r_left = 0;
						pGame->pBoardSquare[i]->r_right = 0;
						pGame->pBoardSquare[i]->r_top = 1;
						pGame->pBoardSquare[i]->r_bottom = 0;
						
						break;
						
					case 'b' :
						
						pGame->pBoardSquare[i]->r_left = 0;
						pGame->pBoardSquare[i]->r_right = 0;
						pGame->pBoardSquare[i]->r_top = 0;
						pGame->pBoardSquare[i]->r_bottom = 1;
						
						break;
						
					case 'n' :
						
						if(pGame->pBoardSquare[i]->piece == 'm') {
							
							pGame->pBoardSquare[i]->r_left = 0.9;
							pGame->pBoardSquare[i]->r_right = 0.9;
							pGame->pBoardSquare[i]->r_top = 0.9;
							pGame->pBoardSquare[i]->r_bottom = 0.9;
							
						}
						
						else {
							
							pGame->pBoardSquare[i]->r_left = 0;
							pGame->pBoardSquare[i]->r_right = 0;
							pGame->pBoardSquare[i]->r_top = 0;
							pGame->pBoardSquare[i]->r_bottom = 0;
							
						}	
						
						break;
						
					default :
						
						break;
						
				}
				
				
				RefreshDisplay(pGame, i);
				
			}
			if(pSave != NULL) 
				fclose(pSave);
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
	FILE* pSave;
	gint i;
	gchar *buffer_force;	
	buffer_force = (gchar*)malloc(100*sizeof(gchar));
	
	pParent = GTK_WIDGET(pGame);
	
	printf("%c",pGame->pBoardSquare[0]->piece);
	
	/* Creation de la fenetre de selection */
	pFileSelection = gtk_file_chooser_dialog_new("Choisir un endroit où sauver la partie...", GTK_WINDOW(pParent), GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_SAVE, GTK_RESPONSE_OK, NULL);
	/* On limite les actions a cette fenetre */
	gtk_window_set_modal(GTK_WINDOW(pFileSelection), TRUE);
	
	/* Filtre de sélection de fichier */
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (pFileSelection), TRUE);
	
    /* Affichage fenetre */
    switch(gtk_dialog_run(GTK_DIALOG(pFileSelection)))
    {
		case GTK_RESPONSE_OK :
			
			// On récupère la date et l'heure pour donner le nom au fichier
			
			printf("%d", 2);
			time_t rawtime;
			struct tm * timeinfo;
			time ( &rawtime );
			timeinfo = localtime ( &rawtime );
			gchar temp[100];
			gchar temp2[300];
			
			/* Recuperation du chemin */
			sChemin = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(pFileSelection));
			strftime(temp, 100, "Sauvegarde du %d-%m-%Y à %H:%M.siam", timeinfo);
			
			sprintf(temp2, "%s/%s", sChemin, temp);
			printf("%s", temp2);
			pSave = fopen(temp2, "w+");

			fprintf(pSave, "%s:", gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[0])));
			fprintf(pSave, "%s:", gtk_label_get_text(GTK_LABEL(pGame->pPlayerLabel[1])));
			
			for(i=0;i<35;i++){
				
				fprintf(pSave,"%c:",pGame->pBoardSquare[i]->piece);
				fprintf(pSave,"%c:",pGame->pBoardSquare[i]->direction);
				
				sprintf(buffer_force,"%d",pGame->pBoardSquare[i]->force);
				fprintf(pSave,"%s:",buffer_force);
				
			}
			if(pSave != NULL) 
				fclose(pSave);
			
			break;
			
		default:
			break;
    }
	gtk_widget_destroy(pFileSelection);
}

void OnButtonWithDrawal(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	// Variables
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
}

void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame) {
	
	GtkWidget *pDialog;
	
	pDialog = gtk_message_dialog_new(GTK_WINDOW(pGame->pWindow), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "GTK-Siam\nMade on a Mac\nCopyright © 2008 Fusion Studios\n\nCrédits :\nThibaut Diehl\nGabriel Féron\nBenoît Trocmé");
	gtk_dialog_run(GTK_DIALOG(pDialog));
	gtk_widget_destroy(pDialog);	
}

void OnQuitBtn(GtkWidget* widget, MainWindow *pGame){
	
	// Variables
    GtkWidget *pQuestion;
	
    // Création de la boîte de dialogue de type OUI-NON
    pQuestion = gtk_message_dialog_new (GTK_WINDOW(pGame->pWindow), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Voulez vous vraiment quitter le jeu ?");
	gtk_window_set_position(GTK_WINDOW(pQuestion), GTK_WIN_POS_CENTER);
	
    // Affichage et attente d'une réponse
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
