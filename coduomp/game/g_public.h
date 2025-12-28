#pragma once

#include "../qcommon/msg.h"
#include "../bgame/bg_public.h"
#include "../script/scr_variable.h"
#include "g_main.h"
#include "../script/scr_const.h"
#include "../bgame/bg_local.h"

struct game_hudelem_s;
struct weaponParms;

#define PERK_COUNT 20

static const char *g_dedicatedEnumNames[4] = { "listen server", "dedicated LAN server", "dedicated internet server", NULL }; // idb

struct BuiltinFunctionDef // sizeof=0xC
{
    const char *actionString;
    void(__cdecl *actionFunc)();
    int32_t type;
};

struct BuiltinMethodDef // sizeof=0xC
{                                       // ...
    const char *actionString;           // ...
    void(__cdecl *actionFunc)(scr_entref_t); // ...
    int32_t type;                           // ...
};

struct gameTypeScript_t // sizeof=0x84
{                                       // ...
    char pszScript[64];
    char pszName[64];                   // ...
    int32_t bTeamBased;
};

struct scr_data_t_s // sizeof=0x10A8
{                                       // ...
    int32_t main;                           // ...
    int32_t startupgametype;                // ...
    int32_t playerconnect;                  // ...
    int32_t playerdisconnect;               // ...
    int32_t playerdamage;                   // ...
    int32_t playerkilled;                   // ...
    int32_t votecalled;
    int32_t playervote;
    int32_t playerlaststand;                // ...
    int32_t iNumGameTypes;                  // ...
    gameTypeScript_t list[32];          // ...
};

struct corpseInfo_t // sizeof=0x4DC
{                                       // ...
    XAnimTree_s *tree;                  // ...
    int32_t entnum;                         // ...
    int32_t time;
    clientInfo_t ci;
    bool falling;
    // padding byte
    // padding byte
    // padding byte
};

struct scr_data_t // sizeof=0x379C
{                                       // ...
    int32_t levelscript;                    // ...
    int32_t gametypescript;
    scr_data_t_s gametype; // ...
    int32_t delete_;                        // ...
    int32_t initstructs;                    // ...
    int32_t createstruct;                   // ...
    corpseInfo_t playerCorpseInfo[8];   // ...
};


enum meansOfDeath_t
{                                       // ...
    MOD_UNKNOWN = 0x0,
    MOD_PISTOL_BULLET = 0x1,
    MOD_RIFLE_BULLET = 0x2,
    MOD_GRENADE = 0x3,
    MOD_GRENADE_SPLASH = 0x4,
    MOD_PROJECTILE = 0x5,
    MOD_PROJECTILE_SPLASH = 0x6,
    MOD_MELEE = 0x7,
    MOD_HEAD_SHOT = 0x8,
    MOD_CRUSH = 0x9,
    MOD_TELEFRAG = 0xA,
    MOD_FALLING = 0xB,
    MOD_SUICIDE = 0xC,
    MOD_TRIGGER_HURT = 0xD,
    MOD_EXPLOSIVE = 0xE,
    MOD_IMPACT = 0xF,
    MOD_NUM = 0x10,
};

// g_spawn_mp
struct SpawnFuncEntry // sizeof=0x8
{                                       // ...
    const char *classname;
    void(__cdecl *callback)(gentity_s *);
};


// player_use_mp
struct useList_t // sizeof=0x8
{                                       // ...
    gentity_s *ent;                     // ...
    float score;
};

