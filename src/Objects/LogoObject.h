#ifndef DEMO_LOGOOBJECT_H
#define DEMO_LOGOOBJECT_H

#include <filesystem>
#include <optional>
#include <string>
#include <vector>

#include "../RenderableObject/RenderableObject.h"

class LogoObject : public RenderableObject {
  public:
    explicit LogoObject(std::vector<std::string> logoPaths);

    void Update(const RenderContext& context) override;
    void Draw(sf::RenderTarget& target) override;

  private:
    std::vector<sf::Texture> _textures;
    std::optional<sf::Sprite> _sprite;
    sf::RectangleShape _fallback;

    sf::Vector2f _velocitySign = {1.0f, 1.0f};
    sf::Vector2f _position = {100.0f, 100.0f};

    bool _hasAnyTexture = false;
    bool _visible = true;
    int _activeIndex = 0;

    void ApplySelectedTexture(int selectedIndex);
    void ResetPosition(const sf::Vector2u& windowSize);
    sf::Vector2f GetCurrentSize() const;
};

#endif // DEMO_LOGOOBJECT_H
