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

private:
    void setVertexData();
};

#endif // CUBE_H
