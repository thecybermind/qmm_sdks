/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//

// g_public.h -- game module information visible to server

#pragma once

#include "bg_public.h"

// Version 11 is >= 0.05 and <= 1.00
// Version 12 is >= 1.10
// Version 15 is >= 2.0
#define GAME_API_VERSION 15

// entity->svFlags
// the server does not know how to interpret most of the values
// in entityStates (level eType), so the game must explicitly flag
// special server behaviors
#define SVF_NOCLIENT                    (1<<0)	// don't send entity to clients, even if it has effects
#define SVF_BOT                         (1<<1)
#define SVF_BROADCAST                   (1<<2)	// send to all connected clients
#define SVF_PORTAL                      (1<<3)	// merge a second pvs at origin2 into snapshots
#define SVF_SENDPVS                     (1<<4)	// even though it doesn't have a sound or modelindex, still run it through the pvs
#define SVF_USE_CURRENT_ORIGIN          (1<<5)	// entity->currentOrigin instead of entity->s.origin
  									            // for link position (missiles and movers)
#define SVF_NOTSINGLECLIENT             (1<<6)  // send entity to everyone but one client
                                                // (entityShared_t->singleClient)
#define SVF_MONSTER                     (1<<7)	// treat as CONTENTS_MONSTER for collision
#define SVF_SINGLECLIENT                (1<<8)  // only send to a single client (entityShared_t->singleClient)
#define SVF_USEBBOX                     (1<<9)	// do not perform perfect collision use the bbox instead
#define SVF_NOFARPLANE                  (1<<10)	// only send this entity to its parent
#define SVF_HIDEOWNER                   (1<<11)	// hide the owner of the client
#define SVF_MONSTERCLIP                 (1<<12)	// treat as CONTENTS_MONSTERCLIP for collision
#define SVF_PLAYERCLIP                  (1<<13)	// treat as CONTENTS_PLAYERCLIP for collision
#define SVF_SENDONCE                    (1<<14) // Send this entity over the network at least one time
#define SVF_SENT                        (1<<15) // This flag is set when the entity has been sent over at least one time

#define SVF_NOSERVERINFO                (1<<16) // don't send CS_SERVERINFO updates to this client
                                                // so that it can be updated for ping tools without
                                                // lagging clients

typedef struct gclient_s   gclient_t;
typedef struct dtiki_s     dtiki_t;
typedef struct tiki_cmd_s  tiki_cmd_t;
typedef struct dtikianim_s dtikianim_t;
typedef struct tiki_s      tiki_t;

typedef struct tikiAnim_s      tikiAnim_t;
typedef struct baseshader_s    baseshader_t;
typedef struct AliasListNode_s AliasListNode_t;
typedef void (*xcommand_t)(void);

#define MAX_NONPVS_SOUNDS 4

typedef struct {
    int   index;
    float volume;
    float minDist;
    float maxDist;
    float pitch;
} nonpvs_sound_t;

typedef struct {
    // su44: sharedEntity_t::s is used instead of it
    //entityState_t	s;				// communicated by server to clients

    qboolean linked; // qfalse if not in any good cluster
    int      linkcount;

    int svFlags; // SVF_NOCLIENT, SVF_BROADCAST, etc

    // only send to this client when SVF_SINGLECLIENT is set
    // if SVF_CLIENTMASK is set, use bitmask for clients to send to (maxclients must be <= 32, up to the mod to enforce this)
    int singleClient;

    int lastNetTime;

    qboolean bmodel; // if false, assume an explicit mins / maxs bounding box
    // only set by gi.SetBrushModel
    vec3_t mins, maxs;
    int    contents; // CONTENTS_TRIGGER, CONTENTS_SOLID, CONTENTS_BODY, etc
    // a non-solid entity should set to 0

    vec3_t absmin, absmax; // derived from mins/maxs and origin + rotation
    float  radius;
    // centroid will be used for all collision detection and world linking.
    // it will not necessarily be the same as the trajectory evaluation for the current
    // time, because each entity must be moved one at a time after time is advanced
    // to avoid simultanious collision issues
    vec3_t centroid; // centroid, to be used with radius

    int areanum;

    vec3_t currentAngles;

    // when a trace call is made and passEntityNum != ENTITYNUM_NONE,
    // an ent will be excluded from testing if:
    // ent->s.number == passEntityNum	(don't interact with self)
    // ent->s.ownerNum = passEntityNum	(don't interact with your own missiles)
    // entity[ent->s.ownerNum].ownerNum = passEntityNum	(don't interact with other missiles from owner)
    int ownerNum;

    // whether or not this entity emitted a sound this frame
    // (used for when the entity shouldn't be sent to clients)
    nonpvs_sound_t nonpvs_sounds[MAX_NONPVS_SOUNDS];
    int            num_nonpvs_sounds;
} entityShared_t;

