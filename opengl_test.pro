QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    Ximea/cameraclass.cpp \
    Ximea/xiApiPlusOcv.cpp \
    main.cpp \
    opengl/appsettings.cpp \
    opengl/opengl_window.cpp \
    window.cpp

HEADERS += \
    Ximea/cameraclass.h \
    Ximea/cv_qt_converter.h \
    Ximea/xiApiPlusOcv.hpp \
    opengl/appsettings.hpp \
    opengl/opengl_window.h \
    window.h

FORMS += \
    window.ui

INCLUDEPATH += /usr/local/include \
               /opt/XIMEA/include \

LIBS += -L/usr/local/lib -lopencv_core -lopencv_videoio -lopencv_objdetect -lopencv_imgcodecs -lopencv_imgproc -lopencv_calib3d \
         -lopencv_features2d -lopencv_xfeatures2d -lopencv_highgui -lopencv_flann  -L/usr/lib -lm3api

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
