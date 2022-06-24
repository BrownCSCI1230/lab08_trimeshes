#include "Sphere.h"

Sphere::Sphere(int param1, int param2) :
    m_radius(0.5),
    m_param1(param1),
    m_param2(param2)
{
    setVertexData();
}

Sphere::~Sphere()
{

}

void Sphere::makeTile(glm::vec3 topLeft, glm::vec3 bottomLeft,
                      glm::vec3 bottomRight, glm::vec3 topRight)
{



    // !!!! NOTE THE NORMAL CALCULATION HERE IS DIFFERENT THAN IN CUBE !!!!
    // ======== TASK ___: TA SOLUTION ==========
    glm::vec3 tlNormal = glm::normalize(topLeft);
    glm::vec3 blNormal = glm::normalize(bottomLeft);
    glm::vec3 brNormal = glm::normalize(bottomRight);
    glm::vec3 trNormal = glm::normalize(topRight);

    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, tlNormal);
    insertVec3(m_vertexData, bottomLeft);
    insertVec3(m_vertexData, blNormal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, brNormal);
    insertVec3(m_vertexData, bottomRight);
    insertVec3(m_vertexData, brNormal);
    insertVec3(m_vertexData, topRight);
    insertVec3(m_vertexData, trNormal);
    insertVec3(m_vertexData, topLeft);
    insertVec3(m_vertexData, tlNormal);
}

void Sphere::makeSlice(float currentTheta, float nextTheta) {




    // ======== TASK ___: TA SOLUTION ==========
    float phiStep = glm::radians(180.f / m_param1);
    for (int bite = 0; bite < m_param1; bite++) {
        float bottomPhi = (bite % (m_param1 + 1)) * phiStep;
        float topPhi = ((bite + 1) % (m_param1 + 1)) * phiStep;

        // top left vertex
        glm::vec3 v1(m_radius * std::sin(topPhi) * std::cos(currentTheta),
                     m_radius * std::cos(topPhi),
                     m_radius * std::sin(topPhi) * std::sin(currentTheta));

        // bottom left vertex
        glm::vec3 v2(m_radius * std::sin(bottomPhi) * std::cos(currentTheta),
                     m_radius * std::cos(bottomPhi),
                     m_radius * std::sin(bottomPhi) * std::sin(currentTheta));

        // bottom right vertex
        glm::vec3 v3(m_radius * std::sin(bottomPhi) * std::cos(nextTheta),
                     m_radius * std::cos(bottomPhi),
                     m_radius * std::sin(bottomPhi) * std::sin(nextTheta));

        // top right vertex
        glm::vec3 v4(m_radius * std::sin(topPhi) * std::cos(nextTheta),
                     m_radius * std::cos(topPhi),
                     m_radius * std::sin(topPhi) * std::sin(nextTheta));

        makeTile(v1, v2, v3, v4);
    }
}

void Sphere::makeSphere()
{
    float thetaStep = glm::radians(360.f / m_param2);
    for (int slice = 0; slice < m_param2; slice++) {
        float currentTheta = slice * thetaStep;
        float nextTheta = (slice + 1) * thetaStep;
        makeSlice(currentTheta, nextTheta);
    }
}

void Sphere::setVertexData() {
    m_param1 = 7;
    m_param2 = 6;

    // Uncomment to make slice
//    float thetaStep = glm::radians(360.f / m_param2);
//    float currentTheta = 0 * thetaStep;
//    float nextTheta = 1 * thetaStep;
//    makeSlice(currentTheta, nextTheta);

    // Uncomment to make sphere
    makeSphere();
}
