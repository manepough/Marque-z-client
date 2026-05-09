// render_hook.h — ManesClient v2.0
// Hooks eglSwapBuffers (system lib — NO offsets needed, works on any MC version)
// Initializes ImGui and renders the full GUI every frame
// Include in main.cpp and call RenderHook::setup() from constructor

#pragma once
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <dlfcn.h>
#include <android/log.h>

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "And64InlineHook/And64InlineHook.hpp"
#include "floatingbutton.h"
#include "stickfight.h"
#include "crosshair.h"
#include "theme.h"

#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "ManesClient", fmt, ##__VA_ARGS__)

// Forward declare your menu draw function from menu.h
extern void BeginDraw();

namespace RenderHook {

typedef EGLBoolean (*eglSwapBuffers_t)(EGLDisplay, EGLSurface);
inline eglSwapBuffers_t orig = nullptr;
inline bool imgui_ready      = false;

inline void applyStyle() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding    = 10.0f;
    s.ChildRounding     = 6.0f;
    s.FrameRounding     = 5.0f;
    s.GrabRounding      = 5.0f;
    s.PopupRounding     = 5.0f;
    s.ScrollbarRounding = 6.0f;
    s.WindowBorderSize  = 1.0f;
    s.FramePadding      = ImVec2(8, 5);
    s.ItemSpacing       = ImVec2(8, 6);

    ImVec4* c = s.Colors;
    c[ImGuiCol_WindowBg]          = ImVec4(0.07f, 0.07f, 0.10f, 0.96f);
    c[ImGuiCol_ChildBg]           = ImVec4(0.05f, 0.05f, 0.08f, 0.80f);
    c[ImGuiCol_Border]            = ImVec4(0.00f, 0.82f, 0.95f, 0.25f);
    c[ImGuiCol_FrameBg]           = ImVec4(0.10f, 0.10f, 0.15f, 0.80f);
    c[ImGuiCol_FrameBgHovered]    = ImVec4(0.00f, 0.82f, 0.95f, 0.15f);
    c[ImGuiCol_TitleBg]           = ImVec4(0.04f, 0.04f, 0.06f, 1.00f);
    c[ImGuiCol_TitleBgActive]     = ImVec4(0.00f, 0.12f, 0.18f, 1.00f);
    c[ImGuiCol_CheckMark]         = ImVec4(0.00f, 0.82f, 0.95f, 1.00f);
    c[ImGuiCol_SliderGrab]        = ImVec4(0.00f, 0.82f, 0.95f, 1.00f);
    c[ImGuiCol_SliderGrabActive]  = ImVec4(0.00f, 0.60f, 0.75f, 1.00f);
    c[ImGuiCol_Button]            = ImVec4(0.00f, 0.82f, 0.95f, 0.20f);
    c[ImGuiCol_ButtonHovered]     = ImVec4(0.00f, 0.82f, 0.95f, 0.40f);
    c[ImGuiCol_ButtonActive]      = ImVec4(0.00f, 0.82f, 0.95f, 0.60f);
    c[ImGuiCol_Tab]               = ImVec4(0.08f, 0.08f, 0.12f, 1.00f);
    c[ImGuiCol_TabHovered]        = ImVec4(0.00f, 0.82f, 0.95f, 0.25f);
    c[ImGuiCol_TabActive]         = ImVec4(0.00f, 0.20f, 0.28f, 1.00f);
    c[ImGuiCol_Header]            = ImVec4(0.00f, 0.82f, 0.95f, 0.15f);
    c[ImGuiCol_HeaderHovered]     = ImVec4(0.00f, 0.82f, 0.95f, 0.25f);
    c[ImGuiCol_HeaderActive]      = ImVec4(0.00f, 0.82f, 0.95f, 0.40f);
    c[ImGuiCol_SeparatorHovered]  = ImVec4(0.00f, 0.82f, 0.95f, 0.50f);
    c[ImGuiCol_ResizeGrip]        = ImVec4(0.00f, 0.82f, 0.95f, 0.25f);
    c[ImGuiCol_ResizeGripHovered] = ImVec4(0.00f, 0.82f, 0.95f, 0.50f);
    c[ImGuiCol_ScrollbarBg]       = ImVec4(0.05f, 0.05f, 0.08f, 0.80f);
    c[ImGuiCol_ScrollbarGrab]     = ImVec4(0.00f, 0.82f, 0.95f, 0.40f);
    c[ImGuiCol_Text]              = ImVec4(0.90f, 0.90f, 0.95f, 1.00f);
    c[ImGuiCol_TextDisabled]      = ImVec4(0.40f, 0.40f, 0.50f, 1.00f);
}

inline void initImGui(EGLDisplay display, EGLSurface surface) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO();
    EGLint w = 1080, h = 1920;
    eglQuerySurface(display, surface, EGL_WIDTH,  &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
    io.DisplaySize     = ImVec2((float)w, (float)h);
    io.FontGlobalScale = 2.2f;   // scale up for mobile screen
    io.IniFilename     = nullptr; // no imgui.ini file

    ImGui_ImplOpenGL3_Init("#version 300 es");
    applyStyle();

    LOG("ImGui initialized — display: %dx%d", w, h);
    imgui_ready = true;
}

inline EGLBoolean hook_eglSwapBuffers(EGLDisplay display, EGLSurface surface) {
    if (!imgui_ready) {
        initImGui(display, surface);
    }

    ImGuiIO& io = ImGui::GetIO();
    EGLint w, h;
    eglQuerySurface(display, surface, EGL_WIDTH,  &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);
    io.DisplaySize = ImVec2((float)w, (float)h);

    // Update theme accent color
    Theme::tick();
    Theme::apply(ImGui::GetStyle());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui::NewFrame();

    // Always-on: floating button + crosshair + stick fighters
    FloatingButton::init(io.DisplaySize.x, io.DisplaySize.y);
    FloatingButton::render();
    RenderCustomCrosshair();
    StickFight::render(
        ImGui::GetBackgroundDrawList(),
        0, 0, io.DisplaySize.x, io.DisplaySize.y
    );

    // Menu — only when floating button is tapped open
    if (FloatingButton::menuOpen) {
        BeginDraw();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig(display, surface);
}

inline void setup() {
    void* egl = dlopen("libEGL.so", RTLD_NOW);
    if (!egl) { LOG("Failed to open libEGL.so"); return; }

    void* fn = dlsym(egl, "eglSwapBuffers");
    if (!fn) { LOG("Failed to find eglSwapBuffers"); return; }

    bool ok = A64HookFunction(fn, (void*)hook_eglSwapBuffers, (void**)&orig);
    LOG("eglSwapBuffers hook: %s", ok ? "SUCCESS" : "FAILED");
}

} // namespace RenderHook
