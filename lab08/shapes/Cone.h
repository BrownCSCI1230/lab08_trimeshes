#ifndef CONE_H
#define CONE_H

#include "OpenGLShape.h"

class Cone : public OpenGLShape
{
public:
    Cone(int param1, int param2);
    ~Cone();

    void updateParams(int param1, int param2) override;

private:
    int m_param1;
    int m_param2;
};

#endif // CONE_H
