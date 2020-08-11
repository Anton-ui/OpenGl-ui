#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::window)
{
    ui->setupUi(this);
    //----------------------------------------------------------------------------
    opengl_window app;

    app.setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    app.setFixedSize(800, 600);
    //----------------------------------------------------------------------------
}

window::~window()
{
    delete ui;
}


void window::on_Start_clicked()
{

}

void window::on_Stop_clicked()
{

}

void window::on_Settings_clicked()
{
    app.show();
}
