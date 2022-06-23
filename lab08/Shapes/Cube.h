#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <gl.h>

#include "OpenGLShape.h"

class Cube : public OpenGLShape
{
public:
    Cube();
    ~Cube();

    std::vector<GLfloat> generateShape();

private:
    void setVertexData();
};

#endif // CUBE_H
