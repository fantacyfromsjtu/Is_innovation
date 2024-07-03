#include <gtk/gtk.h>

GtkBuilder *builder;

void on_button_add_feature_clicked(GtkButton *button, gpointer user_data) {
    GtkEntry *entry = GTK_ENTRY(gtk_builder_get_object(builder, "Entry1"));
    const gchar *text = gtk_entry_get_text(entry);

    // 将新特征添加到特征库
    // add_feature_to_database(text);

    // 更新界面显示
    GtkTextView *text_view = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "TextView_PatMatch"));
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(text_view);
    gtk_text_buffer_set_text(buffer, "特征已添加成功", -1);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "interface.glade", NULL);

    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);
    gtk_widget_show(window);
    gtk_main();

    return 0;
}

