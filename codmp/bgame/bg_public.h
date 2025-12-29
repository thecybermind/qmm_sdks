#pragma once
#include "../qcommon/q_shared.h"
#include "../qcommon/msg.h"
#include "../game/enthandle.h"
#include "../game/client.h"
#define abs8(x) abs(x)
#define abs32(x) abs(x)
enum entity_event_t
{
    EV_NONE,
    EV_FOLIAGE_SOUND,
    EV_STOP_WEAPON_SOUND,
    EV_SOUND_ALIAS,
    EV_SOUND_ALIAS_AS_MASTER,
    EV_STOPSOUNDS,
    EV_STANCE_FORCE_STAND,
    EV_STANCE_FORCE_CROUCH,
    EV_STANCE_FORCE_PRONE,
    EV_ITEM_PICKUP,
    EV_AMMO_PICKUP,
    EV_NOAMMO,
    EV_EMPTYCLIP,
    EV_EMPTY_OFFHAND,
    EV_RESET_ADS,
    EV_RELOAD,
    EV_RELOAD_FROM_EMPTY,
    EV_RELOAD_START,
    EV_RELOAD_END,
    EV_RELOAD_START_NOTIFY,
    EV_RELOAD_ADDAMMO,
    EV_RAISE_WEAPON,
    EV_FIRST_RAISE_WEAPON,
    EV_PUTAWAY_WEAPON,
    EV_WEAPON_ALT,
    EV_PULLBACK_WEAPON,
    EV_FIRE_WEAPON,
    EV_FIRE_WEAPON_LASTSHOT,
    EV_RECHAMBER_WEAPON,
    EV_EJECT_BRASS,
    EV_MELEE_SWIPE,
    EV_FIRE_MELEE,
    EV_PREP_OFFHAND,
    EV_USE_OFFHAND,
    EV_SWITCH_OFFHAND,
    EV_MELEE_HIT,
    EV_MELEE_MISS,
    EV_MELEE_BLOOD,
    EV_FIRE_WEAPON_MG42,
    EV_FIRE_QUADBARREL_1,
    EV_FIRE_QUADBARREL_2,
    EV_BULLET_HIT,
    EV_BULLET_HIT_CLIENT_SMALL,
    EV_BULLET_HIT_CLIENT_LARGE,
    EV_GRENADE_BOUNCE,
    EV_GRENADE_EXPLODE,
    EV_ROCKET_EXPLODE,
    EV_ROCKET_EXPLODE_NOMARKS,
    EV_FLASHBANG_EXPLODE,
    EV_CUSTOM_EXPLODE,
    EV_CUSTOM_EXPLODE_NOMARKS,
    EV_CHANGE_TO_DUD,
    EV_DUD_EXPLODE,
    EV_DUD_IMPACT,
    EV_BULLET,
    EV_PLAY_FX,
    EV_PLAY_FX_ON_TAG,
    EV_PHYS_EXPLOSION_SPHERE,
    EV_PHYS_EXPLOSION_CYLINDER,
    EV_PHYS_EXPLOSION_JOLT,
    EV_PHYS_JITTER,
    EV_EARTHQUAKE,
    EV_GRENADE_SUICIDE,
    EV_DETONATE,
    EV_NIGHTVISION_WEAR,
    EV_NIGHTVISION_REMOVE,
    EV_OBITUARY,
    EV_NO_FRAG_GRENADE_HINT,
    EV_NO_SPECIAL_GRENADE_HINT,
    EV_TARGET_TOO_CLOSE_HINT,
    EV_TARGET_NOT_ENOUGH_CLEARANCE,
    EV_LOCKON_REQUIRED_HINT,
    EV_FOOTSTEP_SPRINT,
    EV_FOOTSTEP_RUN,
    EV_FOOTSTEP_WALK,
    EV_FOOTSTEP_PRONE,
    EV_JUMP,
    EV_LANDING_FIRST,
    EV_LANDING_LAST,
    EV_LANDING_PAIN_FIRST,
    EV_LANDING_PAIN_LAST,
    EV_MAX_EVENTS,
};
static const char *entityTypeNames[17] =
{
    "ET_GENERAL",
    "ET_PLAYER",
    "ET_PLAYER_CORPSE",
    "ET_ITEM",
    "ET_MISSILE",
    "ET_INVISIBLE",
    "ET_SCRIPTMOVER",
    "ET_SOUND_BLEND",
    "ET_FX",
    "ET_LOOP_FX",
    "ET_PRIMARY_LIGHT",
    "ET_MG42",
    "ET_HELICOPTER",
    "ET_PLANE",
    "ET_VEHICLE",
    "ET_VEHICLE_COLLMAP",
    "ET_VEHICLE_CORPSE"
};
static const char *eventnames[135] =
{
  "EV_NONE",
  "EV_FOLIAGE_SOUND",
  "EV_STOP_WEAPON_SOUND",
  "EV_SOUND_ALIAS",
  "EV_SOUND_ALIAS_AS_MASTER",
  "EV_STOPSOUNDS",
  "EV_STANCE_FORCE_STAND",
  "EV_STANCE_FORCE_CROUCH",
  "EV_STANCE_FORCE_PRONE",
  "EV_ITEM_PICKUP",
  "EV_AMMO_PICKUP",
  "EV_NOAMMO",
  "EV_EMPTYCLIP",
  "EV_EMPTY_OFFHAND",
  "EV_RESET_ADS",
  "EV_RELOAD",
  "EV_RELOAD_FROM_EMPTY",
  "EV_RELOAD_START",
  "EV_RELOAD_END",
  "EV_RELOAD_START_NOTIFY",
  "EV_RELOAD_ADDAMMO",
  "EV_RAISE_WEAPON",
  "EV_FIRST_RAISE_WEAPON",
  "EV_PUTAWAY_WEAPON",
  "EV_WEAPON_ALT",
  "EV_PULLBACK_WEAPON",
  "EV_FIRE_WEAPON",
  "EV_FIRE_WEAPON_LASTSHOT",
  "EV_RECHAMBER_WEAPON",
  "EV_EJECT_BRASS",
  "EV_MELEE_SWIPE",
  "EV_FIRE_MELEE",
  "EV_PREP_OFFHAND",
  "EV_USE_OFFHAND",
  "EV_SWITCH_OFFHAND",
  "EV_MELEE_HIT",
  "EV_MELEE_MISS",
  "EV_MELEE_BLOOD",
  "EV_FIRE_WEAPON_MG42",
  "EV_FIRE_QUADBARREL_1",
  "EV_FIRE_QUADBARREL_2",
  "EV_BULLET_HIT",
  "EV_BULLET_HIT_CLIENT_SMALL",
  "EV_BULLET_HIT_CLIENT_LARGE",
  "EV_GRENADE_BOUNCE",
  "EV_GRENADE_EXPLODE",
  "EV_ROCKET_EXPLODE",
  "EV_ROCKET_EXPLODE_NOMARKS",
  "EV_FLASHBANG_EXPLODE",
  "EV_CUSTOM_EXPLODE",
  "EV_CUSTOM_EXPLODE_NOMARKS",
  "EV_CHANGE_TO_DUD",
  "EV_DUD_EXPLODE",
  "EV_DUD_IMPACT",
  "EV_BULLET",
  "EV_PLAY_FX",
  "EV_PLAY_FX_ON_TAG",
  "EV_PHYS_EXPLOSION_SPHERE",
  "EV_PHYS_EXPLOSION_CYLINDER",
  "EV_PHYS_EXPLOSION_JOLT",
  "EV_PHYS_JITTER",
  "EV_EARTHQUAKE",
  "EV_GRENADE_SUICIDE",
  "EV_DETONATE",
  "EV_NIGHTVISION_WEAR",
  "EV_NIGHTVISION_REMOVE",
  "EV_OBITUARY",
  "EV_NO_FRAG_GRENADE_HINT",
  "EV_NO_SPECIAL_GRENADE_HINT",
  "EV_TARGET_TOO_CLOSE_HINT",
  "EV_TARGET_NOT_ENOUGH_CLEARANCE",
  "EV_LOCKON_REQUIRED_HINT",
  "EV_FOOTSTEP_SPRINT",
  "EV_FOOTSTEP_RUN",
  "EV_FOOTSTEP_WALK",
  "EV_FOOTSTEP_PRONE",
  "EV_JUMP",
  "EV_LANDING_DEFAULT",
  "EV_LANDING_BARK",
  "EV_LANDING_BRICK",
  "EV_LANDING_CARPET",
  "EV_LANDING_CLOTH",
  "EV_LANDING_CONCRETE",
  "EV_LANDING_DIRT",
  "EV_LANDING_FLESH",
  "EV_LANDING_FOLIAGE",
  "EV_LANDING_GLASS",
  "EV_LANDING_GRASS",
  "EV_LANDING_GRAVEL",
  "EV_LANDING_ICE",
  "EV_LANDING_METAL",
  "EV_LANDING_MUD",
  "EV_LANDING_PAPER",
  "EV_LANDING_PLASTER",
  "EV_LANDING_ROCK",
  "EV_LANDING_SAND",
  "EV_LANDING_SNOW",
  "EV_LANDING_WATER",
  "EV_LANDING_WOOD",
  "EV_LANDING_ASPHALT",
  "EV_LANDING_CERAMIC",
  "EV_LANDING_PLASTIC",
  "EV_LANDING_RUBBER",
  "EV_LANDING_CUSHION",
  "EV_LANDING_FRUIT",
  "EV_LANDING_PAINTEDMETAL",
  "EV_LANDING_PAIN_DEFAULT",
  "EV_LANDING_PAIN_BARK",
  "EV_LANDING_PAIN_BRICK",
  "EV_LANDING_PAIN_CARPET",
  "EV_LANDING_PAIN_CLOTH",
  "EV_LANDING_PAIN_CONCRETE",
  "EV_LANDING_PAIN_DIRT",
  "EV_LANDING_PAIN_FLESH",
  "EV_LANDING_PAIN_FOLIAGE",
  "EV_LANDING_PAIN_GLASS",
  "EV_LANDING_PAIN_GRASS",
  "EV_LANDING_PAIN_GRAVEL",
  "EV_LANDING_PAIN_ICE",
  "EV_LANDING_PAIN_METAL",
  "EV_LANDING_PAIN_MUD",
  "EV_LANDING_PAIN_PAPER",
  "EV_LANDING_PAIN_PLASTER",
  "EV_LANDING_PAIN_ROCK",
  "EV_LANDING_PAIN_SAND",
  "EV_LANDING_PAIN_SNOW",
  "EV_LANDING_PAIN_WATER",
  "EV_LANDING_PAIN_WOOD",
  "EV_LANDING_PAIN_ASPHALT",
  "EV_LANDING_PAIN_CERAMIC",
  "EV_LANDING_PAIN_PLASTIC",
  "EV_LANDING_PAIN_RUBBER",
  "EV_LANDING_PAIN_CUSHION",
  "EV_LANDING_PAIN_FRUIT",
  "EV_LANDING_PAIN_PAINTEDMETAL"
};
struct pmove_t 
{                                       
    playerState_s *ps;                  
    usercmd_s cmd;                      
    usercmd_s oldcmd;                   
    int tracemask;                      
    int numtouch;
    int touchents[32];
    float mins[3];                      
    float maxs[3];                      
    float xyspeed;
    int proneChange;
    float maxSprintTimeMultiplier;
    bool mantleStarted;                 
    float mantleEndPos[3];              
    int mantleDuration;                 
    int viewChangeTime;                 
    float viewChange;
    unsigned char handler;            
};
struct pmoveHandler_t 
{
    void( *trace)(trace_t *, const float *, const float *, const float *, const float *, int, int);
    void( *playerEvent)(int, int);
};
struct tagInfo_s 
{
    gentity_s *parent;
    gentity_s *next;
    uint16_t name;
    int32_t index;
    float axis[4][3];
    float parentInvAxis[4][3];
};
struct trigger_ent_t 
{                                       
    int32_t threshold;
    int32_t accumulate;
    int32_t timestamp;
    int32_t singleUserEntIndex;
    bool requireLookAt;
};
struct item_ent_t 
{                                       
    int32_t ammoCount;
    int32_t clipAmmoCount;
    int32_t index;
};
struct mover_ent_t 
{                                       
    float decelTime;
    float aDecelTime;
    float speed;
    float aSpeed;
    float midTime;
    float aMidTime;
    float pos1[3];
    float pos2[3];
    float pos3[3];
    float apos1[3];
    float apos2[3];
    float apos3[3];
};
struct entityShared_t 
{                                       
    uint8_t linked;
    uint8_t bmodel;
    uint8_t svFlags;
    int32_t clientMask[2];
    uint8_t inuse;              
    int32_t broadcastTime;
    float mins[3];                      
    float maxs[3];
    int32_t contents;                       
    float absmin[3];                    
    float absmax[3];
    float currentOrigin[3];             
    float currentAngles[3];
    EntHandle ownerNum;
    int32_t eventTime;
};
enum MissileStage
{                                       
    MISSILESTAGE_SOFTLAUNCH,
    MISSILESTAGE_ASCENT,
    MISSILESTAGE_DESCENT,
};
enum MissileFlightMode
{                                       
    MISSILEFLIGHTMODE_TOP,
    MISSILEFLIGHTMODE_DIRECT,
};
struct corpse_ent_t 
{                                       
    int32_t deathAnimStartTime;
};
struct missile_ent_t 
{                                       
    float time;
    int32_t timeOfBirth;
    float travelDist;
    float surfaceNormal[3];
    team_t team;
    float curvature[3];
    float targetOffset[3];
    MissileStage stage;
    MissileFlightMode flightMode;
};
enum EntHandler_t 
{
    ENT_HANDLER_NULL,
    ENT_HANDLER_TRIGGER_MULTIPLE,
    ENT_HANDLER_TRIGGER_HURT,
    ENT_HANDLER_TRIGGER_HURT_TOUCH,
    ENT_HANDLER_TRIGGER_DAMAGE,
    ENT_HANDLER_SCRIPT_MOVER,
    ENT_HANDLER_SCRIPT_MODEL,
    ENT_HANDLER_GRENADE,
    ENT_HANDLER_TIMED_OBJECT,
    ENT_HANDLER_ROCKET,
    ENT_HANDLER_CLIENT,
    ENT_HANDLER_CLIENT_SPECTATOR,
    ENT_HANDLER_CLIENT_DEAD,
    ENT_HANDLER_PLAYER_CLONE,
    ENT_HANDLER_TURRET_INIT,
    ENT_HANDLER_TURRET,
    ENT_HANDLER_DROPPED_ITEM,
    ENT_HANDLER_ITEM_INIT,
    ENT_HANDLER_ITEM,
    ENT_HANDLER_TRIGGER_USE,
    ENT_HANDLER_PRIMARY_LIGHT,
    ENT_HANDLER_PLAYER_BLOCK,
    ENT_HANDLER_VEHICLE,
    ENT_HANDLER_HELICOPTER,
    ENT_HANDLER_COUNT,
};
enum gentityFlags_t 
{
    FL_GODMODE             ,
    FL_DEMI_GODMODE        ,
    FL_NOTARGET            ,
    FL_NO_KNOCKBACK        ,
    FL_DROPPED_ITEM        ,
    FL_NO_BOTS             ,
    FL_NO_HUMANS           ,
    FL_TOGGLE              ,
    FL_SOFTACTIVATE        ,
    FL_PARACHUTE           ,
    FL_NO_HEADCHECK        ,
    FL_SUPPORTS_LINKTO     ,
    FL_NO_AUTO_ANIM_UPDATE ,
    FL_GRENADE_TOUCH_DAMAGE,
    FL_MISSILE_DESTABILIZED = 0x10'000,
    FL_STABLE_MISSILES      = 0x20'000,
    FL_REPEAT_ANIM_UPDATE   = 0x40'000,
    FL_VEHICLE_TARGET       = 0x80'000,
    FL_GROUND_ENT           = 0x100'000,
    FL_CURSOR_HINT          = 0x200'000,
    FL_USE_TURRET           = 0x400'000,
    FL_MISSILE_ATTRACTOR    = 0x800'000,
    FL_WEAPON_BEING_GRABBED = 0x1'000'000,
};
typedef struct gentity_s 
{                                       
    entityState_s s;                    
    entityShared_t r;                   
    struct gclient_s *client;                  
    struct turretInfo_s *pTurretInfo;
    struct scr_vehicle_s *scr_vehicle;
    uint16_t model;
    uint8_t physicsObject;
    uint8_t takedamage;
    uint8_t active;
    uint8_t nopickup;
    EntHandler_t handler;
    uint8_t team;
    uint16_t classname;         
    uint16_t target;
    uint16_t targetname;
    uint32_t attachIgnoreCollision;
    int32_t spawnflags;                     
    gentityFlags_t flags;                          
    int32_t eventTime;
    int32_t freeAfterEvent;
    int32_t unlinkAfterEvent;
    int32_t clipmask;
    int32_t processedFrame;
    EntHandle parent;
    int32_t nextthink;
    int32_t health;                         
    int32_t maxHealth;
    int32_t damage;
    int32_t count;
    gentity_s *chain;
    union 
    {                                       
        item_ent_t item[2];
        trigger_ent_t trigger;
        mover_ent_t mover;
        corpse_ent_t corpse;
        missile_ent_t missile;
    };
    EntHandle missileTargetEnt;
    tagInfo_s *tagInfo;
    gentity_s *tagChildren;
    uint16_t attachModelNames[19]; 
    uint16_t attachTagNames[19];
    int32_t useCount;
    gentity_s *nextFree;
} gentity_t;