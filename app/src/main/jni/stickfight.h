// stickfight.h — ManesClient v2.0
// 6 animated stick figures fighting on your menu background
// Call StickFight::render(draw_list, menuX, menuY, menuW, menuH) inside BeginDraw

#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"
#include <cmath>
#include <cstdlib>

namespace StickFight {

struct Fighter {
    float x, y, vx, vy;
    float hp, maxhp;
    ImU32 col;
    const char* name;
    int state;  // 0=walk 1=run 2=punch 3=kick 4=jump 5=spin
    int dir;    // 1=right -1=left
    int frame;
    bool dead;
    int deathTimer;
};

static const int COUNT = 6;
inline Fighter fighters[COUNT];
inline bool initialized = false;
inline int  tick = 0;
inline struct Particle { float x,y,vx,vy,r,life; ImU32 col; } parts[256];
inline int partCount = 0;

inline void spark(float x, float y, ImU32 col, int n) {
    for (int i = 0; i < n && partCount < 255; i++) {
        float a = (float)(rand() % 628) / 100.0f;
        float s = (float)(rand() % 400 + 100) / 100.0f;
        parts[partCount++] = { x, y, cosf(a)*s, sinf(a)*s-2.0f,
                               (float)(rand()%3+1), 1.0f, col };
    }
}

inline void init(float gnd) {
    const ImU32 cols[COUNT] = {
        IM_COL32(0,209,242,255),   // cyan  - hero
        IM_COL32(255,68,68,255),   // red
        IM_COL32(255,153,0,255),   // orange
        IM_COL32(200,68,255,255),  // purple
        IM_COL32(68,255,136,255),  // green
        IM_COL32(255,255,68,255),  // yellow
    };
    const char* names[COUNT] = {"Manes","Red","Orange","Purple","Green","Yellow"};
    float startX[COUNT] = {80,560,200,400,300,480};
    for (int i = 0; i < COUNT; i++) {
        fighters[i] = {
            startX[i], gnd, (float)((i%2)?-1:1)*1.5f, -8.0f,
            100.0f, 100.0f, cols[i], names[i],
            4, (i%2)?-1:1, 0, false, 0
        };
    }
    initialized = true;
}

inline void drawFighter(ImDrawList* dl, Fighter& c) {
    if (c.dead) {
        // Draw crumpled body
        dl->AddLine(ImVec2(c.x-12, c.y), ImVec2(c.x+12, c.y-8), c.col, 2.5f);
        dl->AddCircleFilled(ImVec2(c.x-14, c.y-10), 8.0f, c.col);
        return;
    }

    float f = (float)c.frame;
    float sw = sinf(f * 0.22f) * 16.0f;
    float bTop = c.y - 58.0f;
    float bBot = c.y - 30.0f;
    float mid  = c.y - 44.0f;
    float d    = (float)c.dir;

    // Head
    dl->AddCircleFilled(ImVec2(c.x, c.y - 70.0f), 10.0f, c.col);
    // Eyes
    dl->AddCircleFilled(ImVec2(c.x + d*3, c.y-72.0f), 2.0f, IM_COL32(0,0,0,200));

    // Body
    dl->AddLine(ImVec2(c.x, bTop), ImVec2(c.x, bBot), c.col, 2.5f);

    // Legs & arms by state
    if (c.state <= 1) { // walk/run
        float spd = c.state == 1 ? 1.6f : 1.0f;
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x + sw*spd, c.y), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x - sw*spd, c.y), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x - sw*0.5f*d, mid+14), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x + sw*0.5f*d, mid+14), c.col, 2.5f);
    } else if (c.state == 2) { // punch
        float ext = sinf(f*0.5f)*0.5f+0.5f;
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x-8,  c.y),    c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x+8,  c.y),    c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x + d*24*(1+ext), mid+2), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x - d*10, mid+14), c.col, 2.5f);
        if (ext > 0.75f)
            dl->AddCircleFilled(ImVec2(c.x + d*26*(1+ext), mid+2), 5.0f, IM_COL32(255,255,255,200));
    } else if (c.state == 3) { // kick
        float ka = sinf(f*0.4f)*0.5f+0.5f;
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x - 8*d, c.y),    c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x + d*30*ka, c.y - 8*(1-ka)), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x - d*12, mid+12), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x + d*8,  mid+8),  c.col, 2.5f);
    } else if (c.state == 4) { // jump
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x - 12, c.y-4),   c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x + 10,  c.y-8),  c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x - d*16, mid-10), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, mid),  ImVec2(c.x + d*8,  mid+10), c.col, 2.5f);
    } else { // spin
        float sa = f * 0.3f;
        for (int i = 0; i < 4; i++) {
            float a = sa + i * IM_PI * 0.5f;
            dl->AddLine(ImVec2(c.x, mid),
                ImVec2(c.x + cosf(a)*22, mid + sinf(a)*22), c.col, 2.5f);
        }
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x-10, c.y), c.col, 2.5f);
        dl->AddLine(ImVec2(c.x, bBot), ImVec2(c.x+10, c.y), c.col, 2.5f);
    }

    // Name tag
    dl->AddText(ImVec2(c.x - 14, c.y - 86), c.col, c.name);

    // HP bar
    float bw = 34.0f, bh = 4.0f;
    float bx = c.x - bw * 0.5f, by = c.y - 80.0f;
    dl->AddRectFilled(ImVec2(bx, by), ImVec2(bx+bw, by+bh), IM_COL32(0,0,0,120), 2.0f);
    float hpRatio = c.hp / c.maxhp;
    ImU32 hpcol = hpRatio > 0.5f ? IM_COL32(68,255,136,220)
                : hpRatio > 0.25f ? IM_COL32(255,170,0,220)
                                   : IM_COL32(255,68,68,220);
    dl->AddRectFilled(ImVec2(bx, by), ImVec2(bx + bw*hpRatio, by+bh), hpcol, 2.0f);
}

