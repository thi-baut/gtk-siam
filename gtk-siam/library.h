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
	GtkWidget *pBoardButton[25];
	GtkWidget *pLabel;
	GtkWidget *pStatusBar;
	GtkWidget *pVBox;
	GtkWidget *pToolbar;
};
typedef struct _MainWindow MainWindow;


/* PROTOTYPES */
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);
gboolean OnNewGame(GtkWidget *pMenUItem, MainWindow *pGame);
void OnButtonSaveGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnButtonOpenGame(GtkWidget *pMenuItem, MainWindow *pGame);
void OnQuitBtn(GtkWidget* widget, gpointer data);
