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
    settingsFile << "circles-ranges=" << circlesRanges[0] << ',' << circlesRanges[1] 
        << ',' << circlesRanges[2] << ',' << circlesRanges[3] 
        << ',' << circlesRanges[4] << ',' << circlesRanges[5] << '\n';
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
    std::vector<std::string> circlesRangesVector = Split(settingsList[6].substr(15), ',');
    circlesRanges[0] = circlesRangesVector[0] == "MAX" ? windowSize[0] : stoi(circlesRangesVector[0]);
    circlesRanges[1] = circlesRangesVector[1] == "MAX" ? windowSize[0] : stoi(circlesRangesVector[1]);
    circlesRanges[2] = circlesRangesVector[2] == "MAX" ? windowSize[1] : stoi(circlesRangesVector[2]);
    circlesRanges[3] = circlesRangesVector[3] == "MAX" ? windowSize[1] : stoi(circlesRangesVector[3]);
    circlesRanges[4] = stoi(circlesRangesVector[4]);
    circlesRanges[5] = stoi(circlesRangesVector[5]);
    simulationSpeed = stoi(settingsList[7].substr(17));
}
