// ManesClient — scaffold.h
// Scaffold: auto-places blocks under you while walking forward
// Tower: rapidly places blocks under you while jumping to go straight up
// Call Scaffold::tick() in your normalTick hook.

#pragma once

namespace Scaffold {
    inline bool  scaffoldEnabled = false;
    inline bool  towerEnabled    = false;
    inline bool  safeWalk        = true;   // prevents falling off edges
    inline int   towerDelay      = 2;      // ticks between tower placements
    inline int   towerTick       = 0;
    inline float scaffoldRange   = 4.5f;

    // Scaffold tick — call once per player tick
    // player: your LocalPlayer pointer
    // gameMode: your GameMode pointer (for useItemOn)
    inline void tick(LocalPlayer* player, GameMode* gameMode) {
        if (!player || !gameMode) return;

        // ── Tower ──────────────────────────────────────────────────────────
        if (towerEnabled) {
            towerTick++;
            if (towerTick >= towerDelay) {
                towerTick = 0;
                // Place block directly below player and jump
                // BlockPos below = player->getPos() - (0, 1, 0)
                Vec3  pos    = player->getPos();
                BlockPos below = { (int)pos.x, (int)pos.y - 1, (int)pos.z };

                // Use held item on the block below (face UP = 1)
                gameMode->useItemOn(player->getSelectedItem(), below, /*face=*/1,
                                    Vec3(0.5f, 1.0f, 0.5f));
                player->jump();
            }
        }

        // ── Scaffold ───────────────────────────────────────────────────────
        if (scaffoldEnabled) {
            Vec3     pos   = player->getPos();
            BlockPos below = { (int)pos.x, (int)pos.y - 1, (int)pos.z };

            // Only place if the block below is air
            BlockSource* bs = player->getDimensionBlockSource();
            if (bs) {
                Block* b = bs->getBlock(below);
                if (b && b->isAir()) {
                    gameMode->useItemOn(player->getSelectedItem(), below, /*face=*/1,
                                        Vec3(0.5f, 1.0f, 0.5f));
                }
            }
        }
    }

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Scaffold"), &scaffoldEnabled);
        if (scaffoldEnabled) {
            ImGui::SameLine();
            ImGui::Checkbox(OBFUSCATE("Safe Walk##sc"), &safeWalk);
        }
        ImGui::Checkbox(OBFUSCATE("Tower"), &towerEnabled);
        if (towerEnabled) {
            ImGui::PushItemWidth(150.0f);
            ImGui::DragInt(OBFUSCATE("Tower Delay (ticks)"), &towerDelay, 0.05f, 1, 10);
            ImGui::PopItemWidth();
        }
        if (scaffoldEnabled || towerEnabled) {
            ImGui::TextDisabled(OBFUSCATE("Hold a placeable block in your hand"));
        }
    }
}
