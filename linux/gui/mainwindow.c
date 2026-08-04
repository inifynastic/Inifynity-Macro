#include "mainwindow.h"
#include "macroengine.h"

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <pthread.h>
#include <stdio.h>

static GtkWidget *window;
static GtkWidget *btnStart;
static GtkWidget *btnStop;
static GtkWidget *hurBox;
static GtkWidget *minBox;
static GtkWidget *secBox;
static GtkWidget *milSecBox;
static gboolean flag = FALSE;

static void handlechangedTimer(GtkSpinButton *spin, gpointer user_data)
{
    (void)spin;
    (void)user_data;
    int mstime = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(hurBox)) * 3600000
               + gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(minBox)) * 60000
               + gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(secBox)) * 1000
               + gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(milSecBox));
    // I used AI for above cuz I sux at math.
    macro_set_timer(mstime);
}

static void handlebtnStart(GtkButton *button, gpointer user_data)
{
    (void)button;
    (void)user_data;
    macro_start_click();
    gtk_widget_set_sensitive(btnStart, FALSE);
    gtk_widget_set_sensitive(btnStop, TRUE);
}

static void handlebtnStop(GtkButton *button, gpointer user_data)
{
    (void)button;
    (void)user_data;
    macro_stop_click();
    gtk_widget_set_sensitive(btnStart, TRUE);
    gtk_widget_set_sensitive(btnStop, FALSE);
}

static gboolean handleHotkey(gpointer user_data)
{
    (void)user_data;
    printf("Hotkey pressed!\n");
    if (!flag) {
        handlebtnStart(NULL, NULL);
        flag = TRUE;
    } else {
        handlebtnStop(NULL, NULL);
        flag = FALSE;
    }
    return G_SOURCE_REMOVE;
}

static void *hotkeyThread(void *user_data)
{
    (void)user_data;
    Display *dpy = XOpenDisplay(NULL);
    if (dpy == NULL)
        return NULL;

    KeyCode key = XKeysymToKeycode(dpy, XK_F6);
    XGrabKey(dpy, key, AnyModifier, DefaultRootWindow(dpy), True,
             GrabModeAsync, GrabModeAsync);
    XSync(dpy, False);

    XEvent event;
    for (;;) {
        XNextEvent(dpy, &event);
        if (event.type == KeyPress && event.xkey.keycode == key)
            g_main_context_invoke(NULL, handleHotkey, NULL);
    }
    return NULL;
}

static void registerHotkey(void)
{
    pthread_t thread;
    if (pthread_create(&thread, NULL, hotkeyThread, NULL) == 0)
        pthread_detach(thread);
}

static GtkWidget *spacer(void)
{
    GtkWidget *s = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_widget_set_hexpand(s, TRUE);
    return s;
}

static GtkWidget *makeSpin(int min, int max, int value)
{
    GtkWidget *spin = gtk_spin_button_new_with_range(min, max, 1);
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(spin), value);
    gtk_widget_set_size_request(spin, 60, -1);
    gtk_widget_add_css_class(spin, "small");
    g_signal_connect(spin, "value-changed", G_CALLBACK(handlechangedTimer), NULL);
    return spin;
}

static void loadCss(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    // Match the Qt UI: 15pt base font (~20px), 10pt labels/spinboxes (~13px)
    gtk_css_provider_load_from_string(provider,
        "window { font-size: 20px; }"
        ".small { font-size: 13px; }");
    gtk_style_context_add_provider_for_display(
        gdk_display_get_default(), GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
}

GtkWidget *mainwindow_new(void)
{
    loadCss();

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Inifynity Macro v0.1");
    gtk_window_set_default_size(GTK_WINDOW(window), 742, 465);

    // Keep the control block pinned to the top-left corner of the window,
    // like the Qt layout widget at (10, 20) with 9px layout margins.
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 6);
    gtk_widget_set_halign(box, GTK_ALIGN_START);
    gtk_widget_set_valign(box, GTK_ALIGN_START);
    gtk_widget_set_margin_start(box, 19);
    gtk_widget_set_margin_top(box, 29);
    gtk_widget_set_margin_end(box, 9);
    gtk_widget_set_margin_bottom(box, 9);
    gtk_widget_set_size_request(box, 443, -1);
    gtk_window_set_child(GTK_WINDOW(window), box);

    GtkWidget *hTitle = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_append(GTK_BOX(box), hTitle);
    gtk_box_append(GTK_BOX(hTitle), spacer());
    GtkWidget *title = gtk_label_new("Inifynity Macro");
    gtk_box_append(GTK_BOX(hTitle), title);
    gtk_box_append(GTK_BOX(hTitle), spacer());

    gtk_box_append(GTK_BOX(box), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 6);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 6);
    gtk_box_append(GTK_BOX(box), grid);

    const char *labels[] = { "Hour", "Minute", "Second", "Millisecond" };
    for (int i = 0; i < 4; i++) {
        GtkWidget *label = gtk_label_new(labels[i]);
        gtk_widget_add_css_class(label, "small");
        gtk_grid_attach(GTK_GRID(grid), label, i, 0, 1, 1);
    }

    hurBox = makeSpin(0, 99, 0);
    minBox = makeSpin(0, 99, 0);
    secBox = makeSpin(0, 99, 0);
    milSecBox = makeSpin(1, 999, 100);
    GtkWidget *spins[] = { hurBox, minBox, secBox, milSecBox };
    for (int i = 0; i < 4; i++) {
        gtk_widget_set_hexpand(spins[i], TRUE);
        gtk_grid_attach(GTK_GRID(grid), spins[i], i, 1, 1, 1);
    }

    gtk_box_append(GTK_BOX(box), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));

    GtkWidget *hHotkey = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_append(GTK_BOX(box), hHotkey);
    gtk_box_append(GTK_BOX(hHotkey), gtk_label_new("Hotkey:"));
    GtkWidget *edithotKey = gtk_entry_new();
    gtk_editable_set_text(GTK_EDITABLE(edithotKey), "F6");
    gtk_editable_set_editable(GTK_EDITABLE(edithotKey), FALSE);
    gtk_widget_set_sensitive(edithotKey, FALSE); // Temporary solution cuz I am too lazy to make editable hot key
    gtk_widget_set_size_request(edithotKey, 130, -1);
    gtk_box_append(GTK_BOX(hHotkey), edithotKey);
    gtk_box_append(GTK_BOX(hHotkey), spacer());

    gtk_box_append(GTK_BOX(box), gtk_separator_new(GTK_ORIENTATION_HORIZONTAL));

    GtkWidget *hButtons = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    gtk_box_append(GTK_BOX(box), hButtons);

    btnStart = gtk_button_new_with_label("Start");
    gtk_widget_set_cursor(btnStart, gdk_cursor_new_from_name("pointer", NULL));
    g_signal_connect(btnStart, "clicked", G_CALLBACK(handlebtnStart), NULL);
    gtk_box_append(GTK_BOX(hButtons), btnStart);

    gtk_box_append(GTK_BOX(hButtons), spacer());

    btnStop = gtk_button_new_with_label("Stop");
    gtk_widget_set_cursor(btnStop, gdk_cursor_new_from_name("pointer", NULL));
    g_signal_connect(btnStop, "clicked", G_CALLBACK(handlebtnStop), NULL);
    gtk_box_append(GTK_BOX(hButtons), btnStop);

    gtk_widget_set_sensitive(btnStop, FALSE);

    // Keep the engine interval in sync with the initial spinbox values
    macro_set_timer(100);
    registerHotkey();

    return window;
}
