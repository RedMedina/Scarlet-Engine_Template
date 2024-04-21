#ifndef __Transform
#define __Transform

#include "Component.h"
#include <glm/glm.hpp>

class Transform : public Component {
public:
    glm::vec3 Position;
    glm::vec3 Rotation;
    glm::vec3 Scale;

    Transform(float x, float y, float z, float RotX, float RotY, float RotZ, float ScaleX, float ScaleY, float ScaleZ);

    void Update() override;
    void Draw() override;
};

#endif