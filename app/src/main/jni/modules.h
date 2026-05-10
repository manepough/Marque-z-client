// modules.h — ManesClient v2.0
// Pure ImGui UI panels only — no MC types (LocalPlayer, GameMode etc.)
// All actual game logic stays in menu.h where those types are defined
// Just #include this in menu.h

#pragma once
#ifndef OBFUSCATE
#define OBFUSCATE(x) (x)
#endif
#include "imgui/imgui.h"

namespace KillAura {
    inline bool  enabled=false; inline float range=4.5f,speed=12.0f;
    inline bool  rotations=true,throughWalls=false; inline int targetMode=0;
    static const char* tModes[]={"Closest","Lowest HP","Players Only"};
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("KillAura"),&enabled);
        if(!enabled)return; ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Range##ka"),&range,2.0f,8.0f,"%.1f blocks");
        ImGui::SliderFloat(OBFUSCATE("Speed##ka"),&speed,4.0f,20.0f,"%.0f CPS");
        ImGui::Combo(OBFUSCATE("Target##ka"),&targetMode,tModes,3);ImGui::PopItemWidth();
        ImGui::Checkbox(OBFUSCATE("Rotations##ka"),&rotations);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Through Walls##ka"),&throughWalls);
        ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace Velocity {
    inline bool enabled=false; inline float horizontal=0,vertical=100; inline bool cancelAll=false;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Velocity"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Horizontal##vel"),&horizontal,0,100,"%.0f%%");
        ImGui::SliderFloat(OBFUSCATE("Vertical##vel"),&vertical,0,100,"%.0f%%");
        ImGui::PopItemWidth();ImGui::Checkbox(OBFUSCATE("Cancel All##vel"),&cancelAll);
        ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace Reach {
    inline bool enabled=false; inline float attackReach=3.5f,blockReach=5.0f;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Reach"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Attack##rc"),&attackReach,3.0f,6.0f,"%.1f");
        ImGui::SliderFloat(OBFUSCATE("Block##rc"),&blockReach,4.5f,8.0f,"%.1f");
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace Hitbox {
    inline bool enabled=false; inline float width=0.3f,height=0.0f;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Hitbox"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Width##hb"),&width,0,1,"%.2f");
        ImGui::SliderFloat(OBFUSCATE("Height##hb"),&height,0,0.5f,"%.2f");
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace AutoClick {
    inline bool enabled=false; inline float minCPS=12,maxCPS=16;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("AutoClick"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Min CPS##ac"),&minCPS,1,20,"%.0f");
        ImGui::SliderFloat(OBFUSCATE("Max CPS##ac"),&maxCPS,1,20,"%.0f");
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace ScaffoldMod {
    inline bool enabled=false,tower=false,safeWalk=true; inline int delay=2;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Scaffold"),&enabled);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Tower"),&tower);
        if(enabled||tower){ImGui::Indent(12);ImGui::Checkbox(OBFUSCATE("Safe Walk##sc"),&safeWalk);
        ImGui::PushItemWidth(180);ImGui::DragInt(OBFUSCATE("Delay##sc"),&delay,0.05f,1,10);
        ImGui::PopItemWidth();ImGui::Unindent(12);}ImGui::Spacing();
    }
}
namespace Speed {
    inline bool enabled=false; inline float speed=1.5f; inline int mode=0;
    static const char* modes[]={"Normal","BHop","Sprint"};
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Speed"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Multiplier##sp"),&speed,1.0f,5.0f,"%.1fx");
        ImGui::Combo(OBFUSCATE("Mode##sp"),&mode,modes,3);
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace AntiAFK {
    inline bool enabled=false; inline int mode=0,interval=100;
    static const char* modes[]={"Head Rotate","Sneak","Jump","Random"};
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Anti-AFK"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(200);
        ImGui::Combo(OBFUSCATE("Mode##afk"),&mode,modes,4);
        ImGui::DragInt(OBFUSCATE("Interval##afk"),&interval,1.0f,20,1200);
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace AutoArmor {
    inline bool enabled=false,onlyOnDamage=false; inline int interval=40;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Auto Armor"),&enabled);if(!enabled)return;
        ImGui::Indent(12);ImGui::PushItemWidth(180);
        ImGui::DragInt(OBFUSCATE("Interval##aa"),&interval,1.0f,10,200);
        ImGui::PopItemWidth();ImGui::Checkbox(OBFUSCATE("Only on Damage##aa"),&onlyOnDamage);
        ImGui::TextDisabled(OBFUSCATE("Priority: Netherite > Diamond > Iron > Gold"));
        ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace ESP {
    inline bool enabled=false,showBox=true,showLines=false,showNames=true;
    inline bool showHealth=true,showDist=true,showArmor=false,players=true,mobs=false;
    inline float maxDist=64.0f;
    inline ImVec4 colorPlayers=ImVec4(0,0.82f,0.95f,1),colorMobs=ImVec4(1,0.3f,0.3f,1);
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("ESP"),&enabled);if(!enabled)return;
        ImGui::Indent(12);
        ImGui::TextDisabled(OBFUSCATE("Targets"));
        ImGui::Checkbox(OBFUSCATE("Players##esp"),&players);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Mobs##esp"),&mobs);
        ImGui::Spacing();ImGui::TextDisabled(OBFUSCATE("Display"));
        ImGui::Checkbox(OBFUSCATE("Box##esp"),&showBox);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Lines##esp"),&showLines);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Names##esp"),&showNames);
        ImGui::Checkbox(OBFUSCATE("Health##esp"),&showHealth);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Dist##esp"),&showDist);ImGui::SameLine();
        ImGui::Checkbox(OBFUSCATE("Armor##esp"),&showArmor);
        ImGui::Spacing();ImGui::TextDisabled(OBFUSCATE("Colors"));
        ImGui::ColorEdit3(OBFUSCATE("Players##espcol"),(float*)&colorPlayers);
        ImGui::ColorEdit3(OBFUSCATE("Mobs##espcol"),(float*)&colorMobs);
        ImGui::PushItemWidth(220);
        ImGui::SliderFloat(OBFUSCATE("Max Dist##esp"),&maxDist,16,128,"%.0f");
        ImGui::PopItemWidth();ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace Xray {
    inline bool enabled=false,diamond=true,gold=true,iron=true,emerald=true;
    inline bool ancient=true,redstone=false,lapis=false,coal=false;
    inline void DrawPanel(){
        ImGui::Checkbox(OBFUSCATE("Xray"),&enabled);if(!enabled)return;
        ImGui::Indent(12);
        ImGui::Checkbox(OBFUSCATE("Diamond##xr"),&diamond);ImGui::SameLine();ImGui::Checkbox(OBFUSCATE("Gold##xr"),&gold);
        ImGui::Checkbox(OBFUSCATE("Iron##xr"),&iron);ImGui::SameLine();ImGui::Checkbox(OBFUSCATE("Emerald##xr"),&emerald);
        ImGui::Checkbox(OBFUSCATE("Ancient##xr"),&ancient);ImGui::SameLine();ImGui::Checkbox(OBFUSCATE("Redstone##xr"),&redstone);
        ImGui::Checkbox(OBFUSCATE("Lapis##xr"),&lapis);ImGui::SameLine();ImGui::Checkbox(OBFUSCATE("Coal##xr"),&coal);
        ImGui::Unindent(12);ImGui::Spacing();
    }
}
namespace PanicMod {
    inline void DrawPanicButton(){
        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Button,ImVec4(0.7f,0.1f,0.1f,0.8f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered,ImVec4(0.9f,0.1f,0.1f,0.9f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive,ImVec4(1,0,0,1));
        if(ImGui::Button(OBFUSCATE("!! PANIC — Disable All !!"),ImVec2(ImGui::GetContentRegionAvail().x,0))){
            KillAura::enabled=Velocity::enabled=Reach::enabled=Hitbox::enabled=false;
            AutoClick::enabled=Speed::enabled=ESP::enabled=Xray::enabled=false;
            AntiAFK::enabled=AutoArmor::enabled=ScaffoldMod::enabled=ScaffoldMod::tower=false;
        }
        ImGui::PopStyleColor(3);
    }
}
