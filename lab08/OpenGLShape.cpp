#include "OpenGLShape.h"

OpenGLShape::OpenGLShape() :
    m_vertexData // PLACEHOLDER: Hard-coded cube
    { //   COORDINATES     /       NORMALS      //
       -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f, // positive z side
       -0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f, // negative z side
        0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
        0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f, // positive x side
        0.5f,-0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f,-0.5f,    -1.0f, 0.0f, 0.0f, // negative x side
       -0.5f,-0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f,-0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f,-0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f, // positive y side
       -0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f, // negative y side
       -0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,
       -0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
        0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,
       -0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
    }
{

}

OpenGLShape::~OpenGLShape()
{

}

/**
 * @brief Returns m_vertexData which contains the shape's normals
 *        and vertices. Student will fill out m_vertexData in their
 *        shapes subclasses.
 * @return std::vector<GLfloat> m_vertexData
 */
std::vector<GLfloat> OpenGLShape::generateShape() {
    return m_vertexData;
}
