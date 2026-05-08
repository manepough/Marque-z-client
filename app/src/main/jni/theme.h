// ManesClient — theme.h
// Dynamic theme / accent color picker.
// Call Theme::apply() once before BeginDraw() to push the style.
// All MANES_ACCENT references are replaced by Theme::accent.

#pragma once
#include "imgui/imgui.h"

namespace Theme {

    // ── Accent colors (user-selectable presets + custom) ─────────────────
    inline ImVec4 accent     = ImVec4(0.00f, 0.82f, 0.95f, 1.00f); // default cyan
    inline ImVec4 accent50   = ImVec4(0.00f, 0.82f, 0.95f, 0.50f);
    inline ImVec4 dim        = ImVec4(0.30f, 0.38f, 0.48f, 1.00f);

    inline bool   rainbowTheme  = false;
    inline float  rainbowHue    = 0.0f;
    inline int    presetIndex   = 0;
    inline bool   useCustom     = false;
    inline ImVec4 customColor   = ImVec4(0.00f, 0.82f, 0.95f, 1.00f);

    struct Preset { const char* name; ImVec4 color; };
    inline Preset presets[] = {
        { "Cyan (default)",  ImVec4(0.00f, 0.82f, 0.95f, 1.00f) },
        { "Purple",          ImVec4(0.60f, 0.20f, 0.95f, 1.00f) },
        { "Green",           ImVec4(0.10f, 0.90f, 0.30f, 1.00f) },
        { "Pink",            ImVec4(0.95f, 0.30f, 0.70f, 1.00f) },
        { "Orange",          ImVec4(0.95f, 0.55f, 0.05f, 1.00f) },
        { "Red",             ImVec4(0.90f, 0.15f, 0.15f, 1.00f) },
        { "White",           ImVec4(0.90f, 0.90f, 0.90f, 1.00f) },
        { "Gold",            ImVec4(1.00f, 0.84f, 0.00f, 1.00f) },
    };
    inline const int presetCount = IM_ARRAYSIZE(presets);

    // Call once per frame before ImGui::NewFrame to update rainbow tick
    inline void tick() {
        if (rainbowTheme) {
            rainbowHue += 0.003f;
            if (rainbowHue > 1.0f) rainbowHue = 0.0f;
            float r, g, b;
            ImGui::ColorConvertHSVtoRGB(rainbowHue, 0.85f, 1.0f, r, g, b);
            accent   = ImVec4(r, g, b, 1.00f);
            accent50 = ImVec4(r, g, b, 0.50f);
        } else if (useCustom) {
            accent   = ImVec4(customColor.x, customColor.y, customColor.z, 1.00f);
            accent50 = ImVec4(customColor.x, customColor.y, customColor.z, 0.50f);
        } else {
            accent   = presets[presetIndex].color;
            accent50 = ImVec4(accent.x, accent.y, accent.z, 0.50f);
        }
    }

    // Apply accent to ImGui style — call before your windows
    inline void apply(ImGuiStyle& style) {
        style.Colors[ImGuiCol_CheckMark]        = accent;
        style.Colors[ImGuiCol_SliderGrab]        = accent;
        style.Colors[ImGuiCol_SliderGrabActive]  = ImVec4(accent.x*0.8f, accent.y*0.8f, accent.z*0.8f, 1.0f);
        style.Colors[ImGuiCol_SeparatorHovered]  = accent50;
        style.Colors[ImGuiCol_TabActive]         = ImVec4(accent.x*0.3f, accent.y*0.3f, accent.z*0.3f, 0.8f);
        style.Colors[ImGuiCol_TabHovered]        = ImVec4(accent.x*0.2f, accent.y*0.2f, accent.z*0.2f, 0.6f);
        style.Colors[ImGuiCol_HeaderHovered]     = ImVec4(accent.x*0.2f, accent.y*0.2f, accent.z*0.2f, 0.5f);
        style.Colors[ImGuiCol_HeaderActive]      = ImVec4(accent.x*0.3f, accent.y*0.3f, accent.z*0.3f, 0.8f);
        style.Colors[ImGuiCol_FrameBgHovered]    = ImVec4(accent.x*0.1f, accent.y*0.1f, accent.z*0.1f, 0.4f);
    }

    inline void DrawPanel() {
        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Text, accent);
        ImGui::TextUnformatted(OBFUSCATE("Theme"));
        ImGui::PopStyleColor();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Checkbox(OBFUSCATE("Rainbow Theme"), &rainbowTheme);
        if (rainbowTheme) {
            ImGui::TextDisabled(OBFUSCATE("Rainbow active — overrides presets"));
            return;
        }

        ImGui::Checkbox(OBFUSCATE("Custom Color##theme"), &useCustom);
        if (useCustom) {
            ImGui::ColorEdit3(OBFUSCATE("##customThemeCol"), (float*)&customColor);
            return;
        }

        // Preset grid
        ImGui::Spacing();
        ImGui::TextDisabled(OBFUSCATE("Presets:"));
        for (int i = 0; i < presetCount; i++) {
            bool selected = (presetIndex == i);
            ImVec4 c = presets[i].color;
            ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(c.x*0.3f, c.y*0.3f, c.z*0.3f, selected ? 0.9f : 0.4f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(c.x*0.5f, c.y*0.5f, c.z*0.5f, 0.8f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(c.x*0.7f, c.y*0.7f, c.z*0.7f, 1.0f));
            if (selected) {
                ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);
                ImGui::PushStyleColor(ImGuiCol_Border, c);
            }
            if (ImGui::Button(OBFUSCATE(presets[i].name), ImVec2(130.0f, 0))) {
                presetIndex = i;
                useCustom = false;
            }
            if (selected) { ImGui::PopStyleVar(); ImGui::PopStyleColor(); }
            ImGui::PopStyleColor(3);

            if ((i % 2) == 0) ImGui::SameLine();
        }
    }
}
