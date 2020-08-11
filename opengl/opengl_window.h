#ifndef OPENGL_WINDOW_H
#define OPENGL_WINDOW_H

#include <QGLWidget>
#include <QKeyEvent>
#include <QDebug>

#define P1 3
#define P2 3
#define P3 2
#define P4 4

struct vector_page
{
    QVector<QString>          vector_page_key;
    QVector<QVector<QString>> vector_page_value;
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
    void initialize_page_data();
    void draw_start_process_pages();
    void process_page1();
    void process_page2();
    void process_page3();
    void process_page4();
    void load();
    void save();
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
