#include "UiController.h"

#include "imgui.h"

void UiController::Draw(AppState& state, const std::vector<std::string>& logoNames) {
    ImGui::Begin("Settings");

    if (!logoNames.empty()) {
        if (state.selectedLogoIndex < 0) {
            state.selectedLogoIndex = 0;
        }
        if (state.selectedLogoIndex >= static_cast<int>(logoNames.size())) {
            state.selectedLogoIndex = static_cast<int>(logoNames.size()) - 1;
        }

        const char* current = logoNames[state.selectedLogoIndex].c_str();
        if (ImGui::BeginCombo("Logo", current)) {
            for (int i = 0; i < static_cast<int>(logoNames.size()); ++i) {
                const bool isSelected = i == state.selectedLogoIndex;
                if (ImGui::Selectable(logoNames[i].c_str(), isSelected)) {
                    state.selectedLogoIndex = i;
                }
                if (isSelected) {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
    }

    ImGui::DragFloat("Speed X", &state.speedX, 1.0f, 1.0f, 2000.0f, "%.1f");
    ImGui::DragFloat("Speed Y", &state.speedY, 1.0f, 1.0f, 2000.0f, "%.1f");
    ImGui::DragFloat("Size Multiplier", &state.sizeMultiplier, 0.01f, 0.1f, 10.0f, "%.2f");
    ImGui::ColorEdit3("Logo Color", state.logoColor);

    if (ImGui::Button("Reset Position")) {
        state.resetRequested = true;
    }

    ImGui::InputText("Pause Text", state.pauseText, sizeof(state.pauseText));
    ImGui::Text("Space: pause/resume");

    ImGui::End();

    state.Clamp();
}
