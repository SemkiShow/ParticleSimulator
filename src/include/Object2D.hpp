#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

extern bool gravity;
extern float gravityForce;
extern float friction;

class Object2D
{
    public:
    void Init(double posX, double posY, double rotX, double rotY, double sclX, double sclY);
    double position[2] = {0, 0};
    double rotation[2] = {0, 0};
    double scale[2] = {0, 0};
    double direction[2] = {0, 0};
    sf::Color color = sf::Color(255, 255, 255);
    void Move(sf::Time deltaTime);
};

class Circle: public Object2D
{
    public:
    void Draw(sf::RenderWindow* window);
    void CheckWallCollision();
};
extern int circlesCount;
extern std::vector<Circle> circles;

void Collide(Circle* a, Circle* b);
void AddRandomCircles(sf::Color color = sf::Color(255, 255, 255));
