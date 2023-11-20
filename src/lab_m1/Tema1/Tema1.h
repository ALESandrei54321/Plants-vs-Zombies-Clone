#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"
//#include "lab_m1/Tema1/Entity.h"


namespace m1
{

    class Entity {
    public:
        Entity(float initialHealth, Mesh* initialMesh, bool isFriend)
            : health(initialHealth), mesh(initialMesh), friendEntity(isFriend) {}

        Entity(float initialHealth, Mesh* initialMesh, glm::vec2 position, int color, int line ,bool isFriend)
            : health(initialHealth), mesh(initialMesh), position(position), color(color), line(line), friendEntity(isFriend) {}


        // Getters and setters
        float GetHealth() const { return health; }
        void SetHealth(float newHealth) { health = newHealth; }

        const glm::vec2& GetPosition() const { return position; }
        void SetPosition(const glm::vec2& newPosition) { position = newPosition; }

        Mesh* GetMesh() const { return mesh; }
        void SetMesh(Mesh* newMesh) { mesh = newMesh; }

        bool IsFriend() const { return friendEntity; }
        void SetFriend(bool isFriend) { friendEntity = isFriend; }

        float GetDeathCounter() const { return deathCounter; }
        void SetDeathCounter(float newDeath) { deathCounter = newDeath; }

        float GetDist() const { return dist; }
        void SetDist(float newdist) { dist = newdist; }

        float GetCooldown() const { return fireCooldown; }
        void SetCooldown(float cooldown) { fireCooldown = cooldown; }

        int GetColor() const { return color; }
        void SetColor(int newcolor) { color = newcolor; }

        int GetLine() const { return line; }
        void SetLine(int newline) { line = newline; }

        float GetRadius() const { return collisionRdius; }
        void SetRadius(float rad) { collisionRdius = rad; }

        float GetCollisionTimer() const { return collisionTimer; }
        void SetCollisionTimer(float time) { collisionTimer = time; }

        glm::mat3 Animate(float deltaTime) {

            if (GetHealth() <= 0) {
                modelMatrix = glm::mat3(1);
                glm::vec2 pos = GetPosition();
                modelMatrix *= transform2D::Translate(pos.x, pos.y);
                modelMatrix *= transform2D::Scale(deathCounter, deathCounter);
                deathCounter -= deltaTime;
                return modelMatrix;
            }
            else {
                modelMatrix = glm::mat3(1);
                glm::vec2 pos = GetPosition();
                modelMatrix *= transform2D::Translate(pos.x, pos.y);
                return modelMatrix;
            }
        }

    private:
        glm::mat3 modelMatrix;
        float health;
        glm::vec2 position;
        Mesh* mesh;
        float deathCounter = 1;
        float dist = 70;
        int color;
        int line;
        float fireCooldown = 0;
        bool friendEntity;
        float collisionRdius = 30;
        float collisionTimer = 0;
    };

    class Hexagon : public Entity {
    public:
        Hexagon(float initialHealth, Mesh* initialMesh, bool isFriend)
            : Entity(initialHealth, initialMesh, isFriend) {}

        Hexagon(float initialHealth, Mesh* initialMesh, glm::vec2 position, int color, int line, bool isFriend)
            : Entity(initialHealth, initialMesh, position, color, line, isFriend) {}

        // Override the Animate method for hexagons
        glm::mat3 Animate(float deltaTime) {
            
            if (GetHealth() <= 0) {
                modelMatrix = glm::mat3(1);
                glm::vec2 pos = GetPosition();
                modelMatrix *= transform2D::Translate(pos.x, pos.y);
                modelMatrix *= transform2D::Scale(GetDeathCounter(), GetDeathCounter());
                SetDeathCounter(GetDeathCounter() - deltaTime);
                return modelMatrix;
            }
            else {
                modelMatrix = glm::mat3(1);
                glm::vec2 pos = GetPosition() - glm::vec2(GetDist() * deltaTime, 0);
                modelMatrix *= transform2D::Translate(pos.x, pos.y);
                SetPosition(pos);
                return modelMatrix;
            }

        }

        // Add any other methods or member variables specific to Hexagon

    private:
        // Add any specific member variables for Hexagon
        glm::mat3 modelMatrix;
    };

    class Collectible : public Entity {
    public:
        Collectible(float initialHealth, Mesh* initialMesh, bool isFriend)
            : Entity(initialHealth, initialMesh, isFriend) {}

        Collectible(float initialHealth, Mesh* initialMesh, glm::vec2 position, int color, int line, bool isFriend)
            : Entity(initialHealth, initialMesh, position, color, line, isFriend) {}

        // Override the Animate method for hexagons
        glm::mat3 Animate(float deltaTime) {
            modelMatrix = glm::mat3(1);
            glm::vec2 pos = GetPosition();
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            return modelMatrix;
        }

        // Add any other methods or member variables specific to Hexagon

    private:
        // Add any specific member variables for Hexagon
        glm::mat3 modelMatrix;
    };

    class Projectile : public Entity {
    public:
        Projectile(float initialHealth, Mesh* initialMesh, bool isFriend)
            : Entity(initialHealth, initialMesh, isFriend) {}

        Projectile(float initialHealth, Mesh* initialMesh, glm::vec2 position, int color, int line, bool isFriend)
            : Entity(initialHealth, initialMesh, position, color, line, isFriend) {}

        // Override the Animate method for hexagons
        glm::mat3 Animate(float deltaTime) {

            
            modelMatrix = glm::mat3(1);
            glm::vec2 pos = GetPosition() + glm::vec2(GetDist() * deltaTime * 5, 0);
            rotation += deltaTime;
            modelMatrix *= transform2D::Translate(pos.x, pos.y);
            modelMatrix *= transform2D::Rotate(-5 * rotation);
            SetPosition(pos);
            return modelMatrix;

        }

        // Add any other methods or member variables specific to Hexagon

    private:
        // Add any specific member variables for Hexagon
        glm::mat3 modelMatrix;
        float rotation = 0;
    };

    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        void LoadMap(float deltaTime, int lives, int star_count);
        void PlaceCannon(int row, int col, int cannonColor);
        void CheckCollisionCannon(Entity& entity1,Entity& entity2, float deltaTime);
        void CheckCollisionProjectile(Entity& entity1, Entity& entity2, float deltaTime);
        bool CheckForEnemy(int row, int col);
     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;
        bool ok;
        bool direction;
        float rotation = 0;
        bool moveRight;
        float dist = 0;
        std::vector<std::vector<Entity>> cannonGrid;
        glm::ivec2 currentMousePosition;
        int lives = 3;
        int coins = 10;
        bool dragging = false;
        int dragedObj = -1;
        std::vector<std::string> cannonColors = { "orange", "blue", "yellow", "purple" };
        std::vector<int> cannonCosts = { 1, 2, 2, 3 };

        float hexagonSpawnTimer = 0;
        std::vector<Hexagon> hexagons;
        std::vector<Projectile> projectiles;
        std::vector<Collectible> collectibles;
        float collectibleSpawnTimer = 7;


        // TODO(student): If you need any other class variables, define them here.

    };
    

}   // namespace m1
