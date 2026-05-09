// modules.h — ManesClient v2.0
// All module settings with sliders and ESP sub-toggles
// #include this in menu.h and call the draw functions per page

#pragma once
#include "imgui/imgui.h"

// ── KillAura ─────────────────────────────────────────────────────────────────
namespace KillAura {
    inline bool  enabled     = false;
    inline float range       = 4.5f;
    inline float speed       = 12.0f;
    inline bool  rotations   = true;
    inline bool  throughWalls= false;
    inline int   targetMode  = 0; // 0=Closest 1=Lowest HP 2=Players only
    static const char* targetModes[] = {"Closest","Lowest HP","Players Only"};

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("KillAura"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Range##ka"),  &range,  2.0f, 8.0f,  "%.1f blocks");
        ImGui::SliderFloat(OBFUSCATE("Speed##ka"),  &speed,  4.0f, 20.0f, "%.0f CPS");
        ImGui::Combo(OBFUSCATE("Target##ka"), &targetMode, targetModes, 3);
        ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Rotations##ka"),    &rotations);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Through Walls##ka"),&throughWalls);
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Velocity ─────────────────────────────────────────────────────────────────
namespace Velocity {
    inline bool  enabled    = false;
    inline float horizontal = 0.0f;
    inline float vertical   = 100.0f;
    inline bool  cancelAll  = false;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Velocity"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Horizontal##vel"), &horizontal, 0.0f, 100.0f, "%.0f%%");
        ImGui::SliderFloat(OBFUSCATE("Vertical##vel"),   &vertical,   0.0f, 100.0f, "%.0f%%");
        ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Cancel All##vel"), &cancelAll);
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Reach ─────────────────────────────────────────────────────────────────────
namespace Reach {
    inline bool  enabled     = false;
    inline float attackReach = 3.5f;
    inline float blockReach  = 5.0f;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Reach"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Attack Reach##rc"), &attackReach, 3.0f, 6.0f, "%.1f");
        ImGui::SliderFloat(OBFUSCATE("Block Reach##rc"),  &blockReach,  4.5f, 8.0f, "%.1f");
        ImGui::PopItemWidth();
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Hitbox ────────────────────────────────────────────────────────────────────
namespace Hitbox {
    inline bool  enabled = false;
    inline float size    = 0.3f;
    inline float height  = 0.0f;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Hitbox"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Width##hb"),  &size,   0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat(OBFUSCATE("Height##hb"), &height, 0.0f, 0.5f, "%.2f");
        ImGui::PopItemWidth();
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── AutoClick ─────────────────────────────────────────────────────────────────
namespace AutoClick {
    inline bool  enabled  = false;
    inline float minCPS   = 12.0f;
    inline float maxCPS   = 16.0f;
    inline bool  leftOnly = true;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("AutoClick"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Min CPS##ac"), &minCPS, 1.0f, 20.0f, "%.0f");
        ImGui::SliderFloat(OBFUSCATE("Max CPS##ac"), &maxCPS, 1.0f, 20.0f, "%.0f");
        ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Left Only##ac"), &leftOnly);
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Scaffold ─────────────────────────────────────────────────────────────────
namespace ScaffoldMod {
    inline bool  enabled  = false;
    inline bool  tower    = false;
    inline bool  safeWalk = true;
    inline int   delay    = 2;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Scaffold"), &enabled);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Tower"), &tower);
        if (enabled || tower) {
            ImGui::Indent(12.0f);
            ImGui::Checkbox(OBFUSCATE("Safe Walk##sc"), &safeWalk);
            ImGui::PushItemWidth(180.0f);
            ImGui::DragInt(OBFUSCATE("Delay (ticks)##sc"), &delay, 0.05f, 1, 10);
            ImGui::PopItemWidth();
            ImGui::Unindent(12.0f);
        }
        ImGui::Spacing();
    }
}

