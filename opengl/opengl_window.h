#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QDebug>

struct vector_page
{
    QVector<QString>          vector_page_key;
    QVector<QVector<QString>> vector_page_value;
    QVector<QVector<bool>>    vector_page_bool;
    QVector<QString>          vector_page_settings;
};

struct opengl_window : QGLWidget
{
    opengl_window();

    void initializeGL()               override;
    void resizeGL(int,int)            override;
    void paintGL()                    override;
    void keyReleaseEvent(QKeyEvent *) override;

private:
    void draw_start_process_pages();
    void process_page1();
    void process_page2();
    void process_page3();
    void process_page4();
    void load(QVector<QString> vector_data);
    void save(QVector<QString> vector_data);
    vector_page page1;
    vector_page page2;
    vector_page page3;
    vector_page page4;
    QVector<vector_page> vector_total;

    QVector<bool>   STATE_LIST;
    QVector<QVector<bool>> state_list;

    QFont font;
    QFont font_selected;
    int var = 0;
    int mid_width = 180;
    int x = 20;
    int y = 40;
    const int dy = 50;
};

#endif // OPENGL_WINDOW_H
