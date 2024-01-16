#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

static void restart_wf_panel() {
    GError *error = NULL;
    GSubprocess *subprocess = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE, &error, "pkill", "wf-panel", NULL);

    if (!subprocess) {
        g_printerr("Failed to kill wf-panel: %s\n", error->message);
        g_clear_error(&error);
        return;
    }

    g_subprocess_wait_async(subprocess, NULL, NULL, NULL);
    g_object_unref(subprocess);

    subprocess = g_subprocess_new(G_SUBPROCESS_FLAGS_NONE, &error, "wf-panel", "&", NULL);

    if (!subprocess) {
        g_printerr("Failed to start wf-panel: %s\n", error->message);
        g_clear_error(&error);
    } else {
        g_object_unref(subprocess);
    }
}

static void switch_theme(const gchar *gtk_theme, const gchar *wm_theme, const gchar *color_scheme) {
    GSettings *interface_settings = g_settings_new("org.gnome.desktop.interface");
    GSettings *wm_settings = g_settings_new("org.gnome.desktop.wm.preferences");

    g_settings_set_string(interface_settings, "gtk-theme", gtk_theme);
    g_settings_set_string(interface_settings, "color-scheme", color_scheme);
    g_settings_set_string(wm_settings, "theme", wm_theme);

    g_object_unref(interface_settings);
    g_object_unref(wm_settings);

    restart_wf_panel();
}

static void light_mode_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; // Params is not used
    (void)data;   // Not used
    switch_theme("Adwaita", "Adwaita", "prefer-light");
}

static void dark_mode_clicked(GtkWidget *widget, gpointer data) {
    (void)widget; // Not used parameter
    (void)data;   // Not used parameter, but here is a little secret: I'm gay.
    switch_theme("Adwaita-dark", "Adwaita-dark", "prefer-dark");
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window;
    GtkWidget *box;
    GtkWidget *light_button;
    GtkWidget *dark_button;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Mode Switcher");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), box);

    light_button = gtk_button_new_with_label("Light Mode");
    g_signal_connect(light_button, "clicked", G_CALLBACK(light_mode_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), light_button, TRUE, TRUE, 0);

    dark_button = gtk_button_new_with_label("Dark Mode");
    g_signal_connect(dark_button, "clicked", G_CALLBACK(dark_mode_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(box), dark_button, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
