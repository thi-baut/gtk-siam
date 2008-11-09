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
#include <CoreFoundation/CoreFoundation.h>

/* STRUCTURES */

struct _Button{

GtkWidget *button; // Contient le bouton GTK+
GtkWidget *image; // Image du pion
gint x; // Coordonnées en x
gint y; // Coordonnées en y
gint force; // Force - poids
gfloat r_left; // r = Resistance
gfloat r_right;
gfloat r_top;
gfloat r_bottom;
gchar piece; // Pion
gchar direction; // Direction (regard de l'animal)

};

typedef struct _Button Button;

// Structure principale contenant toutes les variables d'interface
struct _MainWindow
{
	/* Fenêtre principale */
	GtkWidget *pWindow;

	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;

	GtkWidget *pToolbar;
	GtkWidget *pPlayerLabel[2];

	GtkWidget *pTable;
	Button *pBoardButton[35];
	Button *pTempButton;

	GtkWidget *pLabel[6];

	GtkWidget *pStatusBar;

	GtkWidget *pVBox, *pVBox1, *pVBox2;

	GtkWidget *pHBox;

	GtkWidget *pSeparator[2];
	
	GtkWidget *pStartImage;
	GtkWidget *pWinImage;


	/* Fenêtre "Nouvelle partie" */
	GtkWidget *pNewGameWindow;

	GtkWidget *pNewGameLabel[6];

	GtkWidget *pNewGameButton[2];

	GtkWidget *pComboBoxTimer;
	GtkWidget *pComboBoxCPU;
	GtkWidget *pComboBoxAnimal;
	GtkWidget *pComboBoxToggle;
	
	GtkWidget *pNewGameEntry[2];

	GtkWidget *pNewGameVBox;

	GtkWidget *pNewGameHBox[7];

	GtkWidget *pNewGameHSeparator;
	
	/* Fenêtre "Victoire" */
	
	GtkWidget *pWinTemp;
	GtkWidget *pTempBox;
	GtkWidget *pTempBox2;
	GtkWidget *pButtonNewGame;
	GtkWidget *pButtonExit;

	/* Variables générales */
	gint level; // Niveau du jeu
	gboolean timer; // Timer activé ou non
	gint mode; // J. vs. J. (= TRUE) ou J. vs. CPU (= FALSE)
	gboolean toggle_color;
	const gchar* player_name[2]; // Nom du joueur
	gint chrono; // Valeur du chronomètre
	gboolean pion; // TRUE pour Elephant (blancs donc la partie commence par eux) ou FALSE pour les hippos
	gint round;
	gint turn;
	gint lock_turn;
	gint x;
	gint y;
	GdkColor black;
	GdkColor white;
	GdkColor brown;
	GdkColor black_clicked;
	GdkColor white_clicked;
	GdkColor brown_clicked;
	
	gboolean first_init;
	gboolean first_rotate;

};
typedef struct _MainWindow MainWindow;

/* PROTOTYPES */

// menu.c
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonWithDrawal(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonNewGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnQuitBtn(GtkWidget* widget, MainWindow *pGame);

// newgame.c
void InitGame(GtkWidget *pButton, MainWindow *pGame);
void LoadBoard(MainWindow *pGame);

// time.c
gboolean timeout(MainWindow *pGame);

// init.c
void CreateGameWindow(MainWindow *pGame);

// game.c
void ActionInGame(GtkWidget *pButton, MainWindow *pGame);
void RefreshDisplay(MainWindow *pGame, gint number);
void OnWin(GtkWidget *pMenuItem, MainWindow *pGame);
void OnDestroyWinWindow (GtkWidget *pMenuItem, MainWindow *pGame);
void OnSkipTurn(GtkWidget *pButton, MainWindow* pGame);