inline void update(float gnd, float minX, float maxX) {
    tick++;

    // Respawn all if all dead
    int alive = 0;
    for (int i = 0; i < COUNT; i++) if (!fighters[i].dead) alive++;
    if (alive == 0) {
        init(gnd);
        partCount = 0;
        return;
    }

    for (int i = 0; i < COUNT; i++) {
        Fighter& c = fighters[i];
        if (c.dead) {
            c.deathTimer++;
            if (c.deathTimer > 180) {
                // respawn
                c.dead = false; c.hp = c.maxhp; c.y = gnd;
                c.x = minX + (float)(rand() % (int)(maxX - minX));
                c.vy = -10.0f; c.vx = (c.dir) * 1.5f;
                c.deathTimer = 0;
            }
            continue;
        }

        c.frame++;
        c.vy += 0.55f;
        c.y  += c.vy;
        c.x  += c.vx;
        if (c.y >= gnd)  { c.y = gnd;  c.vy = 0; }
        if (c.x < minX) { c.x = minX; c.vx =  fabsf(c.vx); }
        if (c.x > maxX) { c.x = maxX; c.vx = -fabsf(c.vx); }

        // Find nearest alive enemy
        int ni = -1; float nd = 9999;
        for (int j = 0; j < COUNT; j++) {
            if (j == i || fighters[j].dead) continue;
            float d = fabsf(c.x - fighters[j].x);
            if (d < nd) { nd = d; ni = j; }
        }
        if (ni < 0) continue;
        Fighter& nearest = fighters[ni];
        c.dir = nearest.x > c.x ? 1 : -1;

        int phase = tick % (200 + i * 37);
        if (nd < 65.0f) {
            if (phase < 40)       c.state = 2; // punch
            else if (phase < 80)  c.state = 3; // kick
            else if (phase < 100) { c.state = 4; if (c.y >= gnd) c.vy = -12.0f; } // jump
            else if (phase < 140) c.state = 5; // spin
            else                  { c.state = 0; c.vx = (float)c.dir * 1.5f; }

            // Deal damage
            if ((c.state == 2 || c.state == 3) && nd < 58.0f && tick % 14 == i) {
                nearest.hp -= 4.0f;
                float mx = (c.x + nearest.x) * 0.5f;
                float my = ImMin(c.y, nearest.y) - 30.0f;
                spark(mx, my, c.col, 5);
                spark(mx, my, IM_COL32(255,255,255,255), 3);
                if (c.state == 2) nearest.vx = (float)c.dir * 3.5f;
                else              nearest.vy = -9.0f;

                if (nearest.hp <= 0) {
                    nearest.dead = true;
                    nearest.deathTimer = 0;
                    spark(nearest.x, nearest.y, nearest.col, 18);
                    spark(nearest.x, nearest.y, IM_COL32(255,255,255,255), 10);
                }
            }
        } else {
            c.state = nd > 160.0f ? 1 : 0; // run or walk
            c.vx = (float)c.dir * (nd > 160.0f ? 2.8f : 1.6f);
        }

        // Random jump
        if (tick % (280 + i*53) == 0 && c.y >= gnd) {
            c.vy = -13.0f; c.state = 4;
        }
    }

    // Update particles
    int alive_p = 0;
    for (int i = 0; i < partCount; i++) {
        auto& p = parts[i];
        p.x += p.vx; p.y += p.vy; p.vy += 0.2f; p.life -= 0.04f;
        if (p.life > 0) parts[alive_p++] = p;
    }
    partCount = alive_p;
}

inline void render(ImDrawList* dl, float menuX, float menuY, float menuW, float menuH) {
    float gnd  = menuY + menuH - 20.0f;
    float minX = menuX + 20.0f;
    float maxX = menuX + menuW - 20.0f;

    if (!initialized) init(gnd);

    // Ground line
    dl->AddLine(ImVec2(minX, gnd + 2), ImVec2(maxX, gnd + 2),
                IM_COL32(0, 209, 242, 40), 1.5f);

    update(gnd, minX, maxX);

    // Fighters
    for (int i = 0; i < COUNT; i++)
        drawFighter(dl, fighters[i]);

    // Particles
    for (int i = 0; i < partCount; i++) {
        auto& p = parts[i];
        ImU8 a = (ImU8)(p.life * 255.0f);
        ImU32 col = (p.col & 0x00FFFFFF) | ((ImU32)a << 24);
        dl->AddCircleFilled(ImVec2(p.x, p.y), p.r, col);
    }
}

} // namespace StickFight
