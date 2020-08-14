#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::window)
{
    number = cam_manager.GetNumberOfConnectedCameras();
    cam_vector.resize(number);
    pixmap_vector.resize(number);
    mat_vector.resize(number);

    ui->setupUi(this);
    timer.reset(new QTimer);
    timer->setInterval(1000/30);
    connect(timer.get(), SIGNAL(timeout()), this, SLOT(CaptureImage()));

    for (int var = 0; var < number; ++var)
    {
        view_vector.append(new QGraphicsView);
        scene_vector.append(new QGraphicsScene(this));
        ui->Layout->addWidget(view_vector[var]);
        cam_vector[var].InitCamera(var, number);
        view_vector[var]->setScene(scene_vector[var]);
    }
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
    timer->start();
    for (int var = 0; var < number; ++var)
        if(cam_vector[var].Status() != XI_ON)
            cam_vector[var].Start();
        else qDebug() << "Camera" << var << "not started";
}

void window::on_Stop_clicked()
{
    for (int var = 0; var < number; ++var)
        cam_vector[var].Stop();
    timer->stop();
}

void window::on_Settings_clicked()
{
    app.show();
}

void window::CaptureImage()
{
    for (int var = 0; var < number; var++)
        if(cam_vector[var].Status() == XI_ON)
        {
            //pixmap_vector[var].loadFromData(cam_vector[var].GetUcharImage());

            mat_vector[var] = cam_vector[var].GetMatImage();
            pixmap_vector[var] = Mat2Pixmap(mat_vector[var]);
            view_vector[var]->scene()->clear();
            view_vector[var]->scene()->addPixmap(pixmap_vector[var]);
            view_vector[var]->setScene(scene_vector[var]);
            view_vector[var]->fitInView(pixmap_vector[var].rect(), Qt::KeepAspectRatio);

            app.TakePicture1(mat_vector[var]);
            app.updateGL();
        }
}

QPixmap window::Mat2Pixmap(Mat data)
{
    cvtColor(data, data, COLOR_RGBA2BGRA);
    return QPixmap::fromImage(QImage((unsigned char*) data.data, data.cols, data.rows, QImage:: Format_RGBX8888));
}
