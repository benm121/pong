#include "ui.h"
#include "global.h"

namespace ui {

void drawMenu(MenuFunc spFunc, MenuFunc mpFunc, MenuFunc quitFunc) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static constexpr float buttonWidth = 300.0f;
    static constexpr float buttonHeight = 50.0f;
    static constexpr float spacingAmount = 20.0f;

    ImGui::SetNextWindowPos({global::SCREEN_WIDTH * 0.5f, global::SCREEN_HEIGHT * 0.5f},
                            ImGuiCond_Always,
                            ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize({500.0f, 600.0f});
    ImGui::SetNextWindowBgAlpha(0.8f);

    ImGui::Begin("Main Menu", nullptr,
                  ImGuiWindowFlags_NoDecoration |
                  ImGuiWindowFlags_NoMove |
                  ImGuiWindowFlags_NoSavedSettings);

    ImGui::Dummy({0.0f, spacingAmount * 2.0f});
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - ImGui::CalcTextSize("Pong").x) * 0.5f);  // Center the title
    ImGui::Text("Pong");

    ImGui::Dummy({0.0f, spacingAmount * 2.0f});
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);
    if (ImGui::Button("Single Player", {buttonWidth, buttonHeight})) {
        spFunc();
    }

    ImGui::Dummy({0.0f, spacingAmount});
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);
    if (ImGui::Button("Multi Player", {buttonWidth, buttonHeight})) {
        mpFunc();
    }

    ImGui::Dummy({0.0f, spacingAmount});
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);
    static bool showControlsDialog = false;
    if (ImGui::Button("Controls", {buttonWidth, buttonHeight})) {
        showControlsDialog = true;
    }

    if (showControlsDialog) {
        ImGui::OpenPopup("Controls");
        showControlsDialog = false;
    }

    if (ImGui::BeginPopupModal("Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove)) {
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Text("Player 1: W/S to move up/down");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Text("Player 2: Up/Down arrows to move up/down");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        ImGui::Text("Press ESC to return to the menu");
        ImGui::Spacing();
        ImGui::Spacing();
        ImGui::Spacing();

        if (ImGui::Button("Close", {120.0f, 30.0f})) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::Dummy({0.0f, spacingAmount});
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonWidth) * 0.5f);
    if (ImGui::Button("Quit", ImVec2(buttonWidth, buttonHeight))) {
        quitFunc();
    }

    ImGui::End();
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void drawScore(uint32_t score, float xPos, float yPos) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos({xPos, yPos}, ImGuiCond_Always);
    ImGui::SetNextWindowSize({100.0f, 20.0f});
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin("Score", nullptr,
                  ImGuiWindowFlags_NoDecoration |
                  ImGuiWindowFlags_NoMove |
                  ImGuiWindowFlags_NoSavedSettings |
                  ImGuiWindowFlags_NoInputs);
    ImGui::Text("%d", score);
    ImGui::End();
    ImGui::EndFrame();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

} // namespace ui


