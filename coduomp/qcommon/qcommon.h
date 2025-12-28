#pragma once

#include "../qcommon/q_shared.h"

typedef enum
{
    SE_NONE = 0x0,
    SE_KEY = 0x1,
    SE_CHAR = 0x2,
    SE_CONSOLE = 0x3,
} sysEventType_t;

enum SphereEdgeTraceResult 
{                                       // ...
    SPHERE_HITS_EDGE = 0x0,
    SPHERE_MISSES_EDGE = 0x1,
    SPHERE_MAY_HIT_V0 = 0x2,
    SPHERE_MAY_HIT_V1 = 0x3,
};

struct field_t // sizeof=0x118
{                                       // ...
	int cursor;                         // ...
	int scroll;
	int drawWidth;                      // ...
	int widthInPixels;                  // ...
	float charHeight;                   // ...
	int fixedSize;                      // ...
	char buffer[256];                   // ...
};

enum hitLocation_t  // (MP/SP same)
{                                       // ...
    HITLOC_NONE = 0x0,
    HITLOC_HELMET = 0x1,
    HITLOC_HEAD = 0x2,
    HITLOC_NECK = 0x3,
    HITLOC_TORSO_UPR = 0x4,
    HITLOC_TORSO_LWR = 0x5,
    HITLOC_R_ARM_UPR = 0x6,
    HITLOC_L_ARM_UPR = 0x7,
    HITLOC_R_ARM_LWR = 0x8,
    HITLOC_L_ARM_LWR = 0x9,
    HITLOC_R_HAND = 0xA,
    HITLOC_L_HAND = 0xB,
    HITLOC_R_LEG_UPR = 0xC,
    HITLOC_L_LEG_UPR = 0xD,
    HITLOC_R_LEG_LWR = 0xE,
    HITLOC_L_LEG_LWR = 0xF,
    HITLOC_R_FOOT = 0x10,
    HITLOC_L_FOOT = 0x11,
    HITLOC_GUN = 0x12,
    HITLOC_NUM = 0x13,
};

enum DemoType 
{                                       // ...
    DEMO_TYPE_NONE = 0x0,
    DEMO_TYPE_CLIENT = 0x1,
    DEMO_TYPE_SERVER = 0x2,
};

static const char *WeaponStateNames[27] =
{
  "WEAPON_READY",
  "WEAPON_RAISING",
  "WEAPON_RAISING_ALTSWITCH",
  "WEAPON_DROPPING",
  "WEAPON_DROPPING_QUICK",
  "WEAPON_FIRING",
  "WEAPON_RECHAMBERING",
  "WEAPON_RELOADING",
  "WEAPON_RELOADING_INTERUPT",
  "WEAPON_RELOAD_START",
  "WEAPON_RELOAD_START_INTERUPT",
  "WEAPON_RELOAD_END",
  "WEAPON_MELEE_INIT",
  "WEAPON_MELEE_FIRE",
  "WEAPON_MELEE_END",
  "WEAPON_OFFHAND_INIT",
  "WEAPON_OFFHAND_PREPARE",
  "WEAPON_OFFHAND_HOLD",
  "WEAPON_OFFHAND_START",
  "WEAPON_OFFHAND",
  "WEAPON_OFFHAND_END",
  "WEAPON_DETONATING",
  "WEAPON_SPRINT_RAISE",
  "WEAPON_SPRINT_LOOP",
  "WEAPON_SPRINT_DROP",
  "WEAPON_NIGHTVISION_WEAR",
  "WEAPON_NIGHTVISION_REMOVE"
}; // idb


enum errorParm_t
{                                       // ...
    ERR_FATAL = 0x0,
    ERR_DROP = 0x1,
    ERR_SERVERDISCONNECT = 0x2,
    ERR_DISCONNECT = 0x3,
    ERR_SCRIPT = 0x4,
    ERR_SCRIPT_DROP = 0x5,
    ERR_LOCALIZATION = 0x6,
    ERR_MAPLOADERRORSUMMARY = 0x7,
};

