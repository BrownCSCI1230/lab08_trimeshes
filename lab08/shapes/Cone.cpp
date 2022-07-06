#include "Cone.h"

Cone::Cone(int param1, int param2) :
    m_param1(param1),
    m_param2(param2)
{

}

void Cone::updateParams(int param1, int param2)
{
    m_vertexData = std::vector<GLfloat>();
    m_param1 = param1;
    m_param2 = param2;
}

Cone::~Cone()
{

}

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
void Cone::insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

std::vector<GLfloat> Cone::generateShape()
{
    return m_vertexData;
}
