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
{                                       // ...
    ANALYZE_DATATYPE_ENTITYTYPE_GENERALENTITY = 0x0,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERENTITY = 0x1,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERCORPSEENTITY = 0x2,
    ANALYZE_DATATYPE_ENTITYTYPE_ITEMENTITY = 0x3,
    ANALYZE_DATATYPE_ENTITYTYPE_MISSILEENTITY = 0x4,
    ANALYZE_DATATYPE_ENTITYTYPE_INVISIBLEENTITY = 0x5,
    ANALYZE_DATATYPE_ENTITYTYPE_SCRIPTMOVERENTITY = 0x6,
    ANALYZE_DATATYPE_ENTITYTYPE_SOUNDBLENDENTITY = 0x7,
    ANALYZE_DATATYPE_ENTITYTYPE_FXENTITY = 0x8,
    ANALYZE_DATATYPE_ENTITYTYPE_LOOPFXENTITY = 0x9,
    ANALYZE_DATATYPE_ENTITYTYPE_PRIMARYLIGHTENTITY = 0xA,
    ANALYZE_DATATYPE_ENTITYTYPE_MG42ENTITY = 0xB,
    ANALYZE_DATATYPE_ENTITYTYPE_HELICOPTER = 0xC,
    ANALYZE_DATATYPE_ENTITYTYPE_PLANE = 0xD,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE = 0xE,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE_COLLMAP = 0xF,
    ANALYZE_DATATYPE_ENTITYTYPE_VEHICLE_CORPSE = 0x10,
    ANALYZE_DATATYPE_ENTITYTYPE_TEMPENTITY = 0x11,
    ANALYZE_DATATYPE_ENTITYTYPE_ARCHIVEDENTITY = 0x12,
    ANALYZE_DATATYPE_ENTITYTYPE_CLIENTSTATE = 0x13,
    ANALYZE_DATATYPE_ENTITYTYPE_PLAYERSTATE = 0x14,
    ANALYZE_DATATYPE_ENTITYTYPE_HUDELEM = 0x15,
    ANALYZE_DATATYPE_ENTITYTYPE_BASELINE = 0x16,
    ANALYZE_DATATYPE_ENTITYTYPE_COUNT = 0x17,
};

struct netFieldOrderInfo_t // sizeof=0x6C0
{                                       // ...
    int entState[64];
    int arcEntState[128];               // ...
    int clientState[32];                // ...
    int playerState[160];               // ...
    int objective[8];                   // ...
    int hudElem[40];                    // ...
};

struct SnapshotInfo_s // sizeof=0x18
{                                       // ...
    int clientNum;                      // ...
    const clientHeader_t* client;       // ...
    int snapshotDeltaTime;              // ...
    bool fromBaseline;                  // ...
    bool archived;                      // ...
    // padding byte
    // padding byte
    int* fieldChanges;                  // ...
    PacketEntityType packetEntityType;  // ...
};

struct NetFieldList // sizeof=0x8
{                                       // ...
    const NetField *array;
    unsigned int count;
};
