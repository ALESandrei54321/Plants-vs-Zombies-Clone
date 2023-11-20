#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

void Tema1::LoadMap(float deltaTime, int lives, int star_count) {
    // Define an array of cannon colors in the desired order
    


    if (dragging == true && dragedObj != -1) {

        std::string cannonColor = "cannon_" + cannonColors[dragedObj];

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(currentMousePosition.x, 720 - currentMousePosition.y);
        RenderMesh2D(meshes[cannonColor], shaders["VertexColor"], modelMatrix);
    }

    for (int i = 0; i < projectiles.size(); i++) {
        RenderMesh2D(projectiles[i].GetMesh(), shaders["VertexColor"], projectiles[i].Animate(deltaTime));
    }

    for (int i = 0; i < hexagons.size(); i++) {
        RenderMesh2D(hexagons[i].GetMesh(), shaders["VertexColor"], hexagons[i].Animate(deltaTime));
    }

    for (int i = 0; i < collectibles.size(); i++) {
        modelMatrix = collectibles[i].Animate(deltaTime);
        RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["star_coin"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(collectibles[i].GetMesh(), shaders["VertexColor"], modelMatrix);
        
    }




    for (int i = 0; i < lives; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(820 + 105 * i, 650);
        RenderMesh2D(meshes["heart"], shaders["VertexColor"], modelMatrix);
    }


    int aux_count = 0;
    int aux_line = 0;
    for (int i = 0; i < star_count; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(790 + 40 * (i % 10) + (aux_line % 2) * 20, 650 - 90 - aux_line * 20);
        RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["star_coin"], shaders["VertexColor"], modelMatrix);

        aux_count++;
        if (aux_count >= 10) {
            aux_count = 0;
            aux_line++;
        }
    }

    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100 + i * 190, 650);

        // Use the cannon color based on the current iteration
        std::string cannonColor = "cannon_" + cannonColors[i];

        RenderMesh2D(meshes["square_gray"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes[cannonColor], shaders["VertexColor"], modelMatrix);

        for (int j = 0; j < cannonCosts[i]; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(60 + i * 190 + j * 40, 650 - 90);
            RenderMesh2D(meshes["star_gray"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["star_coin"], shaders["VertexColor"], modelMatrix);
        }
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 250);
    modelMatrix *= transform2D::Scale(0.5, 4);
    RenderMesh2D(meshes["square_red"], shaders["VertexColor"], modelMatrix);


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {


            if (cannonGrid[i][j].GetMesh() != nullptr) {
                /*modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(180 + i * 160, 100 + j * 150);
                RenderMesh2D(cannonGrid[i][j].GetMesh(), shaders["VertexColor"], modelMatrix);*/
                RenderMesh2D(cannonGrid[i][j].GetMesh(), shaders["VertexColor"], cannonGrid[i][j].Animate(deltaTime));
                
            }


            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(180 + i * 160, 100 + j * 150);
            RenderMesh2D(meshes["square_green"], shaders["VertexColor"], modelMatrix);
        }
    }


    





}


void Tema1::PlaceCannon(int row, int col, int cannonColor)
{
    // Check if the position is valid
    if (row >= 0 && row < 3 && col >= 0 && col < 3 && (cannonGrid[row][col].GetMesh() == nullptr)) {
        // Create a new cannon entity and set it in the grid
        cannonGrid[row][col] = Entity(1, meshes["cannon_" + cannonColors[cannonColor]], glm::vec2(180 + row * 160, 100 + col * 150), cannonColor, row, true);
        cannonGrid[row][col].SetPosition(glm::vec2(180 + row * 160, 100 + col * 150));
    }
}

