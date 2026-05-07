// ManesClient — crosshair.h
// Custom crosshair rendering via ImGui ForegroundDrawList
// Add  #include "crosshair.h"  at the top of menu.h
// Call RenderCustomCrosshair() inside BeginDraw() in the HUD overlay block.

#pragma once
#include "imgui/imgui.h"

// ── Crosshair state variables (declare extern in your globals header or here) ─
inline bool  customCrosshair      = false;
inline int   crosshairStyle       = 0;       // 0=Plus  1=X  2=Dot  3=Circle  4=Square  5=T-Shape
inline float crosshairSize        = 10.0f;
inline float crosshairThickness   = 2.0f;
inline float crosshairGap         = 3.0f;    // center gap
inline bool  crosshairDot         = false;
inline bool  crosshairOutline     = true;
inline float crosshairOutlineSize = 1.0f;
inline ImVec4 crosshairColor      = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
inline ImVec4 crosshairOutlineCol = ImVec4(0.00f, 0.00f, 0.00f, 0.80f);
inline bool  crosshairRainbow     = false;
inline float crosshairOpacity     = 1.0f;

// Style names for ImGui::Combo
static const char* CrosshairStyles[] = {
    "Plus (+)", "Cross (X)", "Dot", "Circle", "Square", "T-Shape"
};

// ── Internal rainbow state ─────────────────────────────────────────────────────
namespace CrosshairRGB {
    inline float hue = 0.0f;
    inline ImVec4 getColor() {
        float r, g, b;
        ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, r, g, b);
        return ImVec4(r, g, b, 1.0f);
    }
    inline void tick() { hue += 0.005f; if (hue > 1.0f) hue = 0.0f; }
}

// ── Main render call — put this in the HUD overlay section ────────────────────
inline void RenderCustomCrosshair() {
    if (!customCrosshair) return;

    ImDrawList* dl = ImGui::GetForegroundDrawList();
    ImGuiIO&    io = ImGui::GetIO();

    float cx = io.DisplaySize.x * 0.5f;
    float cy = io.DisplaySize.y * 0.5f;
    float s   = crosshairSize;
    float t   = crosshairThickness;
    float g   = crosshairGap;

    // Resolve colour (rainbow overrides color picker)
    ImVec4 cv = crosshairRainbow ? CrosshairRGB::getColor() : crosshairColor;
    cv.w     *= crosshairOpacity;
    ImU32 col  = ImGui::ColorConvertFloat4ToU32(cv);

    ImVec4 ocv = crosshairOutlineCol;
    ocv.w     *= crosshairOpacity;
    ImU32 ocol = ImGui::ColorConvertFloat4ToU32(ocv);

    float os = crosshairOutlineSize;  // outline stroke extra half-width

    // Helper lambdas
    auto line = [&](float x1, float y1, float x2, float y2) {
        if (crosshairOutline) dl->AddLine(ImVec2(x1,y1), ImVec2(x2,y2), ocol, t + os*2.0f);
        dl->AddLine(ImVec2(x1,y1), ImVec2(x2,y2), col, t);
    };

    switch (crosshairStyle) {

        // ── Plus ──────────────────────────────────────────────────────────
        case 0:
            line(cx - s, cy,     cx - g, cy);     // left
            line(cx + g, cy,     cx + s, cy);     // right
            line(cx,     cy - s, cx,     cy - g); // top
            line(cx,     cy + g, cx,     cy + s); // bottom
            break;

        // ── X cross ────────────────────────────────────────────────────────
        case 1: {
            float d = s * 0.707f;  // 45° projection
            float dg = g * 0.707f;
            line(cx-d, cy-d, cx-dg, cy-dg);
            line(cx+dg, cy+dg, cx+d, cy+d);
            line(cx+d, cy-d, cx+dg, cy-dg);
            line(cx-dg, cy+dg, cx-d, cy+d);
            break;
        }

        // ── Dot ────────────────────────────────────────────────────────────
        case 2:
            if (crosshairOutline) dl->AddCircleFilled(ImVec2(cx,cy), t + os*2, ocol);
            dl->AddCircleFilled(ImVec2(cx,cy), t, col);
            break;

        // ── Circle ─────────────────────────────────────────────────────────
        case 3:
            if (crosshairOutline) dl->AddCircle(ImVec2(cx,cy), s + os, ocol, 32, t + os);
            dl->AddCircle(ImVec2(cx,cy), s, col, 32, t);
            break;

        // ── Square ─────────────────────────────────────────────────────────
        case 4:
            if (crosshairOutline)
                dl->AddRect(ImVec2(cx-s-os, cy-s-os), ImVec2(cx+s+os, cy+s+os), ocol, 0, 0, t+os);
            dl->AddRect(ImVec2(cx-s, cy-s), ImVec2(cx+s, cy+s), col, 0, 0, t);
            break;

        // ── T-Shape ────────────────────────────────────────────────────────
        case 5:
            line(cx - s, cy,     cx + s, cy);     // horizontal
            line(cx,     cy + g, cx,     cy + s); // only bottom arm
            break;
    }

    // Optional center dot (shown for Plus and X styles)
    if (crosshairDot && (crosshairStyle == 0 || crosshairStyle == 1 || crosshairStyle == 5)) {
        if (crosshairOutline) dl->AddCircleFilled(ImVec2(cx,cy), t + os*2, ocol);
        dl->AddCircleFilled(ImVec2(cx,cy), t, col);
    }

    if (crosshairRainbow) CrosshairRGB::tick();
}

