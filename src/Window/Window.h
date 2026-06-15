#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#include "imgui-SFML.h"

#include "../AppState/AppState.h"
#include "../ConfigReader/ConfigReader.h"
#include "../RenderableObject/RenderableObject.h"
#include "../UI/UiController.h"

class Window {
  private:
    sf::RenderWindow _window;
    sf::Clock _deltaClock;
    bool _isRun = true;

    AppState _state;
    UiController _ui;

    std::vector<std::string> _logoNames;
    std::vector<std::unique_ptr<RenderableObject>> _objects;

    void UpdateUserInput();
    void UpdateLogic(float dtSeconds);
    void Render();

  public:
    Window(const Config& config, std::vector<std::string> logoNames);
    ~Window();

    void AddObject(std::unique_ptr<RenderableObject> object);
    void Run();
};

#endif // WINDOW_H
