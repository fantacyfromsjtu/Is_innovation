#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib.h>

// 全局变量，用于存储TextView控件的指针
GtkWidget *text_view;

// 显示消息对话框
void show_dialog(GtkWindow *parent_window, const char *message) {
    GtkWidget *dialog;
    dialog = gtk_message_dialog_new(parent_window,
                                    GTK_DIALOG_DESTROY_WITH_PARENT,
                                    GTK_MESSAGE_INFO,
                                    GTK_BUTTONS_OK,
                                    "%s", message); // 创建消息对话框
    gtk_dialog_run(GTK_DIALOG(dialog)); // 显示对话框并等待用户响应
    gtk_widget_destroy(dialog); // 销毁对话框
}

// 更新TextView内容
void update_text_view(const char *message) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)); // 获取TextView的文本缓冲区
    GtkTextIter iter;
    gtk_text_buffer_get_end_iter(buffer, &iter); // 获取文本缓冲区的末尾迭代器
    gtk_text_buffer_insert(buffer, &iter, message, -1); // 插入新的文本到缓冲区末尾
}

// 检测命令执行函数
gpointer run_detection_command(gpointer data) {
    GtkWindow *parent_window = GTK_WINDOW(data); // 将传入的数据转换为GtkWindow指针
    FILE *fp;
    char path[1035];

    // 执行入侵检测命令并读取输出
    fp = popen("sudo ../build/main ../patterns/patternfile BM", "r");
    if (fp == NULL) {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行失败！")); // 在空闲时间显示错误消息
        return NULL;
    }

    // 读取命令输出并更新TextView
    while (fgets(path, sizeof(path)-1, fp) != NULL) {
        g_idle_add_full(G_PRIORITY_HIGH_IDLE, (GSourceFunc)update_text_view, g_strdup(path), g_free); // 在高优先级空闲时间更新TextView
    }

    // 确保所有输出被正确处理
    if (!feof(fp)) {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行读取失败！")); // 如果读取命令输出失败，显示错误消息
    }

    int ret = pclose(fp);
    if (ret == -1) {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行失败！")); // 如果关闭命令管道失败，显示错误消息
    } else {
        g_idle_add((GSourceFunc)show_dialog, g_strdup("检测命令执行成功！")); // 如果命令执行成功，显示成功消息
    }

    return NULL;
}

// 回调函数，当点击添加特征按钮时调用
void on_add_feature_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *entry = GTK_WIDGET(user_data); // 获取输入框控件的指针
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button)); // 获取顶层窗口控件的指针
    const char *feature = gtk_entry_get_text(GTK_ENTRY(entry)); // 获取输入框中的文本
    
    if (feature == NULL || strlen(feature) == 0) {
        printf("Feature string is empty.\n"); // 如果输入为空，打印错误信息
        return;
    }

    // 打开文件以追加模式写入特征字符串
    FILE *file = fopen("../patterns/patternfile", "a");
    if (file == NULL) {
        printf("Failed to open patternfile.\n"); // 如果打开文件失败，打印错误信息
        return;
    }

    fprintf(file, "%s\n", feature); // 将特征字符串写入文件
    fclose(file);
    
    printf("Feature added: %s\n", feature); // 打印添加的特征字符串

    // 清空输入框内容
    gtk_entry_set_text(GTK_ENTRY(entry), "");

    // 显示成功消息
    show_dialog(GTK_WINDOW(parent_window), "添加成功！");
}

// 回调函数，当点击检测按钮时调用
void on_detect_button_clicked(GtkButton *button, gpointer user_data) {
    GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(button)); // 获取顶层窗口控件的指针
    
    // 清空TextView内容
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "", -1); // 设置TextView的文本为空
    
    // 创建新线程执行检测命令
    GThread *thread = g_thread_new("detection_thread", run_detection_command, parent_window);
    g_thread_unref(thread); // 解除线程引用，允许其自动销毁
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
    window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window")); // 获取主窗口控件的指针
    entry = GTK_WIDGET(gtk_builder_get_object(builder, "feature_entry")); // 获取特征输入框控件的指针
    add_feature_button = GTK_WIDGET(gtk_builder_get_object(builder, "add_feature_button")); // 获取添加特征按钮控件的指针
    detect_button = GTK_WIDGET(gtk_builder_get_object(builder, "detect_button")); // 获取检测按钮控件的指针
    text_view = GTK_WIDGET(gtk_builder_get_object(builder, "output_textview")); // 获取输出TextView控件的指针

    // 连接按钮点击事件至回调函数
    g_signal_connect(add_feature_button, "clicked", G_CALLBACK(on_add_feature_button_clicked), entry);
    g_signal_connect(detect_button, "clicked", G_CALLBACK(on_detect_button_clicked), NULL);

    gtk_window_set_application(GTK_WINDOW(window), app); // 将窗口与应用程序关联
    gtk_widget_show_all(window); // 显示窗口及其所有子控件
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // 创建新的GTK应用程序
    app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL); // 连接activate信号至回调函数
    status = g_application_run(G_APPLICATION(app), argc, argv); // 运行应用程序事件循环
    g_object_unref(app); // 解除应用程序对象的引用

    return status;
}

