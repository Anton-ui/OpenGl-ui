#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>

//--------------------------------------------------
#include "opengl/appsettings.hpp"
#include "opengl/opengl_window.h"
//--------------------------------------------------

QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();

private slots:
    void on_Start_clicked();
    void on_Stop_clicked();
    void on_Settings_clicked();

private:
    Ui::window *ui;
    //--------------------------
    opengl_window app;
    //--------------------------
};
#endif // WINDOW_H