bool Tema1::CheckForEnemy(int row, int col) {

    for (int i = 0; i < hexagons.size(); i++) {
        
        if (hexagons[i].GetLine() == col && hexagons[i].GetColor() == cannonGrid[row][col].GetColor())
            return true;
        
    }
    return false;


}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);



    Mesh* square;
    square = object2D::CreateCenteredSquare("square_green", 60, glm::vec3(0, 1, 0));
    AddMeshToList(square);
    square = object2D::CreateCenteredSquare("square_gray", 60, glm::vec3(0.37, 0.37, 0.37), false);
    AddMeshToList(square);
    square = object2D::CreateCenteredSquare("square_red", 60, glm::vec3(1, 0, 0));
    AddMeshToList(square);

    Mesh* star;
    star = object2D::CreateStar("star_orange", 3, glm::vec3(1, 0.5, 0));
    AddMeshToList(star);
    star = object2D::CreateStar("star_blue", 3, glm::vec3(0, 0, 1));
    AddMeshToList(star);
    star = object2D::CreateStar("star_yellow", 3, glm::vec3(1, 1, 0));
    AddMeshToList(star);
    star = object2D::CreateStar("star_purple", 3, glm::vec3(0.5, 0, 1));
    AddMeshToList(star);
    star = object2D::CreateStar("star_point", 5, glm::vec3(1, 0, 1));
    AddMeshToList(star);
    star = object2D::CreateStar("star_gray", 1.5, glm::vec3(0.37, 0.37, 0.37));
    AddMeshToList(star);
    star = object2D::CreateCoin("star_coin", 20, glm::vec3(1, 1, 0));
    AddMeshToList(star);

    Mesh* hex;
    hex = object2D::CreateHex("hex_orange", 10, glm::vec3(1, 0.5, 0));
    AddMeshToList(hex);
    hex = object2D::CreateHex("hex_blue", 10, glm::vec3(0, 0, 1));
    AddMeshToList(hex);
    hex = object2D::CreateHex("hex_yellow", 10, glm::vec3(1, 1, 0));
    AddMeshToList(hex);
    hex = object2D::CreateHex("hex_purple", 10, glm::vec3(0.5, 0, 1));
    AddMeshToList(hex);

    Mesh* heart = object2D::CreateHeart("heart", 3, glm::vec3(1, 0, 0));
    AddMeshToList(heart);

    Mesh* cannon; 
    cannon = object2D::CreateCannon("cannon_orange", 28, glm::vec3(1, 0.5, 0));
    AddMeshToList(cannon);
    cannon = object2D::CreateCannon("cannon_blue", 28, glm::vec3(0, 0, 1));
    AddMeshToList(cannon);
    cannon = object2D::CreateCannon("cannon_yellow", 28, glm::vec3(1, 1, 0));
    AddMeshToList(cannon);
    cannon = object2D::CreateCannon("cannon_purple", 28, glm::vec3(0.5, 0, 1));
    AddMeshToList(cannon);

    cannonGrid.resize(3, std::vector<Entity>(3, Entity(0.0f, nullptr, true)));


}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{  


    if (collectibleSpawnTimer > 0) {
        collectibleSpawnTimer -= deltaTimeSeconds;
    } else {
        collectibleSpawnTimer = 7;
        if (collectibles.size() == 0) {
            for (int i = 0; i < 3; i++) {
                glm::vec2 pos = glm::vec2(std::rand() % window->GetResolution().x, std::rand() % window->GetResolution().y);
                Collectible newpoint(1, meshes["star_point"],pos,0,0,true);
                collectibles.push_back(newpoint);
            }
            
        }
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (cannonGrid[i][j].GetDeathCounter() <= 0) {
                cannonGrid[i][j].SetMesh(nullptr);
            }

            if (cannonGrid[i][j].GetCollisionTimer() > 0) {
                cannonGrid[i][j].SetCollisionTimer(cannonGrid[i][j].GetCollisionTimer() - deltaTimeSeconds);
            }

            if (cannonGrid[i][j].GetCooldown() > 0) {
                cannonGrid[i][j].SetCooldown(cannonGrid[i][j].GetCooldown() - deltaTimeSeconds);
            }

            if (cannonGrid[i][j].GetHealth() > 0 && CheckForEnemy(i, j) == true && cannonGrid[i][j].GetCooldown() <= 0) {
                Projectile newproj(1, meshes["star_" + cannonColors[cannonGrid[i][j].GetColor()]], cannonGrid[i][j].GetPosition() + glm::vec2(50,0), cannonGrid[i][j].GetColor(), i, true);
                projectiles.push_back(newproj);
                cannonGrid[i][j].SetCooldown(2);
            }

        }
    }


    for (int i = 0; i < hexagons.size(); i++) {
        if (hexagons[i].GetDeathCounter() <= 0 || hexagons[i].GetPosition().x < 50) {
            if (hexagons[i].GetPosition().x < 50 && hexagons[i].GetCollisionTimer() <= 0) {
                hexagons[i].SetCollisionTimer(100);
                lives = max(lives - 1, 0);
            }
            hexagons.erase(hexagons.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].GetHealth() <= 0 || projectiles[i].GetPosition().x > window->GetResolution().x) {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }




    for (int i = 0; i < hexagons.size(); i++) {
        if (hexagons[i].GetCollisionTimer() > 0) {
            hexagons[i].SetCollisionTimer(hexagons[i].GetCollisionTimer() - deltaTimeSeconds);
        }
    }


    hexagonSpawnTimer -= deltaTimeSeconds;

    // Spawn a new hexagon
    if (hexagonSpawnTimer < 0 && lives != 0) {

        int randColor = std::rand() % 4;
        int randLine = std::rand() % 3;


        std::string hexColor = "hex_" + cannonColors[randColor];

        Hexagon newHexagon(3, meshes[hexColor], glm::vec2(window->GetResolution().x, 100 + randLine * 150), randColor, randLine, false);
        hexagons.push_back(newHexagon);


        // Reset the timer
        hexagonSpawnTimer = std::rand() % 8 + 2;
    }


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < hexagons.size(); k++) {
                if (cannonGrid[i][j].GetMesh() != nullptr) {
                    CheckCollisionCannon(cannonGrid[i][j], hexagons[k], deltaTimeSeconds);
                }
                
            }
        }
    }

    for (int i = 0; i < projectiles.size(); i++) {
        for (int k = 0; k < hexagons.size(); k++) {
            CheckCollisionProjectile(projectiles[i], hexagons[k], deltaTimeSeconds);
        }
    }

    if (lives <= 0) {
        exit(EXIT_SUCCESS);
    }


    LoadMap(deltaTimeSeconds, lives, coins);
}

