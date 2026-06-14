#include "Window.h"

#include <algorithm>
#include <cstring>

#include "imgui.h"

Window::Window(const Config& config, std::vector<std::unique_ptr<RenderableObject>> objects, std::vector<std::string> logoNames) {

    _objects = std::move(objects);
    _logoNames = std::move(logoNames);

    _window.create(sf::VideoMode({config.windowWidth, config.windowHeight}), config.windowTitle);

    auto desktop = sf::VideoMode::getDesktopMode();
    _window.setPosition({static_cast<int>(desktop.size.x / 2 - config.windowWidth / 2), static_cast<int>(desktop.size.y / 2 - config.windowHeight / 2)});

    _window.setFramerateLimit(60);
    _window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(_window);

    _state.speedX = config.xLogoSpeed;
    _state.speedY = config.yLogoSpeed;
    _state.sizeMultiplier = config.sizeMultiplier;

    _state.logoColor[0] = config.logoColor[0];
    _state.logoColor[1] = config.logoColor[1];
    _state.logoColor[2] = config.logoColor[2];

    // TODO: че это такое?
    std::strncpy(_state.pauseText, config.pauseText.c_str(), sizeof(_state.pauseText) - 1);
    _state.pauseText[sizeof(_state.pauseText) - 1] = '\0';
}

Window::~Window() {
    ImGui::SFML::Shutdown();
}

void Window::Run() {
    while (_isRun && _window.isOpen()) {
        const float dtSeconds = _deltaClock.restart().asSeconds();

        // TODO: а это че такое (про секунды)?
        ImGui::SFML::Update(_window, sf::seconds(dtSeconds));
        UpdateUserInput();
        _ui.Draw(_state, _logoNames);
        UpdateLogic(dtSeconds);
        Render();

        _state.resetRequested = false;
    }
}

void Window::UpdateUserInput() {
    while (const std::optional event = _window.pollEvent()) {
        ImGui::SFML::ProcessEvent(_window, *event);

        if (event->is<sf::Event::Closed>()) {
            _isRun = false;
            _window.close();
            return;
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::Space) {
                _state.paused = !_state.paused;
            }
        }
    }
}

void Window::UpdateLogic(float dtSeconds) {
    RenderContext context{_window.getSize(), _state, dtSeconds};
    for (const auto& object : _objects) {
        object->Update(context);
    }
}

void Window::Render() {
    _window.clear(sf::Color::Black);

    for (const auto& object : _objects) {
        object->Draw(_window);
    }

    ImGui::SFML::Render(_window);
    _window.display();
}
