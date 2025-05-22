#include "Object2D.hpp"
#include "UI.hpp"

bool gravity = true;
float gravityForce = 10;
float friction = 0.95;
int circlesCount = 1000;
std::vector<Circle> circles;
int threadsNumber = std::max(std::thread::hardware_concurrency(), (unsigned int)1);
// int threadsNumber = 1;

void Object2D::Init(double posX, double posY, double rotX, double rotY, double sclX, double sclY)
{
    position[0] = posX;
    position[1] = posY;
    rotation[0] = rotX;
    rotation[1] = rotY;
    scale[0] = sclX;
    scale[1] = sclY;
}

void Object2D::Move(sf::Time deltaTime)
{
    position[0] += direction[0] * deltaTime.asSeconds();
    position[1] += direction[1] * deltaTime.asSeconds();
    if (gravity) position[1] += gravityForce * deltaTime.asSeconds();
    direction[0] *= friction;
    direction[1] *= friction;
}

void Circle::Draw(sf::RenderWindow* window)
{
    sf::CircleShape circle(scale[0]);
    circle.setPosition({(float)position[0], (float)position[1]});
    circle.setFillColor(color);
    window->draw(circle);
}

void Circle::CheckWallCollision()
{
    if (position[0] < 0) direction[0] += gravityForce;
    if (position[1] - menuOffset < 0) direction[1] += gravityForce;
    if (position[0] + scale[0] * 2 > windowSize[0]) direction[0] -= gravityForce;
    if (position[1] + scale[0] * 2 > windowSize[1]) direction[1] -= gravityForce;

    // if (position[0] - scale[0] * 2 < 0) position[0] = scale[0] * 2;
    // if (position[1] - menuOffset - scale[0] * 2 < 0) position[1] = scale[0] * 2 + menuOffset;
    // if (position[0] + scale[0] * 2 > windowSize[0]) position[0] = windowSize[0] - scale[0] * 2;
    // if (position[1] + scale[0] * 2 > windowSize[1]) position[1] = windowSize[1] - scale[0] * 2;
}

void Collide(Circle* a, Circle* b)
{
    // Calculate collision based on the Pythagorean theorem
    bool isColliding = sqrt(pow(abs(a->position[0] - b->position[0]), 2) + pow(abs(a->position[1] - b->position[1]), 2)) < a->scale[0] + b->scale[0];
    if (isColliding)
    {
        a->direction[0] += (a->position[0] - b->position[0] - a->scale[0] - b->scale[0]) / 2;
        a->direction[1] += (a->position[1] - b->position[1] - a->scale[0] - b->scale[0]) / 2;
        b->direction[0] -= (a->position[0] - b->position[0] - a->scale[0] - b->scale[0]) / 2;
        b->direction[1] -= (a->position[1] - b->position[1] - a->scale[0] - b->scale[0]) / 2;
    }
}

void AddRandomCircles(sf::Color color)
{
    circles.clear();
    for (int i = 0; i < circlesCount; i++)
    {
        circles.push_back(Circle());
        circles[i].Init(rand() % windowSize[0], rand() % windowSize[1], 0, 0, rand() % 10, 0);
        circles[i].color = color;
    }
}

void DoPhysics(int threadID, sf::Time deltaTime)
{
    for (int i = threadID * circles.size() / threadsNumber; i < (threadID + 1) * circles.size() / threadsNumber; i++)
    {
        circles[i].Move(deltaTime);
        circles[i].CheckWallCollision();
        for (int j = 0; j < i; j++)
        {
            Collide(&circles[i], &circles[j]);
        }
    }
}
