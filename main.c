#include <gtk/gtk.h>

static void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button clicked!\n");
}

static void on_entry_activated(GtkWidget *widget, gpointer data) {
    const gchar *text = gtk_entry_get_text(GTK_ENTRY(widget));
    g_print("Entry activated: %s\n", text);
}

static void show_popup(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWindow *parent_window = GTK_WINDOW(data);

    dialog = gtk_message_dialog_new(parent_window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "This is a popup message!");
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *main_box;
    GtkWidget *button_box;
    GtkWidget *button;
    GtkWidget *entry;
    GtkWidget *popup_button;
    GtkCssProvider *provider;
    GdkDisplay *display;
    GdkScreen *screen;

    // Initialize GTK's CSS handling
    provider = gtk_css_provider_new();
    display = gdk_display_get_default();
    screen = gdk_display_get_default_screen(display);

    // Load the CSS file
    gtk_css_provider_load_from_path(provider, "style.css", NULL);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Create the main window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Examples");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a main box and add it to the window
    main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_widget_set_name(main_box, "main-box");
    gtk_container_add(GTK_CONTAINER(window), main_box);

    // Create an entry and add it to the main box
    entry = gtk_entry_new();
    g_signal_connect(entry, "activate", G_CALLBACK(on_entry_activated), NULL);
    gtk_box_pack_start(GTK_BOX(main_box), entry, FALSE, FALSE, 0);

    // Create a button box for the buttons
    button_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_widget_set_name(button_box, "button-box");
    gtk_box_pack_start(GTK_BOX(main_box), button_box, FALSE, FALSE, 0);

    // Create and add a button to the button box
    button = gtk_button_new_with_label("Click Me");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(button_box), button, TRUE, TRUE, 0);

    // Create and add a popup button to the button box
    popup_button = gtk_button_new_with_label("Show Popup");
    g_signal_connect(popup_button, "clicked", G_CALLBACK(show_popup), window);
    gtk_box_pack_start(GTK_BOX(button_box), popup_button, TRUE, TRUE, 0);

    // Show all widgets
    gtk_widget_show_all(window);

    // Clean up
    g_object_unref(provider);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
