/*
 *  library.h
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright Fusion Studios 2008. All rights reserved.
 *
 */

#include <stdlib.h>
#include <gtk/gtk.h>
#include <string.h>

/* STRUCTURES */

// Structure principale contenant toutes les variables d'interface
struct _MainWindow
{
	/* Fenêtre principale */
	GtkWidget *pWindow;
	
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;

	GtkWidget *pToolbar;

	GtkWidget *pTable;
	GtkWidget *pBoardButton[25];

	GtkWidget *pLabel[2];
	
	GtkWidget *pStatusBar;

	GtkWidget *pVBox;
	
	
	/* Fenêtre "Nouvelle partie" */
	GtkWidget *pNewGameWindow;
	
	GtkWidget *pNewGameLabel[5];

	GtkWidget *pNewGameButton[2];

	GtkWidget *pComboBoxLevel;
	GtkWidget *pComboBoxTimer;
	GtkWidget *pComboBoxCPU;
	GtkWidget *pComboBoxAnimal;
	
	GtkWidget *pNewGameEntry;

	GtkWidget *pNewGameVBox;

	GtkWidget *pNewGameHBox[6];
	
	GtkWidget *pNewGameHSeparator;
	
	/* Variables générales */
	gint level; // Niveau du jeu
	gboolean timer; // Timer activé ou non
	gboolean vs_cpu; // J. vs. J. (= FALSE) ou J. vs. CPU (= TRUE)
	const gchar* player_name; // Nom du joueur
	gint chrono; // Valeur du chronomètre
	gboolean pion; // TRUE pour Elephant (blancs donc la partie commence par eux) ou FALSE pour les hippos

};
typedef struct _MainWindow MainWindow;


/* PROTOTYPES */

// menu.c
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonNewGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnQuitBtn(GtkWidget* widget, MainWindow *pGame);

// newgame.c
void InitGame(GtkWidget *pButton, MainWindow *pGame);

// time.c
gboolean timeout(MainWindow *pGame);