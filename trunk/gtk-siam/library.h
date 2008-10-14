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

/* STRUCTURES */

// Structure principale contenant toutes les variables d'interface
struct _MainWindow
{
	GtkWidget *pWindow;
	GtkWidget *pMenuBar;
	GtkWidget *pMenu;
	GtkWidget *pMenuItem;
	GtkWidget *pTable;
	GtkWidget *pLabel;
	GtkWidget *pStatusBar;
	GtkWidget *pVBox;
	GtkWidget *pToolbar;
};
typedef struct _MainWindow MainWindow;


struct _InGame
{
	GtkWidget *pHBoxMain;
	GtkWidget *pPixBackground; //le fond principal du plateau
};
typedef struct _InGame InGame;


struct _GameButton
{
	GtkWidget *pLabel;
	GtkWidget *pPixButton;
	gint posx;
	gint posy;
	gint onBoard; // 1 = on the board, 0 = off the board
	gint resistance;
	gchar direction; //up down right left	
};
typedef struct _GameButton GameButton;


/* PROTOTYPES */
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);
gboolean OnNewGame(GtkWidget *pMenUItem, MainWindow *pGame);
void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnQuitBtn(GtkWidget* widget, gpointer data);