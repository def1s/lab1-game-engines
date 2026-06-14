#include "ConfigReader.h"

#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

ConfigReader::ConfigReader(std::string configPath)
    : _configPath(std::move(configPath)) {}

Config ConfigReader::ReadConfig() const {
    std::ifstream file(_configPath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open config file: " + _configPath);
    }

    nlohmann::json j;
    file >> j;

    Config cfg;
    cfg.windowWidth = j.value("windowWidth", cfg.windowWidth);
    cfg.windowHeight = j.value("windowHeight", cfg.windowHeight);
    cfg.windowTitle = j.value("windowTitle", cfg.windowTitle);
    cfg.fontsPath = j.value("fontsPath", cfg.fontsPath);
    cfg.logoPaths = j.value("logoPaths", cfg.logoPaths);
    cfg.xLogoSpeed = j.value("xLogoSpeed", cfg.xLogoSpeed);
    cfg.yLogoSpeed = j.value("yLogoSpeed", cfg.yLogoSpeed);
    cfg.sizeMultiplier = j.value("sizeMultiplier", cfg.sizeMultiplier);
    cfg.pauseText = j.value("pauseText", cfg.pauseText);

    if (j.contains("logoColor") && j["logoColor"].is_array() && j["logoColor"].size() >= 3) {
        cfg.logoColor[0] = j["logoColor"][0].get<float>();
        cfg.logoColor[1] = j["logoColor"][1].get<float>();
        cfg.logoColor[2] = j["logoColor"][2].get<float>();
    }

    return cfg;
}
