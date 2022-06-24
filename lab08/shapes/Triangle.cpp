#include "Triangle.h"

Triangle::Triangle()
{
    setVertexData();
}

Triangle::~Triangle()
{

}

void Triangle::setVertexData()
{
    m_vertexData =  // PLACEHOLDER: Hard-coded triangle
    { //     COORDINATES     /        NORMALS      //
        -0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
         //0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
         //0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f
        -0.5f, 1.0f,  0.5f,     0.83f, 0.70f, 0.44f,
         0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
        -0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f
    };
}
