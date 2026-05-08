// ManesClient — velocity.h
// Reduces knockback taken by intercepting Actor::lerpMotion
// Hook lerpMotion in your main hook setup and call VelocityPatch::apply()

#pragma once

namespace Velocity {
    inline bool  enabled      = false;
    inline float horizontal   = 0.0f;   // 0% = no knockback, 100% = full knockback
    inline float vertical     = 100.0f; // Usually keep vertical at 100 so you still get lifted
    inline bool  cancelAll    = false;  // Completely zero out all knockback

    // Called from your lerpMotion hook instead of (or before) the original
    // original signature: void Actor::lerpMotion(Vec3 const& motion)
    // Pass the motion vec3 components by pointer so we can modify them in-place
    inline void apply(float* mx, float* my, float* mz) {
        if (!enabled) return;
        if (cancelAll) {
            *mx = 0.0f;
            *my = 0.0f;
            *mz = 0.0f;
            return;
        }
        float hScale = horizontal / 100.0f;
        float vScale = vertical   / 100.0f;
        *mx *= hScale;
        *mz *= hScale;
        *my *= vScale;
    }

    // ImGui panel — call inside your Combat or Movement page
    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Velocity"), &enabled);
        if (!enabled) return;
        ImGui::PushItemWidth(200.0f);
        ImGui::SliderFloat(OBFUSCATE("Horizontal##vel"), &horizontal, 0.0f, 100.0f, "%.0f%%");
        ImGui::SliderFloat(OBFUSCATE("Vertical##vel"),   &vertical,   0.0f, 100.0f, "%.0f%%");
        ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Cancel All Knockback"), &cancelAll);
        if (cancelAll) {
            ImGui::SameLine();
            ImGui::TextDisabled(OBFUSCATE("(overrides sliders)"));
        }
    }
}
