#pragma once

#include "qcommon.h"
#include "ent.h"

#define BUTTON_BIT_COUNT 21
#define MAX_WEAPONS_BITS 7
#define GENTITYNUM_BITS 10

#define MSG_FIELD_ORIGINY -91

struct msg_t 
{                                       
    int overflowed;                     
    int readOnly;                       
    unsigned char* data;              
    unsigned char* splitData;         
    int maxsize;                        
    int cursize;                        
    int splitSize;                      
    int readcount;                      
    int bit;                            
    int lastEntityRef;                  
};


struct NetField 
{                                       
    const char* name;
    size_t offset;
    int bits;
    unsigned char changeHints;
    
    
    
};

struct usercmd_s 
{                                       
    int32_t serverTime;                     
    int32_t buttons;                        
    int32_t angles[3];                      
    uint8_t weapon;             
    uint8_t offHandIndex;
    char forwardmove;                   
    char rightmove;                     
    float meleeChargeYaw;               
    uint8_t meleeChargeDist;    
    char selectedLocation[2];
};
static_assert(sizeof(usercmd_s) == 0x20);

struct hudelem_s;

struct clientState_s;
struct playerState_s;
