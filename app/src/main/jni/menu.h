// ManesClient — menu.h
// Version 2.0 — Full feature update: Velocity, Anti-AFK, Scaffold, Tower,
//               Auto Armor, Reach HUD, ESP Health Bars, Theme Picker, Panic Button
// Target: Minecraft Bedrock 26.20 (1.26.20) — latest as of May 2026
// ⚠ Offsets in offsets.h MUST be re-reversed for 26.20's libminecraftpe.so

#include "crosshair.h"    // v2.0 — Custom crosshair
#include "velocity.h"     // v2.0 — Knockback reduction
#include "antiafk.h"      // v2.0 — Anti-AFK
#include "scaffold.h"     // v2.0 — Scaffold + Tower
#include "autoarmor.h"    // v2.0 — Auto Armor
#include "hud_extras.h"   // v2.0 — Reach HUD + ESP Health Bars
#include "theme.h"        // v2.0 — Theme / Accent Color Picker

#include "Images/YT.h"
#include "Images/Telegram.h"
#include "Images/Discord.h"

#include "Images/amethyst_shard.h"
#include "Images/coal.h"
#include "Images/copper_ingot.h"
#include "Images/diamond.h"
#include "Images/dye_powder_blue.h"
#include "Images/emerald.h"
#include "Images/gold_ingot.h"
#include "Images/iron_ingot.h"
#include "Images/netherite_scrap.h"
#include "Images/redstone_dust.h"
#include "Images/quartz.h"
#include "Images/barrel_side.h"
#include "Images/obsidian.h"

#include "Images/horse.h"
#include "Images/villager.h"
#include "Images/iron_golem.h"
#include "Images/snow_golem.h"
#include "Images/donkey.h"
#include "Images/allay.h"
#include "Images/armadillo.h"
#include "Images/axolotl.h"
#include "Images/bat.h"
#include "Images/bee.h"
#include "Images/camel.h"
#include "Images/cat.h"
#include "Images/chicken.h"
#include "Images/cod.h"
#include "Images/copper_golem.h"
#include "Images/cow.h"
#include "Images/dolphin.h"
#include "Images/fox.h"
#include "Images/frog.h"
#include "Images/glow_squid.h"
#include "Images/goat.h"
#include "Images/happy_ghast.h"
#include "Images/llama.h"
#include "Images/ocelot.h"
#include "Images/panda.h"
#include "Images/parrot.h"
#include "Images/pig.h"
#include "Images/piglin.h"
#include "Images/pufferfish.h"
#include "Images/rabbit.h"
#include "Images/salmon.h"
#include "Images/sheep.h"
#include "Images/sniffer.h"
#include "Images/squid.h"
#include "Images/strider.h"
#include "Images/tadpole.h"
#include "Images/tropical_fish.h"
#include "Images/turtle.h"
#include "Images/wandering_trader.h"
#include "Images/wolf.h"
#include "Images/zombie_piglin.h"
#include "Images/zombie_villager.h"

// ── Accent colour used throughout the UI (cyan) ───────────────────────────────
#define MANES_ACCENT   ImVec4(0.00f, 0.82f, 0.95f, 1.00f)
#define MANES_ACCENT50 ImVec4(0.00f, 0.82f, 0.95f, 0.50f)
#define MANES_DIM      ImVec4(0.30f, 0.38f, 0.48f, 1.00f)

// ─────────────────────────────────────────────────────────────────────────────
// Tick logic (unchanged from original)
// ─────────────────────────────────────────────────────────────────────────────

void TickFunctions() {
    if (auraType < 2) {
        if (maxKillTick > currentKillTick && !canKillAuraDamage) {
            currentKillTick = currentKillTick + 1;
        } else {
            canKillAuraDamage = true;
            currentKillTick = 1;
        }
        if (maxMobAuraTick > currentMobTick && !canMobAuraDamage) {
            currentMobTick = currentMobTick + 1;
        } else {
            canMobAuraDamage = true;
            currentMobTick = 1;
        }
    }
    if (emulateNativeAttack) {
        rotations  = true;
        targetLock = true;
    }
    if (autoClicker) {
        if (maxAutoClickTick > currentAutoClickTick && !canClick) {
            currentAutoClickTick = currentAutoClickTick + 1;
        } else {
            canClick = true;
            currentAutoClickTick = 1;
        }
    }
}

// ─────────────────────────────────────────────────────────────────────────────
// Helper — draws a subtle section header line with label
// ─────────────────────────────────────────────────────────────────────────────
static void SectionHeader(const char* label) {
    ImGui::Spacing();
    ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
    ImGui::TextUnformatted(label);
    ImGui::PopStyleColor();
    ImGui::PushStyleColor(ImGuiCol_Separator, MANES_ACCENT50);
    ImGui::Separator();
    ImGui::PopStyleColor();
    ImGui::Spacing();
}

// ─────────────────────────────────────────────────────────────────────────────
// BeginDraw
// ─────────────────────────────────────────────────────────────────────────────

