#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <gtk/gtk.h>
#include <utime.h>
#include <fcntl.h>

#define APP_NAME "FileSkin"

typedef struct {
    const char *path; GtkWidget *label; GtkWidget *entry;
} AppData;

static void on_touch_clicked(GtkWidget *widget, gpointer data) {
    AppData *d = (AppData *)data; 
    const char *text = gtk_entry_get_text(GTK_ENTRY(d->entry));
    long long sec = atoll(text);
    struct stat st; struct timespec times[2];
    times[0].tv_sec = sec; times [0].tv_nsec = 0;
    times[1].tv_sec = sec; times [1].tv_nsec = 0;
    utimensat(AT_FDCWD, d->path, times, 0);
    stat(d->path, &st);
    gtk_label_set_text(GTK_LABEL(d->label), ctime(&st.st_mtime));
} 

void show_gui(const char *path, long size, const char *version) {
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    GtkWidget *entry = gtk_entry_new();
    GtkWidget *label = gtk_label_new(g_strdup_printf("File: %s\nSize: %ld bytes", path, size));
    char *title = g_strdup_printf("%s %s", APP_NAME, version);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), entry, FALSE, FALSE, 0);
    GtkWidget *btn = gtk_button_new_with_label("Touch");
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, FALSE, 0);
    AppData *data = g_new0(AppData, 1);
    data->path = path; data->label = label; data->entry = entry;
    g_signal_connect(btn, "clicked", G_CALLBACK(on_touch_clicked), (gpointer)data);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_widget_show_all(window);
    gtk_main();
}

int main(int argc, char *argv[]) {
    const char *version = "0.0.2 (Preview)";

    if (argc < 2) { printf("Usage: ./fileskin <path>\n"); return 1; }

    const char *file_path = argv[1];
    struct stat file_info;

    if (stat(file_path, &file_info) != 0) { printf("File not found: %s\n", file_path); return 1; }
    gtk_init(&argc, &argv);
    
    show_gui(file_path, file_info.st_size, version);

    return 0;
}

