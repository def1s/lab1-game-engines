#include "LogoObject.h"

#include <algorithm>

#include "../AppState/AppState.h"

LogoObject::LogoObject(std::vector<std::string> logoPaths) {
    _textures.reserve(logoPaths.size());

    for (const auto& path : logoPaths) {
        sf::Texture texture;
        if (texture.loadFromFile(path)) {
            _textures.push_back(std::move(texture));
        }
    }

    _hasAnyTexture = !_textures.empty();
    if (_hasAnyTexture) {
        _sprite.emplace(_textures[0]);
        _sprite->setPosition(_position);
    } else {
        _fallback.setSize({220.0f, 90.0f});
        _fallback.setPosition(_position);
        _fallback.setFillColor(sf::Color::White);
    }
}

void LogoObject::ApplySelectedTexture(int selectedIndex) {
    if (!_hasAnyTexture) {
        return;
    }

    if (selectedIndex < 0) {
        selectedIndex = 0;
    }
    if (selectedIndex >= static_cast<int>(_textures.size())) {
        selectedIndex = static_cast<int>(_textures.size()) - 1;
    }

    if (_activeIndex != selectedIndex) {
        _activeIndex = selectedIndex;
        _sprite.emplace(_textures[_activeIndex]);
        _sprite->setPosition(_position);
    }
}

sf::Vector2f LogoObject::GetCurrentSize() const {
    if (_hasAnyTexture) {
        return _sprite->getGlobalBounds().size;
    }
    return _fallback.getGlobalBounds().size;
}

void LogoObject::ResetPosition(const sf::Vector2u& windowSize) {
    const auto size = GetCurrentSize();
    _position.x = (static_cast<float>(windowSize.x) - size.x) * 0.5f;
    _position.y = (static_cast<float>(windowSize.y) - size.y) * 0.5f;
}

void LogoObject::Update(const RenderContext& context) {
    _visible = !context.state.paused;

    if (_hasAnyTexture) {
        ApplySelectedTexture(context.state.selectedLogoIndex);
    }

    const sf::Vector2f scale = {context.state.sizeMultiplier, context.state.sizeMultiplier};
    if (_hasAnyTexture) {
        _sprite->setScale(scale);
    } else {
        _fallback.setScale(scale);
    }

    const sf::Color tint(static_cast<std::uint8_t>(context.state.logoColor[0] * 255.0f),
        static_cast<std::uint8_t>(context.state.logoColor[1] * 255.0f),
        static_cast<std::uint8_t>(context.state.logoColor[2] * 255.0f));
    if (_hasAnyTexture) {
        _sprite->setColor(tint);
    } else {
        _fallback.setFillColor(tint);
    }

    if (context.state.resetRequested) {
        ResetPosition(context.windowSize);
    }

    if (!context.state.paused) {
        _position.x += context.state.speedX * _velocitySign.x * context.dtSeconds;
        _position.y += context.state.speedY * _velocitySign.y * context.dtSeconds;
    }

    const auto size = GetCurrentSize();

    if (_position.x <= 0.0f) {
        _position.x = 0.0f;
        _velocitySign.x = 1.0f;
    }
    if (_position.x + size.x >= static_cast<float>(context.windowSize.x)) {
        _position.x = static_cast<float>(context.windowSize.x) - size.x;
        _velocitySign.x = -1.0f;
    }

    if (_position.y <= 0.0f) {
        _position.y = 0.0f;
        _velocitySign.y = 1.0f;
    }
    if (_position.y + size.y >= static_cast<float>(context.windowSize.y)) {
        _position.y = static_cast<float>(context.windowSize.y) - size.y;
        _velocitySign.y = -1.0f;
    }

    if (_hasAnyTexture) {
        _sprite->setPosition(_position);
    } else {
        _fallback.setPosition(_position);
    }
}

void LogoObject::Draw(sf::RenderTarget& target) {
    if (!_visible) {
        return;
    }

    if (_hasAnyTexture) {
        target.draw(*_sprite);
    } else {
        target.draw(_fallback);
    }
}
