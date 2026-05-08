// ManesClient — offsets.h
// Target: Minecraft Bedrock 26.20 (1.26.20) — latest stable May 2026
//
// HOW TO UPDATE OFFSETS FOR A NEW MC VERSION:
//   1. Pull libminecraftpe.so from the new APK  (apktool d or unzip)
//   2. Open in IDA Pro / Ghidra — select ARM 32-bit (armeabi-v7a) or ARM64
//   3. Find each function by the comment next to the offset
//   4. Replace the hex value with the new file offset
//   5. Rebuild & test — start with Font, NormalTick, Attack, Fov as a sanity check
//
// QUICK VERSION BUMP CHECKLIST:
//   [ ] Font                  (camera / font size patch)
//   [ ] NormalTick            (main player loop — many features depend on this)
//   [ ] Attack / GameMode     (kill aura)
//   [ ] PlayerAuthInput       (head rotation)
//   [ ] ClientInstanceOnTick  (tick hook entry point)
//   [ ] Fov                   (fov hack)
//   [ ] FullBright            (gamma patch)
//   [ ] SetupFog / FogState   (fog hack)
//   All others — re-verify if behaviour changes after the update
//
// TIP: Minor patch versions (e.g. 1.21.93 → 1.21.100) rarely move stable
//      system functions.  Major bumps (e.g. 1.21 → 1.22) often do.

// ── 64-bit placeholder (not used in 32-bit build, kept for compatibility) ────
#if defined(__aarch64__)
namespace Offsets64 {
    enum Offsets64 {
        // Not used — this is a 32-bit build
        // Add 64-bit offsets here if you ever add arm64-v8a back
        Placeholder = 0x0,
    };
}
#endif

// ── 32-bit offsets for MC 26.20 ────────────────────────────────────────────
// NOTE: These are carried over from 1.21.111 as a base.
//       Functions that are stable across minor versions usually keep the
//       same offset. Re-verify any offset that behaves unexpectedly.
#if defined(__ARM_ARCH_7A__) || (!defined(__aarch64__) && !defined(__x86_64__))
namespace Offsets32 {
    enum Offsets32 {
        // ── Camera ──────────────────────────────────────────────────────────
        Font                  = 0x1A3C304, // Default 1 float
        NoHurtCam             = 0x3103870, // CameraBobSystem::tick
        NoCamDistortion       = 0xAF56A14, // CameraPortalDistortionSystem::_tick
        NoBoatRotation        = 0x3114BB8, // CameraVehicleRotationLookSystem::tick
        NoCamSleep            = 0xAF57550, // _tickSleepFade SUB
        PlaceCamera           = 0xB1DC87C, // CameraBlendSystem::_tick
        XrayCameraThird       = 0xB1DB2A4, // CameraAvoidanceSystem::tick

        // ── Water / Lava ────────────────────────────────────────────────────
        WaterTrigger1         = 0x46578D8, // ActorHeadWasInWater
        WaterTrigger2         = 0x63B7B9C, // ActorHeadInWaterFlagComponent SUB
        WaterTrigger3         = 0x3E35F94, // WaterSplashEffectRequestComponent SUB
        WaterSpeed            = 0x6E52A70, // doWaterMoveSystem sub
        LavaSpeed             = 0x6407F30, // doLavaMoveSystem sub
        LavaDrown             = 0x6DB9528, // MobMovementGravity::tickLavaGravity
        WaterDrown            = 0x6DB7558, // MobMovementGravity::tickPlayerWaterGravity

        // ── Movement ────────────────────────────────────────────────────────
        SlowDownTriggers      = 0x654C0E4, // BlockMovementSlowdownMultiplierSystemImpl
        NoSlowDown            = 0x645D230, // ItemUseSlowdownSystemImpl sub
        Noclip                = 0x63D2760, // MoveCollisionSystem::System sub
        SpeedHack             = 0x6498748, // doDefaultMoveSystems 2
        JumpHack              = 0x6D8D7F0, // return 0.42
        Gravity               = 0x6D88C20, // -0.08 float
        SetNoJumpDelay        = 0x9DDB410, // MobJump::setNoJumpDelay
        SetOnGround           = 0x4F42DFC, // ActorEntityAccess addOrRemoveComponent<OnGroundFlagComponent>
        MobIsJumping          = 0x9DD8840, // ActorEntityAccess addOrRemoveComponent<MobIsJumpingFlag>

        // ── FOV ─────────────────────────────────────────────────────────────
        Fov                   = 0x4BBDB00, // CameraAPI returns float

        // ── Building ────────────────────────────────────────────────────────
        AutoClickMine         = 0x9CC2258, // GameMode STP
        FastBridge            = 0x9CC3650, // GameMode::useItemOn (client)
        BlockReach            = 0x9CC4B70, // returns 7 or 12 float

        // ── Player input ────────────────────────────────────────────────────
        PlayerAuthInput       = 0x7772168, // Player head rotation
        NativeKeyHandler      = 0x9FA5130, // nativeKeyHandler

