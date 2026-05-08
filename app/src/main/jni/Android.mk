LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

# ── Dobby static library ──────────────────────────────────────────────────────
include $(CLEAR_VARS)
LOCAL_MODULE    := libdobby
LOCAL_SRC_FILES := libraries/$(TARGET_ARCH_ABI)/libdobby.a
include $(PREBUILT_STATIC_LIBRARY)

# ── ManesClient shared library ────────────────────────────────────────────────
include $(CLEAR_VARS)

LOCAL_MODULE    := ManesClient

LOCAL_CFLAGS    := -w -s -Wno-error=format-security -fvisibility=hidden \
                   -fpermissive -fexceptions -marm

LOCAL_CPPFLAGS  := -w -s -Wno-error=format-security -fvisibility=hidden \
                   -Werror -std=c++17 -Wno-error=c++11-narrowing \
                   -fpermissive -Wall -fexceptions -marm

LOCAL_LDFLAGS   += -Wl,--gc-sections,--strip-all,-llog

LOCAL_LDLIBS    := -lz -landroid -lEGL -lGLESv2

LOCAL_ARM_MODE  := arm

LOCAL_C_INCLUDES += \
    $(LOCAL_PATH) \
    $(LOCAL_PATH)/Includes \
    $(LOCAL_PATH)/ImGui \
    $(LOCAL_PATH)/ImGui/backends

LOCAL_STATIC_LIBRARIES := libdobby

LOCAL_SRC_FILES := \
    main.cpp \
    ImGui/imgui.cpp \
    ImGui/imgui_draw.cpp \
    ImGui/imgui_widgets.cpp \
    ImGui/imgui_tables.cpp \
    ImGui/backends/imgui_impl_opengl3.cpp \
    ImGui/backends/imgui_impl_android.cpp \
    KittyMemory/KittyMemory.cpp \
    KittyMemory/MemoryPatch.cpp \
    KittyMemory/MemoryBackup.cpp \
    KittyMemory/KittyUtils.cpp \
    KittyScanner/KittyMemory_new.cpp \
    KittyScanner/KittyScanner.cpp \
    KittyScanner/KittyUtils.cpp \
    Substrate/hde64.c \
    Substrate/SubstrateDebug.cpp \
    Substrate/SubstrateHook.cpp \
    Substrate/SubstratePosixMemory.cpp \
    Arm64/And64InlineHook.cpp \
    ENCRYPT/oxorany.cpp

include $(BUILD_SHARED_LIBRARY)
