#ifndef CYLINDER_H
#define CYLINDER_H

#include "OpenGLShape.h"

class Cylinder : public OpenGLShape
{
public:
    Cylinder(int param1, int param2);
    ~Cylinder();

    void updateParams(int param1, int param2) override;

private:
    int m_param1;
    int m_param2;
};

#endif // CYLINDER_H
