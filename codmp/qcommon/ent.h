#pragma once
#include "q_shared.h"
enum entityType_t
{                                       
    ET_GENERAL,
    ET_PLAYER,
    ET_PLAYER_CORPSE,
    ET_ITEM,
    ET_MISSILE,
    ET_INVISIBLE,
    ET_SCRIPTMOVER,
    ET_SOUND_BLEND,
    ET_FX,
    ET_LOOP_FX,
    ET_PRIMARY_LIGHT,
    ET_MG42,
    ET_HELICOPTER,
    ET_PLANE,
    ET_VEHICLE,
    ET_VEHICLE_COLLMAP,
    ET_VEHICLE_CORPSE,
    ET_EVENTS,
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