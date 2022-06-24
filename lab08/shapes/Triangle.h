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

private:
    void setVertexData();
};

#endif // TRIANGLE_H