enum $6ABDC6367E3229B6421BFD1B2626A094  // (SP/MP same)
{
    CON_CHANNEL_DONT_FILTER = 0x0,
    CON_CHANNEL_ERROR = 0x1,
    CON_CHANNEL_GAMENOTIFY = 0x2,
    CON_CHANNEL_BOLDGAME = 0x3,
    CON_CHANNEL_SUBTITLE = 0x4,
    CON_CHANNEL_OBITUARY = 0x5,
    CON_CHANNEL_LOGFILEONLY = 0x6,
    CON_CHANNEL_CONSOLEONLY = 0x7,
    CON_CHANNEL_GFX = 0x8,
    CON_CHANNEL_SOUND = 0x9,
    CON_CHANNEL_FILES = 0xA,
    CON_CHANNEL_DEVGUI = 0xB,
    CON_CHANNEL_PROFILE = 0xC,
    CON_CHANNEL_UI = 0xD,
    CON_CHANNEL_CLIENT = 0xE,
    CON_CHANNEL_SERVER = 0xF,
    CON_CHANNEL_SYSTEM = 0x10,
    CON_CHANNEL_PLAYERWEAP = 0x11,
    CON_CHANNEL_AI = 0x12,
    CON_CHANNEL_ANIM = 0x13,
    CON_CHANNEL_PHYS = 0x14,
    CON_CHANNEL_FX = 0x15,
    CON_CHANNEL_LEADERBOARDS = 0x16,
    CON_CHANNEL_PARSERSCRIPT = 0x17,
    CON_CHANNEL_SCRIPT = 0x18,
    CON_BUILTIN_CHANNEL_COUNT = 0x19,
};

inline bool Con_IsNotifyChannel(int channel)
{
    return channel == (CON_CHANNEL_GAMENOTIFY || channel == CON_CHANNEL_BOLDGAME || channel == CON_CHANNEL_SUBTITLE);
}


struct SndCurve;
struct SpeakerMapInfo;
struct XModelPiece;



enum CvarSetSource 
{                                       // ...
    CVAR_SOURCE_INTERNAL = 0x0,
    CVAR_SOURCE_EXTERNAL = 0x1,
    CVAR_SOURCE_SCRIPT = 0x2,
    CVAR_SOURCE_DEVGUI = 0x3,
};



/*
==============================================================

MISC

==============================================================
*/

#define RoundUp(N, M) ((N) + ((unsigned int)(M)) - (((unsigned int)(N)) % ((unsigned int)(M))))
#define RoundDown(N, M) ((N) - (((unsigned int)(N)) % ((unsigned int)(M))))

/*
==============================================================

DOBJ MANAGEMENT

==============================================================
*/

struct XModel;
struct DObj_s;
struct DObjModel_s;
struct XAnimTree_s;

/*
==============================================================

TRACES
(CM = Collision Model)

==============================================================
*/
// cm_trace
#define CAPSULE_SIZE_EPSILON 0.01f

struct TraceExtents // sizeof=0x24
{                                       
    TraceExtents()
    {
        start[0] = 0.0f;
        start[1] = 0.0f;
        start[2] = 0.0f;

        end[0] = 0.0f;
        end[1] = 0.0f;
        end[2] = 0.0f;

        invDelta[0] = 0.0f;
        invDelta[1] = 0.0f;
        invDelta[2] = 0.0f;
    }
    float start[3];                     // ...
    float end[3];                       // ...
    float invDelta[3];
};
struct locTraceWork_t // sizeof=0x28
{                                       // ...
    int contents;                       // ...
    TraceExtents extents;               // ...
};
struct traceWork_t // sizeof=0xB0
{                                       // ...
    TraceExtents extents;               // ...
    float delta[3];                     // ...
    float deltaLen;                     // ...
    float deltaLenSq;                   // ...
    float midpoint[3];                  // ...
    float halfDelta[3];                 // ...
    float halfDeltaAbs[3];              // ...
    float size[3];                      // ...
    float bounds[2][3];                 // ...
    int contents;                       // ...
    bool isPoint;                       // ...
    bool axialCullOnly;
    // padding byte
    // padding byte
    float radius;                       // ...
    float offsetZ;                      // ...
    float radiusOffset[3];              // ...
    float boundingRadius;               // ...
    TraceThreadInfo threadInfo;         // ...
};
struct IgnoreEntParams // sizeof=0xC
{                                       // ...
    int baseEntity;                     // ...
    int parentEntity;                   // ...
    bool ignoreSelf;                    // ...
    bool ignoreParent;                  // ...
    bool ignoreSiblings;                // ...
    bool ignoreChildren;                // ...
};
struct pointtrace_t // sizeof=0x34
{                                       // ...
    TraceExtents extents;               // ...
    const IgnoreEntParams *ignoreEntParams; // ...
    int contentmask;                    // ...
    int bLocational;                    // ...
    unsigned __int8 *priorityMap;       // ...
};
struct moveclip_t // sizeof=0x54
{
    float mins[3];
    float maxs[3];
    float outerSize[3];
    TraceExtents extents;
    int passEntityNum;
    int passOwnerNum;
    int contentmask;
};

