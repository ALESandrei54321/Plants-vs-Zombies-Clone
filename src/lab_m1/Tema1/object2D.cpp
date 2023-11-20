#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateCenteredSquare(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(size * glm::vec3(1, 1, 0), color),
        VertexFormat(size * glm::vec3(-1, 1, 0), color),
        VertexFormat(size * glm::vec3(-1, -1, 0), color),
        VertexFormat(size * glm::vec3(1, -1, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(size * glm::vec3(0, 0, 0), color),
        VertexFormat(size * glm::vec3(-0.06, 8, 0), color),
        VertexFormat(size * glm::vec3(1.78, 2.49, 0), color),
        VertexFormat(size * glm::vec3(7.59, 2.53, 0), color),
        VertexFormat(size * glm::vec3(2.91, -0.92, 0), color),
        VertexFormat(size * glm::vec3(4.75, -6.44, 0), color),
        VertexFormat(size * glm::vec3(0.02, -3.06, 0), color),
        VertexFormat(size * glm::vec3(-4.65, -6.51, 0), color),
        VertexFormat(size * glm::vec3(-2.9, -0.97, 0), color),
        VertexFormat(size * glm::vec3(-7.63, 2.42, 0), color),
        VertexFormat(size * glm::vec3(-1.81, 2.46, 0), color)

    };

    std::vector<unsigned int> indices = {7,1,4,8,1,5,6,9,3};

    Mesh* star = new Mesh(name);

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }

    star->InitFromData(vertices, indices);
    return star;
}
Mesh* object2D::CreateHex(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{
    float outerSize = 1.5;
    glm::vec3 innerColor = glm::vec3(0, 0.6, 0.6);

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(outerSize * size * glm::vec3(0, 0, 0), color),
        VertexFormat(outerSize * size * glm::vec3(1.5, 1.5, 0), color),
        VertexFormat(outerSize * size * glm::vec3(2.05, -0.55, 0), color),
        VertexFormat(outerSize * size * glm::vec3(0.55, -2.05, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-1.5, -1.5, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-2.05, 0.55, 0), color),
        VertexFormat(outerSize * size * glm::vec3(-0.55, 2.05, 0), color),

        VertexFormat(size * glm::vec3(1.5, 1.5, 0), innerColor),
        VertexFormat(size * glm::vec3(2.05, -0.55, 0), innerColor),
        VertexFormat(size * glm::vec3(0.55, -2.05, 0), innerColor),
        VertexFormat(size * glm::vec3(-1.5, -1.5, 0), innerColor),
        VertexFormat(size * glm::vec3(-2.05, 0.55, 0), innerColor),
        VertexFormat(size * glm::vec3(-0.55, 2.05, 0), innerColor),
        VertexFormat(size * glm::vec3(0, 0, 0), innerColor),
    };

    std::vector<unsigned int> indices = {  
        13,7,8,13,8,9,13,9,10,13,10,11,13,11,12,13,12,7,
        0,1,2,0,2,3,0,3,4,0,4,5,0,5,6,0,6,1
    
    };

    Mesh* hex = new Mesh(name);

    if (!fill) {
        hex->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        hex->SetDrawMode(GL_TRIANGLES);
    }

    hex->InitFromData(vertices, indices);
    return hex;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{
    int numPoints = 50;
    std::vector<VertexFormat> vertices;

    for (int i = 0; i < numPoints; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(numPoints - 1);
        float x = size * 16 * pow(sin(t * 2 * M_PI), 3);  // Adjusted for a full circle
        float y = size * (13 * cos(t * 2 * M_PI) - 5 * cos(2 * t * 2 * M_PI) - 2 * cos(3 * t * 2 * M_PI) - cos(4 * t * 2 * M_PI));

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices;

    


    float innerSize = 0.7;
    glm::vec3 diffColor = glm::vec3(0.3, 0.3, 0.3);


    for (int i = 0; i < numPoints; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(numPoints - 1);
        float x = size * 16 * pow(sin(t * 2 * M_PI), 3);  // Adjusted for a full circle
        float y = size * (13 * cos(t * 2 * M_PI) - 5 * cos(2 * t * 2 * M_PI) - 2 * cos(3 * t * 2 * M_PI) - cos(4 * t * 2 * M_PI));

        vertices.push_back(VertexFormat(innerSize * glm::vec3(x, y, 0), color - diffColor));
    }

    for (int i = 0; i < numPoints - 1; ++i) {
        indices.push_back(i + numPoints);
        indices.push_back(i + 1 + numPoints);
    }

    for (int i = 0; i < numPoints - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
    }


    heart->InitFromData(vertices, indices);

    if (!fill) {
        heart->SetDrawMode(GL_LINE_STRIP);
    }
    else {
        heart->SetDrawMode(GL_TRIANGLE_FAN);
    }

    return heart;
}

Mesh* object2D::CreateCannon(
    const std::string& name,
    float size,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 diffColor = glm::vec3(0.2, 0.2, 0.2);
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(size * glm::vec3(0, 0, 0), color),
        VertexFormat(size * glm::vec3(-1, 2, 0), color),
        VertexFormat(size * glm::vec3(-1, -2, 0), color),
        VertexFormat(size * glm::vec3(-2, 0, 0), color),
        VertexFormat(size * glm::vec3(-0.8, 0.5, 0), color - diffColor),
        VertexFormat(size * glm::vec3(1.7, 0.5, 0), color - diffColor),
        VertexFormat(size * glm::vec3(1.7, -0.5, 0), color - diffColor),
        VertexFormat(size * glm::vec3(-0.8, -0.5, 0), color - diffColor),
        VertexFormat(size * glm::vec3(1.4, 0.7, 0), color),
        VertexFormat(size * glm::vec3(2, 0.7, 0), color),
        VertexFormat(size * glm::vec3(2, -0.7, 0), color),
        VertexFormat(size * glm::vec3(1.4, -0.7, 0), color)
    };

    Mesh* cannon = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 2,1,3,8,9,10, 8,10,11, 6,5,4,6,4,7};

    cannon->InitFromData(vertices, indices);

    if (!fill) {
        cannon->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        cannon->SetDrawMode(GL_TRIANGLES);
    }

    cannon->InitFromData(vertices, indices);
    return cannon;
}
Mesh* object2D::CreateCoin(
    const std::string& name,
    float radius,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 diffColor = glm::vec3(0.4, 0.4, 0.4);

    int numPoints = 50;
    std::vector<VertexFormat> vertices;
    float innerSize = 0.7;


    for (int i = 0; i < numPoints; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(numPoints - 1);
        float angle = t * 2 * M_PI;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        vertices.push_back(VertexFormat(glm::vec3(x, y, 0), color));
    }

    for (int i = 0; i < numPoints; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(numPoints - 1);
        float angle = t * 2 * M_PI;
        float x = radius * cos(angle);
        float y = radius * sin(angle);

        vertices.push_back(VertexFormat(innerSize * glm::vec3(x, y, 0), color - diffColor));
    }

    Mesh* coin = new Mesh(name);
    std::vector<unsigned int> indices;

    for (int i = 0; i < numPoints - 1; ++i) {
        indices.push_back(i + numPoints);
        indices.push_back(i + 1 + numPoints);
    }

    for (int i = 0; i < numPoints - 1; ++i) {
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    coin->InitFromData(vertices, indices);

    if (!fill) {
        coin->SetDrawMode(GL_LINE_STRIP);
    }
    else {
        coin->SetDrawMode(GL_TRIANGLE_FAN);
    }

    return coin;
}
