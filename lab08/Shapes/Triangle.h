#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <gl.h>

#include "OpenGLShape.h"

class Triangle : public OpenGLShape
{
public:
    Triangle();
    ~Triangle();

    std::vector<GLfloat> generateShape();

private:
    void setVertexData();
};

#endif // TRIANGLE_H