// client data that stays across multiple respawns, but is cleared
// on each level change or team change at ClientBegin()
typedef struct {
    char userinfo[MAX_INFO_STRING];
    char netname[MAX_NAME_LENGTH];
    char dm_playermodel[MAX_QPATH];
    char dm_playergermanmodel[MAX_QPATH];
    char dm_primary[MAX_QPATH];

    float enterTime;

    teamtype_t teamnum;
    int        round_kills;

    char ip[17];
    int  port;
} client_persistant_t;

// this structure is cleared on each ClientSpawn(),
// except for 'client->pers' and 'client->sess'
struct gclient_s {
    // ps MUST be the first element, because the server expects it
    playerState_t ps; // communicated by server to clients

#ifdef GAME_DLL
    // the rest of the structure is private to game
    int                 ping;
    client_persistant_t pers;
    float               cmd_angles[3];

    int lastActiveTime;
    int activeWarning;

    struct gentity_s *ent;
    struct gclient_s *next;
    struct gclient_s *prev;
#endif
};

typedef struct gentity_s {
    entityState_t s; // communicated by server to clients

    struct gclient_s *client; // NULL if not a client
    qboolean          inuse;

    entityShared_t r; // shared by both the server system and game

    solid_t  solid;
    dtiki_t *tiki;
    float    mat[3][3];

    // Leave reminder to the game dll
#if defined(GAME_DLL)
    class Entity *entity;
    float         freetime;
    float         spawntime;
    float         radius2;
    char          entname[64];
    int           clipmask;

    struct gentity_s *next;
    struct gentity_s *prev;
#endif
} gentity_t;

// movers are things like doors, plats, buttons, etc
typedef enum {
    MOVER_POS1,
    MOVER_POS2,
    MOVER_1TO2,
    MOVER_2TO1
} moverState_t;

typedef struct profVar_s {
    int   start;
    int   clockCycles;
    int   calls;
    float time;
    float totTime;
    float avgTime;
    float low;
    float high;

} profVar_t;

typedef struct profGame_s {
    profVar_t AI;
    profVar_t MmoveSingle;
    profVar_t thread_timingList;
    profVar_t gamescripts;
    profVar_t GProbe1;
    profVar_t GProbe2;
    profVar_t GProbe3;
    profVar_t FindPath;
    profVar_t vector_length;
    profVar_t script_trace;
    profVar_t internal_trace;
    profVar_t PreAnimate;
    profVar_t PostAnimate;

} profGame_t;

//===============================================================

