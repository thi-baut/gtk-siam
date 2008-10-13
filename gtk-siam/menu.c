/*
 *  menu.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "library.h"

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
