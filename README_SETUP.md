# ManesClient v2.0 — Mobile Build Setup Guide
# How to build the APK from your phone using GitHub Actions (no PC, no root)

---

## What you need
- A free GitHub account → github.com
- Your Minecraft 26.20 APK (from your phone)
- The ManesClient_v2 project files (this zip)

---

## Step 1 — Get your Minecraft APK

You need the base APK from your phone. Two ways:

**Option A — MT Manager / APK Extractor (easiest)**
1. Install "APK Extractor" from Play Store (any free one)
2. Find Minecraft → Extract
3. Save the .apk somewhere (Files app, Downloads, etc.)

**Option B — SAI (Split APKs Installer)**
1. If your MC is split APKs, use SAI to export it as a single APK

---

## Step 2 — Convert the APK to base64

You need to upload the APK as a GitHub secret. GitHub secrets are text-only,
so you convert the APK to base64 first.

**In your phone browser, go to:**
https://base64.guru/converter/encode/file

Upload your MC .apk → it gives you a giant block of text.
Copy ALL of it (select all → copy).

---

## Step 3 — Create a GitHub repository

1. Open github.com on your phone browser
2. Tap "+" → "New repository"
3. Name it: `ManesClient` (private recommended)
4. Create repository

---

## Step 4 — Upload the project files

1. In your new repo, tap "Add file" → "Upload files"
2. Upload all the files from ManesClient_v2.zip:
   - The whole `app/` folder structure
   - The `.github/workflows/build.yml` file (IMPORTANT)
3. Commit

---

## Step 5 — Add your MC APK as a secret

1. In your repo, go to: **Settings → Secrets and variables → Actions**
2. Tap "New repository secret"
3. Name: `MC_APK_BASE64`
4. Value: paste the giant base64 text from Step 2
5. Save

---

## Step 6 — Run the build

Option A — It runs automatically when you commit/push any file.

Option B — Manual trigger:
1. Go to your repo → **Actions** tab
2. Click "Build ManesClient APK"
3. Click "Run workflow" → "Run workflow"
4. Wait ~3-5 minutes

---

## Step 7 — Download your APK

When the build finishes (green checkmark ✅):
1. Click the workflow run
2. Scroll down to "Artifacts"
3. Tap **ManesClient-v2.0-MC26.20** → Download

OR if it created a Release:
1. Go to repo → **Releases**
2. Download `ManesClient_v2.apk`

---

## Step 8 — Install

1. Uninstall original Minecraft first (or the signature won't match)
2. Open the downloaded APK
3. Allow "Install unknown apps" if prompted
4. Install → Done 🎮

---

## Troubleshooting

**Build fails at "Compile C++"**
→ Your Android.mk might need the correct target. Open it and check:
   `APP_PLATFORM := android-21` (should be fine for modern MC)

**APK installs but crashes**
→ The offsets in offsets.h need to be re-verified for MC 26.20.
   The .so loads but functions are hitting wrong addresses.
   Update offsets.h and rebuild.

**"App not installed" error**
→ You didn't uninstall the original Minecraft first.

**base64 upload is too big for GitHub secrets (limit: 65KB)**
→ GitHub secrets max is 65,536 chars. A full MC APK (~170MB) is WAY too big.
→ See SPLIT_APK_GUIDE.md for the workaround using GitHub LFS or
   uploading your APK to a private release and referencing it by URL.

---

## Secret too big? Use a download URL instead

If the APK base64 is too large for GitHub secrets (it will be for MC),
add this as a secret instead:

  Secret name:  MC_APK_URL
  Secret value: a direct download link to your APK
                (Google Drive direct link, or upload to your own server)

Then in build.yml, replace the "Decode base Minecraft APK" step with:

  - name: Download base Minecraft APK
    run: |
      wget -q "${{ secrets.MC_APK_URL }}" -O base_mc.apk
      echo "Downloaded $(du -sh base_mc.apk | cut -f1)"
