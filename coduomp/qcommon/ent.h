#pragma once

#include "q_shared.h"

enum entityType_t
{                                       // ...
    ET_GENERAL = 0x0,
    ET_PLAYER = 0x1,
    ET_PLAYER_CORPSE = 0x2,
    ET_ITEM = 0x3,
    ET_MISSILE = 0x4,
    ET_INVISIBLE = 0x5,
    ET_SCRIPTMOVER = 0x6,
    ET_SOUND_BLEND = 0x7,
    ET_FX = 0x8,
    ET_LOOP_FX = 0x9,
    ET_PRIMARY_LIGHT = 0xA,
    ET_MG42 = 0xB,
    ET_HELICOPTER = 0xC,
    ET_PLANE = 0xD,
    ET_VEHICLE = 0xE,
    ET_VEHICLE_COLLMAP = 0xF,
    ET_VEHICLE_CORPSE = 0x10,
    ET_EVENTS = 0x11,
};

struct LerpEntityStateTurret // sizeof=0xC
{                                       // XREF: LerpEntityStateTypeUnion/r
    float gunAngles[3];
};
struct LerpEntityStateLoopFx // sizeof=0x8
{                                       // XREF: LerpEntityStateTypeUnion/r
    float cullDist;
    int period;
};

struct LerpEntityStatePrimaryLight // sizeof=0x14
{                                       // XREF: LerpEntityStateTypeUnion/r
    unsigned __int8 colorAndExp[4];
    float intensity;
    float radius;
    float cosHalfFovOuter;
    float cosHalfFovInner;
};
struct LerpEntityStatePlayer // sizeof=0x8
{                                       // XREF: LerpEntityStateTypeUnion/r
    float leanf;
    int movementDir;
};
struct LerpEntityStateVehicle // sizeof=0x1C
{                                       // XREF: LerpEntityStateTypeUnion/r
    float bodyPitch;
    float bodyRoll;
    float steerYaw;
    int materialTime;
    float gunPitch;
    float gunYaw;
    int teamAndOwnerIndex;
};
struct LerpEntityStateMissile // sizeof=0x4
{                                       // XREF: LerpEntityStateTypeUnion/r
    int launchTime;
};
struct LerpEntityStateSoundBlend // sizeof=0x4
{                                       // XREF: LerpEntityStateTypeUnion/r
    float lerp;
};
struct LerpEntityStateBulletHit // sizeof=0xC
{                                       // XREF: LerpEntityStateTypeUnion/r
    float start[3];
};
struct LerpEntityStateEarthquake // sizeof=0xC
{                                       // XREF: LerpEntityStateTypeUnion/r
    float scale;
    float radius;
    int duration;
};
struct LerpEntityStateCustomExplode // sizeof=0x4
{                                       // XREF: LerpEntityStateTypeUnion/r
    int startTime;
};
struct LerpEntityStateExplosion // sizeof=0x8
{                                       // XREF: LerpEntityStateTypeUnion/r
    float innerRadius;
    float magnitude;
};
struct LerpEntityStateExplosionJolt // sizeof=0x10
{                                       // XREF: LerpEntityStateTypeUnion/r
    float innerRadius;
    float impulse[3];
};
struct LerpEntityStatePhysicsJitter // sizeof=0xC
{                                       // XREF: LerpEntityStateTypeUnion/r
    float innerRadius;
    float minDisplacement;
    float maxDisplacement;
};

union LerpEntityStateTypeUnion // sizeof=0x1C
{                                       // XREF: LerpEntityState/r
    LerpEntityStateTurret turret;
    LerpEntityStateLoopFx loopFx;
    LerpEntityStatePrimaryLight primaryLight;
    LerpEntityStatePlayer player;
    LerpEntityStateVehicle vehicle;
    LerpEntityStateMissile missile;
    LerpEntityStateSoundBlend soundBlend;
    LerpEntityStateBulletHit bulletHit;
    LerpEntityStateEarthquake earthquake;
    LerpEntityStateCustomExplode customExplode;
    LerpEntityStateExplosion explosion;
    LerpEntityStateExplosionJolt explosionJolt;
    LerpEntityStatePhysicsJitter physicsJitter;
};

struct LerpEntityState // sizeof=0x68
{                                       // XREF: entityState_s/r
    int eFlags;                         // XREF: ClientEndFrame(gentity_s *)+5D9/r
    trajectory_t pos;                   // XREF: Mantle_FindMantleSurface+244/o
    trajectory_t apos;                  // XREF: CountBitsEnabled(uint)+1B/o
    LerpEntityStateTypeUnion u;
};


union entityState_s_type_index // sizeof=0x4
{                                       // XREF: PM_UpdateLean(playerState_s *,float,usercmd_s *,void (*)(trace_t *,float const * const,float const * const,float const * const,float const * const,int,int))+2AC/o
    int brushmodel;
    int item;
    int xmodel;
    int primaryLight;
};
union entityState_s_un1 // sizeof=0x4
{                                       // XREF: IsValidArrayIndex(uint)+B/o
                                        // entityState_s/r
    operator int()
    {
        return scale;
    }
    int scale;
    int eventParm2;
    int helicopterStage;
};
union entityState_s_un2 // sizeof=0x4
{                                       // XREF: entityState_s/r
    int hintString;
    int vehicleXModel;
};

struct entityState_s // sizeof=0xF4 // (KISAKTODO: should be in q_shared?)
{                                       // XREF: ?SV_SendClientGameState@@YAXPAUclient_t@@@Z/r
    int number;
    int eType;                          // XREF: BounceMissile+1ED/r
    LerpEntityState lerp;               // XREF: Mantle_FindMantleSurface+244/o
    int time2;
    int otherEntityNum;                 // XREF: CG_CompassUpdateActors(int)+540/o
    int attackerEntityNum;
    int groundEntityNum;
    int loopSound;
    int surfType;
    entityState_s_type_index index;
    int clientNum;
    int iHeadIcon;
    int iHeadIconTeam;                  // XREF: G_InitGrenadeEntity(gentity_s *,gentity_s *)+218/o
    int solid;
    unsigned int eventParm;
    int eventSequence;
    int events[4];                      // XREF: G_MoverPush+3FE/o
    int eventParms[4];
    int weapon;
    int weaponModel;
    int legsAnim;
    int torsoAnim;
    entityState_s_un1 un1;
    entityState_s_un2 un2;
    float fTorsoPitch;
    float fWaistPitch;
    unsigned int partBits[4];           // XREF: Fire_Lead:loc_5189EC/o
};
struct archivedEntityShared_t // sizeof=0x24
{                                       // ...
    int svFlags;                        // ...
    int clientMask[2];                  // ...
    float absmin[3];                    // ...
    float absmax[3];                    // ...
};

struct archivedEntity_s // sizeof=0x118
{                                       // ...
    entityState_s s;                    // ...
    archivedEntityShared_t r;           // ...
};
