#include "Window/Window.h"
#include <SFML/Window.hpp>
#include <iostream>

const int W_WIDTH = 1280;
const int W_HEIGHT = 720;

const int RECTANGLE_WIDTH = 100;
const int RECTANGLE_HEIGHT = 100;

const int X_RECTANLE_SPEED = 10;
const int Y_RECTANLE_SPEED = 10;

int xSpeedSign = 1;
int ySpeedSign = 1;
int proceed = 1;

void processInput(sf::Window& window) {
    while (const auto event = window.pollEvent()) {
        if (event->getIf<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* pressedKey = event->getIf<sf::Event::KeyPressed>()) {
            if (pressedKey->code == sf::Keyboard::Key::R) {
                xSpeedSign = -xSpeedSign;
                ySpeedSign = -ySpeedSign;
            }

            if (pressedKey->code == sf::Keyboard::Key::Space) {
                if (proceed == 1) {
                    proceed = 0;
                } else {
                    proceed = 1;
                }
            }
        }
    }
}

std::vector<float> processRectangle(sf::RectangleShape& rectangle) {
    const auto rectangleSizes = rectangle.getGlobalBounds().size;
    const float width = rectangleSizes.x;
    const float height = rectangleSizes.y;

    const auto position = rectangle.getPosition();
    const float x = position.x;
    const float y = position.y;

    const float rightRectangleBound = x + width;
    const float leftRectangleBound = x;
    const float topRectangleBound = y;
    const float bottomRectangleBound = y + height;

    // x
    if (rightRectangleBound >= W_WIDTH) {
        xSpeedSign = -1;
    }
    if (leftRectangleBound <= 0) {
        xSpeedSign = 1;
    }

    // y
    if (bottomRectangleBound >= W_HEIGHT) {
        ySpeedSign = -1;
    }
    if (topRectangleBound <= 0) {
        ySpeedSign = 1;
    }

    const float nextX = x + X_RECTANLE_SPEED * xSpeedSign * proceed;
    const float nextY = y + Y_RECTANLE_SPEED * ySpeedSign * proceed;

    return std::vector{nextX, nextY};
}

int main() {
    setlocale(LC_ALL, "");

    sf::RenderWindow window(sf::VideoMode({W_WIDTH, W_HEIGHT}), "Test window");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    auto rectangleShape = sf::RectangleShape({RECTANGLE_WIDTH, RECTANGLE_HEIGHT});

    while (window.isOpen()) {
        processInput(window);

        window.clear(sf::Color::Black);

        const auto nextRectanglePosition = processRectangle(rectangleShape);

        rectangleShape.setFillColor(sf::Color::Red);
        rectangleShape.setPosition({nextRectanglePosition[0], nextRectanglePosition[1]});

        window.draw(rectangleShape);
        window.display();
    }

    // Window window(wWidth, wHeight);
    // window.Run();

    return 0;
}