struct cLeafBrushNode_s;
struct cLeaf_t;
struct cmodel_t;

// KISAKTODO: move this the fuck outta here
enum DynEntityDrawType 
{                                       // ...
    DYNENT_DRAW_MODEL = 0x0,
    DYNENT_DRAW_BRUSH = 0x1,
    DYNENT_DRAW_COUNT = 0x2,
};
inline DynEntityDrawType &operator++(DynEntityDrawType &e) {
    e = static_cast<DynEntityDrawType>(static_cast<int>(e) + 1);
    return e;
}
inline DynEntityDrawType& operator++(DynEntityDrawType &e, int i)
{
    ++e;
    return e;
}

// cm_test
struct leafList_s // sizeof=0x2C
{                                       // ...
    int count;                          // ...
    int maxcount;                       // ...
    int overflowed;                     // ...
    unsigned __int16 *list;             // ...
    float bounds[2][3];                 // ...
    int lastLeaf;                       // ...
};

// cm_world
struct areaParms_t // sizeof=0x18
{                                       // ...
    const float *mins;                  // ...
    const float *maxs;                  // ...
    int *list;                          // ...
    int count;                          // ...
    int maxcount;                       // ...
    int contentmask;                    // ...
};
struct staticmodeltrace_t // sizeof=0x28
{                                       // ...
    TraceExtents extents;               // ...
    int contents;                       // ...
};
struct sightclip_t // sizeof=0x48
{
    float mins[3];
    float maxs[3];
    float outerSize[3];
    float start[3];
    float end[3];
    int passEntityNum[2];
    int contentmask;
};
struct sightpointtrace_t // sizeof=0x2C
{                                       // ...
    float start[3];                     // ...
    float end[3];                       // ...
    int passEntityNum[2];               // ...
    int contentmask;                    // ...
    int locational;                     // ...
    unsigned __int8 *priorityMap;       // ...
};

// cm_load_obj
struct SpawnVar // sizeof=0xA0C
{                                       // ...
    bool spawnVarsValid;                // ...
    // padding byte
    // padding byte
    // padding byte
    int32_t numSpawnVars;                   // ...
    char *spawnVars[64][2];             // ...
    int32_t numSpawnVarChars;
    char spawnVarChars[2048];
};

// cm_showcollision
#define BOXSIDE_FRONT 1
#define BOXSIDE_BACK 2

