#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <thread>

extern bool gravity;
extern float gravityForce;
extern float friction;
extern int threadsNumber;
extern int simulationSpeed;

class Object2D
{
    public:
    virtual ~Object2D();
    void Init(double posX, double posY, double rotX, double rotY, double sclX, double sclY);
    double position[2] = {0, 0};
    double rotation[2] = {0, 0};
    double scale[2] = {0, 0};
    double direction[2] = {0, 0};
    sf::Color color = sf::Color(255, 255, 255);
    void Move();
    virtual void Draw(sf::RenderWindow* window);
    virtual void CheckWallCollision();
};
extern std::vector<Object2D*> objects;

class Circle: public Object2D
{
    public:
    void Draw(sf::RenderWindow* window) override;
    void CheckWallCollision() override;
};
extern int circlesCount;

void Collide(Object2D* object1, Object2D* object2);
void CleanObjects();

extern int circlesPositionXRange[2];
extern int circlesPositionYRange[2];
extern int circlesSizeRange[2];
void AddRandomCircles(sf::Color color = sf::Color(255, 255, 255));

void DoPhysics(int threadID);
