#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object2D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateSquare(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
    Mesh* CreateCenteredSquare(const std::string& name, float size, glm::vec3 color, bool fill = true);
    Mesh* CreateStar(const std::string& name, float size, glm::vec3 color, bool fill = true);
    Mesh* CreateHex(const std::string& name, float size, glm::vec3 color, bool fill = true);
    Mesh* CreateHeart(const std::string& name, float size, glm::vec3 color, bool fill = true);
    Mesh* CreateCannon(const std::string& name, float size, glm::vec3 color, bool fill = true);
    Mesh* CreateCoin(const std::string& name,float radius,glm::vec3 color,bool fill=true);

}
