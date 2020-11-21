//
// Created by Unknow on 16/02/2020.
//

#include "gtkFunctions.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void on_dtdFileChooserButton_file_set() {
    char *path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets->dtdFileChooserButton));
    console_write("DTD Path : ");
    console_writeline(path);

    console_writeline("Checking file extension and if exists...");

    validDTD = check_file_exist_and_extension(path, "dtd");

    if (validDTD) {
        if (dtdPath) {
            free(dtdPath);
        }
        dtdPath = strdup(path);
        console_writeline("DTD file correct !");
        updateStatus("DTD file loaded", 1);
    } else {
        console_writeline("DTD file could not be loaded !");
        updateStatus("DTD file incorrect !", 2);
    }
    update_button_sensitive();
}

void on_xmlFileChooserButton_file_set() {
    char *path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(widgets->xmlFileChooserButton));
    console_write("XML Path : ");
    console_writeline(path);

    validXML = check_file_exist_and_extension(path, "xml");

    if (validXML) {
        if (xmlPath) {
            free(xmlPath);
        }
        xmlPath = strdup(path);
        console_writeline("XML file correct !");
        updateStatus("XML file loaded", 1);
    } else {
        console_writeline("XML file could not be loaded !");
        updateStatus("XML file incorrect !", 2);
    }
    update_button_sensitive();
}

void on_validateButton_clicked() {
    console_writeline("--------------------------------------------------------");
    console_writeline("Starting validation....\n");

    if (validate_dtd(xmlPath, dtdPath)) {
        console_writeline("Your XML document is conform to given DTD !");
        updateStatus("Your XML document is conform to given DTD !", 1);
    } else {
        console_writeline("ERROR - Your xml document could not be valided !");
        updateStatus("ERROR - Your xml document could not be valided !", 2);
    }
    console_writeline("--------------------------------------------------------");
}

void on_flushButton_clicked() {
    console_clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void startGTK(int *argc, char ***argv, char *gladeFile) {
    gtk_init(argc, argv);
    builder = gtk_builder_new_from_file(gladeFile);
    connectWidgets();

    gtk_widget_set_sensitive(GTK_WIDGET(widgets->validateButton), 0);
    initTextBuffer();


    g_signal_connect(widgets->window, "destroy", G_CALLBACK(onDestroy), NULL);
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);

    gtk_widget_show_all(widgets->window);


    gtk_main();

    g_slice_free(App_widgets, widgets);
}

void connectWidgets() {
    widgets = g_slice_new(App_widgets);

    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->validateButton = GTK_BUTTON(gtk_builder_get_object(builder, "validateButton"));
    widgets->xmlFileChooserButton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "xmlFileChooserButton"));
    widgets->dtdFileChooserButton = GTK_FILE_CHOOSER_BUTTON(gtk_builder_get_object(builder, "dtdFileChooserButton"));
    widgets->statusLabel = GTK_LABEL(gtk_builder_get_object(builder, "statusLabel"));
    widgets->consoleTextView = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "consoleTextView"));
    widgets->consoleTextBuffer = gtk_text_view_get_buffer(widgets->consoleTextView);
    widgets->scrollableWindow = GTK_SCROLLED_WINDOW(gtk_builder_get_object(builder, "scrollableWindow"));
}

void onDestroy() {
    gtk_main_quit();
}

void updateStatus(const char *status_message, int type) {
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context;
    switch (type) {
        case 1:
            //SUCCESS color
            gtk_css_provider_load_from_data(provider, "label { color: #00FF23;}", -1, NULL);
            break;
        case 2:
            //ERROR color
            gtk_css_provider_load_from_data(provider, "label { color: #FF0227;}", -1, NULL);
            break;
        default:
            //DEFAULT color
            gtk_css_provider_load_from_data(provider, "label { color: black;}", -1, NULL);
            break;
    }
    context = gtk_widget_get_style_context(GTK_WIDGET(widgets->statusLabel));
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER (provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);


    gtk_label_set_text(widgets->statusLabel, status_message);
}

void initTextBuffer() {
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context;
    gtk_css_provider_load_from_data(provider, "textview {"
                                              " font: 17px serif;"
                                              "}"
                                              "textview text {"
                                              " color: #2DFF1A;"
                                              " background-color: black;"
                                              "}", -1, NULL);

    context = gtk_widget_get_style_context(GTK_WIDGET(widgets->consoleTextView));
    gtk_style_context_add_provider(context,
                                   GTK_STYLE_PROVIDER (provider),
                                   GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    console_clear();
    console_writeline(
            "Console...");
}

void console_clear() {
    gtk_text_buffer_set_text(widgets->consoleTextBuffer, "", -1);
}

void console_write(const char *text) {
    GtkAdjustment *vadjustment = gtk_scrolled_window_get_vadjustment(widgets->scrollableWindow);

    GtkTextIter *endIter = calloc(sizeof(GtkTextIter), 1);
    gtk_text_buffer_get_end_iter(widgets->consoleTextBuffer, endIter);
    gtk_text_buffer_insert(widgets->consoleTextBuffer, endIter, text, -1);

    g_free(endIter);

    gtk_adjustment_set_value(vadjustment, gtk_adjustment_get_upper(vadjustment));
    gtk_adjustment_clamp_page(vadjustment, 0., gtk_adjustment_get_upper(vadjustment));
    gtk_adjustment_set_value(vadjustment, gtk_adjustment_get_upper(vadjustment));
}

void console_writeline(const char *text) {
    console_write(text);
    console_write("\n");

//    GtkTextIter *endIter = calloc(sizeof(GtkTextIter), 1);
//    gtk_text_buffer_get_end_iter(widgets->consoleTextBuffer, endIter);
//    gtk_text_buffer_insert(widgets->consoleTextBuffer, endIter, "\n", -1);
//    g_free(endIter);
}

void update_button_sensitive() {
    gtk_widget_set_sensitive(GTK_WIDGET(widgets->validateButton), validXML && validDTD);
}