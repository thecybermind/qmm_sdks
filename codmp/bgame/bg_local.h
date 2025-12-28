#pragma once

#include "../qcommon/msg.h"

#include "../qcommon/qcommon.h"
#include "../qcommon/ent.h"

#include "../game/enthandle.h"

#include "bg_weapons.h"

#include <cstdint>

enum team_t;

enum animBodyPart_t
{                                       // ...
    ANIM_BP_UNUSED = 0x0,
    ANIM_BP_LEGS = 0x1,
    ANIM_BP_TORSO = 0x2,
    ANIM_BP_BOTH = 0x3,
    NUM_ANIM_BODYPARTS = 0x4,
};

enum aistateEnum_t
{                                       // ...
    AISTATE_COMBAT = 0x0,
    MAX_AISTATES = 0x1,
};
inline aistateEnum_t &operator--(aistateEnum_t &e) {
    e = static_cast<aistateEnum_t>(static_cast<int>(e) - 1);
    return e;
}
inline aistateEnum_t &operator--(aistateEnum_t &e, int i)
{
    --e;
    return e;
}

enum scriptAnimStrafeStates_t 
{                                       // ...
    ANIM_STRAFE_NOT = 0x0,
    ANIM_STRAFE_LEFT = 0x1,
    ANIM_STRAFE_RIGHT = 0x2,
    NUM_ANIM_STRAFESTATES = 0x3,
};

enum scriptAnimMoveTypes_t 
{                                       // ...
    ANIM_MT_UNUSED = 0x0,
    ANIM_MT_IDLE = 0x1,
    ANIM_MT_IDLECR = 0x2,
    ANIM_MT_IDLEPRONE = 0x3,
    ANIM_MT_WALK = 0x4, // ...
    ANIM_MT_WALKBK = 0x5, // ...
    ANIM_MT_WALKCR = 0x6, // ...
    ANIM_MT_WALKCRBK = 0x7, // ...
    ANIM_MT_WALKPRONE = 0x8, // ...
    ANIM_MT_WALKPRONEBK = 0x9, // ...
    ANIM_MT_RUN = 0xA, // ...
    ANIM_MT_RUNBK = 0xB, // ...
    ANIM_MT_RUNCR = 0xC, // ...
    ANIM_MT_RUNCRBK = 0xD, // ...
    ANIM_MT_TURNRIGHT = 0xE,
    ANIM_MT_TURNLEFT = 0xF,
    ANIM_MT_TURNRIGHTCR = 0x10,
    ANIM_MT_TURNLEFTCR = 0x11,
    ANIM_MT_CLIMBUP = 0x12,
    ANIM_MT_CLIMBDOWN = 0x13,
    ANIM_MT_SPRINT = 0x14,
    ANIM_MT_MANTLE_ROOT = 0x15,
    ANIM_MT_MANTLE_UP_57 = 0x16,
    ANIM_MT_MANTLE_UP_51 = 0x17,
    ANIM_MT_MANTLE_UP_45 = 0x18,
    ANIM_MT_MANTLE_UP_39 = 0x19,
    ANIM_MT_MANTLE_UP_33 = 0x1A,
    ANIM_MT_MANTLE_UP_27 = 0x1B,
    ANIM_MT_MANTLE_UP_21 = 0x1C,
    ANIM_MT_MANTLE_OVER_HIGH = 0x1D,
    ANIM_MT_MANTLE_OVER_MID = 0x1E,
    ANIM_MT_MANTLE_OVER_LOW = 0x1F,
    ANIM_MT_FLINCH_FORWARD = 0x20,
    ANIM_MT_FLINCH_BACKWARD = 0x21,
    ANIM_MT_FLINCH_LEFT = 0x22,
    ANIM_MT_FLINCH_RIGHT = 0x23,
    ANIM_MT_STUMBLE_FORWARD = 0x24, // ...
    ANIM_MT_STUMBLE_BACKWARD = 0x25, // ...
    ANIM_MT_STUMBLE_WALK_FORWARD = 0x26, // ...
    ANIM_MT_STUMBLE_WALK_BACKWARD = 0x27, // ...
    ANIM_MT_STUMBLE_CROUCH_FORWARD = 0x28, // ...
    ANIM_MT_STUMBLE_CROUCH_BACKWARD = 0x29, // ...
    ANIM_MT_STUMBLE_SPRINT_FORWARD = 0x2A,
    NUM_ANIM_MOVETYPES = 0x2B,
};

