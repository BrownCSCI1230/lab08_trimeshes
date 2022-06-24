#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

#include <vector>
#include <gl.h>

class OpenGLShape
{
public:
    OpenGLShape();
    ~OpenGLShape();

    std::vector<GLfloat> generateShape();

protected:
    std::vector<GLfloat> m_vertexData;

};

#endif // OPENGLSHAPE_H
