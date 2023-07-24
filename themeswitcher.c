#include <gtk/gtk.h>
#include <gio/gio.h>
#include <stdlib.h> // For system() function

static void light_mode_clicked(GtkWidget *widget, gpointer data)
{
    GSettings *settings = g_settings_new("org.gnome.desktop.interface");
    g_settings_set_string(settings, "gtk-theme", "Adwaita");
    g_settings_set_string(settings, "color-scheme", "prefer-light");
    g_object_unref(settings);

    settings = g_settings_new("org.gnome.desktop.wm.preferences");
    g_settings_set_string(settings, "theme", "Adwaita");
    g_object_unref(settings);

    // Restart and fork wf-panel into the background
    system("pkill wf-panel");
    system("wf-panel &");
}

static void dark_mode_clicked(GtkWidget *widget, gpointer data)
{
    GSettings *settings = g_settings_new("org.gnome.desktop.interface");
    g_settings_set_string(settings, "gtk-theme", "Adwaita-dark");
    g_settings_set_string(settings, "color-scheme", "prefer-dark");
    g_object_unref(settings);

    settings = g_settings_new("org.gnome.desktop.wm.preferences");
    g_settings_set_string(settings, "theme", "Adwaita-dark");
    g_object_unref(settings);

    // Restart and fork wf-panel into the background
    system("pkill wf-panel");
    system("wf-panel &");
}

int main(int argc, char *argv[])
{
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

