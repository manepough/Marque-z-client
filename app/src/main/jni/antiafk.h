// ManesClient — antiafk.h
// Prevents AFK kick by making subtle head movements each tick.
// Call AntiAFK::tick() inside your ClientInstance::onTick hook.

#pragma once
#include <cmath>
#include <cstdlib>

namespace AntiAFK {
    inline bool  enabled    = false;
    inline int   mode       = 0;       // 0=Rotate  1=Sneak toggle  2=Jump  3=Random
    inline float intensity  = 5.0f;    // degrees of rotation for Rotate mode
    inline int   tickTimer  = 0;
    inline int   interval   = 100;     // ticks between actions (~5 sec at 20tps)
    inline float rotDir     = 1.0f;

    static const char* Modes[] = { "Head Rotate", "Sneak Toggle", "Jump", "Random" };

    inline void tick(LocalPlayer* player) {
        if (!enabled || !player) return;
        tickTimer++;
        if (tickTimer < interval) return;
        tickTimer = 0;

        int m = (mode == 3) ? (rand() % 3) : mode;

        switch (m) {
            case 0: // Head rotate — tiny yaw nudge back and forth
                {
                    float yaw = player->getYHeadRot();
                    player->setYHeadRot(yaw + intensity * rotDir);
                    rotDir = -rotDir;
                }
                break;
            case 1: // Sneak toggle
                {
                    bool sneaking = player->isSneaking();
                    player->setSneaking(!sneaking);
                }
                break;
            case 2: // Jump
                player->jump();
                break;
        }
    }

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Anti-AFK"), &enabled);
        if (!enabled) return;
        ImGui::PushItemWidth(200.0f);
        ImGui::Combo(OBFUSCATE("Mode##afk"), &mode, Modes, IM_ARRAYSIZE(Modes));
        ImGui::DragInt(OBFUSCATE("Interval (ticks)##afk"), &interval, 1.0f, 20, 1200);
        if (mode == 0 || mode == 3) {
            ImGui::SliderFloat(OBFUSCATE("Rotate Amount##afk"), &intensity, 1.0f, 45.0f, "%.0f deg");
        }
        ImGui::PopItemWidth();
        ImGui::TextDisabled(OBFUSCATE("20 ticks = ~1 second"));
    }
}
