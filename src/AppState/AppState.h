#ifndef DEMO_APPSTATE_H
#define DEMO_APPSTATE_H

#include <algorithm>

struct AppState {
    int selectedLogoIndex = 0;
    float speedX = 180.0f;
    float speedY = 180.0f;
    float sizeMultiplier = 1.0f;
    float logoColor[3] = {1.0f, 1.0f, 1.0f};

    bool paused = false;
    // TODO: все же лучше заюзать строку
    char pauseText[255] = "Pause";

    bool resetRequested = false;

    void Clamp() {
        speedX = std::max(1.0f, speedX);
        speedY = std::max(1.0f, speedY);
        sizeMultiplier = std::clamp(sizeMultiplier, 0.1f, 10.0f);
        logoColor[0] = std::clamp(logoColor[0], 0.0f, 1.0f);
        logoColor[1] = std::clamp(logoColor[1], 0.0f, 1.0f);
        logoColor[2] = std::clamp(logoColor[2], 0.0f, 1.0f);
    }
};

#endif // DEMO_APPSTATE_H
