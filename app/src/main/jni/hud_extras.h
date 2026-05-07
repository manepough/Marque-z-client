// ManesClient — hud_extras.h
// Reach display HUD + per-entity health bars drawn above ESP boxes
// Call HudExtras::renderHUD()  in your HUD overlay (outside menu)
// Call HudExtras::renderHealthBars() alongside RenderESP()

#pragma once
#include "imgui/imgui.h"

namespace HudExtras {

    // ── Reach display ─────────────────────────────────────────────────────
    inline bool  showReach        = false;
    inline float reachOffsetX     = 0.0f;
    inline float reachOffsetY     = 80.0f;
    inline float currentBlockReach = 4.5f;   // updated from your BlockReach patch
    inline float currentAttackReach = 3.0f;  // updated from your killAura range var

    // ── Health bars ───────────────────────────────────────────────────────
    inline bool  espHealthBars    = false;
    inline bool  healthNumbers    = true;     // show "12.5 / 20" text
    inline bool  healthColorScale = true;     // green→yellow→red based on HP
    inline float barWidth         = 40.0f;
    inline float barHeight        = 5.0f;

    // Color helper: green → yellow → red based on health fraction
    inline ImU32 healthColor(float fraction) {
        fraction = ImClamp(fraction, 0.0f, 1.0f);
        float r, g, b;
        if (fraction > 0.5f) {
            // green to yellow
            float t = (1.0f - fraction) * 2.0f;
            r = t; g = 1.0f; b = 0.0f;
        } else {
            // yellow to red
            float t = fraction * 2.0f;
            r = 1.0f; g = t; b = 0.0f;
        }
        return IM_COL32((int)(r*255), (int)(g*255), (int)(b*255), 220);
    }

    // Called every HUD frame (pass your killaura range & blockreach patch value)
    inline void renderHUD(float attackRange, float blockRange) {
        if (!showReach) return;

        ImGuiIO& io = ImGui::GetIO();
        float cx = io.DisplaySize.x * 0.5f + reachOffsetX;
        float cy = io.DisplaySize.y * 0.5f + reachOffsetY;

        char buf[64];
        snprintf(buf, sizeof(buf), OBFUSCATE("ATK: %.1f  BLK: %.1f"), attackRange, blockRange);

        ImDrawList* dl = ImGui::GetForegroundDrawList();
        ImVec2 textSize = ImGui::CalcTextSize(buf);
        float px = cx - textSize.x * 0.5f;
        float py = cy;

        // Shadow
        dl->AddText(ImVec2(px+1, py+1), IM_COL32(0,0,0,180), buf);
        // Text (cyan accent)
        dl->AddText(ImVec2(px, py), IM_COL32(0, 209, 242, 255), buf);
    }

    // Called alongside RenderESP — draws health bars above each actor's box
    // actors: your actor list with world->screen position already projected
    // For each actor pass: screen top-center X/Y, current HP, max HP, name
    inline void renderHealthBar(ImDrawList* dl,
                                 float screenX, float screenY,
                                 float hp, float maxHp,
                                 const char* name = nullptr)
    {
        if (!espHealthBars || !dl) return;
        if (maxHp <= 0.0f) return;

        float fraction = hp / maxHp;
        float bx = screenX - barWidth * 0.5f;
        float by = screenY - barHeight - 4.0f;

        // Background
        dl->AddRectFilled(ImVec2(bx-1, by-1),
                          ImVec2(bx + barWidth + 1, by + barHeight + 1),
                          IM_COL32(0,0,0,160), 2.0f);
        // Fill
        ImU32 col = healthColorScale
                  ? healthColor(fraction)
                  : IM_COL32(80, 255, 80, 220);
        dl->AddRectFilled(ImVec2(bx, by),
                          ImVec2(bx + barWidth * fraction, by + barHeight),
                          col, 2.0f);
        // Border
        dl->AddRect(ImVec2(bx, by),
                    ImVec2(bx + barWidth, by + barHeight),
                    IM_COL32(255,255,255,60), 2.0f, 0, 1.0f);

        // Health number text
        if (healthNumbers) {
            char hbuf[32];
            snprintf(hbuf, sizeof(hbuf), "%.0f/%.0f", hp, maxHp);
            ImVec2 ts = ImGui::CalcTextSize(hbuf);
            float tx = screenX - ts.x * 0.5f;
            float ty = by - ts.y - 2.0f;
            dl->AddText(ImVec2(tx+1, ty+1), IM_COL32(0,0,0,180), hbuf);
            dl->AddText(ImVec2(tx, ty), col, hbuf);
        }
    }

    // Settings panel — add inside the UI → ESP tab
    inline void DrawReachPanel() {
        ImGui::Spacing();
        ImGui::Checkbox(OBFUSCATE("Reach Display HUD"), &showReach);
        if (showReach) {
            ImGui::PushItemWidth(180.0f);
            ImGui::DragFloat(OBFUSCATE("Offset X##rd"), &reachOffsetX, 1.0f, -800.0f, 800.0f, "%.0f");
            ImGui::DragFloat(OBFUSCATE("Offset Y##rd"), &reachOffsetY, 1.0f, -500.0f, 500.0f, "%.0f");
            ImGui::PopItemWidth();
        }
    }

    inline void DrawHealthBarPanel() {
        ImGui::Spacing();
        ImGui::Checkbox(OBFUSCATE("ESP Health Bars"), &espHealthBars);
        if (!espHealthBars) return;
        ImGui::Checkbox(OBFUSCATE("Show Numbers##hb"), &healthNumbers);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Color Scale##hb"), &healthColorScale);
        ImGui::PushItemWidth(180.0f);
        ImGui::SliderFloat(OBFUSCATE("Bar Width##hb"),  &barWidth,  10.0f, 100.0f, "%.0f");
        ImGui::SliderFloat(OBFUSCATE("Bar Height##hb"), &barHeight, 2.0f,  12.0f,  "%.0f");
        ImGui::PopItemWidth();
    }
}
