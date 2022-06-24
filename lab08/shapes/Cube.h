#ifndef CUBE_H
#define CUBE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

#include "OpenGLShape.h"

class Cube : public OpenGLShape
{
public:
    Cube(int param1);
    ~Cube();

private:
    void makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight);
    void makeFace(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight);
    void setVertexData();

    int m_param1;
};

#endif // CUBE_H