// ── Speed ─────────────────────────────────────────────────────────────────────
namespace Speed {
    inline bool  enabled = false;
    inline float speed   = 1.5f;
    inline int   mode    = 0; // 0=Normal 1=BHop 2=Sprint
    static const char* modes[] = {"Normal","BHop","Sprint"};

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Speed"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Multiplier##sp"), &speed, 1.0f, 5.0f, "%.1fx");
        ImGui::Combo(OBFUSCATE("Mode##sp"), &mode, modes, 3);
        ImGui::PopItemWidth();
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── ESP ───────────────────────────────────────────────────────────────────────
namespace ESP {
    inline bool  enabled    = false;
    inline bool  showBox    = true;
    inline bool  showLines  = false;
    inline bool  showNames  = true;
    inline bool  showHealth = true;
    inline bool  showDist   = true;
    inline bool  showArmor  = false;
    inline bool  showItems  = false;
    inline bool  players    = true;
    inline bool  mobs       = false;
    inline float maxDist    = 64.0f;
    inline ImVec4 colorPlayers = ImVec4(0.0f, 0.82f, 0.95f, 1.0f);
    inline ImVec4 colorMobs    = ImVec4(1.0f, 0.3f,  0.3f,  1.0f);

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("ESP"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::Spacing();

        // Target types
        ImGui::TextDisabled(OBFUSCATE("Targets"));
        ImGui::Checkbox(OBFUSCATE("Players##esp"), &players);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Mobs##esp"),    &mobs);

        ImGui::Spacing();
        ImGui::TextDisabled(OBFUSCATE("Display"));

        // Box row
        ImGui::Checkbox(OBFUSCATE("Box##esp"),    &showBox);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Lines##esp"),  &showLines);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Names##esp"),  &showNames);

        // Info row
        ImGui::Checkbox(OBFUSCATE("Health##esp"), &showHealth);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Dist##esp"),   &showDist);
        ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Armor##esp"),  &showArmor);

        ImGui::Checkbox(OBFUSCATE("Items##esp"),  &showItems);

        ImGui::Spacing();
        ImGui::TextDisabled(OBFUSCATE("Colors"));
        ImGui::ColorEdit3(OBFUSCATE("Players##espcol"), (float*)&colorPlayers);
        ImGui::ColorEdit3(OBFUSCATE("Mobs##espcol"),    (float*)&colorMobs);

        ImGui::Spacing();
        ImGui::PushItemWidth(220.0f);
        ImGui::SliderFloat(OBFUSCATE("Max Distance##esp"), &maxDist, 16.0f, 128.0f, "%.0f");
        ImGui::PopItemWidth();
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Xray ─────────────────────────────────────────────────────────────────────
namespace Xray {
    inline bool enabled  = false;
    inline bool diamond  = true;
    inline bool gold     = true;
    inline bool iron     = true;
    inline bool coal     = false;
    inline bool emerald  = true;
    inline bool redstone = false;
    inline bool lapis    = false;
    inline bool ancient  = true;

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Xray"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::Checkbox(OBFUSCATE("Diamond##xr"),        &diamond);  ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Gold##xr"),           &gold);
        ImGui::Checkbox(OBFUSCATE("Iron##xr"),           &iron);     ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Emerald##xr"),        &emerald);
        ImGui::Checkbox(OBFUSCATE("Ancient Debris##xr"), &ancient);  ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Redstone##xr"),       &redstone);
        ImGui::Checkbox(OBFUSCATE("Lapis##xr"),          &lapis);    ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Coal##xr"),           &coal);
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── AntiAFK ──────────────────────────────────────────────────────────────────
namespace AntiAFK {
    inline bool enabled   = false;
    inline int  mode      = 0;
    inline int  interval  = 100;
    static const char* modes[] = {"Head Rotate","Sneak","Jump","Random"};

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Anti-AFK"), &enabled);
        if (!enabled) return;
        ImGui::Indent(12.0f);
        ImGui::PushItemWidth(200.0f);
        ImGui::Combo(OBFUSCATE("Mode##afk"), &mode, modes, 4);
        ImGui::DragInt(OBFUSCATE("Interval (ticks)##afk"), &interval, 1.0f, 20, 1200);
        ImGui::PopItemWidth();
        ImGui::Unindent(12.0f);
        ImGui::Spacing();
    }
}

// ── Panic button ─────────────────────────────────────────────────────────────
namespace PanicMod {
    inline bool panic = false;

    inline void DrawPanicButton() {
        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(0.7f,0.1f,0.1f,0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f,0.1f,0.1f,0.9f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,  ImVec4(1.0f,0.0f,0.0f,1.0f));
        if (ImGui::Button(OBFUSCATE("!! PANIC — Disable All !!"),
                          ImVec2(ImGui::GetContentRegionAvail().x, 0))) {
            KillAura::enabled = false;
            Velocity::enabled = false;
            Reach::enabled    = false;
            Hitbox::enabled   = false;
            AutoClick::enabled= false;
            Speed::enabled    = false;
            ESP::enabled      = false;
            Xray::enabled     = false;
            AntiAFK::enabled  = false;
        }
        ImGui::PopStyleColor(3);
    }
}
