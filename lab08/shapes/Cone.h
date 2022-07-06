#ifndef CONE_H
#define CONE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

class Cone
{
public:
    Cone(int param1, int param2);
    ~Cone();

    void updateParams(int param1, int param2);
    std::vector<GLfloat> generateShape();

private:
    void insertVec3(std::vector<float> &data, glm::vec3 v);

    std::vector<GLfloat> m_vertexData;
    int m_param1;
    int m_param2;
};

#endif // CONE_H
