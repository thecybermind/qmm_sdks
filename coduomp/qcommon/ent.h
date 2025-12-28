#pragma once

#include "q_shared.h"

enum entityType_t
{                                       
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

struct LerpEntityStateTurret 
{                                       
    float gunAngles[3];
};
struct LerpEntityStateLoopFx 
{                                       
    float cullDist;
    int period;
};

struct LerpEntityStatePrimaryLight 
{                                       
    unsigned char colorAndExp[4];
    float intensity;
    float radius;
    float cosHalfFovOuter;
    float cosHalfFovInner;
};
struct LerpEntityStatePlayer 
{                                       
    float leanf;
    int movementDir;
};
struct LerpEntityStateVehicle 
{                                       
    float bodyPitch;
    float bodyRoll;
    float steerYaw;
    int materialTime;
    float gunPitch;
    float gunYaw;
    int teamAndOwnerIndex;
};
struct LerpEntityStateMissile 
{                                       
    int launchTime;
};
struct LerpEntityStateSoundBlend 
{                                       
    float lerp;
};
struct LerpEntityStateBulletHit 
{                                       
    float start[3];
};
struct LerpEntityStateEarthquake 
{                                       
    float scale;
    float radius;
    int duration;
};
struct LerpEntityStateCustomExplode 
{                                       
    int startTime;
};
struct LerpEntityStateExplosion 
{                                       
    float innerRadius;
    float magnitude;
};
struct LerpEntityStateExplosionJolt 
{                                       
    float innerRadius;
    float impulse[3];
};
struct LerpEntityStatePhysicsJitter 
{                                       
    float innerRadius;
    float minDisplacement;
    float maxDisplacement;
};

union LerpEntityStateTypeUnion 
{                                       
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

struct LerpEntityState 
{                                       
    int eFlags;                         
    trajectory_t pos;                   
    trajectory_t apos;                  
    LerpEntityStateTypeUnion u;
};


union entityState_s_type_index 
{                                       
    int brushmodel;
    int item;
    int xmodel;
    int primaryLight;
};
union entityState_s_un1 
{                                       
                                        // entityState_s/r
    operator int()
    {
        return scale;
    }
    int scale;
    int eventParm2;
    int helicopterStage;
};
union entityState_s_un2 
{                                       
    int hintString;
    int vehicleXModel;
};

struct entityState_s 
{                                       
    int number;
    int eType;                          
    LerpEntityState lerp;               
    int time2;
    int otherEntityNum;                 
    int attackerEntityNum;
    int groundEntityNum;
    int loopSound;
    int surfType;
    entityState_s_type_index index;
    int clientNum;
    int iHeadIcon;
    int iHeadIconTeam;                  
    int solid;
    unsigned int eventParm;
    int eventSequence;
    int events[4];                      
    int eventParms[4];
    int weapon;
    int weaponModel;
    int legsAnim;
    int torsoAnim;
    entityState_s_un1 un1;
    entityState_s_un2 un2;
    float fTorsoPitch;
    float fWaistPitch;
    unsigned int partBits[4];           
};
struct archivedEntityShared_t 
{                                       
    int svFlags;                        
    int clientMask[2];                  
    float absmin[3];                    
    float absmax[3];                    
};

struct archivedEntity_s 
{                                       
    entityState_s s;                    
    archivedEntityShared_t r;           
};
