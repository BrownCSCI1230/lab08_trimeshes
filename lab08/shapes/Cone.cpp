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
