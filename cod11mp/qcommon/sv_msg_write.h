#pragma once
#include "net_chan.h"
#include "msg.h"
static const unsigned int kbitmask[33] =
{
    0,
    1,
    3,
    7,
    0x0F,
    0x1F,
    0x3F,
    0x7F,
    0x0FF,
    0x1FF,
    0x3FF,
    0x7FF,
    0x0FFF,
    0x1FFF,
    0x3FFF,
    0x7FFF,
    0x0FFFF,
    0x1FFFF,
    0x3FFFF,
    0x7FFFF,
    0x0FFFFF,
    0x1FFFFF,
    0x3FFFFF,
    0x7FFFFF,
    0x0FFFFFF,
    0x1FFFFFF,
    0x3FFFFFF,
    0x7FFFFFF,
    0x0FFFFFFF,
    0x1FFFFFFF,
    0x3FFFFFFF,
    0x7FFFFFFF,
    0x0FFFFFFFF,
};
enum PacketEntityType 
{                                       
    ANALYZE_DATATYPE_ENTITYTYPE_GENERALENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERCORPSEENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_ITEMENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_MISSILEENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_INVISIBLEENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_SCRIPTMOVERENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_SOUNDBLENDENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_FXENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_LOOPFXENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_PRIMARYLIGHTENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_MG42ENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_HELICOPTER,
    ANALYZE_DATATYPE_ENTITYTYPE_PLANE,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE_COLLMAP,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE_CORPSE,
    ANALYZE_DATATYPE_ENTITYTYPE_TEMPENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_ARCHIVEDENTITY,
    ANALYZE_DATATYPE_ENTITYTYPE_CLIENTSTATE,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERSTATE,
    ANALYZE_DATATYPE_ENTITYTYPE_HUDELEM,
    ANALYZE_DATATYPE_ENTITYTYPE_BASELINE,
    ANALYZE_DATATYPE_ENTITYTYPE_COUNT,
};
struct netFieldOrderInfo_t 
{                                       
    int entState[64];
    int arcEntState[128];               
    int clientState[32];                
    int playerState[160];               
    int objective[8];                   
    int hudElem[40];                    
};
struct SnapshotInfo_s 
{                                       
    int clientNum;                      
    const clientHeader_t* client;       
    int snapshotDeltaTime;              
    bool fromBaseline;                  
    bool archived;                      
    int* fieldChanges;                  
    PacketEntityType packetEntityType;  
};
struct NetFieldList 
{                                       
    const NetField *array;
    unsigned int count;
};