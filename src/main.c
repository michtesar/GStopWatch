#include <gtk/gtk.h>
#include <stdbool.h>

typedef struct {
    GtkWidget *w_lbl_time;
    GtkWidget *w_lbl_elapsed;
    GtkWidget *w_btn_stop;
} app_widgets;

bool is_stopped = false;
GDateTime *reference_time;

gboolean timer_handler(app_widgets *widgets);

int main(int argc, char *argv[]) {
    GtkBuilder *builder;
    GtkWidget *window;
    app_widgets *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    widgets->w_lbl_time = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_time"));
    widgets->w_lbl_elapsed = GTK_WIDGET(gtk_builder_get_object(builder, "lbl_elapsed"));
    widgets->w_btn_stop = GTK_WIDGET(gtk_builder_get_object(builder, "btn_stop"));
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);

    // start 1 second timer
    g_timeout_add(10, (GSourceFunc) timer_handler, widgets);

    gtk_widget_show(window);
    gtk_main();
    g_slice_free(app_widgets, widgets);

    return 0;
}

// handler for the 1 second timer tick
gboolean timer_handler(app_widgets *widgets) {
    GDateTime *date_time;
    gchar *dt_format;
    
    date_time = g_date_time_new_now_local();                               // get local time
    dt_format = g_date_time_format(date_time, "%H:%M:%S");          // 24hr time format
    gtk_label_set_text(GTK_LABEL(widgets->w_lbl_time), dt_format);    // update label

    if (is_stopped) {
        GTimeSpan elapsed_time_us = g_date_time_difference(date_time, reference_time);
        char elapsed_time_char[10];

        int us = (int) elapsed_time_us;
        int ms = us / 1000;
        int sec = ms / 1000;
        ms %= 1000;
        int min = sec / 60;
        sec %= 60;
        min %= 60;

        sprintf(elapsed_time_char, "%02d:%02d:%03d", min, sec, ms);
        gtk_label_set_text(GTK_LABEL(widgets->w_lbl_elapsed), elapsed_time_char);
    }

    g_free(dt_format);

    return TRUE;
}

void on_window_main_destroy() {
    gtk_main_quit();
}

void on_stop_clicked(GtkButton *button) {
    is_stopped = !is_stopped;
    if (is_stopped == true) {
        reference_time = g_date_time_new_now_local();
        gtk_button_set_label(button, "Stop");
    } else {
        gtk_button_set_label(button, "Start");
    }
}