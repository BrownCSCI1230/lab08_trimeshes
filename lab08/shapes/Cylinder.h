#ifndef CYLINDER_H
#define CYLINDER_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

class Cylinder
{
public:
    Cylinder(int param1, int param2);
    ~Cylinder();

    void updateParams(int param1, int param2);
    std::vector<GLfloat> generateShape();

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);

    std::vector<GLfloat> m_vertexData;
    int m_param1;
    int m_param2;
};

#endif // CYLINDER_H
