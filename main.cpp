#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    appSettings::properties();
    window w;
    w.show();

    return a.exec();
}