struct ShowCollisionBrushPt // sizeof=0x14
{                                       // ...
    float xyz[3];
    __int16 sideIndex[3];
    // padding byte
    // padding byte
};
struct winding_t // sizeof=0x34
{
    int numpoints;
    float p[4][3];
};
struct cLeaf_t // sizeof=0x2C
{                                       // ...
    unsigned __int16 firstCollAabbIndex;
    unsigned __int16 collAabbCount;
    int brushContents;                  // ...
    int terrainContents;                // ...
    float mins[3];                      // ...
    float maxs[3];                      // ...
    int leafBrushNode;                  // ...
    __int16 cluster;
    // padding byte
    // padding byte
};
struct cmodel_t // sizeof=0x48
{                                       // ...
    float mins[3];
    float maxs[3];
    float radius;
    cLeaf_t leaf;                       // ...
};
struct clipMap_t // sizeof=0x11C
{                                       // ...
    const char *name;                   // ...
    int isInUse;                        // ...
    int planeCount;                     // ...
    struct cplane_s *planes;                   // ...
    unsigned int numStaticModels;       // ...
    struct cStaticModel_s *staticModelList;    // ...
    unsigned int numMaterials;          // ...
    struct dmaterial_t *materials;             // ...
    unsigned int numBrushSides;         // ...
    struct cbrushside_t *brushsides;           // ...
    unsigned int numBrushEdges;         // ...
    unsigned __int8 *brushEdges;        // ...
    unsigned int numNodes;              // ...
    struct cNode_t *nodes;                     // ...
    unsigned int numLeafs;              // ...
    struct cLeaf_t *leafs;                     // ...
    unsigned int leafbrushNodesCount;   // ...
    struct cLeafBrushNode_s *leafbrushNodes;   // ...
    unsigned int numLeafBrushes;        // ...
    unsigned __int16 *leafbrushes;      // ...
    unsigned int numLeafSurfaces;       // ...
    unsigned int *leafsurfaces;         // ...
    unsigned int vertCount;             // ...
    float (*verts)[3];                  // ...
    int triCount;                       // ...
    unsigned __int16 *triIndices;       // ...
    unsigned __int8 *triEdgeIsWalkable; // ...
    int borderCount;                    // ...
    struct CollisionBorder *borders;           // ...
    int partitionCount;                 // ...
    struct CollisionPartition *partitions;     // ...
    int aabbTreeCount;                  // ...
    struct CollisionAabbTree *aabbTrees;       // ...
    unsigned int numSubModels;          // ...
    struct cmodel_t *cmodels;                  // ...
    unsigned __int16 numBrushes;        // ...
    // padding byte
    // padding byte
    struct cbrush_t *brushes;                  // ...
    int numClusters;                    // ...
    int clusterBytes;                   // ...
    unsigned __int8 *visibility;        // ...
    int vised;                          // ...
    struct MapEnts *mapEnts;                   // ...
    struct cbrush_t *box_brush;                // ...
    cmodel_t box_model;                 // ...
    unsigned __int16 dynEntCount[2];    // ...
    struct DynEntityDef *dynEntDefList[2];     // ...
    struct DynEntityPose *dynEntPoseList[2];   // ...
    struct DynEntityClient *dynEntClientList[2]; // ...
    struct DynEntityColl *dynEntCollList[2];   // ...
    unsigned int checksum;              // ...
};


/*
==============================================================

Profiler

==============================================================
*/
enum MapProfileTrackedValue
{                                       // ...
    MAP_PROFILE_FILE_OPEN = 0x0,
    MAP_PROFILE_FILE_SEEK = 0x1,
    MAP_PROFILE_FILE_READ = 0x2,
    MAP_PROFILE_VALUE_MAX = 0x3,
};
struct MapProfileElement // sizeof=0x18
{                                       // ...
    unsigned __int64 ticksStart;
    unsigned __int64 ticksTotal;
    unsigned __int64 ticksSelf;
};
struct MapProfileEntry // sizeof=0x70
{                                       // ...
    const char *label;
    int accessCount;
    unsigned __int64 ticksStart;
    unsigned __int64 ticksTotal;
    unsigned __int64 ticksSelf;
    int indent;
    MapProfileEntry *parent;
    MapProfileElement elements[3];
};
struct MapProfileHotSpot // sizeof=0x18
{                                       // ...
    const char *label;                  // ...
    int accessCount;                    // ...
    __int64 ticksSelf;                  // ...
    __int64 ticksFile;                  // ...
};
struct mapLoadProfile_t // sizeof=0xA880
{                                       // ...
    bool isLoading;                     // ...
    // padding byte
    // padding byte
    // padding byte
    int profileEntryCount;              // ...
    MapProfileEntry profileEntries[384]; // ...
    MapProfileEntry *currentEntry;      // ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    unsigned __int64 ticksStart;        // ...
    unsigned __int64 ticksFinish;       // ...
    unsigned __int64 ticksProfiled;     // ...
    int elementAccessCount[3];          // ...
    // padding byte
    // padding byte
    // padding byte
    // padding byte
    MapProfileElement elements[3];      // ...
};

// statmonitor
struct statmonitor_s // sizeof=0x8
{                                       // ...
    int endtime;                        // ...
    void *material;                 // ...
};


#define FloatAsInt(f) (*(int*)&(f))

inline bool IsPowerOf2(int num)
{
    return (num & (num - 1)) == 0;
}

template <typename T>
inline T Buf_Read(unsigned char **pos)
{
    T value = *(reinterpret_cast<const T *>(*pos));
    *pos += sizeof(T);
    return value;
}

