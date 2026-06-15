#ifndef DEMO_CONFIGREADER_H
#define DEMO_CONFIGREADER_H

#include <string>
#include <vector>

struct Config {
    unsigned int windowWidth = 1280;
    unsigned int windowHeight = 720;
    std::string windowTitle = "Lab1";

    std::string fontsPath = "fonts/futura.ttf";
    std::vector<std::string> logoPaths;

    float xLogoSpeed = 180.0f;
    float yLogoSpeed = 180.0f;
    float sizeMultiplier = 0.35f;
    float logoColor[3] = {1.0f, 1.0f, 1.0f};

    std::string pauseText = "Пауза";
};

class ConfigReader {
  private:
    std::string _configPath;

  public:
    explicit ConfigReader(std::string configPath);
    Config ReadConfig() const;
};

#endif // DEMO_CONFIGREADER_H
