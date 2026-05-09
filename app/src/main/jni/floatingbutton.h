// floatingbutton.h — ManesClient v2.0
// Draggable floating button — tap to toggle GUI, drag to move
// Call FloatingButton::init(w,h) once then FloatingButton::render() every frame

#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <cmath>

namespace FloatingButton {
    inline bool  menuOpen=false,dragging=false,initialized=false;
    inline float btnX=0,btnY=0,radius=30,dragOffX=0,dragOffY=0;
    inline float dragStartX=0,dragStartY=0,pulseT=0;

    inline void init(float sw,float sh){
        if(initialized)return;
        btnX=sw-radius-24;btnY=sh*0.38f;initialized=true;
    }

    inline void render(){
        ImGuiIO& io=ImGui::GetIO();
        ImDrawList* dl=ImGui::GetForegroundDrawList();
        pulseT+=0.05f;
        float cx=btnX,cy=btnY,r=radius;
        ImVec2 mouse=io.MousePos;
        bool down=io.MouseDown[0],click=ImGui::IsMouseClicked(0);
        float dx=mouse.x-cx,dy=mouse.y-cy;
        bool hov=(sqrtf(dx*dx+dy*dy)<=r+8);

        if(click&&hov){dragging=true;dragOffX=mouse.x-cx;dragOffY=mouse.y-cy;dragStartX=cx;dragStartY=cy;}
        if(dragging){
            if(down){btnX=ImClamp(mouse.x-dragOffX,r,io.DisplaySize.x-r);btnY=ImClamp(mouse.y-dragOffY,r,io.DisplaySize.y-r);cx=btnX;cy=btnY;}
            else{float mv=sqrtf((btnX-dragStartX)*(btnX-dragStartX)+(btnY-dragStartY)*(btnY-dragStartY));if(mv<8)menuOpen=!menuOpen;dragging=false;}
        }

        if(menuOpen){float p=sinf(pulseT)*0.5f+0.5f;dl->AddCircle(ImVec2(cx,cy),r+10+p*6,IM_COL32(0,209,242,(ImU8)(p*80+20)),0,1.5f);}
        dl->AddCircleFilled(ImVec2(cx+2,cy+3),r,IM_COL32(0,0,0,80));
        dl->AddCircleFilled(ImVec2(cx,cy),r,IM_COL32(15,15,22,235));
        ImU32 bc=menuOpen?IM_COL32(0,209,242,255):hov?IM_COL32(0,209,242,160):IM_COL32(80,80,100,200);
        dl->AddCircle(ImVec2(cx,cy),r,bc,0,2.0f);

        ImU32 ic=menuOpen?IM_COL32(0,209,242,255):IM_COL32(180,180,200,255);
        float ix=cx-9,iy=cy-9,iw=18,ih=18,lw=2.2f;
        dl->AddLine(ImVec2(ix,iy+ih),ImVec2(ix,iy),ic,lw);
        dl->AddLine(ImVec2(ix,iy),ImVec2(ix+iw*0.5f,iy+ih*0.55f),ic,lw);
        dl->AddLine(ImVec2(ix+iw*0.5f,iy+ih*0.55f),ImVec2(ix+iw,iy),ic,lw);
        dl->AddLine(ImVec2(ix+iw,iy),ImVec2(ix+iw,iy+ih),ic,lw);

        ImU32 dc=menuOpen?IM_COL32(80,255,120,255):IM_COL32(120,120,140,255);
        dl->AddCircleFilled(ImVec2(cx+r*0.62f,cy-r*0.62f),5,dc);
    }
}
