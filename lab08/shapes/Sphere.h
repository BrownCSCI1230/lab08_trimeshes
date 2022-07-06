#ifndef SPHERE_H
#define SPHERE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

class Sphere
{
public:
    Sphere(int param1, int param2);
    ~Sphere();

    void updateParams(int param1, int param2);
    std::vector<GLfloat> generateShape();

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void setVertexData();
    void makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                  glm::vec3 bottomRight, glm::vec3 topRight);
    void makeSlice(float currTheta, float nextTheta);
    void makeSphere();

    std::vector<GLfloat> m_vertexData;
    float m_radius;
    int m_param1;
    int m_param2;
};

#endif // SPHERE_H
