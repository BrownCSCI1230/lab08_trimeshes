#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

#include "OpenGLShape.h"

class Sphere : public OpenGLShape
{
public:
    Sphere(int param1, int param2);
    ~Sphere();

private:
    void setVertexData();
    void makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight);
    void makeSlice(float currTheta, float nextTheta);
    void makeSphere();

    float m_radius;
    int m_param1;
    int m_param2;
};

#endif // SPHERE_H
