#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include "imgui-SFML.h"
#include "UI.hpp"
#include "Settings.hpp"
#include "Object2D.hpp"

int main()
{
    settings.Load("settings.txt");

    // SFML init
    sf::RenderWindow window(sf::VideoMode({(unsigned int)windowSize[0], (unsigned int)windowSize[1]}), "Particle Simulator");
    window.setFramerateLimit(0);
    
    // ImGUI init
    (void) ImGui::SFML::Init(window);

    if (settings.verticalSync)
        window.setVerticalSyncEnabled(true);
    else
        window.setVerticalSyncEnabled(false);

    sf::Font font("assets/JetBrainsMonoNerdFont-Medium.ttf");
    sf::Text FPS(font);
    FPS.setPosition({0, menuOffset * 1.f});
    FPS.setString(std::to_string(123));
    FPS.setFillColor(sf::Color(0, 255, 255));
    FPS.setCharacterSize(24);
    srand(time(0));

    // Add objects
    AddRandomCircles();

    sf::Clock deltaTimeClock;
    sf::Time deltaTime;
    sf::Clock delayClock;
    bool lastVSync = settings.verticalSync;
    int lastCirclesCount = circlesCount;

    // Main loop
    while (window.isOpen())
    {
        deltaTime = deltaTimeClock.restart();
        ImGui::SFML::Update(window, deltaTime);

        while (const auto event = window.pollEvent())
        {
            ImGui::SFML::ProcessEvent(window, *event);
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        ShowMenuBar();
        if (isSettings) ShowSettings(&isSettings);

        // Physics iteration
        std::vector<std::thread> threads;
        for (int i = 0; i < threadsNumber; i++)
            threads.emplace_back([&]{DoPhysics(i, deltaTime);});
        for (int i = 0; i < threadsNumber; i++)
            threads[i].join();

        window.clear();
        
        for (int i = 0; i < circles.size(); i++)
        {
            circles[i].Draw(&window);
        }
        
        if (delayClock.getElapsedTime().asSeconds() >= 0.3)
        {
            delayClock.restart();
            FPS.setString("FPS: " + std::to_string(1 / deltaTime.asSeconds()));
            
            if (lastVSync != settings.verticalSync)
            {
                lastVSync = settings.verticalSync;
                if (settings.verticalSync)
                    window.setVerticalSyncEnabled(true);
                else
                    window.setVerticalSyncEnabled(false);
            }
            if (lastCirclesCount != circlesCount)
            {
                lastCirclesCount = circlesCount;
                AddRandomCircles();
            }
        }
        if (settings.showFPS) window.draw(FPS);

        ImGui::SFML::Render(window);
        window.display();
    }

    settings.Save("settings.txt");
    ImGui::SFML::Shutdown();
}
