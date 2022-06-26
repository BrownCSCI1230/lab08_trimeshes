QT += widgets opengl openglwidgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    Settings.h \
    glwidget.h \
    mainwindow.h \
    shapes/Cone.h \
    shapes/Cube.h \
    shapes/Cylinder.h \
    shapes/OpenGLShape.h \
    shapes/Sphere.h \
    shapes/Triangle.h

SOURCES += \
    Settings.cpp \
    glwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    shapes/Cone.cpp \
    shapes/Cube.cpp \
    shapes/Cylinder.cpp \
    shapes/OpenGLShape.cpp \
    shapes/Sphere.cpp \
    shapes/Triangle.cpp

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target