typedef struct gameImport_s {
    void (*Printf)(const char *format, ...);
    void (*DPrintf)(const char *format, ...);
    void (*DPrintf2)(const char *format, ...);
    void (*DebugPrintf)(const char *format, ...);
    void (*Error)(int level, const char *format, ...);
    int (*Milliseconds)();
    const char *(*LV_ConvertString)(const char *string);

    // Added in 2.0
    const char *(*CL_LV_ConvertString)(const char *string);

    void *(*Malloc)(size_t size);
    void (*Free)(void *ptr);
    cvar_t *(*Cvar_Get)(const char *varName, const char *varValue, int varFlags);
    void (*cvar_set)(const char *varName, const char *varValue);
    cvar_t *(*cvar_set2)(const char *varName, const char *varValue, qboolean force);
    cvar_t *(*NextCvar)(cvar_t *var);
	// void (*Cvar_CheckRange)(cvar_t* var, float min, float max, qboolean integral);
    int (*Argc)();
    char *(*Argv)(int arg);
    char *(*Args)();
    void (*AddCommand)(const char *cmdName, xcommand_t cmdFunction);
    long (*FS_ReadFile)(const char *qpath, void **buffer, qboolean quiet);
    void (*FS_FreeFile)(void *buffer);
    int (*FS_WriteFile)(const char *qpath, const void *buffer, int size);
    fileHandle_t (*FS_FOpenFileWrite)(const char *fileName);
    fileHandle_t (*FS_FOpenFileAppend)(const char *fileName);
	long (*FS_FOpenFile)(const char* qpath, fileHandle_t *file, qboolean uniqueFILE, qboolean quiet);
    const char *(*FS_PrepFileWrite)(const char *fileName);
    size_t (*FS_Write)(const void *buffer, size_t size, fileHandle_t fileHandle);
    size_t (*FS_Read)(void *buffer, size_t len, fileHandle_t fileHandle);
    void (*FS_FCloseFile)(fileHandle_t fileHandle);
    int (*FS_Tell)(fileHandle_t fileHandle);
    int (*FS_Seek)(fileHandle_t fileHandle, long int offset, int origin);
    void (*FS_Flush)(fileHandle_t fileHandle);
    int (*FS_FileNewer)(const char *source, const char *destination);
    void (*FS_CanonicalFilename)(char *fileName);
    char **(*FS_ListFiles)(const char *qpath, const char *extension, qboolean wantSubs, int *numFiles);
    void (*FS_FreeFileList)(char **list);
    const char *(*GetArchiveFileName)(const char *fileName, const char *extension);
    void (*SendConsoleCommand)(const char *text);

    // Added in 2.0
    void (*ExecuteConsoleCommand)(int exec_when, const char *text);

    void (*DebugGraph)(float value);
    void (*SendServerCommand)(int client, const char *format, ...);
    void (*DropClient)(int client, const char *reason);
    void (*MSG_WriteBits)(int value, int bits);
    void (*MSG_WriteChar)(int c);
    void (*MSG_WriteByte)(int c);
    void (*MSG_WriteSVC)(int c);
    void (*MSG_WriteShort)(int c);
    void (*MSG_WriteLong)(int c);
    void (*MSG_WriteFloat)(float f);
    void (*MSG_WriteString)(const char *s);
    void (*MSG_WriteAngle8)(float f);
    void (*MSG_WriteAngle16)(float f);
    void (*MSG_WriteCoord)(float f);
    void (*MSG_WriteDir)(vec3_t dir);
    void (*MSG_StartCGM)(int type);
    void (*MSG_EndCGM)();
    void (*MSG_SetClient)(int client);
    void (*SetBroadcastVisible)(const vec3_t pos, const vec3_t posB);
    void (*SetBroadcastHearable)(const vec3_t pos, const vec3_t posB);
    void (*SetBroadcastAll)();
    void (*setConfigstring)(int index, const char *val);
    char *(*getConfigstring)(int index);
    void (*SetUserinfo)(int index, const char *val);
    void (*GetUserinfo)(int index, char *buffer, int bufferSize);
    void (*SetBrushModel)(gentity_t *ent, const char *name);
    void (*ModelBoundsFromName)(const char *name, vec3_t mins, vec3_t maxs);
    qboolean (*SightTraceEntity)(
        gentity_t   *touch,
        const vec3_t start,
        const vec3_t mins,
        const vec3_t maxs,
        const vec3_t end,
        int          contentMask,
        qboolean     cylinder
    );
    qboolean (*SightTrace)(
        const vec3_t start,
        const vec3_t mins,
        const vec3_t maxs,
        const vec3_t end,
        int          passEntityNum,
        int          passEntityNum2,
        int          contentMask,
        qboolean     cylinder
    );
    void (*trace)(
        trace_t     *results,
        const vec3_t start,
        const vec3_t mins,
        const vec3_t maxs,
        const vec3_t end,
        int          passEntityNum,
        int          contentMask,
        qboolean     cylinder,
        qboolean     traceDeep
    );

    // Added in 2.0
    float (*CM_VisualObfuscation)(const vec3_t start, const vec3_t end);

    baseshader_t *(*GetShader)(int shaderNum);
    int (*pointcontents)(const vec3_t p, int passEntityNum);
    int (*PointBrushnum)(const vec3_t p, clipHandle_t model);
    void (*AdjustAreaPortalState)(gentity_t *ent, qboolean open);
    int (*AreaForPoint)(vec3_t pos);
    qboolean (*AreasConnected)(int area1, int area2);
    qboolean (*InPVS)(float *p1, float *p2);
    void (*linkentity)(gentity_t *gEnt);
    void (*unlinkentity)(gentity_t *gEnt);
    int (*AreaEntities)(const vec3_t mins, const vec3_t maxs, int *list, int maxcount);
    void (*ClipToEntity)(
        trace_t     *tr,
        const vec3_t start,
        const vec3_t mins,
        const vec3_t maxs,
        const vec3_t end,
        int          entityNum,
        int          contentMask
    );

    // Added in 2.0
    qboolean (*HitEntity)(gentity_t *pEnt, gentity_t *pOther);

    int (*imageindex)(const char *name);
    int (*itemindex)(const char *name);
    int (*soundindex)(const char *name, int streamed);
    dtiki_t *(*TIKI_RegisterModel)(const char *path);
    dtiki_t *(*modeltiki)(const char *name);
    dtikianim_t *(*modeltikianim)(const char *name);
    void (*SetLightStyle)(int index, const char *data);
    const char *(*GameDir)();
    qboolean (*setmodel)(gentity_t *ent, const char *name);
    void (*clearmodel)(gentity_t *ent);
    int (*TIKI_NumAnims)(dtiki_t *tiki);
    int (*TIKI_NumSurfaces)(dtiki_t *tiki);
    int (*TIKI_NumTags)(dtiki_t *tiki);
    void (*TIKI_CalculateBounds)(dtiki_t *tiki, float scale, vec3_t mins, vec3_t maxs);
    void *(*TIKI_GetSkeletor)(dtiki_t *tiki, int entNum);
    const char *(*Anim_NameForNum)(dtiki_t *tiki, int animNum);
    int (*Anim_NumForName)(dtiki_t *tiki, const char *name);
    int (*Anim_Random)(dtiki_t *tiki, const char *name);
    int (*Anim_NumFrames)(dtiki_t *tiki, int animNum);
    float (*Anim_Time)(dtiki_t *tiki, int animNum);
    float (*Anim_Frametime)(dtiki_t *tiki, int animNum);
    float (*Anim_CrossTime)(dtiki_t *tiki, int animNum);
    void (*Anim_Delta)(dtiki_t *tiki, int animNum, float *delta);

    // Added in 2.0
    void (*Anim_AngularDelta)(dtiki_t *tiki, int animNum, float *delta);

    qboolean (*Anim_HasDelta)(dtiki_t *tiki, int animNum);
    void (*Anim_DeltaOverTime)(dtiki_t *tiki, int animNum, float time1, float time2, float *delta);

    // Added in 2.0
    void (*Anim_AngularDeltaOverTime)(dtiki_t *tiki, int animNum, float time1, float time2, float *delta);

    int (*Anim_Flags)(dtiki_t *tiki, int animNum);
    int (*Anim_FlagsSkel)(dtiki_t *tiki, int animNum);
    qboolean (*Anim_HasCommands)(dtiki_t *tiki, int animNum);
    // qboolean (*Anim_HasCommands_Client)(dtiki_t *tiki, int animNum);
    int (*NumHeadModels)(const char *model);
    void (*GetHeadModel)(const char *model, int num, char *name);
    int (*NumHeadSkins)(const char *model);
    void (*GetHeadSkin)(const char *model, int num, char *name);
    qboolean (*Frame_Commands)(dtiki_t *tiki, int animNum, int frameNum, tiki_cmd_t *tikiCmds);
    // qboolean (*Frame_Commands_Client)(dtiki_t *tiki, int animNum, int frameNum, tiki_cmd_t *tikiCmds);
    int (*Surface_NameToNum)(dtiki_t *tiki, const char *name);
    const char *(*Surface_NumToName)(dtiki_t *tiki, int surfacenum);
    int (*Tag_NumForName)(dtiki_t *pmdl, const char *name);
    const char *(*Tag_NameForNum)(dtiki_t *pmdl, int tagNum);
    orientation_t (*TIKI_OrientationInternal)(dtiki_t *tiki, int entNum, int tagNum, float scale);
    void *(*TIKI_TransformInternal)(dtiki_t *tiki, int entNum, int tagNum);
    qboolean (*TIKI_IsOnGroundInternal)(dtiki_t *tiki, int entNum, int num, float threshold);
    void (*TIKI_SetPoseInternal)(
        dtiki_t *tiki, int entNum, const frameInfo_t *frameInfo, int *boneTag, vec4_t *boneQuat, float actionWeight
    );
    const char *(*CM_GetHitLocationInfo)(int location, float *radius, float *offset);
    const char *(*CM_GetHitLocationInfoSecondary)(int location, float *radius, float *offset);

    qboolean (*Alias_Add)(dtiki_t *pmdl, const char *alias, const char *name, const char *parameters);
    const char *(*Alias_FindRandom)(dtiki_t *tiki, const char *alias, AliasListNode_t **ret);
    void (*Alias_Dump)(dtiki_t *tiki);
    void (*Alias_Clear)(dtiki_t *tiki);
    void (*Alias_UpdateDialog)(dtikianim_t *tiki, const char *alias);

    const char *(*TIKI_NameForNum)(dtiki_t *tiki);

    qboolean (*GlobalAlias_Add)(const char *alias, const char *name, const char *parameters);
    const char *(*GlobalAlias_FindRandom)(const char *alias, AliasListNode_t **ret);
    void (*GlobalAlias_Dump)();
    void (*GlobalAlias_Clear)();

    void (*centerprintf)(gentity_t *ent, const char *format, ...);
    void (*locationprintf)(gentity_t *ent, int x, int y, const char *format, ...);
    void (*Sound)(
        vec3_t     *org,
        int         entNum,
        int         channel,
        const char *soundName,
        float       volume,
        float       minDist,
        float       pitch,
        float       maxDist,
        int         streamed
    );
    void (*StopSound)(int entNum, int channel);
    float (*SoundLength)(int channel, const char *name);
    unsigned char *(*SoundAmplitudes)(int channel, const char *name);
    int (*S_IsSoundPlaying)(int channel, const char *name);
    short unsigned int (*CalcCRC)(unsigned char *start, int count);

    debugline_t   **DebugLines;
    int            *numDebugLines;
    debugstring_t **DebugStrings;
    int            *numDebugStrings;

    void (*LocateGameData)(
        gentity_t *gEnts, int numGEntities, int sizeofGEntity, playerState_t *clients, int sizeofGameClient
    );
    void (*SetFarPlane)(int farPlane);
    void (*SetSkyPortal)(qboolean skyPortal);
    void (*Popmenu)(int client, int i);
    void (*Showmenu)(int client, const char *name, qboolean force);
    void (*Hidemenu)(int client, const char *name, qboolean force);
    void (*Pushmenu)(int client, const char *name);
    void (*HideMouseCursor)(int client);
    void (*ShowMouseCursor)(int client);
    const char *(*MapTime)();
    void (*LoadResource)(const char *name);
    void (*ClearResource)();
    int (*Key_StringToKeynum)(const char *str);
    const char *(*Key_KeynumToBindString)(int keyNum);
    void (*Key_GetKeysForCommand)(const char *command, int *key1, int *key2);
    void (*ArchiveLevel)(qboolean loading);
    void (*AddSvsTimeFixup)(int *piTime);
    void (*HudDrawShader)(int info, const char *name);
    void (*HudDrawAlign)(int info, int horizontalAlign, int verticalAlign);
    void (*HudDrawRect)(int info, int x, int y, int width, int height);
    void (*HudDrawVirtualSize)(int info, qboolean virtualScreen);
    void (*HudDrawColor)(int info, float *color);
    void (*HudDrawAlpha)(int info, float alpha);
    void (*HudDrawString)(int info, const char *string);
    void (*HudDrawFont)(int info, const char *fontName);
    qboolean (*SanitizeName)(const char *oldName, char *newName, size_t bufferSize);

    //
    // Added in OPM
    //

    int (*pvssoundindex)(const char* name, int streamed);

    cvar_t *fsDebug;

    //
    // New functions will start from here
    //

} game_import_t;

