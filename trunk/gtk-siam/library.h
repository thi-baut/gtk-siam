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
	GtkWidget *pWindow;
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pTable;
	GtkWidget *pBoardButton[25];
	GtkWidget *pLabel;
	GtkWidget *pLabel2;
	GtkWidget *pStatusBar;
	GtkWidget *pVBox;
	GtkWidget *pToolbar;
	GtkWidget *pImage;
	GtkWidget *pButton;
	GtkWidget *pEventBoxes[25];
	GtkWidget *pBoard_Black;
	GtkWidget *pBoard_White;
	GtkWidget *pTimerLabel;
	gint chrono;
	
	// New Game Window
	GtkWidget *pNewGameWindow;
	GtkWidget *pNewGameLabel[4];
	GtkWidget *pNewGameButton[2];
	GtkWidget *pComboBoxLevel;
	GtkWidget *pComboBoxTimer;
	GtkWidget *pComboBoxCPU;
	GtkWidget *pNewGameEntry;
	GtkWidget *pNewGameVBox;
	GtkWidget *pNewGameHBox[5];
	
	// Game config
	gint level;
	gboolean timer;
	gboolean vs_cpu;
	const gchar* player_name;	

};
typedef struct _MainWindow MainWindow;


/* PROTOTYPES */
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);
gboolean OnNewGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnQuitBtn(GtkWidget* widget, gpointer data);
