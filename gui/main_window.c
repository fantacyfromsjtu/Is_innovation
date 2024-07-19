#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>

// 显示消息对话框
void show_dialog(GtkWindow *parent_window, const char *message) {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(parent_window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

// 检测命令执行函数
gpointer run_detection_command(gpointer data) {
    GtkWindow *parent_window = GTK_WINDOW(data);
    
    // 执行入侵检测命令
    int ret = system("sudo ../build/main ../patterns/patternfile BM");
    if (ret == -1) {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行失败！"));
    } else {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行成功！"));
    }

    return NULL;
}

// 回调函数，当点击添加特征按钮时调用
void on_add_feature_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data);
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    const char *feature = gtk_entry_get_text(GTK_ENTRY(entry));
    
    if (feature == NULL || strlen(feature) == 0) {
        printf("Feature string is empty.\n");
        return;
    }

    // 打开文件以追加模式写入特征字符串
    FILE *file = fopen("../patterns/patternfile", "a");
    if (file == NULL) {
        printf("Failed to open patternfile.\n");
        return;
    }

    fprintf(file, "%s\n", feature);
    fclose(file);
    
    printf("Feature added: %s\n", feature);

    // 清空输入框内容
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    // 显示成功消息
    show_dialog(GTK_WINDOW(parent_window), "添加成功！");
}

// 回调函数，当点击检测按钮时调用
void on_detect_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button));
    
    // 创建新线程执行检测命令
    GThread *thread = g_thread_new("detection_thread", run_detection_command, parent_window);
    g_thread_unref(thread);
}

// 初始化GTK应用程序
void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *entry;
    GtkWidget *add_feature_button;
    GtkWidget *detect_button;

    // 从Glade文件加载界面
    builder = gtk_builder_new_from_file("../gui/main_window.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "feature_entry"));
    add_feature_button = GTK_WIDGET(gtk_builder_get_object(builder, "add_feature_button"));
    detect_button = GTK_WIDGET(gtk_builder_get_object(builder, "detect_button"));

    // 连接按钮点击事件至回调函数
    g_signal_connect(add_feature_button, "clicked", G_CALLBACK(on_add_feature_button_clicked), entry);
    g_signal_connect(detect_button, "clicked", G_CALLBACK(on_detect_button_clicked), NULL);

    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // 创建新的GTK应用程序
    app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

