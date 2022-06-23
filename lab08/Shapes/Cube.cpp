#include "Cube.h"

Cube::Cube()
{
    setVertexData();
}

Cube::~Cube()
{

}

void Cube::setVertexData()
{
    m_vertexData =
    { //   COORDINATES     /       NORMALS      //
       -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f, // positive z side
       -0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f,-0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f, // negative z side
        0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f,-0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
       -0.5f, 0.5f,-0.5f,     0.0f, 0.0f,-1.0f,
        0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f, // positive x side
        0.5f,-0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f,-0.5f,    -1.0f, 0.0f, 0.0f, // negative x side
       -0.5f,-0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f,-0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f,-0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f,-0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f, // positive y side
       -0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, 0.5f,-0.5f,     0.0f, 1.0f, 0.0f,
       -0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
        0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f, // negative y side
       -0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,
       -0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
        0.5f,-0.5f, 0.5f,     0.0f,-1.0f, 0.0f,
       -0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
        0.5f,-0.5f,-0.5f,     0.0f,-1.0f, 0.0f,
    };
}

//std::vector<GLfloat> Cube::generateShape()
//{
//    return m_vertexData;
//}
