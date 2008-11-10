/*
 *  library.h
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright Fusion Studios 2008. All rights reserved.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <cairo.h>
#include <string.h>
#include <time.h>

/* CONSTANTES */
// Rappel : seulement en cas de besoin
#ifdef __APPLE__
#endif

#ifdef WIN32
#endif

#define NUMBER_CENTER (number >= 25 && (number2 == 6 || number2 == 7 || number2 == 8 || number2 == 11 || number2 == 12 || number2 == 13 || number2 == 16 || number2 == 17 || number2 == 18))

/* STRUCTURES */

// Structure utilisée pour chaque case du jeu
struct _Button {

	GtkWidget *button; // Pointeur vers le bouton GTK+
	GtkWidget *image; // Pointeur vers l'image du pion
	gint x; // Coordonnées en abscisse
	gint y; // Coordonnées en ordonnée
	gint force; // Force
	gfloat r_left; // Résistance
	gfloat r_right;
	gfloat r_top;
	gfloat r_bottom;
	gchar piece; // Pion
	gchar direction; // Direction (regard de l'animal)

};
typedef struct _Button Button;

// Structure principale
struct _MainWindow {
	
	/* Boutons */
	Button *pBoardSquare[35];
	Button *pTempButton;
	
	/* Fenêtre principale */
	GtkWidget *pWindow;
	GtkWidget *pStartImage;
	GtkWidget *pToolbar;
	GtkWidget *pPlayerLabel[2];
	GtkWidget *pStatusBar;
	GtkWidget *pLabel[6];
	GtkWidget *pHBox;
	GtkWidget *pVBox[2];
	GtkWidget *pTable;
	
	/* Fenêtre "Nouvelle partie" */
	GtkWidget *pNewGameWindow;
	
	GtkWidget *pComboBoxTimer;
	GtkWidget *pComboBoxCPU;
	GtkWidget *pComboBoxAnimal;
	GtkWidget *pComboBoxToggle;
	GtkWidget *pNewGameEntry[2];
	
	/* Fenêtre "Victoire" */
	GtkWidget *pVictoryWindow;

	/* Variables générales */
	gint level; // Niveau du jeu
	gboolean timer; // Timer activé ou non
	gint mode; // 0 = Contre l'ordinateur - 1 = Contre un autre joueur
	gboolean toggle_color; // Surlignage activé ou non
	gboolean first_init; // Permet de savoir si c'est le jeu a déjà été chargé
	const gchar* player_name[2]; // Noms des joueurs
	
	gint chrono; // Valeur du chronomètre
	gint round; // Pour savoir dans quel étape on est (origine ou cible)
	gint turn; // Pour savoir qui doit joueur
	gint number; // Permet la copie temporaire de la case d'origine - sert au menu de rotation
	
#ifndef WIN32
	// Couleurs des widgets
	GdkColor black;
	GdkColor white;
	GdkColor brown;
	GdkColor grey;
#endif

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
void OnButtonBottom(GtkWidget *pButton, MainWindow *pGame) ;
void OnButtonTop(GtkWidget *pButton, MainWindow *pGame) ;
void OnButtonRight(GtkWidget *pButton, MainWindow *pGame) ;
void OnButtonLeft(GtkWidget *pButton, MainWindow *pGame) ;


