#include "PauseTextObject.h"

#include "../AppState/AppState.h"

PauseTextObject::PauseTextObject(const std::filesystem::path& fontPath) : _text(_font, "Pause", 56) {
    bool loaded = _font.openFromFile(fontPath);
    if (!loaded) {
        loaded = _font.openFromFile(std::filesystem::path("..") / fontPath);
    }
    if (loaded) {
        _text.setFont(_font);
    }
    _text.setFillColor(sf::Color::White);
}

void PauseTextObject::Update(const RenderContext& context) {
    _visible = context.state.paused;
    _text.setString(context.state.pauseText);

    const auto bounds = _text.getGlobalBounds();
    const float x = (static_cast<float>(context.windowSize.x) - bounds.size.x) * 0.5f;
    const float y = (static_cast<float>(context.windowSize.y) - bounds.size.y) * 0.5f;
    _text.setPosition({x, y});
}

void PauseTextObject::Draw(sf::RenderTarget& target) {
    if (_visible) {
        target.draw(_text);
    }
}
