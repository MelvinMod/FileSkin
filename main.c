#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <gtk/gtk.h>
#include <utime.h>

#define APP_NAME "FileSkin"

static void on_touch_clicked(GtkWidget *widget, gpointer data) {
    utime((const char *)data, NULL);
}

void show_gui(const char *path, long size, const char *version) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    char *title = g_strdup_printf("%s %s", APP_NAME, version);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_box_pack_start(GTK_BOX(box), gtk_label_new(g_strdup_printf("File: %s\nSize: %ld bytes", path, size)), TRUE, TRUE, 0);
    GtkWidget *btn = gtk_button_new_with_label("Touch");
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
    g_signal_connect(btn, "clicked", G_CALLBACK(on_touch_clicked), (gpointer)path);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    const char *version = "0.0.1 (Preview)";

    if (argc < 2) { printf("Usage: ./fileskin <path>\n"); return 1; }

    const char *file_path = argv[1];
    struct stat file_info;

    if (stat(file_path, &file_info) != 0) { printf("File not found: %s\n", file_path); return 1; }
    gtk_init(&argc, &argv);
    
    show_gui(file_path, file_info.st_size, version);

    return 0;
}

