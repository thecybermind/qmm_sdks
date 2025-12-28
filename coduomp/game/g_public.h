#pragma once
//#include <xanim/xanim.h>
#include "../qcommon/msg.h"
#include "../bgame/bg_public.h"
#include "../script/scr_variable.h"
#include "g_main.h"
#include "../game/game_public.h"
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

static uint16_t *modNames[16] =
{
    &scr_const.mod_unknown,
    &scr_const.mod_pistol_bullet,
    &scr_const.mod_rifle_bullet,
    &scr_const.mod_grenade,
    &scr_const.mod_grenade_splash,
    &scr_const.mod_projectile,
    &scr_const.mod_projectile_splash,
    &scr_const.mod_melee,
    &scr_const.mod_head_shot,
    &scr_const.mod_crush,
    &scr_const.mod_telefrag,
    &scr_const.mod_falling,
    &scr_const.mod_suicide,
    &scr_const.mod_trigger_hurt,
    &scr_const.mod_explosive,
    &scr_const.mod_impact
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


const entityHandler_t entityHandlers[] =
{
  { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
  { NULL, NULL, NULL, &Touch_Multi, NULL, NULL, NULL, NULL, 0, 0 },
  { NULL, NULL, NULL, NULL, &hurt_use, NULL, NULL, NULL, 0, 0 },
  { NULL, NULL, NULL, &hurt_touch, &hurt_use, NULL, NULL, NULL, 0, 0 },
  {
    NULL,
    NULL,
    NULL,
    NULL,
    &Use_trigger_damage,
    &Pain_trigger_damage,
    &Die_trigger_damage,
    NULL,
    0,
    0
  },
  { NULL, &Reached_ScriptMover, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
  { NULL, &Reached_ScriptMover, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
  {
    &G_ExplodeMissile,
    NULL,
    NULL,
    &Touch_Item_Auto,
    NULL,
    NULL,
    NULL,
    NULL,
    3,
    4
  },
  { &G_TimedObjectThink, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
  { &G_ExplodeMissile, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 5, 6 },
  { NULL, NULL, NULL, NULL, NULL, NULL, &player_die, &G_PlayerController, 0, 0 },
  { NULL, NULL, NULL, NULL, NULL, NULL, &player_die, NULL, 0, 0 },
  { NULL, NULL, NULL, NULL, NULL, NULL, NULL, &G_PlayerController, 0, 0 },
  { &BodyEnd, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
  {
    &turret_think_init,
    NULL,
    NULL,
    NULL,
    &turret_use,
    NULL,
    NULL,
    &turret_controller,
    0,
    0
  },
  {
    &turret_think,
    NULL,
    NULL,
    NULL,
    &turret_use,
    NULL,
    NULL,
    &turret_controller,
    0,
    0
  },
  {
    &DroppedItemClearOwner,
    NULL,
    NULL,
    &Touch_Item_Auto,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    0
  },
  {
    &FinishSpawningItem,
    NULL,
    NULL,
    &Touch_Item_Auto,
    NULL,
    NULL,
    NULL,
    NULL,
    0,
    0
  },
  { NULL, NULL, NULL, &Touch_Item_Auto, NULL, NULL, NULL, NULL, 0, 0 },
    //{ NULL, NULL, NULL, NULL, &KISAK_NULLSUB, NULL, NULL, NULL, 0, 0 },
    { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
    { NULL, &Reached_ScriptMover, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
    { &G_FreeEntity, NULL, NULL, NULL, NULL, NULL, NULL, NULL, 0, 0 },
    {
      &G_VehEntHandler_Think,
      NULL,
      NULL,
      &G_VehEntHandler_Touch,
      &G_VehEntHandler_Use,
      &Helicopter_Pain,
      &G_VehEntHandler_Die,
      &G_VehEntHandler_Controller,
      0,
      0
    },
    {
      &Helicopter_Think,
      NULL,
      NULL,
      NULL,
      NULL,
      &Helicopter_Pain,
      &Helicopter_Die,
      &Helicopter_Controller,
      0,
      0
    }
}; // idb
