#ifndef OPENGLSHAPE_H
#define OPENGLSHAPE_H

#include <vector>
#include <gl.h>
#include <glm/glm.hpp>

/**
 *
 * inserts a glm::vec3 into a vector of floats
 * this will come in handy if you want to take advantage of vectors to build your shape
 * make sure to call reserve beforehand to speed this up
 */
inline void insertVec3(std::vector<float> &data, glm::vec3 v){
    data.push_back(v.x);
    data.push_back(v.y);
    data.push_back(v.z);
}

class OpenGLShape
{
public:
    OpenGLShape();
    ~OpenGLShape();

    std::vector<GLfloat> generateShape();

protected:
    std::vector<GLfloat> m_vertexData;
};

#endif // OPENGLSHAPE_H