void BeginDraw() {
    if (!panic) {
        Theme::tick();                          // update rainbow/custom accent each frame
        Theme::apply(ImGui::GetStyle());        // push accent into ImGui style

        ImGuiIO& io      = ImGui::GetIO();
        ImVec2   center  = ImGui::GetMainViewport()->GetCenter();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));

        // ── Load icons ───────────────────────────────────────────────────────
        static GLint youtube_icon   = 0; if (!youtube_icon)   youtube_icon   = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(YoutubeIcon),   sizeof(YoutubeIcon));
        static GLint telegram_icon  = 0; if (!telegram_icon)  telegram_icon  = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TelegramIcon),  sizeof(TelegramIcon));
        static GLint discord_icon   = 0; if (!discord_icon)   discord_icon   = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DiscordIcon),   sizeof(DiscordIcon));

        static GLint amethyst_shard_icon  = 0; if (!amethyst_shard_icon)  amethyst_shard_icon  = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AmethystShardIcon),  sizeof(AmethystShardIcon));
        static GLint coal_icon            = 0; if (!coal_icon)            coal_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CoalIcon),            sizeof(CoalIcon));
        static GLint copper_ingot_icon    = 0; if (!copper_ingot_icon)    copper_ingot_icon    = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CopperIngotIcon),    sizeof(CopperIngotIcon));
        static GLint diamond_icon         = 0; if (!diamond_icon)         diamond_icon         = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DiamondIcon),         sizeof(DiamondIcon));
        static GLint dye_powder_blue_icon = 0; if (!dye_powder_blue_icon) dye_powder_blue_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DyePowderBlueIcon), sizeof(DyePowderBlueIcon));
        static GLint emerald_icon         = 0; if (!emerald_icon)         emerald_icon         = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(EmeraldIcon),         sizeof(EmeraldIcon));
        static GLint gold_ingot_icon      = 0; if (!gold_ingot_icon)      gold_ingot_icon      = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GoldIngotIcon),      sizeof(GoldIngotIcon));
        static GLint iron_ingot_icon      = 0; if (!iron_ingot_icon)      iron_ingot_icon      = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(IronIngotIcon),      sizeof(IronIngotIcon));
        static GLint netherite_scrap_icon = 0; if (!netherite_scrap_icon) netherite_scrap_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(NetheriteScrapIcon), sizeof(NetheriteScrapIcon));
        static GLint redstone_dust_icon   = 0; if (!redstone_dust_icon)   redstone_dust_icon   = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(RedstoneDustIcon),   sizeof(RedstoneDustIcon));
        static GLint quartz_icon          = 0; if (!quartz_icon)          quartz_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(QuartzIcon),          sizeof(QuartzIcon));
        static GLint barrel_side_icon     = 0; if (!barrel_side_icon)     barrel_side_icon     = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BarrelSideIcon),     sizeof(BarrelSideIcon));
        static GLint obsidian_icon        = 0; if (!obsidian_icon)        obsidian_icon        = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ObsidianIcon),        sizeof(ObsidianIcon));

        static GLint horse_icon            = 0; if (!horse_icon)            horse_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HorseIcon),            sizeof(HorseIcon));
        static GLint villager_icon         = 0; if (!villager_icon)         villager_icon         = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(VillagerIcon),         sizeof(VillagerIcon));
        static GLint iron_golem_icon       = 0; if (!iron_golem_icon)       iron_golem_icon       = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(IronGolemIcon),       sizeof(IronGolemIcon));
        static GLint snow_golem_icon       = 0; if (!snow_golem_icon)       snow_golem_icon       = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SnowGolemIcon),       sizeof(SnowGolemIcon));
        static GLint donkey_icon           = 0; if (!donkey_icon)           donkey_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DonkeyIcon),           sizeof(DonkeyIcon));
        static GLint allay_icon            = 0; if (!allay_icon)            allay_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AllayIcon),            sizeof(AllayIcon));
        static GLint armadillo_icon        = 0; if (!armadillo_icon)        armadillo_icon        = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ArmadilloIcon),        sizeof(ArmadilloIcon));
        static GLint axolotl_icon          = 0; if (!axolotl_icon)          axolotl_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(AxolotlIcon),          sizeof(AxolotlIcon));
        static GLint bat_icon              = 0; if (!bat_icon)              bat_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BatIcon),              sizeof(BatIcon));
        static GLint bee_icon              = 0; if (!bee_icon)              bee_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(BeeIcon),              sizeof(BeeIcon));
        static GLint camel_icon            = 0; if (!camel_icon)            camel_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CamelIcon),            sizeof(CamelIcon));
        static GLint cat_icon              = 0; if (!cat_icon)              cat_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CatIcon),              sizeof(CatIcon));
        static GLint chicken_icon          = 0; if (!chicken_icon)          chicken_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ChickenIcon),          sizeof(ChickenIcon));
        static GLint cod_icon              = 0; if (!cod_icon)              cod_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CodIcon),              sizeof(CodIcon));
        static GLint copper_golem_icon     = 0; if (!copper_golem_icon)     copper_golem_icon     = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CopperGolemIcon),     sizeof(CopperGolemIcon));
        static GLint cow_icon              = 0; if (!cow_icon)              cow_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(CowIcon),              sizeof(CowIcon));
        static GLint dolphin_icon          = 0; if (!dolphin_icon)          dolphin_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(DolphinIcon),          sizeof(DolphinIcon));
        static GLint fox_icon              = 0; if (!fox_icon)              fox_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(FoxIcon),              sizeof(FoxIcon));
        static GLint frog_icon             = 0; if (!frog_icon)             frog_icon             = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(FrogIcon),             sizeof(FrogIcon));
        static GLint glow_squid_icon       = 0; if (!glow_squid_icon)       glow_squid_icon       = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GlowSquidIcon),       sizeof(GlowSquidIcon));
        static GLint goat_icon             = 0; if (!goat_icon)             goat_icon             = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(GoatIcon),             sizeof(GoatIcon));
        static GLint happy_ghast_icon      = 0; if (!happy_ghast_icon)      happy_ghast_icon      = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(HappyGhastIcon),      sizeof(HappyGhastIcon));
        static GLint llama_icon            = 0; if (!llama_icon)            llama_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(LlamaIcon),            sizeof(LlamaIcon));
        static GLint ocelot_icon           = 0; if (!ocelot_icon)           ocelot_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(OcelotIcon),           sizeof(OcelotIcon));
        static GLint panda_icon            = 0; if (!panda_icon)            panda_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PandaIcon),            sizeof(PandaIcon));
        static GLint parrot_icon           = 0; if (!parrot_icon)           parrot_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ParrotIcon),           sizeof(ParrotIcon));
        static GLint pig_icon              = 0; if (!pig_icon)              pig_icon              = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PigIcon),              sizeof(PigIcon));
        static GLint piglin_icon           = 0; if (!piglin_icon)           piglin_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PiglinIcon),           sizeof(PiglinIcon));
        static GLint pufferfish_icon       = 0; if (!pufferfish_icon)       pufferfish_icon       = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(PufferfishIcon),       sizeof(PufferfishIcon));
        static GLint rabbit_icon           = 0; if (!rabbit_icon)           rabbit_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(RabbitIcon),           sizeof(RabbitIcon));
        static GLint salmon_icon           = 0; if (!salmon_icon)           salmon_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SalmonIcon),           sizeof(SalmonIcon));
        static GLint sheep_icon            = 0; if (!sheep_icon)            sheep_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SheepIcon),            sizeof(SheepIcon));
        static GLint sniffer_icon          = 0; if (!sniffer_icon)          sniffer_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SnifferIcon),          sizeof(SnifferIcon));
        static GLint squid_icon            = 0; if (!squid_icon)            squid_icon            = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(SquidIcon),            sizeof(SquidIcon));
        static GLint strider_icon          = 0; if (!strider_icon)          strider_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(StriderIcon),          sizeof(StriderIcon));
        static GLint tadpole_icon          = 0; if (!tadpole_icon)          tadpole_icon          = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TadpoleIcon),          sizeof(TadpoleIcon));
        static GLint tropical_fish_icon    = 0; if (!tropical_fish_icon)    tropical_fish_icon    = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TropicalfishIcon),    sizeof(TropicalfishIcon));
        static GLint turtle_icon           = 0; if (!turtle_icon)           turtle_icon           = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(TurtleIcon),           sizeof(TurtleIcon));
        static GLint wandering_trader_icon = 0; if (!wandering_trader_icon) wandering_trader_icon = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(WanderingtraderIcon), sizeof(WanderingtraderIcon));
        static GLint wolf_icon             = 0; if (!wolf_icon)             wolf_icon             = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(WolfIcon),             sizeof(WolfIcon));
        static GLint zombie_piglin_icon    = 0; if (!zombie_piglin_icon)    zombie_piglin_icon    = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ZombiepiglinIcon),    sizeof(ZombiepiglinIcon));
        static GLint zombie_villager_icon  = 0; if (!zombie_villager_icon)  zombie_villager_icon  = CreateTextureFromMemoryPNG(const_cast<std::uint8_t*>(ZombievillagerIcon),  sizeof(ZombievillagerIcon));

        float imageSize = ImGui::GetFontSize();

        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        // ════════════════════════════════════════════════════════════════════
        // WELCOME / DESCRIPTION  (shown once before main menu)
        // ════════════════════════════════════════════════════════════════════
        if (!readMe) {
            if (ImGui::Begin(OBFUSCATE("Welcome"), NULL,
                    ImGuiWindowFlags_NoCollapse |
                    ImGuiWindowFlags_NoResize   |
                    ImGuiWindowFlags_NoMove)) {

                g_window = ImGui::GetCurrentWindow();
                ImGui::SetWindowSize(ImVec2(screenWidth / 2, screenHeight / 1.25f));

                if (ImGui::BeginTabBar(OBFUSCATE("WelcomeTabs"))) {
                    // ── English ──────────────────────────────────────────────
                    if (ImGui::BeginTabItem(OBFUSCATE("English"))) {
                        ImGui::SetWindowFontScale(1.8f);
                        ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
                        ImGui::TextWrapped(OBFUSCATE(
                            "ManesClient\n"
                            "Free, open-source Minecraft Bedrock client.\n"
                            "Do not purchase this from anyone."));
                        ImGui::PopStyleColor();
                        ImGui::SetWindowFontScale(1.1f);
                        ImGui::Spacing();
                        ImGui::PushStyleColor(ImGuiCol_Text, MANES_DIM);
                        ImGui::Text(OBFUSCATE("Version 2.0  |  MC 26.20"));
                        ImGui::PopStyleColor();
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::Spacing();
                        ImGui::TextWrapped(OBFUSCATE(
                            "Changelog 1.1:\n"
                            "- New UI theme (dark steel / cyan)\n"
                            "- Updated Xray\n"
                            "- Improved Anti Bot\n"
                            "- Performance improvements\n"));
                        ImGui::Spacing();
                        if (ImGui::Button(OBFUSCATE("I understand, let me in"), ImVec2(-1, 0))) {
                            readMe = true;
                        }
                        ImGui::SetWindowFontScale(1.0f);
                        ImGui::EndTabItem();
                    }
                    // ── Russian ───────────────────────────────────────────────
                    if (ImGui::BeginTabItem(OBFUSCATE("Russian"))) {
                        ImGui::SetWindowFontScale(1.8f);
                        ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
                        ImGui::TextWrapped(OBFUSCATE(
                            "ManesClient\n"
                            "Бесплатный Minecraft Bedrock клиент.\n"
                            "Не покупайте его ни у кого."));
                        ImGui::PopStyleColor();
                        ImGui::SetWindowFontScale(1.1f);
                        ImGui::Spacing();
                        ImGui::PushStyleColor(ImGuiCol_Text, MANES_DIM);
                        ImGui::Text(OBFUSCATE("Версия 2.0  |  MC 26.20"));
                        ImGui::PopStyleColor();
                        ImGui::Spacing();
                        ImGui::Separator();
                        ImGui::Spacing();
                        ImGui::TextWrapped(OBFUSCATE(
                            "Changelog 1.1:\n"
                            "- Новая тема интерфейса\n"
                            "- Обновлён Xray\n"
                            "- Улучшен Anti Bot\n"
                            "- Оптимизация\n"));
                        ImGui::Spacing();
                        if (ImGui::Button(OBFUSCATE("Понял, запустить"), ImVec2(-1, 0))) {
                            readMe = true;
                        }
                        ImGui::SetWindowFontScale(1.0f);
                        ImGui::EndTabItem();
                    }
                    ImGui::EndTabBar();
                }
            }
            ImGui::End();

        // ════════════════════════════════════════════════════════════════════
        // MAIN MENU
        // ════════════════════════════════════════════════════════════════════
        } else {

            // Window title — arch-specific
            #if defined(__aarch64__)
            if (ImGui::Begin(OBFUSCATE("ManesClient v2.0  |  x64  |  MC 26.20"), NULL, ImGuiWindowFlags_NoResize)) {
            #elif defined(__ARM_ARCH_7A__)
            if (ImGui::Begin(OBFUSCATE("ManesClient v2.0  |  x32  |  MC 26.20"), NULL, ImGuiWindowFlags_NoResize)) {
            #else
            if (ImGui::Begin(OBFUSCATE("ManesClient v2.0  |  x86_64  |  MC 26.20"), NULL, ImGuiWindowFlags_NoResize)) {
            #endif
                g_window = ImGui::GetCurrentWindow();
                ImGui::SetWindowSize(ImVec2(screenWidth / 2.5f, screenHeight / 1.5f));

                float pointSize = calculateResolutionScale(screenWidth, screenHeight, 2480, 1116);
                BackGroundDots(250, 2 * pointSize, 5 * pointSize, 100 * pointSize);

                ImGuiStyle& style = ImGui::GetStyle();

                // Save original button colours — we override per-item in the sidebar
                ImVec4 origBtn     = style.Colors[ImGuiCol_Button];
                ImVec4 origBtnHov  = style.Colors[ImGuiCol_ButtonHovered];
                ImVec4 origBtnAct  = style.Colors[ImGuiCol_ButtonActive];

                // ── Sidebar nav ───────────────────────────────────────────────
                ImGui::BeginChild(OBFUSCATE("##Nav"), ImVec2(calcResX * 150, 0), false);

                const char* navLabels[] = {
                    "Movement", "Combat", "Building", "Players",
                    "Visuals",  "Hotkeys", "Other",   "Info"
                };
                const int navCount = 8;

                style.FrameBorderSize = 0.0f;

                for (int i = 0; i < navCount; i++) {
                    bool active = (pageId == i);
                    if (active) {
                        style.Colors[ImGuiCol_Button]        = ImVec4(0.00f, 0.55f, 0.65f, 0.30f);
                        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.65f, 0.75f, 0.40f);
                    } else {
                        style.Colors[ImGuiCol_Button]        = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
                        style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.40f, 0.48f, 0.20f);
                    }

                    // Active indicator bar on left edge
                    if (active) {
                        ImVec2 p = ImGui::GetCursorScreenPos();
                        ImGui::GetWindowDrawList()->AddRectFilled(
                            p,
                            ImVec2(p.x + 3.0f * scaleGlobal, p.y + ImGui::GetTextLineHeightWithSpacing()),
                            ImGui::GetColorU32(MANES_ACCENT)
                        );
                        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 5.0f * scaleGlobal);
                    }

                    if (active) {
                        ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
                    }
                    if (ImGui::Button(OBFUSCATE(navLabels[i]))) pageId = i;
                    if (active) ImGui::PopStyleColor();
                }

                ImGui::EndChild();

                // Restore colours
                style.Colors[ImGuiCol_Button]        = origBtn;
                style.Colors[ImGuiCol_ButtonHovered] = origBtnHov;
                style.Colors[ImGuiCol_ButtonActive]  = origBtnAct;
                style.FrameBorderSize = 2.0f;

                // Vertical divider
                ImGui::SameLine();
                float lineHeight = ImGui::GetWindowHeight();
                ImVec2 startV = ImGui::GetCursorScreenPos();
                startV.y = ImGui::GetWindowPos().y;
                ImVec2 endV = ImVec2(startV.x, startV.y + lineHeight);
                ImGui::GetWindowDrawList()->AddLine(
                    startV, endV,
                    ImGui::GetColorU32(ImGuiCol_Separator), scaleGlobal * 1.5f);
                ImGui::SameLine(calcResX * 226);

                // ── Page content ──────────────────────────────────────────────
                ImGui::BeginGroup();
                switch (pageId) {

                    // ═══════════════════════════════════════════════════════
                    // PAGE 0 — MOVEMENT
                    // ═══════════════════════════════════════════════════════
                    case 0:
                        ImGui::PushItemWidth(calcResX * 100);
                        if (ImGui::BeginTabBar(OBFUSCATE("##MovTabs"))) {
                            if (!isLANGame) {
                                if (ImGui::BeginTabItem(OBFUSCATE("Speed"))) {
                                    SectionHeader("Speed Settings");
                                    ImGui::DragInt(OBFUSCATE("SpeedHack"),    &speedValue,      0.05f, 1, 50);
                                    ImGui::SameLine();
                                    ImGui::DragInt(OBFUSCATE("Water Speed"),  &waterSpeedValue, 0.05f, 1, 50);
                                    ImGui::DragInt(OBFUSCATE("Lava Speed"),   &lavaSpeedValue,  0.05f, 1, 50);
                                    ImGui::Spacing();
                                    ImGui::Checkbox(OBFUSCATE("Always Sprinting"), &alwaysSprinting);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("No SlowDown"),      &noSlowDown);
                                    ImGui::Checkbox(OBFUSCATE("No Web"),           &offSlowdownTrigger);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("No Jump Delay"),    &noJumpDelay);
                                    ImGui::EndTabItem();
                                }
                            }
                            if (ImGui::BeginTabItem(OBFUSCATE("Physics"))) {
                                if (!isLANGame) {
                                    SectionHeader("Physics");
                                    ImGui::DragFloat(OBFUSCATE("JumpHack"),  &jumpValue,    0.05f, 1, 50, "%.0f");
                                    ImGui::PushItemWidth(calcResX * 300);
                                    ImGui::SliderFloat(OBFUSCATE("Gravity"), &gravityValue, -0.08f, 0.08f, "%.2f");
                                    ImGui::PushItemWidth(0);
                                    ImGui::Checkbox(OBFUSCATE("Fast Fall"),      &fastFall);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("Step"),           &step);
                                    ImGui::Checkbox(OBFUSCATE("Ladder Fly"),     &ladderFly);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("Noclip"),         &noclip);
                                    ImGui::Checkbox(OBFUSCATE("Creative Fly"),   &creativeFly);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("Force Creative Fly"), &forceCreativeFly);
                                    ImGui::Checkbox(OBFUSCATE("No Water"),       &offWaterTrigger);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("Strafe"),         &strafe);
                                    DrawSeparatorToWindowEdge(endV, 16.0f);
                                }
                                SectionHeader("Anti Cheat");
                                ImGui::Checkbox(OBFUSCATE("OFF Drowning"),  &offDrown);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Damage Fly (Sprint to control)"), &damageFly);
                                ImGui::EndTabItem();
                            }
                            ImGui::EndTabBar();
                        }
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 1 — COMBAT
                    // ═══════════════════════════════════════════════════════
                    case 1:
                        if (ImGui::BeginTabBar(OBFUSCATE("##CombatTabs"))) {
                            // ── Players tab ─────────────────────────────────
                            if (ImGui::BeginTabItem(OBFUSCATE("Players"))) {
                                ImGui::PushID(21);
                                SectionHeader("Kill Aura");
                                ImGui::Checkbox(OBFUSCATE("KillAura"), &killAura);
                                if (killAura) {
                                    ImGui::PushItemWidth(calcResX * 200);
                                    if (ImGui::DragFloat(OBFUSCATE("Kill Range"), &killRange, 0.015f, 1.0f, 10.0f, "%.1f")) {
                                        if (killRange > rotationsRange) rotationsRange = killRange;
                                    }
                                    if (rotations || targetLock) {
                                        if (ImGui::DragFloat(OBFUSCATE("Rot / Lock Range"), &rotationsRange, 0.015f, 1.0f, 100.0f, "%.1f")) {
                                            if (killRange > rotationsRange) killRange = rotationsRange;
                                        }
                                    }
                                    if (!useGeyserCooldown) {
                                        ImGui::DragInt(OBFUSCATE("Kill Delay"), &maxKillTick, 0.05f, 1, 150);
                                        ImGui::SameLine();
                                    }
                                    ImGui::Checkbox(OBFUSCATE("Use Geyser Cooldown"), &useGeyserCooldown);
                                    ImGui::PushItemWidth(0);
                                }
                                SectionHeader("HitBox");
                                ImGui::Checkbox(OBFUSCATE("HitBox"), &hitBox);
                                if (hitBox) {
                                    ImGui::SameLine();
                                    ImGui::PushItemWidth(calcResX * 200);
                                    ImGui::DragFloat(OBFUSCATE("##HBSize"), &hitBoxValue, 0.015f, 0.6f, 10.0f, "%.1f");
                                    ImGui::PushItemWidth(0);
                                }
                                DrawSeparatorToWindowEdge(endV, 16.0f);
                                SectionHeader("Aura Settings");
                                ImGui::PushItemWidth(calcResX * 200);
                                if (!useGeyserCooldown && !emulateNativeAttack) {
                                    ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraType, IM_ARRAYSIZE(AuraType));
                                } else {
                                    ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraTypeGeyser, IM_ARRAYSIZE(AuraTypeGeyser));
                                    if (auraType == 2) auraType = 1;
                                }
                                ImGui::PushItemWidth(0);
                                ImGui::Checkbox(OBFUSCATE("Swing"), &swing);
                                ImGui::SameLine();
                                if (!emulateNativeAttack) {
                                    ImGui::Checkbox(OBFUSCATE("Rotations"),  &rotations);
                                    ImGui::Checkbox(OBFUSCATE("Target Lock"),&targetLock);
                                    ImGui::SameLine();
                                }
                                ImGui::Checkbox(OBFUSCATE("Hurt Check"), &hurtCheck);
                                ImGui::Checkbox(OBFUSCATE("Simulate Native Attack (Split Touch Recommended)"), &emulateNativeAttack);
                                ImGui::PopID();
                                ImGui::EndTabItem();
                            }
                            // ── Mobs tab ─────────────────────────────────────
                            if (ImGui::BeginTabItem(OBFUSCATE("Mobs"))) {
                                if (ImGui::BeginTabBar(OBFUSCATE("##MobTabs"))) {
                                    ImGui::PushID(22);
                                    if (ImGui::BeginTabItem(OBFUSCATE("Settings"))) {
                                        ImGui::Checkbox(OBFUSCATE("MobAura"), &mobAura);
                                        if (mobAura) {
                                            ImGui::PushItemWidth(calcResX * 200);
                                            ImGui::DragFloat(OBFUSCATE("Mob Range"), &mobAuraRange, 0.015f, 1.0f, 10.0f, "%.1f");
                                            if (!useGeyserCooldown) {
                                                ImGui::DragInt(OBFUSCATE("Mob Delay"), &maxMobAuraTick, 0.05f, 1, 150);
                                                ImGui::SameLine();
                                            }
                                            ImGui::Checkbox(OBFUSCATE("Use Geyser Cooldown"), &useGeyserCooldown);
                                            ImGui::PushItemWidth(0);
                                        }
                                        DrawSeparatorToWindowEdge(endV, 16.0f);
                                        SectionHeader("Aura");
                                        ImGui::PushItemWidth(calcResX * 200);
                                        if (!useGeyserCooldown) {
                                            ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraType, IM_ARRAYSIZE(AuraType));
                                        } else {
                                            ImGui::Combo(OBFUSCATE("Aura Type"), &auraType, AuraTypeGeyser, IM_ARRAYSIZE(AuraTypeGeyser));
                                            if (auraType == 2) auraType = 1;
                                        }
                                        ImGui::Checkbox(OBFUSCATE("Swing"),       &swing);
                                        ImGui::SameLine();
                                        ImGui::Checkbox(OBFUSCATE("Rotations"),   &rotations);
                                        ImGui::Checkbox(OBFUSCATE("Target Lock"), &targetLock);
                                        ImGui::SameLine();
                                        ImGui::Checkbox(OBFUSCATE("Hurt Check"),  &hurtCheck);
                                        ImGui::PushItemWidth(0);
                                        ImGui::EndTabItem();
                                    }
                                    // ── Mob exclusion list ─────────────────
                                    if (ImGui::BeginTabItem(OBFUSCATE("Exclude"))) {
                                        ImGui::TextDisabled(OBFUSCATE("Checked = MobAura ignores this mob"));
                                        ImGui::BeginChild(OBFUSCATE("##MobList"), ImVec2(0, 0), true);
                                        ImGui::SetWindowFontScale(1.75f);
                                        float is = imageSize * 2.25f;
                                        // Using a macro to reduce repetition
                                        #define MOB_ROW(flag, icon) \
                                            ImGui::Checkbox(OBFUSCATE("##" #flag), &flag); \
                                            ImGui::SameLine(); \
                                            ImGui::Image((ImTextureID)(intptr_t)icon, ImVec2(is, is)); \
                                            ImGui::SameLine();

                                        MOB_ROW(noHorses,      horse_icon)
                                        MOB_ROW(noVillagers,   villager_icon)
                                        MOB_ROW(noSnowMan,     snow_golem_icon)
                                        MOB_ROW(noIronGolem,   iron_golem_icon) ImGui::NewLine();
                                        MOB_ROW(noDonkeys,     donkey_icon)
                                        MOB_ROW(noAllays,      allay_icon)
                                        MOB_ROW(noArmadillos,  armadillo_icon)
                                        MOB_ROW(noAxolotls,    axolotl_icon) ImGui::NewLine();
                                        MOB_ROW(noBats,        bat_icon)
                                        MOB_ROW(noBees,        bee_icon)
                                        MOB_ROW(noCamels,      camel_icon)
                                        MOB_ROW(noCats,        cat_icon) ImGui::NewLine();
                                        MOB_ROW(noChickens,    chicken_icon)
                                        MOB_ROW(noCods,        cod_icon)
                                        MOB_ROW(noCopperGolems,copper_golem_icon)
                                        MOB_ROW(noCows,        cow_icon) ImGui::NewLine();
                                        MOB_ROW(noDolphins,    dolphin_icon)
                                        MOB_ROW(noFoxes,       fox_icon)
                                        MOB_ROW(noFrogs,       frog_icon)
                                        MOB_ROW(noGlowSquids,  glow_squid_icon) ImGui::NewLine();
                                        MOB_ROW(noGoats,       goat_icon)
                                        MOB_ROW(noHappyGhasts, happy_ghast_icon)
                                        MOB_ROW(noLlamas,      llama_icon)
                                        MOB_ROW(noOcelots,     ocelot_icon) ImGui::NewLine();
                                        MOB_ROW(noPandas,      panda_icon)
                                        MOB_ROW(noParrots,     parrot_icon)
                                        MOB_ROW(noPigs,        pig_icon)
                                        MOB_ROW(noPiglins,     piglin_icon) ImGui::NewLine();
                                        MOB_ROW(noPufferfishes, pufferfish_icon)
                                        MOB_ROW(noRabbits,     rabbit_icon)
                                        MOB_ROW(noSalmons,     salmon_icon)
                                        MOB_ROW(noSheeps,      sheep_icon) ImGui::NewLine();
                                        MOB_ROW(noSniffers,    sniffer_icon)
                                        MOB_ROW(noSquids,      squid_icon)
                                        MOB_ROW(noStriders,    strider_icon)
                                        MOB_ROW(noTadpoles,    tadpole_icon) ImGui::NewLine();
                                        MOB_ROW(noTropicalfishes, tropical_fish_icon)
                                        MOB_ROW(noTurtles,     turtle_icon)
                                        MOB_ROW(noWanderingtraders, wandering_trader_icon)
                                        MOB_ROW(noWolfs,       wolf_icon) ImGui::NewLine();
                                        MOB_ROW(noZombiepiglins,   zombie_piglin_icon)
                                        MOB_ROW(noZombievillagers, zombie_villager_icon) ImGui::NewLine();
                                        #undef MOB_ROW

                                        ImGui::SetWindowFontScale(1.0f);
                                        ImGui::EndChild();
                                        ImGui::EndTabItem();
                                    }
                                    ImGui::EndTabBar();
                                    ImGui::PopID();
                                }
                                ImGui::EndTabItem();
                            }
                            // ── Other combat ─────────────────────────────────
                            if (ImGui::BeginTabItem(OBFUSCATE("Other"))) {
                                SectionHeader("Misc Combat");
                                ImGui::Checkbox(OBFUSCATE("Kill Near Items"), &killItems);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Anti Fireball"), &antiFireball);
                                ImGui::PushItemWidth(calcResX * 200);
                                ImGui::Checkbox(OBFUSCATE("Auto Clicker"), &autoClicker);
                                ImGui::SameLine();
                                if (autoClicker) {
                                    ImGui::DragInt(OBFUSCATE("Click Delay"), &maxAutoClickTick, 0.05f, 1, 150);
                                }
                                if (!isLANGame) {
                                    ImGui::Checkbox(OBFUSCATE("Anti Knockback"), &antiKnockback);
                                }
                                ImGui::PushItemWidth(0);
                                ImGui::EndTabItem();
                            }
                            ImGui::EndTabBar();
                        }
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 2 — BUILDING
                    // ═══════════════════════════════════════════════════════
                    case 2:
                        SectionHeader("Building");
                        ImGui::Checkbox(OBFUSCATE("1-Click Auto Mine"), &clickAutoMine);
                        ImGui::SameLine();
                        ImGui::Checkbox(OBFUSCATE("Auto Click Build (hold build)"), &fastBridge);
                        ImGui::Checkbox(OBFUSCATE("Creative Block Reach"), &blockReach);
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 3 — PLAYER LIST
                    // ═══════════════════════════════════════════════════════
                    case 3:
                        ImGui::Checkbox(OBFUSCATE("Anti Bot"), &antiBot);
                        ImGui::Spacing();
                        if (ImGui::BeginTabBar(OBFUSCATE("##ListTabs"))) {
                            if (ImGui::BeginTabItem(OBFUSCATE("All"))) {
                                ImGui::BeginChild(OBFUSCATE("##PlayersPanel"), ImVec2(0, 0), true);
                                if (!nearPlayerList.empty()) insertionSortPlayers(nearPlayerList);
                                for (PlayerStruct pl : nearPlayerList) {
                                    if (!pl.isBot) {
                                        if      (pl.isProtected) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0.3f, 0.3f, 1));
                                        else if (pl.isFriend)    ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
                                        else                     ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.7f, 1, 0.7f, 1));
                                        ImGui::PushID(pl.nickname.c_str());
                                        ImGuiColoredText(pl.nameTag);
                                        if (!pl.isFriend) {
                                            ImGui::SameLine();
                                            if (ImGui::SmallButton(OBFUSCATE("+ Friend"))) friendList.push_back(pl.nickname);
                                            ImGui::SameLine();
                                            if (ImGui::SmallButton(OBFUSCATE("+ Bot")))    botList.push_back(pl.nickname);
                                        }
                                        ImGui::Separator();
                                        ImGui::PopID();
                                        ImGui::PopStyleColor();
                                    }
                                }
                                ImGui::EndChild();
                                ImGui::EndTabItem();
                            }
                            ImGui::PushStyleColor(ImGuiCol_Text, MANES_ACCENT);
                            if (ImGui::BeginTabItem(OBFUSCATE("Friends"))) {
                                ImGui::BeginChild(OBFUSCATE("##FriendsPanel"), ImVec2(0, 0), true);
                                for (std::string fn : friendList) {
                                    ImGui::PushID(fn.c_str());
                                    ImGuiColoredText(fn);
                                    ImGui::SameLine();
                                    if (ImGui::SmallButton(OBFUSCATE("Remove"))) {
                                        friendList.erase(std::remove(friendList.begin(), friendList.end(), fn), friendList.end());
                                    }
                                    ImGui::Separator();
                                    ImGui::PopID();
                                }
                                ImGui::EndChild();
                                ImGui::EndTabItem();
                            }
                            ImGui::PopStyleColor();
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1, 0.85f, 0.2f, 1));
                            if (ImGui::BeginTabItem(OBFUSCATE("Bots"))) {
                                ImGui::BeginChild(OBFUSCATE("##BotsPanel"), ImVec2(0, 0), true);
                                for (std::string bn : botList) {
                                    ImGui::PushID(bn.c_str());
                                    ImGuiColoredText(bn);
                                    ImGui::SameLine();
                                    if (ImGui::SmallButton(OBFUSCATE("Remove"))) {
                                        botList.erase(std::remove(botList.begin(), botList.end(), bn), botList.end());
                                    }
                                    ImGui::Separator();
                                    ImGui::PopID();
                                }
                                ImGui::EndChild();
                                ImGui::EndTabItem();
                            }
                            ImGui::PopStyleColor();
                            ImGui::EndTabBar();
                        }
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 4 — VISUALS
                    // ═══════════════════════════════════════════════════════
                    case 4:
                        if (ImGui::BeginTabBar(OBFUSCATE("##VisTabs"))) {
                            // Xray tab
                            if (ImGui::BeginTabItem(OBFUSCATE("Xray"))) {
                                ImGui::Checkbox(OBFUSCATE("Xray Caves"), &xrayCaves);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Xray Camera (3rd Person)"), &xrayCam);
                                ImGui::BeginChild(OBFUSCATE("##XrayPanel"), ImVec2(0, 0), xrayDefault);
                                if (ImGui::Checkbox(OBFUSCATE("Xray"), &xrayDefault)) rebuildChunkGeometry = true;
                                if (xrayDefault) {
                                    ImGui::Separator();
                                    // Helper lambda to draw a checkbox + icon pair
                                    auto xrow = [&](bool& flag, GLint icon) {
                                        if (ImGui::Checkbox(OBFUSCATE("##"), &flag)) if (flag) rebuildChunkGeometry = true;
                                        ImGui::SameLine();
                                        ImGui::Image((ImTextureID)(intptr_t)icon, ImVec2(imageSize * 1.5f, imageSize * 1.5f));
                                        ImGui::SameLine(0, calcResX * 30);
                                    };
                                    xrow(xrayDiamond,  diamond_icon);
                                    xrow(xrayIron,     iron_ingot_icon);
                                    xrow(xrayGold,     gold_ingot_icon); ImGui::NewLine();
                                    xrow(xrayCoal,     coal_icon);
                                    xrow(xrayCopper,   copper_ingot_icon);
                                    xrow(xrayLapis,    dye_powder_blue_icon); ImGui::NewLine();
                                    xrow(xrayEmerald,  emerald_icon);
                                    xrow(xrayRedstone, redstone_dust_icon);
                                    xrow(xrayAmethyst, amethyst_shard_icon); ImGui::NewLine();
                                    xrow(xrayNetherite,netherite_scrap_icon);
                                    xrow(xrayQuartz,   quartz_icon);
                                    xrow(xrayObsidian, obsidian_icon); ImGui::NewLine();
                                    xrow(xrayBarrel,   barrel_side_icon); ImGui::NewLine();
                                }
                                ImGui::EndChild();
                                ImGui::EndTabItem();
                            }
                            // Render tab
                            if (ImGui::BeginTabItem(OBFUSCATE("Render"))) {
                                ImGui::PushItemWidth(calcResX * 250);
                                ImGui::Combo(OBFUSCATE("Fog Mode"), &fogState, FogStatement, IM_ARRAYSIZE(FogStatement));
                                ImGui::PushItemWidth(calcResX * 450);
                                ImGui::Combo(OBFUSCATE("Chams"), &chamsint, Chams, IM_ARRAYSIZE(Chams));
                                if (chamsint > 1) {
                                    DrawSeparatorToWindowEdge(endV, 16.0f);
                                    ImGui::PushItemWidth(calcResX * 42);
                                    ImGui::ColorEdit3(OBFUSCATE("##VisCol"), (float*)&visibleColor);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("RGB"), &enableRainbow);
                                }
                                if (chamsint == 6 || chamsint == 7) {
                                    ImGui::SameLine();
                                    ImGui::ColorEdit3(OBFUSCATE("##WallCol"), (float*)&inWallColor);
                                    ImGui::SameLine();
                                    ImGui::Checkbox(OBFUSCATE("RGB##w"), &enableRainbowWall);
                                }
                                ImGui::PushItemWidth(0);
                                if (chamsint > 1) DrawSeparatorToWindowEdge(endV, 16.0f);
                                ImGui::Checkbox(OBFUSCATE("Enable FOV"), &enableFov);
                                if (enableFov) {
                                    ImGui::SameLine();
                                    ImGui::PushItemWidth(calcResX * 500);
                                    ImGui::SliderFloat(OBFUSCATE("##FOV"), &fov, -90.0f, 90.0f, "%.0f");
                                    ImGui::PushItemWidth(0);
                                }
                                ImGui::Checkbox(OBFUSCATE("FullBright"),       &fullBright);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("OSMT FPS Boost"),   &osmtBoost);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Freelook"),         &look360);
                                ImGui::Checkbox(OBFUSCATE("No Hurt Cam"),      &noHurtCam);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("No Cam Distortion"),&noCamDist);
                                ImGui::Checkbox(OBFUSCATE("No Boat Rot Limit"),&noBoatRotation);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("No Sleep Vignette"),&noCamSleep);
                                ImGui::Checkbox(OBFUSCATE("Place Camera"),     &placeCam);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Anti Invisible"),   &antiInvis);
                                if (!isLANGame) {
                                    ImGui::Checkbox(OBFUSCATE("Derp"), &derp);
                                    ImGui::SameLine();
                                }
                                ImGui::Checkbox(OBFUSCATE("No Blur"),          &noBlur);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("Anti Blindness"),   &antiBlind);
                                if (antiBlind && fogState == 0) fogState = 1;
                                ImGui::EndTabItem();
                            }
                            // UI tab
                            if (ImGui::BeginTabItem(OBFUSCATE("UI"))) {
                                ImGui::PushID(23);
                                if (ImGui::BeginTabBar(OBFUSCATE("##UITabs"))) {
                                    if (ImGui::BeginTabItem(OBFUSCATE("General"))) {
                                        ImGui::PushItemWidth(calcResX * 300);
                                        ImGui::SliderInt(OBFUSCATE("Font Size"), &fontSize, 0, 10);
                                        ImGui::Checkbox(OBFUSCATE("Always Show Paperdoll"), &showPaperdoll);
                                        ImGui::SameLine();
                                        ImGui::Checkbox(OBFUSCATE("No Cave Vignette"), &noCaveVignette);
                                        ImGui::Checkbox(OBFUSCATE("Death Position"),    &deathPosition);
                                        if (showPosition) DrawSeparatorToWindowEdge(endV, 16.0f);
                                        ImGui::Checkbox(OBFUSCATE("Show Position"), &showPosition);
                                        if (showPosition) {
                                            ImGui::DragFloat(OBFUSCATE("Offset X"), &offsetTextPosX, 0.05f, -1500.0f, 1500.0f, "%.0f");
                                            ImGui::DragFloat(OBFUSCATE("Offset Y"), &offsetTextPosY, 0.05f, -1000.0f, 1000.0f, "%.0f");
                                        }
                                        if (showPosition || playerNear) DrawSeparatorToWindowEdge(endV, 16.0f);
                                        ImGui::Checkbox(OBFUSCATE("Near Players"), &playerNear);
                                        if (playerNear) {
                                            ImGui::DragFloat(OBFUSCATE("Offset X  "), &offsetTextPlayerNearPosX, 0.05f, -1500.0f, 1500.0f, "%.0f");
                                            ImGui::DragFloat(OBFUSCATE("Offset Y  "), &offsetTextPlayerNearPosY, 0.05f, -1000.0f, 1000.0f, "%.0f");
                                        }
                                        ImGui::PushItemWidth(0);
                                        ImGui::EndTabItem();
                                    }
                                    if (ImGui::BeginTabItem(OBFUSCATE("ESP"))) {
                                        ImGui::Checkbox(OBFUSCATE("ESP"), &esp);
                                        if (esp) {
                                            ImGui::Checkbox(OBFUSCATE("Box"),      &espBox);
                                            ImGui::SameLine();
                                            ImGui::Checkbox(OBFUSCATE("Line"),     &espLine);
                                            ImGui::SameLine();
                                            ImGui::Checkbox(OBFUSCATE("Distance"), &espDistance);
                                            ImGui::Checkbox(OBFUSCATE("Nametag"),  &espNametag);
                                            ImGui::SameLine();
                                            ImGui::Checkbox(OBFUSCATE("Health"),   &espHealth);
                                            ImGui::SameLine();
                                            ImGui::Checkbox(OBFUSCATE("Platform"), &espPlatform);
                                        }
                                        ImGui::EndTabItem();
                                    }
                                    // ── Crosshair tab (v2.0) ──────────────────
                                    if (ImGui::BeginTabItem(OBFUSCATE("Crosshair"))) {
                                        DrawCrosshairPanel();
                                        ImGui::EndTabItem();
                                    }
                                    ImGui::EndTabBar();
                                }
                                ImGui::PopID();
                                ImGui::EndTabItem();
                            }
                            ImGui::EndTabBar();
                        }
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 5 — HOTKEYS
                    // ═══════════════════════════════════════════════════════
                    case 5:
                        ImGui::BeginChild(OBFUSCATE("##HotkeyPanel"), ImVec2(0, 0), true);
                        ImGui::PushItemWidth(calcResX * 300);
                        SectionHeader("Android Buttons");
                        ImGui::Combo(OBFUSCATE("VOLUME UP"),   &hotkeyVolumeUp,   Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("VOLUME DOWN"), &hotkeyVolumeDown, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("BACK"),        &hotkeyBack,       Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        SectionHeader("Keyboard");
                        ImGui::Combo(OBFUSCATE("A"), &hotkey_A, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("B"), &hotkey_B, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("C"), &hotkey_C, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("D"), &hotkey_D, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("E"), &hotkey_E, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("F"), &hotkey_F, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("G"), &hotkey_G, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("H"), &hotkey_H, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("I"), &hotkey_I, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("J"), &hotkey_J, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("K"), &hotkey_K, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("L"), &hotkey_L, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("M"), &hotkey_M, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("N"), &hotkey_N, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("O"), &hotkey_O, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("P"), &hotkey_P, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("Q"), &hotkey_Q, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("R"), &hotkey_R, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("S"), &hotkey_S, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("T"), &hotkey_T, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("U"), &hotkey_U, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("V"), &hotkey_V, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("W"), &hotkey_W, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("X"), &hotkey_X, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        ImGui::Combo(OBFUSCATE("Y"), &hotkey_Y, Hotkeys, IM_ARRAYSIZE(Hotkeys)); ImGui::Combo(OBFUSCATE("Z"), &hotkey_Z, Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        SectionHeader("Numpad");
                        for (int np = 0; np <= 9; np++) {
                            char label[16]; snprintf(label, sizeof(label), "NUMPAD %d", np);
                            int* targets[] = {&hotkey_numpad_0,&hotkey_numpad_1,&hotkey_numpad_2,&hotkey_numpad_3,
                                              &hotkey_numpad_4,&hotkey_numpad_5,&hotkey_numpad_6,&hotkey_numpad_7,
                                              &hotkey_numpad_8,&hotkey_numpad_9};
                            ImGui::Combo(OBFUSCATE(label), targets[np], Hotkeys, IM_ARRAYSIZE(Hotkeys));
                        }
                        ImGui::PushItemWidth(0);
                        ImGui::EndChild();
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 6 — OTHER
                    // ═══════════════════════════════════════════════════════
                    case 6:
                        if (ImGui::BeginTabBar(OBFUSCATE("##OtherTabs"))) {
                            if (ImGui::BeginTabItem(OBFUSCATE("Tweaks"))) {
                                SectionHeader("Exploits");
                                ImGui::Checkbox(OBFUSCATE("Unlock Marketplace Items"), &unlockMarket);
                                ImGui::Checkbox(OBFUSCATE("Fast Item Drop"),           &fastDrop);
                                ImGui::SameLine();
                                ImGui::Checkbox(OBFUSCATE("No Emote Cooldown"),        &noEmoteCooldown);
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem(OBFUSCATE("LAN"))) {
                                ImGui::PushItemWidth(calcResX * 300);
                                ImGui::DragInt(OBFUSCATE("Max Players (re-enter world)"), &myMaxPlayers, 0.05f, 1, 1000);
                                ImGui::PushItemWidth(0);
                                ImGui::EndTabItem();
                            }
                            if (ImGui::BeginTabItem(OBFUSCATE("Config"))) {
                                SectionHeader("Config File");
                                std::string loadPath = oxorany("/sdcard/Download/ManesClient.json");
                                ImGui::TextDisabled(OBFUSCATE("/sdcard/Download/ManesClient.json"));
                                ImGui::Spacing();
                                if (ImGui::Button(OBFUSCATE("Load"), ImVec2(calcResX * 80, 0))) {
                                    std::ifstream file(loadPath);
                                    if (file.good()) loadConfig(loadPath);
                                    onFunctionSound = true;
                                    AddNotification(oxorany("Config Loaded"), 6.0f, ImVec4(0.00f, 0.70f, 0.84f, 0.80f));
                                }
                                ImGui::SameLine();
                                if (ImGui::Button(OBFUSCATE("Save"), ImVec2(calcResX * 80, 0))) {
                                    saveConfig(loadPath);
                                    onFunctionSound = true;
                                    AddNotification(oxorany("Config Saved"), 6.0f, ImVec4(0.00f, 0.70f, 0.84f, 0.80f));
                                }
                                ImGui::EndTabItem();
                            }
                            ImGui::EndTabBar();
                        }
                        break;

                    // ═══════════════════════════════════════════════════════
                    // PAGE 7 — INFO
                    // ═══════════════════════════════════════════════════════
                    case 7:
                        SectionHeader("ManesClient");
                        ImGui::Text(OBFUSCATE("Version:  2.0"));
                        ImGui::Text(OBFUSCATE("MC:       26.20"));
                        #if defined(__aarch64__)
                        ImGui::Text(OBFUSCATE("Arch:     arm64-v8a  (64-bit)"));
                        #elif defined(__ARM_ARCH_7A__)
                        ImGui::Text(OBFUSCATE("Arch:     armeabi-v7a (32-bit)"));
                        #else
                        ImGui::Text(OBFUSCATE("Arch:     x86_64"));
                        #endif
                        DrawSeparatorToWindowEdge(endV, 16.0f);
                        // Social links (update these to your own)
                        {
                            float sz = ImGui::GetFontSize();
                            ImGui::Image((ImTextureID)(intptr_t)youtube_icon,  ImVec2(sz, sz)); ImGui::SameLine(calcResX * 35); ImGui::Text(OBFUSCATE(": your YouTube"));
                            DrawSeparatorToWindowEdge(endV, 6.0f);
                            ImGui::Image((ImTextureID)(intptr_t)telegram_icon, ImVec2(sz, sz)); ImGui::SameLine(calcResX * 35); ImGui::Text(OBFUSCATE(": your Telegram"));
                            DrawSeparatorToWindowEdge(endV, 6.0f);
                            ImGui::Image((ImTextureID)(intptr_t)discord_icon,  ImVec2(sz, sz)); ImGui::SameLine(calcResX * 35); ImGui::Text(OBFUSCATE(": your Discord"));
                        }
                        DrawSeparatorToWindowEdge(endV, 16.0f);
                        ImGui::TextDisabled(OBFUSCATE("ManesClient — Project Manes"));
                        break;
                }
                ImGui::EndGroup();
                ImGui::PopStyleVar(ImGuiStyleVar_WindowTitleAlign);
            }
            ImGui::End();
        }
    }

    // ── HUD overlays (outside menu) ───────────────────────────────────────
    if (CI != NULL) {
        if (!inMenu && !panic) {
            if (inHudScreen) {
                glm::mat4 currentViewMatrix = CI->getViewMatrix();
                LevelRenderer* Render = CI->getLevelRenderer();
                if (Render) {
                    LevelRendererCamera* RenderPlayer = Render->getLevelRendererPlayer();
                    if (RenderPlayer) {
                        glm::vec2 currentFov = RenderPlayer->getFov();
                        CameraPos = RenderPlayer->getCameraPos();
                        ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
        if (xrayDefault)    RenderOreESP(draw_list, CameraPos, currentFov, currentViewMatrix);
                        if (deathPosition)  RenderDeathPosition(draw_list, CameraPos, currentFov, currentViewMatrix);
                        if (esp)            RenderESP(draw_list, CameraPos, currentFov, currentViewMatrix);
                        RenderCustomCrosshair(); // v2.0 — drawn via ForegroundDrawList (crosshair.h)
                    }
                }
            }
        }
    }

    if (!inMenu) {
        if (showPosition) {
            char buf[100];
            snprintf(buf, sizeof(buf), OBFUSCATE("Pos: %.1f, %.1f, %.1f"), playerPosX, playerPosY, playerPosZ);
            DrawBackgroundText(buf, offsetTextPosX, offsetTextPosY, ImVec4(1,1,1,1), ImVec4(0,0,0,0.5f));
        }
        if (playerNear) {
            char buf[100];
            if (nearPlayer.empty()) {
                snprintf(buf, sizeof(buf), OBFUSCATE("No players nearby"));
                DrawBackgroundText(buf, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY, ImVec4(1,0.4f,0.4f,1), ImVec4(0,0,0,0.5f));
            } else {
                snprintf(buf, sizeof(buf), OBFUSCATE("Players nearby: %d"), (int)nearPlayer.size());
                DrawBackgroundText(buf, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY, ImVec4(1,1,1,1), ImVec4(0,0,0,0.5f));
            }
            if (!nearFriendList.empty()) {
                char buf2[100];
                snprintf(buf2, sizeof(buf2), OBFUSCATE("Friends nearby: %d"), (int)nearFriendList.size());
                DrawBackgroundText(buf2, offsetTextPlayerNearPosX, offsetTextPlayerNearPosY + 40 * scaleGlobal, MANES_ACCENT, ImVec4(0,0,0,0.5f));
            }
        }
    }

    if (enableRainbow)     { visibleColor.x = redd/255; visibleColor.y = greenn/255; visibleColor.z = bluee/255; }
    if (enableRainbowWall) { inWallColor.x  = redd/255; inWallColor.y  = greenn/255; inWallColor.z  = bluee/255; }
    performRGBChange();
    Patches();
    if (!useGeyserCooldown) TickFunctions();
}
