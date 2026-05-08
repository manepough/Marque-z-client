// ManesClient — autoarmor.h
// Automatically equips the best armor from inventory each tick.
// Call AutoArmor::tick() in your normalTick hook.

#pragma once

namespace AutoArmor {
    inline bool  enabled    = false;
    inline bool  onlyOnDamage = false;  // only equip when hit
    inline int   tickTimer  = 0;
    inline int   interval   = 40;       // check every 2 seconds

    // Simple armor tier priority (higher = better)
    // netherite > diamond > iron > golden > chain > leather
    inline int getArmorTier(const std::string& name) {
        if (name.find("netherite") != std::string::npos) return 6;
        if (name.find("diamond")   != std::string::npos) return 5;
        if (name.find("iron")      != std::string::npos) return 4;
        if (name.find("golden")    != std::string::npos) return 3;
        if (name.find("chainmail") != std::string::npos) return 2;
        if (name.find("leather")   != std::string::npos) return 1;
        return 0;
    }

    // Slot indices: 0=helmet, 1=chestplate, 2=leggings, 3=boots
    inline const char* getArmorSuffix(int slot) {
        switch (slot) {
            case 0: return "helmet";
            case 1: return "chestplate";
            case 2: return "leggings";
            case 3: return "boots";
            default: return "";
        }
    }

    // Call this each tick
    // player: your LocalPlayer*
    // gameMode: your GameMode* (for inventory swaps)
    inline void tick(LocalPlayer* player) {
        if (!enabled || !player) return;
        tickTimer++;
        if (tickTimer < interval) return;
        tickTimer = 0;

        Container* inv = player->getInventory();
        Container* armor = player->getArmorContainer();
        if (!inv || !armor) return;

        for (int slot = 0; slot < 4; slot++) {
            const char* suffix = getArmorSuffix(slot);
            ItemStack* current = armor->getItem(slot);
            int bestTier = current ? getArmorTier(current->getName()) : 0;
            int bestInvSlot = -1;

            for (int i = 0; i < inv->getSize(); i++) {
                ItemStack* item = inv->getItem(i);
                if (!item || item->isNull()) continue;
                std::string name = item->getName();
                if (name.find(suffix) == std::string::npos) continue;
                int tier = getArmorTier(name);
                if (tier > bestTier) {
                    bestTier = tier;
                    bestInvSlot = i;
                }
            }

            if (bestInvSlot >= 0) {
                // Swap inventory slot to armor slot
                player->swapArmorWithInventory(bestInvSlot, slot);
            }
        }
    }

    inline void DrawPanel() {
        ImGui::Checkbox(OBFUSCATE("Auto Armor"), &enabled);
        if (!enabled) return;
        ImGui::PushItemWidth(150.0f);
        ImGui::DragInt(OBFUSCATE("Check Interval (ticks)##aa"), &interval, 1.0f, 10, 200);
        ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Only on Damage##aa"), &onlyOnDamage);
        ImGui::TextDisabled(OBFUSCATE("Priority: Netherite > Diamond > Iron > Gold > Chain > Leather"));
    }
}
