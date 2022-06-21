#include "OpenGLShape.h"

OpenGLShape::OpenGLShape() :
    m_vertexData // PLACEHOLDER: Hard-coded triangle
    { //     COORDINATES     /        NORMALS      //
        -0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
         //0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
         //0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f
        -0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f
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
