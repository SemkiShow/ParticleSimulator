#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "UI.hpp"

class Object2D
{
    public:
        void Init(double posX, double posY, double rotX, double rotY, double sclX, double sclY);
        double position[2];
        double rotation[2];
        double scale[2];
        sf::Color color = sf::Color(255, 255, 255);
};

class Circle: public Object2D
{
    public:
        void Draw(sf::RenderWindow* window);
        void CheckWallColision();
};

void Collide(Circle* a, Circle* b);
