/*
 *  newgame.c
 *  GTK-Siam
 *
 *  Created by Gabriel Féron on 13/10/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "library.h"

void OnButtonNewGame (GtkWidget *pButtonNewGame, App *pApp) {
	gtk_widget_hide_all(GTK_WIDGET(pApp->pNewGame->pWindow));
	gtk_widget_show_all(GTK_WIDGET(pApp->pGame->pWindow));
}