enum scriptAnimEventTypes_t 
{                                       // ...
    ANIM_ET_PAIN = 0x0,
    ANIM_ET_DEATH = 0x1,
    ANIM_ET_FIREWEAPON = 0x2,
    ANIM_ET_JUMP = 0x3,
    ANIM_ET_JUMPBK = 0x4,
    ANIM_ET_LAND = 0x5,
    ANIM_ET_DROPWEAPON = 0x6,
    ANIM_ET_RAISEWEAPON = 0x7,
    ANIM_ET_CLIMB_MOUNT = 0x8,
    ANIM_ET_CLIMB_DISMOUNT = 0x9,
    ANIM_ET_RELOAD = 0xA,
    ANIM_ET_CROUCH_TO_PRONE = 0xB,
    ANIM_ET_PRONE_TO_CROUCH = 0xC,
    ANIM_ET_STAND_TO_CROUCH = 0xD,
    ANIM_ET_CROUCH_TO_STAND = 0xE,
    ANIM_ET_STAND_TO_PRONE = 0xF,
    ANIM_ET_PRONE_TO_STAND = 0x10,
    ANIM_ET_MELEEATTACK = 0x11,
    ANIM_ET_KNIFE_MELEE = 0x12,
    ANIM_ET_KNIFE_MELEE_CHARGE = 0x13,
    ANIM_ET_SHELLSHOCK = 0x14,
    NUM_ANIM_EVENTTYPES = 0x15,
};

enum animScriptConditionTypes_t 
{                                       // ...
    ANIM_CONDTYPE_BITFLAGS = 0x0,       // ...
    ANIM_CONDTYPE_VALUE = 0x1,       // ...
    NUM_ANIM_CONDTYPES = 0x2,
};


enum ShockViewTypes 
{                                       // ...
    SHELLSHOCK_VIEWTYPE_BLURRED = 0x0,
    SHELLSHOCK_VIEWTYPE_FLASHED = 0x1,
    SHELLSHOCK_VIEWTYPE_NONE = 0x2,
};

union hudelem_color_t // sizeof=0x4
{                                       // XREF: DrawSingleHudElem2d+114/r
    struct
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };
    uint32_t rgba;
};
static_assert(sizeof(union hudelem_color_t) == 0x4);

enum ViewLockTypes 
{                                       // XREF: playerState_s/r
    PLAYERVIEWLOCK_NONE = 0x0,
    PLAYERVIEWLOCK_FULL = 0x1,
    PLAYERVIEWLOCK_WEAPONJITTER = 0x2,
    PLAYERVIEWLOCKCOUNT = 0x3,
};

struct scr_anim_s // sizeof=0x4
{   
    scr_anim_s()
    {
        linkPointer = NULL;
    }
    scr_anim_s(int i)
    {
        linkPointer = (const char *)i; // KISAKHACK
    }
    union
    {
        struct
        {
            uint16_t index;
            uint16_t tree;
        };
        const char* linkPointer;
    };
};

struct loadAnim_t // sizeof=0x48
{
    scr_anim_s anim;
    int32_t iNameHash;
    char szAnimName[64];
};

struct pml_t // sizeof=0x80
{                                       // ...
    float forward[3];
    float right[3];                     // ...
    float up[3];                        // ...
    float frametime;                    // ...
    int32_t msec;                           // ...
    int32_t walking;                        // ...
    int32_t groundPlane;                    // ...
    int32_t almostGroundPlane;              // ...
    trace_t groundTrace;
    float impactSpeed;
    float previous_origin[3];           // ...
    float previous_velocity[3];         // ...
};

struct animStringItem_t // sizeof=0x8
{                                       // ...
    const char *string;                 // ...
    int32_t hash;                           // ...
};

struct controller_info_t // sizeof=0x60
{                                       // ...
    float angles[6][3];
    float tag_origin_angles[3];         // ...
    float tag_origin_offset[3];         // ...
};

struct animConditionTable_t // sizeof=0x8
{                                       // ...
    animScriptConditionTypes_t type;    // ...
    animStringItem_t *values;           // ...
};

struct viewDamage_t // sizeof=0xC
{                                       // ...
    int32_t time;
    int32_t duration;
    float yaw;
};

struct shellshock_parms_t_screenblend // sizeof=0x14
{                                       // ...
    int32_t blurredFadeTime;
    int32_t blurredEffectTime;
    int32_t flashWhiteFadeTime;
    int32_t flashShotFadeTime;
    ShockViewTypes type;
};

struct shellshock_parms_t_view // sizeof=0xC
{                                       // ...
    int32_t fadeTime;
    float kickRate;
    float kickRadius;
};

struct shellshock_parms_t_sound // sizeof=0x230
{                                       // ...
    bool affect;
    char loop[64];
    char loopSilent[64];
    char end[64];
    char endAbort[64];
    // padding byte
    // padding byte
    // padding byte
    int32_t fadeInTime;
    int32_t fadeOutTime;
    float drylevel;
    float wetlevel;
    char roomtype[16];
    float channelvolume[64];
    int32_t modEndDelay;
    int32_t loopFadeTime;
    int32_t loopEndDelay;
};

struct shellshock_parms_t_lookcontrol // sizeof=0x14
{                                       // ...
    bool affect;
    // padding byte
    // padding byte
    // padding byte
    int32_t fadeTime;
    float mouseSensitivity;
    float maxPitchSpeed;
    float maxYawSpeed;
};

struct shellshock_parms_t_movement // sizeof=0x1
{                                       // ...
    bool affect;
};

