# ManesClient

A free, open-source Minecraft Bedrock Android client using ImGui.

## Requirements

- Android NDK r21+
- Android Studio Arctic Fox or newer
- ABI: **armeabi-v7a (32-bit)**
- Minecraft Bedrock **1.21.93**

## Build

1. Clone this repo
2. Open in Android Studio
3. Set NDK path in `local.properties`:
   ```
   ndk.dir=/path/to/ndk
   sdk.dir=/path/to/sdk
   ```
4. Run `Build > Make Project`
5. APK output: `app/build/outputs/apk/debug/`

## Project Structure

```
app/src/main/
├── java/com/mojang/minecraftpe/platforms/
│   ├── Platform1.java     ← Activity + lib loader
│   └── Platform2.java     ← GLSurfaceView renderer
├── jni/
│   ├── main.cpp           ← entry point
│   ├── menu.h             ← UI (edit features here)
│   ├── dark_theme.h       ← colour scheme
│   ├── offsets.h          ← memory offsets per MC version
│   ├── variables.h        ← global state
│   ├── Android.mk         ← NDK build rules (32-bit)
│   └── Application.mk     ← ABI settings
└── AndroidManifest.xml
```

## Notes

- Config file: `/sdcard/Download/ManesClient.json`
- 32-bit only build — offsets in `Offsets32` namespace
- Do **not** sell this. It is completely free.
