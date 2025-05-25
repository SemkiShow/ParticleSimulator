#include "Object2D.hpp"
#include "UI.hpp"

bool gravity = true;
float gravityForce = 10;
float friction = 0.95;
int circlesCount = 1000;
std::vector<Object2D*> objects;
int threadsNumber = std::max(std::thread::hardware_concurrency(), (unsigned int)1);
int simulationSpeed = 0;

Object2D::~Object2D() {}

void Object2D::Init(double posX, double posY, double rotX, double rotY, double sclX, double sclY)
{
    position[0] = posX;
    position[1] = posY;
    rotation[0] = rotX;
    rotation[1] = rotY;
    scale[0] = sclX;
    scale[1] = sclY;
}

void Object2D::Move()
{
    position[0] += direction[0];
    position[1] += direction[1];
    if (gravity) position[1] += gravityForce;
    direction[0] *= friction;
    direction[1] *= friction;
}

void Object2D::Draw(sf::RenderWindow* window)
{
    std::cout << "Tried to run Object2D::Draw!\n";
}

void Object2D::CheckWallCollision()
{
    std::cout << "Tried to run Object2D::CheckWallCollision!\n";
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
    if (position[0] < 0) direction[0] = abs(direction[0]);
    if (position[1] - menuOffset < 0) direction[1] = abs(direction[1]);
    if (position[0] + scale[0] * 2 > windowSize[0]) direction[0] = -abs(direction[0]);
    if (position[1] + scale[0] * 2 > windowSize[1]) direction[1] = -abs(direction[1]) - (gravity ? gravityForce : 0);
}

void Collide(Object2D* object1, Object2D* object2)
{
    // Handle two Circles
    if (auto* a = dynamic_cast<Circle*>(object1); auto* b = dynamic_cast<Circle*>(object2))
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
    else
    {
        std::cout << "Tried to collide an unsupported type of Object2D!\n";
    }
}

void CleanObjects()
{
    for (int i = 0; i < objects.size(); i++)
        delete objects[i];
    objects.clear();
}

int circlesRanges[6];
void AddRandomCircles(sf::Color color)
{
    for (int i = 0; i < circlesCount; i++)
    {
        objects.push_back(new Circle());
        objects[i]->Init(rand() % (circlesRanges[1] - circlesRanges[0] + 1) + circlesRanges[0], 
            rand() % (circlesRanges[3] - circlesRanges[2] + 1) + circlesRanges[2], 0, 0, 
            rand() % (circlesRanges[5] - circlesRanges[4] + 1) + circlesRanges[4], 0);
        objects[i]->color = color;
    }
}

void DoPhysics(int threadID)
{
    for (int i = threadID * objects.size() / threadsNumber; i < (threadID + 1) * objects.size() / threadsNumber; i++)
    {
        objects[i]->Move();
        objects[i]->CheckWallCollision();
        for (int j = 0; j < i; j++)
        {
            Collide(objects[i], objects[j]);
        }
    }
}
