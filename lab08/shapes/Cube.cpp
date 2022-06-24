#include "Cube.h"

Cube::Cube(int param1) :
    m_param1(param1)
{
    if (m_param1 == 0) {
        m_param1 = 1;
    }
    setVertexData();
}

Cube::~Cube()
{

}

void Cube::makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight, glm::vec3 topRight)
{
    // [TODO]: Task 2 -- create a tile (aka 2 triangles) out of the 4
    //         given points (once you have the tile, make sure you add
    //         the points to m_vertexData)
    // Note: pay attention to how you are calculating your normals! you will
    //       be using this function to create a cube and a sphere

    glm::vec3 t1Normal = glm::normalize(glm::cross(bottomLeft - topLeft,
                                                   bottomRight - bottomLeft));
    glm::vec3 t2Normal = glm::normalize(glm::cross(topRight - bottomRight,
                                                   topLeft - topRight));

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, t1Normal);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, t1Normal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, t1Normal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, t2Normal);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, t2Normal);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, t2Normal);
}

void Cube::makeFace(glm::vec3 topLeft, glm::vec3 bottomLeft,
                    glm::vec3 bottomRight, glm::vec3 topRight)
{
    // [TODO]: Task 3 -- create a single side of the cube out of the 4
    //         given points and makeTile()
    // Note: think about how param 1 affects the number of triangles on
    //       the face of the cube

    // gets the step size in the x, y, and z directions
    float stepX = (bottomRight.x - topLeft.x) / m_param1;
    float stepY = (bottomRight.y - topLeft.y) / m_param1;
    float stepZ = (bottomRight.z - topLeft.z) / m_param1;
    glm::vec3 stepSize = glm::vec3(stepX, stepY, stepZ);

    // goes through each tile on the face
    for (int row = 0; row < m_param1; row++) {
        for (int col = 0; col < m_param1; col++) {

            glm::vec3 first = topLeft + stepSize * glm::vec3(col, col, col);
            glm::vec3 third = topLeft + stepSize * glm::vec3((col + 1), (col + 1), (col + 1));
            glm::vec3 second = first + stepSize * glm::vec3((row + 1), (row + 1), (row + 1));
            glm::vec3 fourth = third - stepSize * glm::vec3((row + 1), (row + 1), (row + 1));

            makeTile(first, second, third, fourth);
        }
    }
}

void Cube::setVertexData()
{
    // uncomment this for task 2:

    makeTile(glm::vec3(-0.5f, 0.5f, 0.0f),
             glm::vec3(-0.5f, -0.5f, 0.0f),
             glm::vec3(0.5f, -0.5f, 0.0f),
             glm::vec3(0.5f, 0.5f, 0.0f));

    makeTile(glm::vec3(0.5f, 0.5f, 0.0f),
             glm::vec3(0.5f, -0.5f, 0.0f),
             glm::vec3(0.5f, -0.5f, -1.0f),
             glm::vec3(0.5f, 0.5f, -1.0f));

    // uncomment this for task 3:

//    makeFace(glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(-0.5f, -0.5f, 0.0f),
//             glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.05f, 0.5f, 0.0f));
}
