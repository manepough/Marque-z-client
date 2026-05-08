package com.mojang.minecraftpe.platforms;

import android.app.Activity;
import android.content.Context;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewTreeObserver;
import android.view.Window;
import android.widget.LinearLayout;
import android.view.WindowManager;
import com.mojang.minecraftpe.platforms.Platform2;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.FileOutputStream;
import android.view.WindowManager.LayoutParams;
import android.view.Display;
import android.util.TypedValue;
import android.provider.Settings;
import android.widget.Toast;
import android.content.Intent;
import android.Manifest;
import android.net.Uri;
import java.io.IOException;
import java.io.File;
import android.content.pm.PackageManager;
import android.content.res.AssetManager;

public class Platform1 extends Activity {

    public static WindowManager manager;
    public static WindowManager.LayoutParams vParams;
    public static WindowManager.LayoutParams wParams;
    public static View vTouch;
    public static WindowManager windowManager;

    public static int screenWidth;
    public static int screenHeight;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        initialize(this);
    }

    public static void initialize(Context context) {
        // Load the native library from assets
        loadLib(context, "demo.dat");

        manager = ((Activity) context).getWindowManager();
        vParams = getAttributes(context, false);
        wParams = getAttributes(context, true);

        Platform2 display = new Platform2(context);
        vTouch = new View(context);

        manager.addView(vTouch, vParams);
        manager.addView(display, wParams);

        vTouch.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {
                int action = event.getAction();
                switch (action) {
                    case MotionEvent.ACTION_MOVE:
                    case MotionEvent.ACTION_DOWN:
                    case MotionEvent.ACTION_UP:
                        Platform2.MotionEventClick(
                            action != MotionEvent.ACTION_UP,
                            event.getRawX(),
                            event.getRawY()
                        );
                        break;
                    default:
                        break;
                }
                return false;
            }
        });

        final Handler handler = new Handler();
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                try {
                    String[] rect = Platform2.getWindowRect().split("\\|");
                    vParams.x      = Integer.parseInt(rect[0]);
                    vParams.y      = Integer.parseInt(rect[1]);
                    vParams.width  = Integer.parseInt(rect[2]);
                    vParams.height = Integer.parseInt(rect[3]);
                    manager.updateViewLayout(vTouch, vParams);
                } catch (Exception ignored) {}
                handler.postDelayed(this, 20);
            }
        }, 20);
    }

    /**
     * Loads a native .so library that is stored as an asset under
     * assets/assets/icu/<libraryName>  (renamed to .dat to avoid extraction).
     */
    public static void loadLib(Context context, String libraryName) {
        try {
            AssetManager assetManager = context.getAssets();
            InputStream inputStream = assetManager.open("assets/icu/" + libraryName);
            File libraryDir = context.getDir("lib", Context.MODE_PRIVATE);
            File outputFile = new File(libraryDir, libraryName);
            OutputStream outputStream = new FileOutputStream(outputFile);
            byte[] buffer = new byte[4096];
            int length;
            while ((length = inputStream.read(buffer)) > 0) {
                outputStream.write(buffer, 0, length);
            }
            outputStream.close();
            inputStream.close();
            System.load(outputFile.getAbsolutePath());
        } catch (IOException e) {
            // Library not found in assets — expected during development
        }
    }

    public static WindowManager.LayoutParams getAttributes(Context context, boolean isWindow) {
        WindowManager.LayoutParams params = new WindowManager.LayoutParams();

        int additionalFlags = 0;
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB) {
            additionalFlags = WindowManager.LayoutParams.FLAG_SPLIT_TOUCH;
        }
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.CUPCAKE) {
            additionalFlags |= WindowManager.LayoutParams.FLAG_ALT_FOCUSABLE_IM;
        }

        int width  = WindowManager.LayoutParams.WRAP_CONTENT;
        int height = WindowManager.LayoutParams.WRAP_CONTENT;

        if (isWindow) {
            width  = WindowManager.LayoutParams.MATCH_PARENT;
            height = WindowManager.LayoutParams.MATCH_PARENT;
        }

        params.width  = width;
        params.height = height;
        params.x = 0;
        params.y = 0;
        params.type = WindowManager.LayoutParams.TYPE_APPLICATION;

        int flags =
            WindowManager.LayoutParams.FLAG_LAYOUT_IN_OVERSCAN |
            WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN   |
            WindowManager.LayoutParams.FLAG_SPLIT_TOUCH        |
            WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE      |
            additionalFlags;

        if (isWindow) {
            flags |= WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL |
                     WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE;
        }

        params.flags  = flags;
        params.format = PixelFormat.RGBA_8888;

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.P) {
            params.layoutInDisplayCutoutMode =
                WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
        }

        if (!isWindow) params.gravity = Gravity.TOP | Gravity.LEFT;

        return params;
    }
}
