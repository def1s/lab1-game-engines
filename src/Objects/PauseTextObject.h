#ifndef DEMO_PAUSETEXTOBJECT_H
#define DEMO_PAUSETEXTOBJECT_H

#include <filesystem>

#include "../RenderableObject/RenderableObject.h"

class PauseTextObject : public RenderableObject {
  public:
    explicit PauseTextObject(const std::filesystem::path& fontPath);

    void Update(const RenderContext& context) override;
    void Draw(sf::RenderTarget& target) override;

  private:
    sf::Font _font;
    sf::Text _text;
    bool _visible = false;
};

#endif // DEMO_PAUSETEXTOBJECT_H
