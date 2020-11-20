//
// Created by Unknow on 16/02/2020.
//

#ifndef CODECC_GTKFUNCTIONS_H
#define CODECC_GTKFUNCTIONS_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"
#include "cli_menu.h"

static GtkBuilder *builder;

static int validXML = 0;
static int validDTD = 0;
static char *xmlPath = NULL;
static char *dtdPath = NULL;

typedef struct {
    GtkWidget *window;
    GtkButton *validateButton;
    GtkFileChooserButton *xmlFileChooserButton;
    GtkFileChooserButton *dtdFileChooserButton;
    GtkLabel *statusLabel;
    GtkTextBuffer *consoleTextBuffer;
    GtkTextView *consoleTextView;
} App_widgets;


static App_widgets *widgets;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

G_MODULE_EXPORT void on_dtdFileChooserButton_file_set();

G_MODULE_EXPORT void on_xmlFileChooserButton_file_set();

G_MODULE_EXPORT void on_validateButton_clicked();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void startGTK(int *argc, char ***argv, char *gladeFile);

void connectWidgets();

void onDestroy();

void updateStatus(const char *message);

void initTextBuffer();

void console_clear();

void console_write(const char *text);

void console_writeline(const char *text);

void update_button_sensitive();

#endif //CODECC_GTKFUNCTIONS_H
