// main.cpp — ManesClient v2.0
// Entry point — __attribute__((constructor)) runs automatically when
// libManesClient.so is loaded by Minecraft at startup
// This sets up the render hook (eglSwapBuffers) and touch hook

#include "render_hook.h"
#include "touch_hook.h"
#include "menu.h"
#include <android/log.h>
#include <jni.h>

#define LOG(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, "ManesClient", fmt, ##__VA_ARGS__)

// This runs automatically the moment the .so is loaded — no offsets needed
__attribute__((constructor))
void ManesClient_Init() {
    LOG("=== ManesClient v2.0 Loading ===");

    // Hook eglSwapBuffers → renders ImGui GUI every frame
    RenderHook::setup();

    // Hook AInputQueue_getEvent → sends touch to ImGui
    TouchHook::setup();

    LOG("=== ManesClient v2.0 Ready ===");
}

// Optional: JNI_OnLoad as backup entry point
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* reserved) {
    LOG("JNI_OnLoad called");
    return JNI_VERSION_1_6;
}
