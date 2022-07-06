#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

class Triangle
{
public:
    Triangle();
    ~Triangle();

    void updateParams(int param1, int param2);
    std::vector<GLfloat> generateShape();

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);
    void setVertexData();

    std::vector<GLfloat> m_vertexData;
};

#endif // TRIANGLE_H
