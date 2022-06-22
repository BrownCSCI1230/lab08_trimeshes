#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>

#include <QMouseEvent>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

// QOpenGLWidget is a widget for rendiering OpenGL graphics
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = nullptr); // QWidget is the base class for all user interface objects
    ~GLWidget();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;

    // Orbital Camera stuff
    QPointF m_oldXY;
    bool m_isDragging = false;
    virtual void mousePressEvent(QMouseEvent *event) override; // mouse down; m_isDragging = true
    virtual void mouseMoveEvent(QMouseEvent *event) override; // mouse dragged as long as m_isDragging == true
    virtual void mouseReleaseEvent(QMouseEvent *event) override; // mouse up; m_isDragging = false

private:
    bool m_core;
    int m_xRot = 0;
    int m_yRot = 0;
    int m_zRot = 0;
    QPoint m_lastPos;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_logoVbo;
    QOpenGLShaderProgram *m_program = nullptr;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    QMatrix4x4 m_proj;
    QMatrix4x4 m_camera;
    QMatrix4x4 m_world;
    static bool m_transparent;
};

#endif // GLWIDGET_H

