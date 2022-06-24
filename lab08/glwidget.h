#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "shapes/OpenGLShape.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

#include <glm/glm.hpp>
#include <QMatrix4x4>

#include <QMouseEvent>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

// QOpenGLWidget is a widget for rendiering OpenGL graphics
class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = nullptr); // QWidget is the base class for all user interface objects
    ~GLWidget();

    void settingsChange();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    QMatrix4x4 glmMatToQMat(glm::mat4x4 m);

    // Orbital Camera stuff
    float m_movementSpeed = 60.0;
    glm::vec2 m_oldXY;
    glm::vec2 m_angleXY = glm::vec2(0.0, 0.0);
    bool m_isDragging = false;
    virtual void mousePressEvent(QMouseEvent *event) override; // mouse down; m_isDragging = true
    virtual void mouseMoveEvent(QMouseEvent *event) override; // mouse dragged as long as m_isDragging == true
    virtual void mouseReleaseEvent(QMouseEvent *event) override; // mouse up; m_isDragging = false

private:
    std::vector<GLfloat> verts;
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    void bindVbo();

    QOpenGLShaderProgram *m_program = nullptr;
    int m_default_projLoc;
    int m_default_mvLoc;
    int m_default_normalLoc;
    int m_default_lightPos;

    QOpenGLShaderProgram *m_normalsProgram = nullptr;
    int m_normal_projLoc;
    int m_normal_mvLoc;

    QOpenGLShaderProgram *m_wireframeProgram = nullptr;
    int m_wireframe_projLoc;
    int m_wireframe_mvLoc;

    int m_numTriangles;
    int m_projMatrixLoc = 0;
    int m_mvMatrixLoc = 0;
    int m_normalMatrixLoc = 0;
    int m_lightPosLoc = 0;
    glm::mat4x4 m_proj;
    glm::mat4x4 m_camera;
    glm::mat4x4 m_world;
    static bool m_transparent;

    int m_currShape;
    std::unique_ptr<OpenGLShape> m_shape;
};

#endif // GLWIDGET_H
