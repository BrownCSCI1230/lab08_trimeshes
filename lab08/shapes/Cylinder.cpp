#include "Cylinder.h"

Cylinder::Cylinder(int param1, int param2):
    m_param1(param1),
    m_param2(param2)
{

}

void Cylinder::updateParams(int param1, int param2)
{
    m_vertexData = std::vector<GLfloat>();
    m_param1 = param1;
    m_param2 = param2;
}

Cylinder::~Cylinder()
{

}

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
void Cylinder::insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

std::vector<GLfloat> Cylinder::generateShape()
{
    return m_vertexData;
}
