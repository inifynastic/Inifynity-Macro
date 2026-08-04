#include "mainwindow.h"

#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data)
{
    (void)user_data;
    GtkWidget *win = mainwindow_new();
    gtk_window_set_application(GTK_WINDOW(win), app);
    gtk_window_present(GTK_WINDOW(win));
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new(
        "com.inifynastic.InifynityMacro", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