typedef struct gameExport_s {
    int apiversion;

    // the init function will only be called when a game starts,
    // not each time a level is loaded.  Persistant data for clients
    // and the server can be allocated in init
    void (*Init)(int startTime, int randomSeed);
    void (*Shutdown)(void);
    void (*Cleanup)(qboolean samemap);
    void (*Precache)(void);

    void (*SetMap)(const char *mapName);
    void (*Restart)();
    void (*SetTime)(int svsStartTime, int svsTime);

    // each new level entered will cause a call to SpawnEntities
    void (*SpawnEntities)(char *entstring, int levelTime);

    // return NULL if the client is allowed to connect, otherwise return
    // a text string with the reason for denial
    const char *(*ClientConnect)(int clientNum, qboolean firstTime, qboolean differentMap);

    void (*ClientBegin)(gentity_t *ent, usercmd_t *cmd);
    void (*ClientUserinfoChanged)(gentity_t *ent, const char *userinfo);
    void (*ClientDisconnect)(gentity_t *ent);
    void (*ClientCommand)(gentity_t *ent);
    void (*ClientThink)(gentity_t *ent, usercmd_t *cmd, usereyes_t *eyeinfo);

    void (*BotBegin)(gentity_t *ent);
    void (*BotThink)(gentity_t *ent, int msec);

    void (*PrepFrame)(void);
    void (*RunFrame)(int levelTime, int frameTime);

    void (*ServerSpawned)(void);

    void (*RegisterSounds)();
    qboolean (*AllowPaused)();

    // ConsoleCommand will be called when a command has been issued
    // that is not recognized as a builtin function.
    // The game can issue gi.argc() / gi.argv() commands to get the command
    // and parameters.  Return qfalse if the game doesn't recognize it as a command.
    qboolean (*ConsoleCommand)(void);

    void (*ArchivePersistant)(const char *name, qboolean loading);

    // ReadLevel is called after the default map information has been
    // loaded with SpawnEntities, so any stored client spawn spots will
    // be used when the clients reconnect.
    void (*WriteLevel)(const char *filename, qboolean autosave, byte** savedCgameState, size_t* savedCgameStateSize);
    qboolean (*ReadLevel)(const char *filename, byte** savedCgameState, size_t* savedCgameStateSize);
    qboolean (*LevelArchiveValid)(const char *filename);

    void (*ArchiveInteger)(int *i);
    void (*ArchiveFloat)(float *fl);
    void (*ArchiveString)(char *s);
    void (*ArchiveSvsTime)(int *pi);
    orientation_t (*TIKI_Orientation)(gentity_t *edict, int num);
    void (*DebugCircle)(float *org, float radius, float r, float g, float b, float alpha, qboolean horizontal);
    void (*SetFrameNumber)(int frameNumber);
    void (*SoundCallback)(int entNum, soundChannel_t channelNumber, const char *name);

    //
    // global variables shared between game and server
    //

    // The gentities array is allocated in the game dll so it
    // can vary in size from one game to another.
    //
    // The size will be fixed when ge->Init() is called
    // the server can't just use pointer arithmetic on gentities, because the
    // server's sizeof(struct gentity_s) doesn't equal gentitySize
    profGame_t       *profStruct;
    struct gentity_s *gentities;
    int               gentitySize;
    int               num_entities; // current number, <= max_entities
    int               max_entities;

    const char *errorMessage;
} game_export_t;
