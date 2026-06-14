#ifndef DEMO_UICONTROLLER_H
#define DEMO_UICONTROLLER_H

#include <string>
#include <vector>

#include "../AppState/AppState.h"

class UiController {
  public:
    void Draw(AppState& state, const std::vector<std::string>& logoNames);
};

#endif // DEMO_UICONTROLLER_H
