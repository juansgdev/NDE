#include <stdlib.h>
#include <gtk-layer-shell/gtk-layer-shell.h>
#include <webkit2/webkit2.h>
#include <gtk/gtk.h>

void exec_app (WebKitUserContentManager *manager, WebKitJavascriptResult   *js_result, gpointer user_data) {
  JSCValue *value = webkit_javascript_result_get_js_value(js_result);
  char *program = jsc_value_to_string(value);

  system(program);
}

static void activate (GtkApplication* app, void *_data) {
  GtkWindow *gtk_window = GTK_WINDOW(gtk_application_window_new(app));

  gtk_layer_init_for_window(gtk_window);

  // Set behind other programs
  // GTK_LAYER_SHELL_LAYER_TOP --> above common windows
  // GTK_LAYER_SHELL_LAYER_OVERLAY --> above all

  // gtk_layer_set_layer(gtk_window, GTK_LAYER_SHELL_LAYER_TOP);
  // gtk_window_fullscreen(GTK_WINDOW(gtk_window));
  // set window above the common windows
  
  gtk_layer_set_layer(gtk_window, GTK_LAYER_SHELL_LAYER_BACKGROUND);
  gtk_layer_auto_exclusive_zone_enable(gtk_window);

  // Config to enable keyboard input
  gtk_layer_set_keyboard_mode(gtk_window, GTK_LAYER_SHELL_KEYBOARD_MODE_ON_DEMAND);

  // Expand to all the screen
  static const gboolean anchors[] = {TRUE, TRUE, TRUE, TRUE};
  for (int i = 0; i < GTK_LAYER_SHELL_EDGE_ENTRY_NUMBER; i++) {
    gtk_layer_set_anchor(gtk_window, i, anchors[i]);
  }

  WebKitUserContentManager *manager = webkit_user_content_manager_new();
  webkit_user_content_manager_register_script_message_handler(manager, "app_entry");
  g_signal_connect(manager, "script-message-received::app_entry", G_CALLBACK(exec_app), gtk_window);

  // Create, configure and append webview to the window in lines below
  WebKitWebView *webapp = WEBKIT_WEB_VIEW(webkit_web_view_new_with_user_content_manager(manager));
  
  // webview configs & debug
  WebKitSettings *settings = webkit_web_view_get_settings(webapp);
  webkit_settings_set_enable_html5_local_storage(settings, TRUE);
  webkit_settings_set_allow_file_access_from_file_urls(settings, TRUE);
  webkit_settings_set_allow_universal_access_from_file_urls(settings, TRUE);
  webkit_settings_set_enable_javascript(settings, TRUE);
  webkit_settings_set_enable_developer_extras(settings, TRUE);
  webkit_web_view_set_settings(webapp, settings);

  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webapp), "file:///home/juan/dev/nde/app/index.html");
  gtk_container_add(GTK_CONTAINER(gtk_window), GTK_WIDGET(webapp));
  gtk_widget_show_all(GTK_WIDGET(gtk_window));
}

int main (int argc, char **argv) {
  GtkApplication *app = gtk_application_new("sh.wmww.gtk-layer-example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
  return status;
}