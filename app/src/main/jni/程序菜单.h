#include "imgui_custom.h"

static bool switchyuri = false;
static bool hudInitialized = false;

void MainMenu() {
    if (!hudInitialized) {
        Custom::HUD::InitHUDData();
        hudInitialized = true;
    }
    Custom::HUD::RenderHUD(ImGui::GetBackgroundDrawList(), ImGui::GetIO().DisplaySize, 1.0f);

    ImGui::SetNextWindowPos(ImVec2((ImGui::GetIO().DisplaySize.x - 620) * 0.5f, (ImGui::GetIO().DisplaySize.y - 650) * 0.5f));
    ImGui::SetNextWindowSize(ImVec2(620, 650));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 24.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.1f, 0.1f, 0.1f, 0.98f));

    if (ImGui::Begin("Hello, world!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar)) {
        static int tab = 0;
        ImVec2 mainWindowPos = ImGui::GetWindowPos();
        ImVec2 mainWindowSize = ImGui::GetWindowSize();
        ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x, mainWindowPos.y));
        ImGui::SetNextWindowSize(ImVec2(mainWindowSize.x, 80));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 24.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        if (ImGui::BeginChild("TopChild", ImVec2(mainWindowSize.x, 80), true, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            ImDrawList* draw_list = ImGui::GetWindowDrawList();
            ImVec2 p_min = ImGui::GetWindowPos();
            ImVec2 p_max = ImVec2(p_min.x + mainWindowSize.x, p_min.y + 80);
            draw_list->AddRectFilled(p_min, p_max, ImGui::GetColorU32(ImVec4(0.15f, 0.15f, 0.15f, 1.0f)), 24.0f, ImDrawFlags_RoundCornersTop);
            ImVec2 topChildSize = ImGui::GetWindowSize();
            ImGui::SetWindowFontScale(1.8f);
            ImVec2 textSize = ImGui::CalcTextSize("WowSOSO");
            ImVec2 versionSize = ImGui::CalcTextSize("testVersion");
            float textPosX = 36.0f;
            float textPosY = (topChildSize.y - ImGui::GetTextLineHeight()) * 0.5f;
            ImGui::SetCursorPos(ImVec2(textPosX, textPosY));
            ImGui::PushStyleColor(ImGuiCol_Text, Custom::Colors::accent);
            ImGui::Text("W");
            ImGui::PopStyleColor();
            ImGui::SameLine(0, 0);
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
            ImGui::Text("uriEngine");
            ImGui::PopStyleColor();
            float versionPosX = topChildSize.x - 36.0f - versionSize.x;
            ImGui::SameLine(0, versionPosX - textPosX - textSize.x);
            ImGui::PushStyleColor(ImGuiCol_Text, Custom::Colors::accent);
            ImGui::Text("test");
            ImGui::PopStyleColor();
            ImGui::SetWindowFontScale(1.0f);
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);

        float contentMargin = 20.0f;
        float contentTop = mainWindowPos.y + 80 + contentMargin;
        float contentBottom = mainWindowPos.y + mainWindowSize.y - 80 - contentMargin;
        float contentHeight = contentBottom - contentTop;
        float contentWidth = mainWindowSize.x - 2 * contentMargin;

        ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x + contentMargin, contentTop));
        ImGui::SetNextWindowSize(ImVec2(contentWidth, contentHeight));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));

        if (ImGui::BeginChild("ContentArea", ImVec2(contentWidth, contentHeight), true, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar)) {
            switch(tab) {
                case 0:
                {
                    float horizontalSpacing = 20.0f;
                    float verticalSpacing = 5.0f;
                    float availableWidth = contentWidth - horizontalSpacing;
                    float leftWidth = availableWidth * 0.5f;
                    float rightWidth = availableWidth * 0.5f;
                    float leftChildHeight = (contentHeight - verticalSpacing) * 0.5f;
                    ImGui::BeginGroup();
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
                    if (ImGui::BeginChild("Child1", ImVec2(leftWidth, leftChildHeight), true, ImGuiWindowFlags_NoScrollbar)) {
                        static bool hudEnabled = true;
                        if (Custom::Switch("Show HUD", &hudEnabled)) {
                        }
                        Custom::Switch("Switch", &switchyuri);
                        ImGui::EndChild();
                    }
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar(2);
                    ImGui::Dummy(ImVec2(0, 0));
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
                    if (ImGui::BeginChild("Child3", ImVec2(leftWidth, leftChildHeight), true, ImGuiWindowFlags_NoScrollbar)) {
                        ImGui::Text("Yuri | 尤里");
                        ImGui::Text("Mail:3413266371@qq.com");
                        ImGui::EndChild();
                    }
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar(2);
                    ImGui::EndGroup();
                    ImGui::SameLine(0, horizontalSpacing);
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
                    ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
                    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
                    if (ImGui::BeginChild("Child2", ImVec2(rightWidth, contentHeight), true, ImGuiWindowFlags_NoScrollbar)) {
                        auto& modules = Custom::HUD::GetModules();
                        for (auto& mod : modules) {
                            bool enabled = mod.enabled;
                            if (Custom::Switch(mod.name.c_str(), &enabled)) {
                                mod.enabled = enabled;
                            }
                        }
                        ImGui::EndChild();
                    }
                    ImGui::PopStyleColor();
                    ImGui::PopStyleVar(2);
                    break;
                }

                case 1:
                break;
                
                case 2:
                break;
                
                case 3:
                break;
            }
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
        ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x + 20, mainWindowPos.y + mainWindowSize.y - 80));
        ImGui::SetNextWindowSize(ImVec2(280, 60));
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.12f, 0.12f, 0.12f, 1.0f));
        if (ImGui::BeginChild("BottomLeftChild", ImVec2(280, 60), true, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize)) {
            ImVec2 childSize = ImGui::GetWindowSize();
            float tabHeight = 45.0f;
            float centerY = (childSize.y - tabHeight) * 0.5f;
            ImGui::SetCursorPos(ImVec2(20, centerY));
            if (Custom::Tab("I", "Tab 1", tab == 0, ImVec2(-6.0f, 0.0f))) tab = 0;
            ImGui::SameLine(0, 15);
            if (Custom::Tab("P", "Tab 2", tab == 1, ImVec2(-2.0f, 0.0f))) tab = 1;
            ImGui::SameLine(0, 15);
            if (Custom::Tab("R", "Tab 3", tab == 2, ImVec2(-2.0f, 0.0f))) tab = 2;
            ImGui::SameLine(0, 15);
            if (Custom::Tab("D", "Tab 4", tab == 3, ImVec2(-2.0f, 2.0f))) tab = 3;
            ImGui::EndChild();
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleVar(2);
        ImGui::End();
    }
    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);
}

/*
 * 作者: Yuri | 尤里
 * 邮箱: 3413266371@qq.com
 * 版本: Pc没有弄完
 */