LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libafjni
LOCAL_STATIC_LIBRARIES := libboost libafutil libjsoncpp libBox2D libluabind liblua libpng liblog4cplus libpoly2tri libvorbis libogg
LOCAL_SHARED_LIBRARIES := libopenal-soft
LOCAL_LDLIBS := -landroid -llog -lGLESv2 -lz
LOCAL_SRC_FILES := \
    main_android.cpp \
    Platform.cpp \
    PlatformAndroid.cpp \
    Utils.cpp \
    Game.cpp \
    OGL.cpp \
    InputManager.cpp \
    InputKeyboard.cpp \
    InputTouchScreen.cpp \
    InputMouse.cpp \
    Scene.cpp \
    SceneObject.cpp \
    TextureManager.cpp \
    Logger.cpp \
    Renderer.cpp \
    AssetManager.cpp \
    SceneObjectAsset.cpp \
    SceneAsset.cpp \
    Image.cpp \
    SceneObjectFactory.cpp \
    Script.cpp \
    Script2.cpp \
    SceneObjectManager.cpp \
    Component.cpp \
    PhasedComponentManager.cpp \
    PhysicsComponentManager.cpp \
    CollisionComponentManager.cpp \
    RenderComponentManager.cpp \
    CameraComponent.cpp \
    PlayerComponent.cpp \
    ShroomCannonComponent.cpp \
    MissileComponent.cpp \
    ExplosionComponent.cpp \
    BlasterShotComponent.cpp \
    PhysicsBodyComponent.cpp \
    PhysicsJointComponent.cpp \
    PhysicsRopeComponent.cpp \
    CollisionFilter.cpp \
    CollisionDieComponent.cpp \
    CollisionSparksComponent.cpp \
    CollisionDamageComponent.cpp \
    CollisionSensorComponent.cpp \
    CollisionRopeComponent.cpp \
    RenderComponent.cpp \
    RenderPolygonsComponent.cpp \
    RenderQuadComponent.cpp \
    RenderTerrainComponent.cpp \
    RenderBackgroundComponent.cpp \
    RenderStripeComponent.cpp \
    RenderDamageComponent.cpp \
    ParticleEffectComponent.cpp \
    ParticleEmmiter.cpp \
    Drawable.cpp \
    Animation.cpp \
    AnimationComponent.cpp \
    Const.cpp \
    HealthBarComponent.cpp \
    ScriptSensorListener.cpp \
    JointProxy.cpp \
    ScriptComponent.cpp \
    ShroomGuardianComponent.cpp \
    TextArea.cpp \
    DialogComponent.cpp \
    ScriptDialogComponent.cpp \
    Settings.cpp \
    HermitePath.cpp \
    SingleTweening.cpp \
    SequentialTweening.cpp \
    PathComponent.cpp \
    FollowPathComponent.cpp \
    DebugDraw.cpp \
    ShroomSnakeComponent.cpp \
    KnobComponent.cpp \
    Level.cpp \
    MainMenuComponent.cpp \
    ScriptMainMenuComponent.cpp \
    Frame.cpp \
    PickerComponent.cpp \
    ScriptPickerComponent.cpp \
    UIComponentManager.cpp \
    PauseMenuComponent.cpp \
    RopeLaunchComponent.cpp \
    RopePullComponent.cpp \
    RenderBatch.cpp \
    RenderQueue.cpp \
    TetrobotComponent.cpp \
    TetrocrabComponent.cpp \
    LaserComponent.cpp \
    RenderBeamComponent.cpp \
    Light.cpp \
    RenderLightComponent.cpp \
    PointLight.cpp \
    LightComponent.cpp \
    ConeLight.cpp \
    LineLight.cpp \
    AudioManager.cpp \
    RenderDottedLineComponent.cpp \
    RenderDottedCircleComponent.cpp \
    GravityGunAimComponent.cpp \
    GravityGunComponent.cpp \
    ScriptCollisionComponent.cpp \
    FadeOutComponent.cpp \
    TargetableComponent.cpp \
    BehaviorRoamComponent.cpp \
    BehaviorComponent.cpp \
    BehaviorSeekComponent.cpp \
    BehaviorAvoidComponent.cpp \
    BehaviorDetourComponent.cpp \
    BehaviorInterceptComponent.cpp \
    AudioSourceDummy.cpp \
    RenderHealthbarComponent.cpp \
    SpawnerComponent.cpp \
    ScorpComponent.cpp \
    FireballComponent.cpp \
    TeleportComponent.cpp \
    StainedGlassComponent.cpp \
    LevelCompletedComponent.cpp \
    GameOverComponent.cpp \
    NumericIndicatorComponent.cpp \
    PowerupComponent.cpp \
    GoalIndicatorComponent.cpp \
    GoalAreaComponent.cpp \
    BloodComponent.cpp \
    StunnedComponent.cpp \
    InvulnerabilityComponent.cpp \
    RenderChainComponent.cpp \
    ChoiceComponent.cpp \
    ScriptChoiceComponent.cpp \
    WeaponComponent.cpp \
    WeaponBlasterComponent.cpp \
    WeaponGGComponent.cpp \
    WeaponFireballComponent.cpp \
    WeaponStationComponent.cpp \
    WeaponShotgunComponent.cpp \
    BuckshotComponent.cpp \
    RenderTrailComponent.cpp \
    BarrelComponent.cpp \
    TurretComponent.cpp \
    GoalComponent.cpp \
    PyrobotComponent.cpp \
    WeaponFlamethrowerComponent.cpp \
    MeasurementComponent.cpp \
    Inventory.cpp \
    InventoryComponent.cpp \
    PlaceholderComponent.cpp \
    TimebombComponent.cpp \
    BossSkullComponent.cpp \
    BossSkullGunComponent.cpp \
    SpiderComponent.cpp \
    SceneInstance.cpp \
    BabySpiderComponent.cpp \
    SpiderNestComponent.cpp \
    BossQueenComponent.cpp \
    CollisionCancelComponent.cpp \
    WeaponPistolComponent.cpp \
    BulletComponent.cpp \
    EnforcerComponent.cpp \
    SentryComponent.cpp \
    WeaponMachineGunComponent.cpp \
    GorgerComponent.cpp \
    WeaponRLauncherComponent.cpp \
    RocketComponent.cpp \
    WeaponProxMineComponent.cpp \
    ProxMineComponent.cpp \
    InputContext.cpp \
    InputController.cpp \
    InputControllerPC.cpp \
    InputContextCutscenePC.cpp \
    InputContextPlayerPC.cpp \
    InputContextUIPC.cpp \
    InputControllerTS.cpp \
    InputContextCutsceneTS.cpp \
    InputContextPlayerTS.cpp \
    InputContextUITS.cpp \
    LaserSightComponent.cpp \
    RoboArmComponent.cpp \
    InputContextRoboArmPC.cpp \
    InputContextRoboArmTS.cpp \
    RenderProjComponent.cpp \
    CrateComponent.cpp \
    WeaponChainsawComponent.cpp \
    OrboComponent.cpp \
    RenderLBoltComponent.cpp \
    WeaponLGunComponent.cpp \
    WarderComponent.cpp \
    WeaponPlasmaGunComponent.cpp \
    PlasmaComponent.cpp \
    KeeperComponent.cpp \
    DummyComponent.cpp \
    DudeComponent.cpp \
    CollisionModifyComponent.cpp \
    RingLight.cpp \
    HealthStationComponent.cpp \
    SummonComponent.cpp \
    BossCoreProtectorComponent.cpp \
    ToxicSplashComponent.cpp \
    ToxicCloudComponent.cpp \
    AcidWormComponent.cpp \
    WeaponAcidballComponent.cpp \
    AcidballComponent.cpp \
    CentipedeComponent.cpp \
    WeaponSpitterComponent.cpp \
    SpitComponent.cpp \
    BeetleComponent.cpp \
    RenderTentacleComponent.cpp \
    TentaclePulseComponent.cpp \
    TentacleSwingComponent.cpp \
    TentacleAttractComponent.cpp \
    InputContextBoatPC.cpp \
    BoatComponent.cpp \
    InputContextBoatTS.cpp \
    PowerGenComponent.cpp \
    TentacleSquidComponent.cpp \
    BossSquidComponent.cpp \
    InputContextMechPC.cpp \
    MechComponent.cpp \
    InputContextMechTS.cpp \
    HomerComponent.cpp \
    SeekerComponent.cpp \
    WeaponSeekerComponent.cpp \
    WeaponEShieldComponent.cpp \
    InputContextTurret.cpp \
    InputContextTurretPC.cpp \
    InputContextTurretTS.cpp \
    GovernedTurretComponent.cpp \
    BossChopperComponent.cpp \
    FloatComponent.cpp \
    CreatureComponent.cpp \
    GasCloudComponent.cpp \
    OctopusComponent.cpp \
    WalkerComponent.cpp \
    SnakeComponent.cpp \
    CountdownComponent.cpp \
    BossBuddyComponent.cpp \
    QuadPulseComponent.cpp \
    BuddySideComponent.cpp \
    WeaponRopeComponent.cpp \
    BuddyTongueComponent.cpp \
    NapalmComponent.cpp \
    BossNatanComponent.cpp \
    DizzyComponent.cpp \
    PowerBeamComponent.cpp \
    Tetrobot2Component.cpp \
    WeaponHeaterComponent.cpp \
    WeaponAimComponent.cpp \
    GuardianComponent.cpp \
    RenderSaturationComponent.cpp \
    FootageTrackComponent.cpp \
    RenderTextComponent.cpp \
    LetterBoxComponent.cpp \
    InputHintComponent.cpp \
    CrosshairComponent.cpp \
    SawerComponent.cpp \
    TentacleInflateComponent.cpp \
    BuzzSawComponent.cpp \
    CollisionBuzzSawComponent.cpp \
    CollisionBuzzSawMissileComponent.cpp \
    LRFileInterface.cpp \
    LRRenderInterface.cpp \
    LRSystemInterface.cpp \
    LRManager.cpp \
    LRComponent.cpp \
    Texture.cpp \
    UITimerComponent.cpp \
    ScriptUITimerComponent.cpp \
    InputBinding.cpp \
    UserData.cpp \
    UpgradeManager.cpp \
    UpgradeDisplayComponent.cpp \
    GameLogAppender.cpp \
    Statistics.cpp \
    PuzzleHintAreaComponent.cpp \
    PuzzleHintIndicatorComponent.cpp \
    PuzzleHintComponent.cpp \
    InputGamepad.cpp \
    InputGamepadBinding.cpp \
    BossBeholderComponent.cpp \
    DamageFlashComponent.cpp \
    StaminaBarComponent.cpp \
    GameShell.cpp \
    SteamShell.cpp \
    DummyShell.cpp

include $(BUILD_SHARED_LIBRARY)
