#include "Triangle.h"

Triangle::Triangle()
{
    setVertexData();
}

Triangle::~Triangle()
{

}

void Triangle::updateParams(int param1, int param2)
{

}

void Triangle::setVertexData()
{
    // [TODO]: Task 1 -- update m_vertexData with the vertices and normals
    //         needed to tesselate a triangle
    // Note: you may find the insertVec3 function (in the OpenGLShape class
    //       useful in adding your points into m_vertexData

    // ======== TASK 1: TA SOLUTION ==========
    glm::vec3 first = glm::vec3(-0.5f, -0.5f, 0.0f);
    glm::vec3 second = glm::vec3(0.5f, -0.5f, 0.0f);
    glm::vec3 third = glm::vec3(-0.5f, 0.5f, 0.0f);

    glm::vec3 normal = glm::normalize(glm::cross(second - first,
                                                 third - second));

    insertVec3(m_vertexData, first);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, second);
    insertVec3(m_vertexData, normal);
    insertVec3(m_vertexData, third);
    insertVec3(m_vertexData, normal);
}

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
void Triangle::insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

std::vector<GLfloat> Triangle::generateShape()
{
    return m_vertexData;
}
