#ifndef DEMO_RENDERABLEOBJECT_H
#define DEMO_RENDERABLEOBJECT_H

#include <SFML/Graphics.hpp>

struct AppState;

struct RenderContext {
    sf::Vector2u windowSize;
    const AppState& state;
    float dtSeconds;
};

class RenderableObject {
  public:
    virtual ~RenderableObject() = default;
    virtual void Update(const RenderContext& context) = 0;
    virtual void Draw(sf::RenderTarget& target) = 0;
};

#endif // DEMO_RENDERABLEOBJECT_H
