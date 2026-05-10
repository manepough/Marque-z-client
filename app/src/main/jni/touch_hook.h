// touch_hook.h — ManesClient v2.0
// Hooks AInputQueue_getEvent from libandroid.so
// Forwards finger position + tap state to ImGui so the floating button works
// NO MC offsets needed — hooks the Android system library directly
// Call TouchHook::setup() from your constructor

#pragma once
#include <android/input.h>
#include <dlfcn.h>
#include <android/log.h>
#include "imgui/imgui.h"
#include "And64InlineHook/And64InlineHook.hpp"

#define TLOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "ManesClient", fmt, ##__VA_ARGS__)

namespace TouchHook {

typedef int32_t (*getEvent_t)(AInputQueue*, AInputEvent**);
inline getEvent_t orig_getEvent = nullptr;

inline int32_t hook_getEvent(AInputQueue* queue, AInputEvent** outEvent) {
    int32_t result = orig_getEvent(queue, outEvent);

    if (result >= 0 && outEvent && *outEvent) {
        int32_t type = AInputEvent_getType(*outEvent);
        if (type == AINPUT_EVENT_TYPE_MOTION) {
            ImGuiIO& io = ImGui::GetIO();
            int32_t action = AMotionEvent_getAction(*outEvent);
            int32_t masked = action & AMOTION_EVENT_ACTION_MASK;

            float x = AMotionEvent_getX(*outEvent, 0);
            float y = AMotionEvent_getY(*outEvent, 0);

            io.MousePos = ImVec2(x, y);

            switch (masked) {
                case AMOTION_EVENT_ACTION_DOWN:
                case AMOTION_EVENT_ACTION_POINTER_DOWN:
                    io.MouseDown[0] = true;
                    break;
                case AMOTION_EVENT_ACTION_UP:
                case AMOTION_EVENT_ACTION_POINTER_UP:
                case AMOTION_EVENT_ACTION_CANCEL:
                    io.MouseDown[0] = false;
                    break;
                case AMOTION_EVENT_ACTION_MOVE:
                    // position already updated above
                    break;
            }
        }
    }
    return result;
}

inline void setup() {
    void* lib = dlopen("libandroid.so", RTLD_NOW);
    if (!lib) { TLOG("Failed to open libandroid.so"); return; }
    void* fn = dlsym(lib, "AInputQueue_getEvent");
    if (!fn) { TLOG("Failed to find AInputQueue_getEvent"); return; }
    A64HookFunction(fn, (void*)hook_getEvent, (void**)&orig_getEvent);
    TLOG("Touch hook: %s", orig_getEvent ? "SUCCESS" : "FAILED");
}

} // namespace TouchHook
