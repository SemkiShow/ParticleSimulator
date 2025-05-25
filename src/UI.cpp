#include "UI.hpp"
#include "Settings.hpp"
#include "Object2D.hpp"

bool isSettings = true;
int menuOffset = 20;
int windowSize[2] = {16*50*2, 9*50*2};

void ShowSettings(bool* isOpen)
{
    if (!ImGui::Begin("Settings", isOpen))
    {
        ImGui::End();
        return;
    }
    ImGui::Checkbox("vsync", &settings.verticalSync);
    ImGui::Checkbox("show-fps", &settings.showFPS);
    ImGui::Checkbox("gravity", &gravity);
    ImGui::SliderFloat("gravity-force", &gravityForce, 0, 100);
    ImGui::SliderFloat("friction", &friction, 0, 1);
    if (ImGui::TreeNode("circles"))
    {
        ImGui::SliderInt("circles-count", &circlesCount, 0, 10000);

        ImGui::SliderInt2("circles-position-x-range", &circlesRanges[0], 0, windowSize[0]);
        ImGui::SliderInt2("circles-position-y-range", &circlesRanges[2], 0, windowSize[1]);
        ImGui::SliderInt2("circles-size-range", &circlesRanges[4], 1, 10);
        
        ImGui::TreePop();
    }
    ImGui::SliderInt("simulation-speed", &simulationSpeed, 0, 1000);
    ImGui::End();
}

void ShowMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            if (ImGui::MenuItem("Restart"))
            {
                CleanObjects();
                AddRandomCircles();
            }
            if (ImGui::MenuItem("Settings"))
            {
                isSettings = true;
                ShowSettings(&isSettings);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
    return;
}