        // ── Game state ──────────────────────────────────────────────────────
        InMainMenu            = 0x4086AB4, // CubemapBackgroundScreen
        InLanGame1            = 0xB26A008, // NetherNet::SimpleNetworkInterfaceImpl::SendPacket
        InLanGame2            = 0xB26A234, // NetherNet::SimpleNetworkInterfaceImpl::ReadPacket

        // ── Items / Economy ─────────────────────────────────────────────────
        FastDrop              = 0x4358EDC, // GuiData::_tickItemDrop float field
        UnlockMarket          = 0x46CF620, // Entitlement::isOwned
        GetMaxPlayers         = 0xB14C3C4, // AppPlatform::getMaxPlayers

        // ── Rendering ───────────────────────────────────────────────────────
        FogState              = 0x4C08F08, // LevelRendererCamera::_getFogDensitySettingType
        SetupFog              = 0x4C00420, // LevelRendererPlayer::setupFog
        FullBright            = 0x4C6B95C, // BaseOptions::getGamma
        NoBlur1               = 0x4BBE1E4, // FullScreenEffectRenderer::renderHeadlocked
        NoBlur2               = 0x4BBEAB4, // FullScreenEffectRenderer::render
        ShowPaperdoll         = 0x4373FB8, // HudPlayerRenderer::update
        Block_getRenderLayer  = 0xA52E0F4, // Block::getRenderLayer
        RebuildAllChunkGeometry= 0x4BF10A8,// LevelRenderer::rebuildAllRenderChunkGeometry
        VignetteRenderer      = 0x4376084, // HudVignetteRenderer::render
        NoNametags            = 0x4AEE80C, // BaseActorRenderer::renderText

        // ── Actors ──────────────────────────────────────────────────────────
        ForEachActivePlayer   = 0x9E9B8F4, // GameplayUserManager::forEachActivePlayer
        GetRuntimeActor       = 0xA6B0D68, // Level::getRuntimeActorList
        IsAttackable          = 0x995B500, // Actor::isAttackableGamemode
        Attack                = 0x9CC075C, // GameMode::_attack
        LerpMotion            = 0x9947CDC, // Actor::lerpMotion
        NormalTick            = 0x4BEDA24, // LocalPlayer::normalTick
        Swing                 = 0x4BF031C, // LocalPlayer::swing
        SetSprinting          = 0x4BF05B8, // LocalPlayer::setSprinting
        GetEntityTypeId       = 0x9937698, // Actor::getEntityTypeId
        GetHealth             = 0x9943D0,  // Actor::getHealth
        SetClimbing           = 0x9945610, // Actor::setClimbing
        SetYHeadRot           = 0x995AF30, // Actor::setYHeadRot
        SetYBodyRot           = 0x986C5D4, // Mob::setYBodyRotation
        SetInvisible          = 0x99597B8, // Actor::setInvisible
        Intersects            = 0x994727C, // Actor::intersects
        GetYHeadRot           = 0x995AE58, // Actor::getYHeadRot
        InitMaxAutoStep       = 0x9956C54, // Actor::_initializeMaxAutoStep
        GetAABBDim            = 0x993AE58, // Actor::getAABBDim
        IsEmoting             = 0x9E072A8, // Player::isEmoting
        GetNameTag            = 0x994C468, // Actor::getNameTag
        GetDimensionBlockSource= 0x9931890,// Actor::getDimensionBlockSource

        // ── Abilities ───────────────────────────────────────────────────────
        GetAbilities          = 0x9DF943C, // Player::getAbilities
        GetLayer              = 0x9DF9450, // LayeredAbilities::getLayer
        SetAbility            = 0x9DF87E0, // Abilities::setAbility

        // ── UI / Client ─────────────────────────────────────────────────────
        Subtitle              = 0x43164C4, // TileMessage::setSubtitle
        ClientInstanceOnTick  = 0x4478734, // ClientInstance::onTick
        HandleDestroyOrAttack = 0x4462B60, // ClientInputCallbacks::handleDestoryOrAttackButtonPress
        PlayUI                = 0x448AED8, // ClientInstance::playUI
        DisplayMessage        = 0x4BF196C, // LocalPlayer::displayClientMessage
        ScreenName            = 0x448482C, // ClientInstance::getScreenName

        // ── Anti cheat / misc ────────────────────────────────────────────────
        FastDrowning          = 0x6DB9528, // same as LavaDrown — double use
        NoCaveVignette        = 0x4376084, // same node as VignetteRenderer
        NoEmoteCooldown       = 0x9E0DEAD, // Player::isEmoting cooldown — VERIFY

        // ── HUD / Crosshair (new in ManesClient v1.1) ────────────────────
        // These are not memory patches — crosshair is drawn via ImGui
        // ForegroundDrawList in crosshair.h.  No offsets needed here.
        // If you want to HIDE the vanilla crosshair via memory patch:
        //   CrosshairAlpha = 0x0,  // TODO: find HudCrosshairRenderer::render
        //   CrosshairScale = 0x0,  // TODO: find crosshair scale float field
    };
}

// Alias namespace so existing code that uses Offsets64 still compiles on 32-bit
namespace Offsets64 = Offsets32;
#endif
