#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTimer>

//--------------------------------------------------
#include "opengl/appsettings.hpp"
#include "opengl/opengl_window.h"
//--------------------------------------------------
#include "Ximea/cv_qt_converter.h"
#include "Ximea/cameraclass.h"

using namespace cv;
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QMainWindow
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();
    QPixmap Mat2Pixmap(Mat data);

private slots:
    void on_Start_clicked();
    void on_Stop_clicked();
    void on_Settings_clicked();

    void CaptureImage();

private:
    Ui::window *ui;
    QVector<XimeaCamera>       cam_vector;
    QVector<QGraphicsView*>   view_vector;
    QVector<QPixmap>        pixmap_vector;
    QVector<Mat>               mat_vector;
    QVector<QGraphicsScene*> scene_vector;
    unique_ptr<QTimer> timer;
    xiAPIplus cam_manager;
    quint8 number;
    //--------------------------
    opengl_window app;
    //--------------------------
};
#endif // WINDOW_H