// ── ImGui panel — put this inside the UI tab (Visuals page) ──────────────────
// Usage:   DrawCrosshairPanel();
inline void DrawCrosshairPanel() {
    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.00f, 0.82f, 0.95f, 1.00f));
    ImGui::TextUnformatted("Crosshair");
    ImGui::PopStyleColor();
    ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(0.00f, 0.82f, 0.95f, 0.50f));
    ImGui::Separator();
    ImGui::PopStyleColor();
    ImGui::Spacing();

    ImGui::Checkbox(OBFUSCATE("Custom Crosshair"), &customCrosshair);
    if (!customCrosshair) return;

    ImGui::PushItemWidth(200.0f);
    ImGui::Combo(OBFUSCATE("Style"), &crosshairStyle, CrosshairStyles, IM_ARRAYSIZE(CrosshairStyles));
    ImGui::PopItemWidth();

    ImGui::PushItemWidth(300.0f);
    ImGui::SliderFloat(OBFUSCATE("Size"),      &crosshairSize,      1.0f,  40.0f, "%.0f");
    ImGui::SliderFloat(OBFUSCATE("Thickness"), &crosshairThickness, 0.5f,  8.0f,  "%.1f");
    if (crosshairStyle == 0 || crosshairStyle == 1 || crosshairStyle == 5) {
        ImGui::SliderFloat(OBFUSCATE("Gap"),   &crosshairGap,       0.0f,  20.0f, "%.0f");
    }
    ImGui::SliderFloat(OBFUSCATE("Opacity"),   &crosshairOpacity,   0.0f,  1.0f,  "%.2f");
    ImGui::PopItemWidth();

    ImGui::Spacing();

    // Color row
    ImGui::Checkbox(OBFUSCATE("Rainbow"), &crosshairRainbow);
    ImGui::SameLine();
    if (!crosshairRainbow) {
        ImGui::ColorEdit3(OBFUSCATE("Color##CH"),    (float*)&crosshairColor);
    } else {
        ImGui::TextDisabled(OBFUSCATE("(Rainbow active)"));
    }

    // Outline row
    ImGui::Checkbox(OBFUSCATE("Outline##CH"),        &crosshairOutline);
    if (crosshairOutline) {
        ImGui::SameLine();
        ImGui::ColorEdit3(OBFUSCATE("Outline Col##CH"), (float*)&crosshairOutlineCol);
        ImGui::PushItemWidth(200.0f);
        ImGui::SliderFloat(OBFUSCATE("Outline Width"), &crosshairOutlineSize, 0.5f, 4.0f, "%.1f");
        ImGui::PopItemWidth();
    }

    // Center dot option (only relevant for line-based styles)
    if (crosshairStyle == 0 || crosshairStyle == 1 || crosshairStyle == 5) {
        ImGui::Checkbox(OBFUSCATE("Center Dot##CH"), &crosshairDot);
    }

    // Live preview inside a child window
    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.50f, 0.50f, 0.50f, 1.00f));
    ImGui::TextUnformatted(OBFUSCATE("Preview (center of screen when menu is closed)"));
    ImGui::PopStyleColor();
}