void Tema1::CheckCollisionCannon(Entity& entity1,Entity& entity2, float deltaTime) {

    glm::vec2 pos1 = entity1.GetPosition();
    glm::vec2 pos2 = entity2.GetPosition();
    float distance = glm::distance(pos1, pos2);
    float sumRadii = entity1.GetRadius() + entity2.GetRadius();

    // Check for collision
    if (distance <= sumRadii) {

        if (entity1.IsFriend() != entity2.IsFriend() && entity1.GetCollisionTimer() <= 0 && entity1.GetHealth() > 0 && entity2.GetHealth() > 0) {
            entity1.SetHealth(entity1.GetHealth() - 1);
            entity2.SetCollisionTimer(0.1);
            entity2.SetCollisionTimer(0.1);
        }
    }
}

void Tema1::CheckCollisionProjectile(Entity& entity1, Entity& entity2, float deltaTime) {

    glm::vec2 pos1 = entity1.GetPosition();
    glm::vec2 pos2 = entity2.GetPosition();
    float distance = glm::distance(pos1, pos2);
    float sumRadii = entity1.GetRadius() + entity2.GetRadius();

    // Check for collision
    if (distance <= sumRadii) {

        if (entity1.IsFriend() != entity2.IsFriend() && entity1.GetCollisionTimer() <= 0 && entity2.GetCollisionTimer() <= 0 && entity1.GetColor() == entity2.GetColor() && entity1.GetHealth() > 0 && entity2.GetHealth() > 0) {
            entity1.SetHealth(entity1.GetHealth() - 1);
            entity2.SetHealth(entity2.GetHealth() - 1);
            entity2.SetCollisionTimer(0.1);
            entity2.SetCollisionTimer(0.1);
        }
    }
}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    currentMousePosition.x = mouseX;
    currentMousePosition.y = mouseY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    int sceneX = mouseX;
    int sceneY = 720 - mouseY;

    for (int i = 0; i < collectibles.size(); i++) {
        glm::vec2 pos = collectibles[i].GetPosition();
        float leftLim = pos.x - 30;
        float rightLim = pos.x + 30;
        float topLim = pos.y + 30;
        float botLim = pos.y - 30;
        if (sceneX >= leftLim && sceneX <= rightLim &&
            sceneY >= botLim && sceneY <= topLim) {
            coins++;
            collectibles.erase(collectibles.begin() + i);
            i--;
            return;
        }
    }

    if (button == 2) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float squareCenterX = 180 + i * 160;
                float squareCenterY = 100 + j * 150;
                float squareSize = 60;
                float leftLim = squareCenterX - squareSize;
                float rightLim = squareCenterX + squareSize;
                float topLim = squareCenterY + squareSize;
                float botLim = squareCenterY - squareSize;

               // Check if the mouse is within the bounds of the current square
                if (sceneX >= leftLim && sceneX <= rightLim &&
                   sceneY >= botLim && sceneY <= topLim) {
                    // Handle click inside the square

                    // For example, print a message indicating which square was clicked

                    if (cannonGrid[i][j].GetMesh() != nullptr) {
                    cannonGrid[i][j].SetHealth(0);
                    }
    

                   break; // Break the loop once a square is clicked
                }
            }
        }
    }
    

    
    for (int i = 0; i < 4; i++) {
        // Calculate the bounds of the square

        float squareCenterX = 100 + i * 190;
        float squareCenterY = 650;
        float squareSize = 60;
        float leftLim = squareCenterX - squareSize;  //  100 + i * 190, 650
        float rightLim = squareCenterX + squareSize;
        float topLim = squareCenterY + squareSize;
        float botLim = squareCenterY - squareSize;

        // Check if the mouse is within the bounds of the current square
        if (sceneX >= leftLim && sceneX <= rightLim &&
            sceneY >= botLim && sceneY <= topLim) {

            dragging = true;
            dragedObj = i;

            break; // Break the loop once a square is clicked
        }
    }


}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event

    int sceneX = mouseX;
    int sceneY = 720 - mouseY;


    if (dragging && dragedObj != -1) {

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                float squareCenterX = 180 + i * 160;
                float squareCenterY = 100 + j * 150;
                float squareSize = 60;
                float leftLim = squareCenterX - squareSize;
                float rightLim = squareCenterX + squareSize;
                float topLim = squareCenterY + squareSize;
                float botLim = squareCenterY - squareSize;

                // Check if the mouse is within the bounds of the current square
                if (sceneX >= leftLim && sceneX <= rightLim &&
                    sceneY >= botLim && sceneY <= topLim) {

                    if (coins >= cannonCosts[dragedObj] && cannonGrid[i][j].GetMesh() == nullptr) {
                        coins -= cannonCosts[dragedObj];
                        PlaceCannon(i, j, dragedObj);
                    }


                    break; // Break the loop once a square is clicked
                }
            }
        }

    }

    dragging = false;
    dragedObj = -1;
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
