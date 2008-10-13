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
};

struct _NewGameWindow
{
	GtkWidget *pWindow;
	GtkWidget *pLabel[4];
	GtkWidget *pButton[2];
	GtkWidget *pRadioButton[7];
	GtkWidget *pEntry;
	GtkWidget *pVBox;
	GtkWidget *pHBox[5];
};

typedef struct _MainWindow MainWindow;
typedef struct _NewGameWindow NewGameWindow;

struct _App
{
	MainWindow *pGame;
	NewGameWindow *pNewGame;
};

typedef struct _App App;


/* PROTOTYPES */
void OnButtonNewGame (GtkWidget *pButtonNewGame, App *pApp);
void OnGameRules(GtkWidget *pMenuItem, MainWindow *pGame);
void OnAbout(GtkWidget *pMenuItem, MainWindow *pGame);