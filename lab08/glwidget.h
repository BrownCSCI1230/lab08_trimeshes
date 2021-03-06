#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "shapes/OpenGLShape.h"
#include <glm/glm.hpp>

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

    void settingsChange();

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    QMatrix4x4 glmMatToQMat(glm::mat4x4 m);
    void bindVbo();

    // Orbital Camera and Mouse Events stuff
    float m_movementSpeed = 60.0;
    float m_zoomZ = 1.0;
    glm::vec2 m_oldXY;
    glm::vec2 m_angleXY = glm::vec2(0.0, 0.0);
    bool m_isDragging = false;
    void updateView();
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;

private:
    // VAO/VBO
    QOpenGLVertexArrayObject m_vao;
    QOpenGLBuffer m_vbo;

    // Shape shader program stuff
    QOpenGLShaderProgram *m_program = nullptr;
    int m_default_projLoc;
    int m_default_mvLoc;
    int m_default_normalLoc;
    int m_default_lightPos;

    // Normal arrows shader program stuff
    QOpenGLShaderProgram *m_normalsProgram = nullptr; // arrow body
    int m_normal_projLoc;
    int m_normal_mvLoc;
    QOpenGLShaderProgram *m_normalsTipsProgram = nullptr; // arrow head
    int m_normalTip_projLoc;
    int m_normalTip_mvLoc;

    // Wireframe shader program stuff
    QOpenGLShaderProgram *m_wireframeProgram = nullptr;
    int m_wireframe_projLoc;
    int m_wireframe_mvLoc;

    // Vertices, matrices, etc.
    std::vector<GLfloat> verts;
    int m_numTriangles;
    glm::mat4x4 m_proj;
    glm::mat4x4 m_camera;
    glm::mat4x4 m_world;
    static bool m_transparent;

    // Tracking shape to render
    int m_currShape;
    std::unique_ptr<OpenGLShape> m_shape;
};

#endif // GLWIDGET_H
