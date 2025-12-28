#pragma once

#include "qcommon.h"
#include "ent.h"

#define BUTTON_BIT_COUNT 21
#define MAX_WEAPONS_BITS 7
#define GENTITYNUM_BITS 10

#define MSG_FIELD_ORIGINY -91

struct msg_t // sizeof=0x28
{                                       // ...
    int overflowed;                     // ...
    int readOnly;                       // ...
    unsigned char* data;              // ...
    unsigned char* splitData;         // ...
    int maxsize;                        // ...
    int cursize;                        // ...
    int splitSize;                      // ...
    int readcount;                      // ...
    int bit;                            // ...
    int lastEntityRef;                  // ...
};


struct NetField // sizeof=0x10
{                                       // ...
    const char* name;
    size_t offset;
    int bits;
    unsigned char changeHints;
    // padding byte
    // padding byte
    // padding byte
};

struct usercmd_s // sizeof=0x20
{                                       // XREF: ?SV_BotUserMove@@YAXPAUclient_t@@@Z/r
    int32_t serverTime;                     // XREF: CG_DrawDisconnect+85/r
    int32_t buttons;                        // XREF: CG_CheckForPlayerInput+5D/r
    int32_t angles[3];                      // XREF: CG_CheckPlayerMovement+B/o
    uint8_t weapon;             // XREF: CL_CreateCmd+64/w
    uint8_t offHandIndex;
    char forwardmove;                   // XREF: CG_CheckPlayerMovement:loc_4413AE/r
    char rightmove;                     // XREF: CG_CheckPlayerMovement+26/r
    float meleeChargeYaw;               // XREF: CL_CreateCmd+67/w
    uint8_t meleeChargeDist;    // XREF: CL_CreateCmd+6A/w
    char selectedLocation[2];
};
static_assert(sizeof(usercmd_s) == 0x20);

struct hudelem_s;

struct clientState_s;
struct playerState_s;
