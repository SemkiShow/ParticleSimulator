#include "Settings.hpp"
#include "UI.hpp"
#include "Object2D.hpp"

Settings settings;

std::vector<std::string> Split(std::string input, char delimiter = ' ')
{
    std::vector<std::string> output;
    output.push_back("");
    int index = 0;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == delimiter)
        {
            index++;
            output.push_back("");
            continue;
        }
        output[index] += input[i];
    }
    return output;
}

void Settings::Save(std::string fileName)
{
    // Read the file
    std::fstream settingsFile;
    settingsFile.open(fileName, std::ios::out);
    settingsFile << "vsync=" << (verticalSync ? "true" : "false") << '\n';
    settingsFile << "show-fps=" << (showFPS ? "true" : "false") << '\n';
    settingsFile << "gravity=" << (gravity ? "true" : "false") << '\n';
    settingsFile << "gravity-force=" << gravityForce << '\n';
    settingsFile << "friction=" << friction << '\n';
    settingsFile << "circles-count=" << circlesCount << '\n';
    settingsFile << "simulation-speed=" << simulationSpeed << '\n';
    settingsFile.close();
}

void Settings::Load(std::string fileName)
{
    // Read the file
    std::fstream settingsFile;
    settingsFile.open(fileName, std::ios::in);
    std::vector<std::string> settingsList;
    std::string buf;
    while (std::getline(settingsFile, buf))
        settingsList.push_back(buf);
    settingsFile.close();

    // Process the file
    verticalSync = settingsList[0].substr(6) == "true";
    showFPS = settingsList[1].substr(9) == "true";
    gravity = settingsList[2].substr(8) == "true";
    gravityForce = stof(settingsList[3].substr(14));
    friction = stof(settingsList[4].substr(9));
    circlesCount = stoi(settingsList[5].substr(14));
    simulationSpeed = stoi(settingsList[6].substr(17));
}
