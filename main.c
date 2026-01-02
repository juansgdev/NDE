#include <gtk-layer-shell/gtk-layer-shell.h>
#include <webkit2/webkit2.h>
#include <gtk/gtk.h>

static void activate (GtkApplication* app, void *_data) {
  GtkWindow *gtk_window = GTK_WINDOW(gtk_application_window_new(app));

  gtk_layer_init_for_window(gtk_window);

  // Set behind other programs
  gtk_layer_set_layer(gtk_window, GTK_LAYER_SHELL_LAYER_BACKGROUND);
  gtk_layer_auto_exclusive_zone_enable(gtk_window);

  // Config to enable keyboard input
  gtk_layer_set_keyboard_mode(gtk_window, GTK_LAYER_SHELL_KEYBOARD_MODE_ON_DEMAND);

  // Expand to all the screen
  static const gboolean anchors[] = {TRUE, TRUE, TRUE, TRUE};
  for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
    gtk_layer_set_anchor(gtk_window, i, anchors[i]);
  }

  // Create and append webview in window
  GtkWidget *webapp;
  webapp = webkit_web_view_new();
  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webapp), "file:///home/juan/dev/nde/index.html");
  gtk_container_add(GTK_CONTAINER(gtk_window), webapp);
  gtk_widget_show_all(GTK_WIDGET(gtk_window));
}

int main (int argc, char **argv) {
  GtkApplication *app = gtk_application_new("sh.wmww.gtk-layer-example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}