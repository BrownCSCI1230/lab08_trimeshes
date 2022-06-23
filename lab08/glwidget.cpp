#include "glwidget.h"
#include "Settings.h"
#include "Shapes/Triangle.h"
#include "Shapes/Cube.h"
#include <glm/gtc/matrix_transform.hpp>

#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>
#include <iostream>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent),
      m_currShape(SHAPE_TRIANGLE),
      m_shape(std::unique_ptr<Triangle>(new Triangle))
{
    std::cout<<"GLWIDGET CONSTRUCTOR"<<std::endl;
}

GLWidget::~GLWidget()
{
    if (m_program == nullptr)
        return;
    makeCurrent();
    m_logoVbo.destroy();
    delete m_program;
    m_program = nullptr;
    doneCurrent();
}

static const char *vertexShaderSourceCore =
    "#version 150\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 150\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(1.0, 0.78, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "   //fragColor = vec4(1.0);\n"
    "}\n";

void GLWidget::initializeGL()
{
    std::cout<<"INITIALIZE GL"<<std::endl;
    initializeOpenGLFunctions();
    glClearColor(103/255.f, 142/255.f, 166/255.f, 1); // set the background color

    m_program = new QOpenGLShaderProgram; // allow OpenGL shader programs to be linked and used
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    m_program->bindAttributeLocation("vertex", 0);
    m_program->bindAttributeLocation("normal", 1);
    m_program->link();

    m_program->bind();
    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_mvMatrixLoc = m_program->uniformLocation("mvMatrix");
    m_normalMatrixLoc = m_program->uniformLocation("normalMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    m_vao.create();
    m_vao.bind();

    bindVbo();

    // Camera stuff (facing -z direction positioned at (0, 0, -5))
    // m_camera is the model-view matrix. The projection matrix is separately tracked as m_proj
     m_camera.setToIdentity();
     m_camera.translate(0, 0, -5);

    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));

    m_program->release();
}

void GLWidget::bindVbo()
{
    // Create the OpenGLShape and get its vertices and normals
    std::vector<GLfloat> verts = m_shape->generateShape();

    m_logoVbo.create();
    m_logoVbo.bind();
    m_logoVbo.allocate(verts.data(), verts.size()*sizeof(GLfloat));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                             nullptr);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                             reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_logoVbo.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_world.setToIdentity();

    QOpenGLVertexArrayObject::Binder vaoBinder(&m_vao);
    m_program->bind();
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);
    QMatrix3x3 normalMatrix = m_world.normalMatrix();
    m_program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    if (m_currShape == SHAPE_TRIANGLE) {
        glDrawArrays(GL_TRIANGLES, 0, 6);
    } else if (m_currShape == SHAPE_CUBE) {
        glDrawArrays(GL_TRIANGLES, 0, 12);
    }

    m_program->release();
}

void GLWidget::resizeGL(int w, int h)
{
    m_proj.setToIdentity();
    m_proj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}


/* -----------------------------------------------
 *   Mouse Events for Orbital Camera stuff below
 * -----------------------------------------------
*/

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton) {
        m_oldXY = event->position();
        m_isDragging = true;
        update(); // updates widget
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (m_isDragging && (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)) {
        m_isDragging = false;
        update(); // updates widget
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_isDragging) {
        QPointF dxdy = event->position() - m_oldXY;
        m_camera(0,3) += (dxdy.x() * 0.01);
        m_camera(1,3) -= (dxdy.y() * 0.01);
        m_oldXY = event->position();
        update(); // updates widget
    }
}

/* -----------------------------------------------
 *   Settings Change below
 * -----------------------------------------------
*/
void GLWidget::settingsChanged()
{
    UiSettingsChanged();
    bindVbo();
    update();
}

void GLWidget::UiSettingsChanged()
{
    if (settings.shapeType != m_currShape) {
        if (settings.shapeType == SHAPE_TRIANGLE) {
            m_shape = std::make_unique<Triangle>();
            m_currShape = SHAPE_TRIANGLE;
        } else if (settings.shapeType == SHAPE_CUBE) {
            m_shape = std::make_unique<Cube>();
            m_currShape = SHAPE_CUBE;
        } else if (settings.shapeType == SHAPE_SPHERE) {
//            m_shape = std::make_unique<Sphere>(settings.shapeParameter1, settings.shapeParameter2);
        }
    }
}