const struct shellshock_parms_t // sizeof=0x268
{                                       // ...
    shellshock_parms_t_screenblend screenBlend;
    shellshock_parms_t_view view;
    shellshock_parms_t_sound sound;
    shellshock_parms_t_lookcontrol lookControl;
    shellshock_parms_t_movement movement;
    // padding byte
    // padding byte
    // padding byte
};

struct shellshock_t // sizeof=0x20
{                                       // ...
    const shellshock_parms_t* parms;
    int32_t startTime;
    int32_t duration;
    int32_t loopEndTime;
    float sensitivity;
    float viewDelta[2];
    int32_t hasSavedScreen;
};

struct __declspec(align(8)) animation_s // sizeof=0x68
{                                       // ...
    char name[64];
    int32_t initialLerp;
    float moveSpeed;
    int32_t duration;
    int32_t nameHash;
    int32_t flags;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    int64_t movetype;
    int32_t noteType;
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct animScriptCondition_t // sizeof=0xC
{                                       // ...
    int32_t index;
    uint32_t value[2];
};


struct animScriptCommand_t // sizeof=0x10
{                                       // ...
    int16_t bodyPart[2];
    int16_t animIndex[2];
    int16_t animDuration[2];
    void /*snd_alias_list_t*/* soundAlias;
};

enum animScriptParseMode_t 
{                                       // ...
    PARSEMODE_DEFINES = 0x0,
    PARSEMODE_ANIMATION = 0x1,
    PARSEMODE_CANNED_ANIMATIONS = 0x2,
    PARSEMODE_STATECHANGES = 0x3,
    PARSEMODE_EVENTS = 0x4,
    NUM_PARSEMODES = 0x5,
};

struct animScriptItem_t // sizeof=0x100
{                                       // ...
    int32_t numConditions;
    animScriptCondition_t conditions[10];
    int32_t numCommands;
    animScriptCommand_t commands[8];
};

struct animScript_t // sizeof=0x204
{                                       // ...
    int32_t numItems;
    animScriptItem_t* items[128];
};

struct scr_animtree_t // sizeof=0x4
{                                       // ...
    scr_animtree_t()
    {
        anims = NULL;
    }
    void/*XAnim_s*/* anims;                     // ...
};

struct __declspec(align(8)) animScriptData_t // sizeof=0x9A9D0
{                                       // ...
    animation_s animations[512];
    uint32_t numAnimations;
    animScript_t scriptAnims[1][43];
    animScript_t scriptCannedAnims[1][43];
    animScript_t scriptStateChange[1][1];
    animScript_t scriptEvents[21];
    animScriptItem_t scriptItems[2048];
    int32_t numScriptItems;
    scr_animtree_t animTree;            // ...
    uint16_t torsoAnim;
    uint16_t legsAnim;
    uint16_t turningAnim;
    // padding byte
    // padding byte
    void/*snd_alias_list_t*/* (__cdecl* soundAlias)(const char*);
    int32_t(__cdecl* playSoundAlias)(int32_t, void/*snd_alias_list_t*/*);
    // padding byte
    // padding byte
    // padding byte
    // padding byte
};

struct lerpFrame_t // sizeof=0x30
{                                       // ...
    float yawAngle;
    int32_t yawing;
    float pitchAngle;
    int32_t pitching;
    int32_t animationNumber;
    animation_s* animation;
    int32_t animationTime;
    float oldFramePos[3];
    float animSpeedScale;
    int32_t oldFrameSnapshotTime;
};

struct clientControllers_t // sizeof=0x60
{                                       // ...
    float angles[6][3];
    float tag_origin_angles[3];
    float tag_origin_offset[3];
};

struct clientInfo_t // sizeof=0x4CC
{                                       // ...
    int32_t infoValid;                      // ...
    int32_t nextValid;
    int32_t clientNum;
    char name[16];
    team_t team;
    team_t oldteam;
    int32_t rank;
    int32_t prestige;
    int32_t perks;
    int32_t score;
    int32_t location;
    int32_t health;
    char model[64];
    char attachModelNames[6][64];
    char attachTagNames[6][64];
    lerpFrame_t legs;
    lerpFrame_t torso;
    float lerpMoveDir;
    float lerpLean;
    float playerAngles[3];              // ...
    int32_t leftHandGun;
    int32_t dobjDirty;
    clientControllers_t control;
    uint32_t clientConditions[10][2];
    XAnimTree_s* pXAnimTree;            // ...
    int32_t iDObjWeapon;
    uint8_t weaponModel;
    // padding byte
    // padding byte
    // padding byte
    int32_t stanceTransitionTime;
    int32_t turnAnimEndTime;
    char turnAnimType;
    // padding byte
    // padding byte
    // padding byte
    int32_t attachedVehEntNum;
    int32_t attachedVehSlotIndex;
    bool hideWeapon;
    bool usingKnife;
    // padding byte
    // padding byte
};

struct bgs_t_human // sizeof=0x10
{                                       // ...
    scr_animtree_t tree;                // ...
    scr_anim_s torso;
    scr_anim_s legs;
    scr_anim_s turning;
};

struct bgs_t // sizeof=0xADD08
{                                       // ...
    animScriptData_t animScriptData;    // ...
    bgs_t_human generic_human; // ...
    int32_t time;                           // ...
    int32_t latestSnapshotTime;             // ...
    int32_t frametime;                      // ...
    int32_t anim_user;                      // ...
    XModel* (__cdecl* GetXModel)(const char*); // ...
    void(__cdecl* CreateDObj)(DObjModel_s*, uint16_t, XAnimTree_s*, int32_t, int32_t, clientInfo_t*); // ...
    uint16_t(__cdecl* AttachWeapon)(DObjModel_s*, uint16_t, clientInfo_t*); // ...
    DObj_s* (__cdecl* GetDObj)(uint32_t, int32_t); // ...
    void(__cdecl* SafeDObjFree)(uint32_t, int32_t); // ...
    void* (__cdecl* AllocXAnim)(int32_t);   // ...
    clientInfo_t clientinfo[64];        // ...
};

struct hudElemSoundInfo_t // sizeof=0x4
{                                       // ...
    int32_t lastPlayedTime;
};

enum he_type_t 
{                                       // XREF: hudelem_s/r
    HE_TYPE_FREE = 0x0,
    HE_TYPE_TEXT = 0x1,
    HE_TYPE_VALUE = 0x2,
    HE_TYPE_PLAYERNAME = 0x3,
    HE_TYPE_MAPNAME = 0x4,
    HE_TYPE_GAMETYPE = 0x5,
    HE_TYPE_MATERIAL = 0x6,
    HE_TYPE_TIMER_DOWN = 0x7,
    HE_TYPE_TIMER_UP = 0x8,
    HE_TYPE_TENTHS_TIMER_DOWN = 0x9,
    HE_TYPE_TENTHS_TIMER_UP = 0xA,
    HE_TYPE_CLOCK_DOWN = 0xB,
    HE_TYPE_CLOCK_UP = 0xC,
    HE_TYPE_WAYPOINT = 0xD,
    HE_TYPE_COUNT = 0xE,
};

struct hudelem_s // sizeof=0xA0
{                                       // XREF: .data:g_dummyHudCurrent/r
    he_type_t type;
    float x;
    float y;
    float z;                            // XREF: .rdata:off_866438/o
    int32_t targetEntNum;
    float fontScale;
    int32_t font;
    int32_t alignOrg;
    int32_t alignScreen;
    hudelem_color_t color;
    hudelem_color_t fromColor;
    int32_t fadeStartTime;                  // XREF: _memmove:UnwindDown3/o
    int32_t fadeTime;                       // XREF: Sys_GetPhysicalCpuCount+131/o
    int32_t label;
    int32_t width;
    int32_t height;
    int32_t materialIndex;
    int32_t offscreenMaterialIdx;           // XREF: Image_CopyBitmapData:off_810011/o
    int32_t fromWidth;                      // XREF: .rdata:008CF9F1/o
    int32_t fromHeight;
    int32_t scaleStartTime;                 // XREF: .rdata:008CFA4D/o
    int32_t scaleTime;
    float fromX;
    float fromY;
    int32_t fromAlignOrg;
    int32_t fromAlignScreen;                // XREF: SV_Shutdown(char const *):loc_5D1039/o
    int32_t moveStartTime;                  // XREF: .rdata:val_dc_luminance/o
    int32_t moveTime;                       // XREF: .rdata:008CFA2D/o
    int32_t time;                           // XREF: .rdata:off_866450/o
    int32_t duration;
    float value;                        // XREF: unzlocal_CheckCurrentFileCoherencyHeader:loc_67D5A6/o
    int32_t text;
    float sort;
    hudelem_color_t glowColor;
    int32_t fxBirthTime;                    // XREF: R_Cinematic_BinkOpenPath:loc_792B62/o
    int32_t fxLetterTime;                   // XREF: .rdata:008CFA1D/o
    int32_t fxDecayStartTime;               // XREF: .rdata:008CFA31/o
    int32_t fxDecayDuration;                // XREF: .rdata:008E8CBD/o
    int32_t soundID;
    int32_t flags;
};

struct MantleState // sizeof=0x10
{                                       // XREF: playerState_s/r
    float yaw;
    int32_t timer;
    int32_t transIndex;
    int32_t flags;
};

struct playerState_s_hud // sizeof=0x26C0
{                                       // XREF: playerState_s/r
    hudelem_s current[31];              // XREF: Sys_GetPhysicalCpuCount+131/o
    hudelem_s archival[31];             // XREF: SV_Shutdown(char const *):loc_5D1039/o
};

enum ActionSlotType 
{                                       // XREF: playerState_s/r
    ACTIONSLOTTYPE_DONOTHING = 0x0,
    ACTIONSLOTTYPE_SPECIFYWEAPON = 0x1,
    ACTIONSLOTTYPE_ALTWEAPONTOGGLE = 0x2,
    ACTIONSLOTTYPE_NIGHTVISION = 0x3,
    ACTIONSLOTTYPECOUNT = 0x4,
};

struct ActionSlotParam_SpecifyWeapon // sizeof=0x4
{                                       // XREF: ActionSlotParam/r
    uint32_t index;
};

struct ActionSlotParam // sizeof=0x4
{                                       // XREF: playerState_s/r
    ActionSlotParam_SpecifyWeapon specifyWeapon;
};

struct SprintState // sizeof=0x14
{                                       // XREF: playerState_s/r cg_s/r
    int32_t sprintButtonUpRequired;
    int32_t sprintDelay;
    int32_t lastSprintStart;
    int32_t lastSprintEnd;
    int32_t sprintStartMaxLength;
};

enum objectiveState_t 
{                                       // XREF: objective_t/r
                                        // Scr_Objective_Add/r ...
    OBJST_EMPTY = 0x0,
    OBJST_ACTIVE = 0x1,
    OBJST_INVISIBLE = 0x2,
    OBJST_DONE = 0x3,
    OBJST_CURRENT = 0x4,
    OBJST_FAILED = 0x5,
    OBJST_NUMSTATES = 0x6,
};

struct objective_t // sizeof=0x1C
{                                       // XREF: playerState_s/r
    objectiveState_t state;
    float origin[3];                    // XREF: .data:00946428/o
    int32_t entNum;
    int32_t teamNum;                        // XREF: _memmove+2E8/o
    // _memcpy+2E8/o
    int32_t icon;
};

enum pmflags_t  // (MP/SP same)
{
    PMF_PRONE = 1 << 0,
    PMF_DUCKED = 1 << 1,
    PMF_MANTLE = 1 << 2,
    PMF_LADDER = 1 << 3,
    PMF_SIGHT_AIMING = 1 << 4,
    PMF_BACKWARDS_RUN = 1 << 5,
    PMF_WALKING = 1 << 6,
    PMF_TIME_HARDLANDING = 1 << 7,
    PMF_TIME_KNOCKBACK = 1 << 8,
    PMF_PRONEMOVE_OVERRIDDEN = 1 << 9,
    PMF_RESPAWNED = 1 << 10,
    PMF_FROZEN = 1 << 11,
    PMF_NO_PRONE = 1 << 12,
    PMF_LADDER_FALL = 1 << 13,
    PMF_JUMPING = 1 << 14,
    PMF_SPRINTING = 1 << 15,
    PMF_SHELLSHOCKED = 1 << 16,
    PMF_MELEE_CHARGE = 1 << 17,
    PMF_NO_SPRINT = 1 << 18,
    PMF_NO_JUMP = 1 << 19,
    PMF_VEHICLE_ATTACHED = 1 << 20
};

enum pmtype_t 
{
    PM_NORMAL = 0x0,
    PM_NORMAL_LINKED = 0x1,
    PM_NOCLIP = 0x2,
    PM_UFO = 0x3,
    PM_SPECTATOR = 0x4,
    PM_INTERMISSION = 0x5,
    PM_LASTSTAND = 0x6,
    PM_DEAD = 0x7,
    PM_DEAD_LINKED = 0x8,
};

struct playerState_s // sizeof=0x2F64
{                                       // XREF: gclient_s/r
                                        // clSnapshot_t/r ...
    int32_t commandTime;
    pmtype_t pm_type;
    int32_t bobCycle;                       // XREF: R_ChangeState_1(GfxCmdBufState *,uint)+2AB/o
    int32_t pm_flags; // LWSS: See "#define PMF_"
    int32_t weapFlags;
    int32_t otherFlags;                     // XREF: SpectatorClientEndFrame(gentity_s *):loc_4F9901/r
    // SpectatorClientEndFrame(gentity_s *):loc_4F990E/r ...
    int32_t pm_time;
    float origin[3];                    // XREF: SV_GetClientPositionAtTime(int,int,float * const)+12C/r
    // SV_GetClientPositionAtTime(int,int,float * const)+138/r ...
    float velocity[3];
    float oldVelocity[2];
    int32_t weaponTime;
    int32_t weaponDelay;
    int32_t grenadeTimeLeft;
    int32_t throwBackGrenadeOwner;
    int32_t throwBackGrenadeTimeLeft;
    int32_t weaponRestrictKickTime;
    int32_t foliageSoundTime;
    int32_t gravity;
    float leanf;
    int32_t speed;
    float delta_angles[3];
    int32_t groundEntityNum;
    float vLadderVec[3];
    int32_t jumpTime;
    float jumpOriginZ;                  // XREF: .rdata:008CFA21/o
    // .rdata:008CFA25/o ...
    int32_t legsTimer;
    int32_t legsAnim;
    int32_t torsoTimer;
    int32_t torsoAnim;
    int32_t legsAnimDuration;
    int32_t torsoAnimDuration;
    int32_t damageTimer;
    int32_t damageDuration;
    int32_t flinchYawAnim;
    int32_t movementDir;
    int32_t eFlags;                         // XREF: SpectatorClientEndFrame(gentity_s *):doFollow/r
    int32_t eventSequence;                  // XREF: R_HW_SetSamplerState(IDirect3DDevice9 *,uint,uint,uint)+337/o
    int32_t events[4];
    uint32_t eventParms[4];
    int32_t oldEventSequence;
    int32_t clientNum;
    int32_t offHandIndex;
    OffhandSecondaryClass offhandSecondary;
    uint32_t weapon;
    int32_t weaponstate;
    uint32_t weaponShotCount;
    float fWeaponPosFrac;
    int32_t adsDelayTime;
    int32_t spreadOverride;
    int32_t spreadOverrideState;
    int32_t viewmodelIndex;
    float viewangles[3];
    int32_t viewHeightTarget;
    float viewHeightCurrent;
    int32_t viewHeightLerpTime;
    int32_t viewHeightLerpTarget;
    int32_t viewHeightLerpDown;
    float viewAngleClampBase[2];
    float viewAngleClampRange[2];
    int32_t damageEvent;
    int32_t damageYaw;
    int32_t damagePitch;
    int32_t damageCount;
    int32_t stats[5];                       // XREF: SV_GetClientPositionAtTime(int,int,float * const)+E9/r
    int32_t ammo[128];
    int32_t ammoclip[128];
    uint32_t weapons[4];
    uint32_t weaponold[4];
    uint32_t weaponrechamber[4];
    float proneDirection;
    float proneDirectionPitch;
    float proneTorsoPitch;
    ViewLockTypes viewlocked;
    int32_t viewlocked_entNum;
    int32_t cursorHint;
    int32_t cursorHintString;
    int32_t cursorHintEntIndex;
    int32_t iCompassPlayerInfo;
    int32_t radarEnabled;
    int32_t locationSelectionInfo;
    SprintState sprintState;
    float fTorsoPitch;
    float fWaistPitch;
    float holdBreathScale;
    int32_t holdBreathTimer;
    float moveSpeedScaleMultiplier;
    MantleState mantleState;
    float meleeChargeYaw;
    int32_t meleeChargeDist;
    int32_t meleeChargeTime;
    int32_t perks;
    ActionSlotType actionSlotType[4];
    ActionSlotParam actionSlotParam[4];
    int32_t entityEventSequence;
    int32_t weapAnim;
    float aimSpreadScale;
    int32_t shellshockIndex;
    int32_t shellshockTime;
    int32_t shellshockDuration;
    float dofNearStart;
    float dofNearEnd;
    float dofFarStart;
    float dofFarEnd;
    float dofNearBlur;
    float dofFarBlur;
    float dofViewmodelStart;
    float dofViewmodelEnd;
    int32_t hudElemLastAssignedSoundID;
    objective_t objective[16];          // XREF: _memmove+2E8/o
    // _memcpy+2E8/o ...
    uint8_t weaponmodels[128];
    int32_t deltaTime;
    int32_t killCamEntity;                  // XREF: SpectatorClientEndFrame(gentity_s *)+163/w
    // SpectatorClientEndFrame(gentity_s *)+17B/w
    playerState_s_hud hud;
    // XREF: SV_Shutdown(char const *):loc_5D1039/o
    // TRACK_sv_main(void)+A/o ...
};

struct CEntPlayerInfo // sizeof=0xC
{                                       // ...
    clientControllers_t* control;       // ...
    uint8_t tag[6];             // ...
    // padding byte
    // padding byte
};

struct CEntTurretAngles // sizeof=0x8
{                                       // ...
    float pitch;
    float yaw;
};

struct CEntTurretInfo // sizeof=0x10
{                                       // ...
    union
    {
        CEntTurretAngles angles;
        const float *viewAngles;
    };
    float barrelPitch;
    bool playerUsing;
    uint8_t tag_aim;
    uint8_t tag_aim_animated;
    uint8_t tag_flash;
};

struct CEntVehicleInfo // sizeof=0x24
{                                       // ...
    int16_t pitch;
    int16_t yaw;
    int16_t roll;
    int16_t barrelPitch;
    float barrelRoll;
    int16_t steerYaw;
    // padding byte
    // padding byte
    float time;
    uint16_t wheelFraction[4];
    uint8_t wheelBoneIndex[4];
    uint8_t tag_body;
    uint8_t tag_turret;
    uint8_t tag_barrel;
    // padding byte
};


struct CEntFx // sizeof=0x8  (SP/MP Same)
{                                       // ...
    int32_t triggerTime;
    void* /*FxEffect**/ effect;
};


struct GfxSkinCacheEntry // sizeof=0xC
{                                       // ...
    uint32_t frameCount;
    int skinnedCachedOffset;
    uint16_t numSkinnedVerts;
    uint16_t ageCount;
};

struct cpose_t // sizeof=0x64
{                                       // ...
    uint16_t lightingHandle;
    uint8_t eType;
    uint8_t eTypeUnion;
    uint8_t localClientNum;
    volatile uint32_t cullIn;
    uint8_t isRagdoll;
    int32_t ragdollHandle;
    int32_t killcamRagdollHandle;
    int32_t physObjId;
    float origin[3];
    float angles[3];
    GfxSkinCacheEntry skinCacheEntry;
    union // sizeof=0x24
    {                                       // ...
        CEntPlayerInfo player;
        CEntTurretInfo turret;
        CEntVehicleInfo vehicle;
        CEntFx fx;
    };
};

struct centity_s // sizeof=0x1DC
{                                       // ...
    cpose_t pose;
    LerpEntityState currentState;
    entityState_s nextState;
    bool nextValid;
    bool bMuzzleFlash;
    bool bTrailMade;
    // padding byte
    int32_t previousEventSequence;
    int32_t miscTime;
    float lightingOrigin[3];
    XAnimTree_s* tree;
};

struct turretInfo_s // sizeof=0x48
{                                       // ...
    int32_t inuse;                          // ...
    int32_t flags;
    int32_t fireTime;
    float arcmin[2];
    float arcmax[2];
    float dropPitch;
    int32_t stance;
    int32_t prevStance;
    int32_t fireSndDelay;
    float userOrigin[3];
    float playerSpread;
    float pitchCap;
    int32_t triggerDown;
    uint8_t fireSnd;
    uint8_t fireSndPlayer;
    uint8_t stopSnd;
    uint8_t stopSndPlayer;
};

struct VehicleRideSlot_t // sizeof=0xC
{                                       // ...
    uint32_t tagName;
    int32_t boneIdx;
    int32_t entNum;
};

struct vehicle_node_t // sizeof=0x44 // (SP/MP Same)
{                                       // ...
    uint16_t name;
    uint16_t target;
    uint16_t script_linkname;
    uint16_t script_noteworthy;
    int16_t index;
    // padding byte
    // padding byte
    int32_t rotated;
    float speed;
    float lookAhead;
    float origin[3];
    float dir[3];
    float angles[3];
    float length;
    int16_t nextIdx;
    int16_t prevIdx;
};

struct vehicle_pathpos_t // sizeof=0xC0 // (SP/MP Same)
{                                       // ...
    int16_t nodeIdx;
    int16_t endOfPath;
    float frac;
    float speed;
    float lookAhead;
    float slide;
    float origin[3];
    float angles[3];
    float lookPos[3];
    vehicle_node_t switchNode[2];
};

struct vehicle_physic_t // sizeof=0xF8
{                                       // ...
    float origin[3];
    float prevOrigin[3];
    float angles[3];
    float prevAngles[3];
    float maxAngleVel[3];
    float yawAccel;
    float yawDecel;
    char inputAccelerationOLD;
    char inputTurning;
    // padding byte
    // padding byte
    float driverPedal;
    float driverSteer;
    int32_t onGround;
    float colVelDelta[3];
    float mins[3];
    float maxs[3];
    float vel[3];
    float bodyVel[3];
    float rotVel[3];
    float accel[3];
    float maxPitchAngle;
    float maxRollAngle;
    float wheelZVel[4];
    float wheelZPos[4];
    int32_t wheelSurfType[4];
    float worldTilt[3];
    float worldTiltVel[3];
};

struct VehicleTags // sizeof=0x60
{                                       // ...
    VehicleRideSlot_t riderSlots[3];
    int32_t detach;
    int32_t popout;
    int32_t body;
    int32_t turret;
    int32_t turret_base;
    int32_t barrel;
    int32_t flash[5];
    int32_t wheel[4];
};

enum VehicleMoveState 
{                                       // ...
    VEH_MOVESTATE_STOP = 0x0,
    VEH_MOVESTATE_MOVE = 0x1,
    VEH_MOVESTATE_HOVER = 0x2,
};

enum VehicleTurretState 
{                                       // ...
    VEH_TURRET_STOPPED = 0x0,
    VEH_TURRET_STOPPING = 0x1,
    VEH_TURRET_MOVING = 0x2,
};

struct VehicleTurret // sizeof=0x14 // (SP/MP Same)
{                                       // ...
    int32_t fireTime;
    int32_t fireBarrel;
    float barrelOffset;
    int32_t barrelBlocked;
    VehicleTurretState turretState;
};

struct VehicleJitter // sizeof=0x3C // (SP/MP Same)
{                                       // ...
    int32_t jitterPeriodMin;
    int32_t jitterPeriodMax;
    int32_t jitterEndTime;
    float jitterOffsetRange[3];
    float jitterDeltaAccel[3];
    float jitterAccel[3];
    float jitterPos[3];
};

struct VehicleHover // sizeof=0x1C // (SP/MP same)
{                                       // ...
    float hoverRadius;
    float hoverSpeed;
    float hoverAccel;
    float hoverGoalPos[3];
    int32_t useHoverAccelForAngles;
};

struct scr_vehicle_s // sizeof=0x354
{                                       // ...
    vehicle_pathpos_t pathPos;
    vehicle_physic_t phys;
    int32_t entNum;                         // ...
    int16_t infoIdx;
    // padding byte
    // padding byte
    int32_t flags;
    int32_t team;
    VehicleMoveState moveState;
    int16_t waitNode;
    // padding byte
    // padding byte
    float waitSpeed;
    VehicleTurret turret;
    VehicleJitter jitter;
    VehicleHover hover;
    int32_t drawOnCompass;
    uint16_t lookAtText0;
    uint16_t lookAtText1;
    int32_t manualMode;
    float manualSpeed;
    float manualAccel;
    float manualDecel;
    float manualTime;
    float speed;
    float maxDragSpeed;
    float turningAbility;
    int32_t hasTarget;
    int32_t hasTargetYaw;
    int32_t hasGoalYaw;
    int32_t stopAtGoal;
    int32_t stopping;
    int32_t targetEnt;
    EntHandle lookAtEnt;
    float targetOrigin[3];
    float targetOffset[3];
    float targetYaw;
    float goalPosition[3];
    float goalYaw;
    float prevGoalYaw;
    float yawOverShoot;
    int32_t yawSlowDown;
    float nearGoalNotifyDist;
    float joltDir[2];
    float joltTime;
    float joltWave;
    float joltSpeed;
    float joltDecel;
    int32_t playEngineSound;
    EntHandle idleSndEnt;
    EntHandle engineSndEnt;
    float idleSndLerp;
    float engineSndLerp;
    VehicleTags boneIndex;
    int32_t turretHitNum;
    float forcedMaterialSpeed;
};

enum proneCheckType_t 
{                                       // ...
    PCT_CLIENT = 0x0,
    PCT_ACTOR = 0x1,
};

enum itemType_t 
{                                       // ...
    IT_BAD = 0x0,
    IT_WEAPON = 0x1,
};

struct gitem_s // sizeof=0x4
{
    itemType_t giType;
};

enum PmStanceFrontBack 
{                                       // ...
    PM_STANCE_STAND = 0x0,
    PM_STANCE_PRONE = 0x1,
    PM_STANCE_CROUCH = 0x2,
    PM_STANCE_BACKWARD_FIRST = 0x3,
    PM_STANCE_BACKWARD_RUN = 0x3,
    PM_STANCE_BACKWARD_PRONE = 0x4,
    PM_STANCE_BACKWARD_CROUCH = 0x5,
    NUM_PM_STANCE_FRONTBACK = 0x6,
};

struct viewLerpWaypoint_s // sizeof=0xC
{                                       // ...
    int32_t iFrac;
    float fViewHeight;
    int32_t iOffset;
};

// bg_mantle
struct MantleResults // sizeof=0x38
{                                       // ...
    float dir[3];                       // ...
    float startPos[3];                  // ...
    float ledgePos[3];
    float endPos[3];
    int32_t flags;                          // ...
    int32_t duration;
};

struct MantleAnimTransition // sizeof=0xC
{                                       // ...
    int32_t upAnimIndex;                    // ...
    int32_t overAnimIndex;                  // ...
    float height;                       // ...
};

// bg_weapons
struct BulletFireParams // sizeof=0x40
{                                       // ...
    int32_t weaponEntIndex;                 // ...
    int32_t ignoreEntIndex;                 // ...
    float damageMultiplier;             // ...
    int32_t methodOfDeath;                  // ...
    float origStart[3];                 // ...
    float start[3];                     // ...
    float end[3];                       // ...
    float dir[3];                       // ...
};

struct BulletTraceResults // sizeof=0x44
{                                       // ...
    trace_t trace;                      // ...
    struct gentity_s *hitEnt;                  // ...
    float hitPos[3];                    // ...
    bool ignoreHitEnt;                  // ...
    // padding byte
    // padding byte
    // padding byte
    int32_t depthSurfaceType;               // ...
};

struct viewState_t // sizeof=0x24
{                                       // ...
    playerState_s *ps;                  // ...
    int32_t damageTime;                     // ...
    int32_t time;                           // ...
    float v_dmg_pitch;                  // ...
    float v_dmg_roll;                   // ...
    float xyspeed;                      // ...
    float frametime;                    // ...
    float fLastIdleFactor;              // ...
    int32_t*weapIdleTime;                  // ...
};

struct weaponState_t // sizeof=0x54
{                                       // ...
    const playerState_s *ps;            // ...
    float xyspeed;                      // ...
    float frametime;                    // ...
    float vLastMoveAng[3];              // ...
    float fLastIdleFactor;              // ...
    int32_t time;                           // ...
    int32_t damageTime;                     // ...
    float v_dmg_pitch;                  // ...
    float v_dmg_roll;                   // ...
    float vGunOffset[3];                // ...
    float vGunSpeed[3];                 // ...
    float swayAngles[3];                // ...
    int32_t*weapIdleTime;                  // ...
};

// bg_vehicles_mp
enum vehicleRideSlots_t 
{
    VEHICLE_RIDESLOT_DRIVER = 0x0,
    VEHICLE_RIDESLOT_PASSENGER = 0x1,
    VEHICLE_RIDESLOT_GUNNER = 0x2,
    VEHICLE_RIDESLOTS_COUNT = 0x3,
};


const float playerMins[] = { -15.0, -15.0, 0.0 };
const float playerMaxs[] = { 15.0, 15.0, 70.0 };

const int serverOnlyEvents[4] = { 31, 20, 19, -1 }; // idb
const int singleClientEvents[13] = { 6, 7, 8, 34, 13, 14, 32, 33, 34, 37, 42, 43, -1 }; // idb
