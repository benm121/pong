#include "ui.h"

namespace ui {

void drawScore(uint32_t score, float xPos, float yPos) {

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::SetNextWindowPos({xPos, yPos}, ImGuiCond_Always);
    ImGui::SetNextWindowSize({100.0f, 20.0f});
    ImGui::SetNextWindowBgAlpha(0.0f);

    ImGui::Begin("Fixed Numbers", nullptr, 
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


