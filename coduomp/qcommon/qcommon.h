#pragma once
#include "../qcommon/q_shared.h"
typedef enum
{
    SE_NONE,
    SE_KEY,
    SE_CHAR,
    SE_CONSOLE,
} sysEventType_t;
enum SphereEdgeTraceResult 
{                                       
    SPHERE_HITS_EDGE,
    SPHERE_MISSES_EDGE,
    SPHERE_MAY_HIT_V0,
    SPHERE_MAY_HIT_V1,
};
struct field_t 
{                                       
	int cursor;                         
	int scroll;
	int drawWidth;                      
	int widthInPixels;                  
	float charHeight;                   
	int fixedSize;                      
	char buffer[256];                   
};
enum hitLocation_t  // (MP/SP same)
{                                       
    HITLOC_NONE,
    HITLOC_HELMET,
    HITLOC_HEAD,
    HITLOC_NECK,
    HITLOC_TORSO_UPR,
    HITLOC_TORSO_LWR,
    HITLOC_R_ARM_UPR,
    HITLOC_L_ARM_UPR,
    HITLOC_R_ARM_LWR,
    HITLOC_L_ARM_LWR,
    HITLOC_R_HAND,
    HITLOC_L_HAND,
    HITLOC_R_LEG_UPR,
    HITLOC_L_LEG_UPR,
    HITLOC_R_LEG_LWR,
    HITLOC_L_LEG_LWR,
    HITLOC_R_FOOT,
    HITLOC_L_FOOT,
    HITLOC_GUN,
    HITLOC_NUM,
};
enum DemoType 
{                                       
    DEMO_TYPE_NONE,
    DEMO_TYPE_CLIENT,
    DEMO_TYPE_SERVER,
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
{                                       
    ERR_FATAL,
    ERR_DROP,
    ERR_SERVERDISCONNECT,
    ERR_DISCONNECT,
    ERR_SCRIPT,
    ERR_SCRIPT_DROP,
    ERR_LOCALIZATION,
    ERR_MAPLOADERRORSUMMARY,
};
enum $6ABDC6367E3229B6421BFD1B2626A094  // (SP/MP same)
{
    CON_CHANNEL_DONT_FILTER,
    CON_CHANNEL_ERROR,
    CON_CHANNEL_GAMENOTIFY,
    CON_CHANNEL_BOLDGAME,
    CON_CHANNEL_SUBTITLE,
    CON_CHANNEL_OBITUARY,
    CON_CHANNEL_LOGFILEONLY,
    CON_CHANNEL_CONSOLEONLY,
    CON_CHANNEL_GFX,
    CON_CHANNEL_SOUND,
    CON_CHANNEL_FILES,
    CON_CHANNEL_DEVGUI,
    CON_CHANNEL_PROFILE,
    CON_CHANNEL_UI,
    CON_CHANNEL_CLIENT,
    CON_CHANNEL_SERVER,
    CON_CHANNEL_SYSTEM,
    CON_CHANNEL_PLAYERWEAP,
    CON_CHANNEL_AI,
    CON_CHANNEL_ANIM,
    CON_CHANNEL_PHYS,
    CON_CHANNEL_FX,
    CON_CHANNEL_LEADERBOARDS,
    CON_CHANNEL_PARSERSCRIPT,
    CON_CHANNEL_SCRIPT,
    CON_BUILTIN_CHANNEL_COUNT,
};
inline bool Con_IsNotifyChannel(int channel)
{
    return channel == (CON_CHANNEL_GAMENOTIFY || channel == CON_CHANNEL_BOLDGAME || channel == CON_CHANNEL_SUBTITLE);
}
struct SndCurve;
struct SpeakerMapInfo;
struct XModelPiece;
enum CvarSetSource 
{                                       
    CVAR_SOURCE_INTERNAL,
    CVAR_SOURCE_EXTERNAL,
    CVAR_SOURCE_SCRIPT,
    CVAR_SOURCE_DEVGUI,
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
struct TraceExtents 
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
    float start[3];                     
    float end[3];                       
    float invDelta[3];
};
struct locTraceWork_t 
{                                       
    int contents;                       
    TraceExtents extents;               
};
struct traceWork_t 
{                                       
    TraceExtents extents;               
    float delta[3];                     
    float deltaLen;                     
    float deltaLenSq;                   
    float midpoint[3];                  
    float halfDelta[3];                 
    float halfDeltaAbs[3];              
    float size[3];                      
    float bounds[2][3];                 
    int contents;                       
    bool isPoint;                       
    bool axialCullOnly;
    float radius;                       
    float offsetZ;                      
    float radiusOffset[3];              
    float boundingRadius;               
    TraceThreadInfo threadInfo;         
};
struct IgnoreEntParams 
{                                       
    int baseEntity;                     
    int parentEntity;                   
    bool ignoreSelf;                    
    bool ignoreParent;                  
    bool ignoreSiblings;                
    bool ignoreChildren;                
};
struct pointtrace_t 
{                                       
    TraceExtents extents;               
    const IgnoreEntParams *ignoreEntParams; 
    int contentmask;                    
    int bLocational;                    
    unsigned char *priorityMap;       
};
struct moveclip_t 
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
enum DynEntityDrawType 
{                                       
    DYNENT_DRAW_MODEL,
    DYNENT_DRAW_BRUSH,
    DYNENT_DRAW_COUNT,
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
struct leafList_s 
{                                       
    int count;                          
    int maxcount;                       
    int overflowed;                     
    unsigned short *list;             
    float bounds[2][3];                 
    int lastLeaf;                       
};
struct areaParms_t 
{                                       
    const float *mins;                  
    const float *maxs;                  
    int *list;                          
    int count;                          
    int maxcount;                       
    int contentmask;                    
};
struct staticmodeltrace_t 
{                                       
    TraceExtents extents;               
    int contents;                       
};
struct sightclip_t 
{
    float mins[3];
    float maxs[3];
    float outerSize[3];
    float start[3];
    float end[3];
    int passEntityNum[2];
    int contentmask;
};
struct sightpointtrace_t 
{                                       
    float start[3];                     
    float end[3];                       
    int passEntityNum[2];               
    int contentmask;                    
    int locational;                     
    unsigned char *priorityMap;       
};
struct SpawnVar 
{                                       
    bool spawnVarsValid;                
    int32_t numSpawnVars;                   
    char *spawnVars[64][2];             
    int32_t numSpawnVarChars;
    char spawnVarChars[2048];
};
#define BOXSIDE_FRONT 1
#define BOXSIDE_BACK 2
struct ShowCollisionBrushPt 
{                                       
    float xyz[3];
    short sideIndex[3];
};
struct winding_t 
{
    int numpoints;
    float p[4][3];
};
struct cLeaf_t 
{                                       
    unsigned short firstCollAabbIndex;
    unsigned short collAabbCount;
    int brushContents;                  
    int terrainContents;                
    float mins[3];                      
    float maxs[3];                      
    int leafBrushNode;                  
    short cluster;
};
struct cmodel_t 
{                                       
    float mins[3];
    float maxs[3];
    float radius;
    cLeaf_t leaf;                       
};
struct clipMap_t 
{                                       
    const char *name;                   
    int isInUse;                        
    int planeCount;                     
    struct cplane_s *planes;                   
    unsigned int numStaticModels;       
    struct cStaticModel_s *staticModelList;    
    unsigned int numMaterials;          
    struct dmaterial_t *materials;             
    unsigned int numBrushSides;         
    struct cbrushside_t *brushsides;           
    unsigned int numBrushEdges;         
    unsigned char *brushEdges;        
    unsigned int numNodes;              
    struct cNode_t *nodes;                     
    unsigned int numLeafs;              
    struct cLeaf_t *leafs;                     
    unsigned int leafbrushNodesCount;   
    struct cLeafBrushNode_s *leafbrushNodes;   
    unsigned int numLeafBrushes;        
    unsigned short *leafbrushes;      
    unsigned int numLeafSurfaces;       
    unsigned int *leafsurfaces;         
    unsigned int vertCount;             
    float (*verts)[3];                  
    int triCount;                       
    unsigned short *triIndices;       
    unsigned char *triEdgeIsWalkable; 
    int borderCount;                    
    struct CollisionBorder *borders;           
    int partitionCount;                 
    struct CollisionPartition *partitions;     
    int aabbTreeCount;                  
    struct CollisionAabbTree *aabbTrees;       
    unsigned int numSubModels;          
    struct cmodel_t *cmodels;                  
    unsigned short numBrushes;        
    struct cbrush_t *brushes;                  
    int numClusters;                    
    int clusterBytes;                   
    unsigned char *visibility;        
    int vised;                          
    struct MapEnts *mapEnts;                   
    struct cbrush_t *box_brush;                
    cmodel_t box_model;                 
    unsigned short dynEntCount[2];    
    struct DynEntityDef *dynEntDefList[2];     
    struct DynEntityPose *dynEntPoseList[2];   
    struct DynEntityClient *dynEntClientList[2]; 
    struct DynEntityColl *dynEntCollList[2];   
    unsigned int checksum;              
};
/*
==============================================================
Profiler
==============================================================
*/
enum MapProfileTrackedValue
{                                       
    MAP_PROFILE_FILE_OPEN,
    MAP_PROFILE_FILE_SEEK,
    MAP_PROFILE_FILE_READ,
    MAP_PROFILE_VALUE_MAX,
};
struct MapProfileElement 
{                                       
    unsigned __int64 ticksStart;
    unsigned __int64 ticksTotal;
    unsigned __int64 ticksSelf;
};
struct MapProfileEntry 
{                                       
    const char *label;
    int accessCount;
    unsigned __int64 ticksStart;
    unsigned __int64 ticksTotal;
    unsigned __int64 ticksSelf;
    int indent;
    MapProfileEntry *parent;
    MapProfileElement elements[3];
};
struct MapProfileHotSpot 
{                                       
    const char *label;                  
    int accessCount;                    
    __int64 ticksSelf;                  
    __int64 ticksFile;                  
};
struct mapLoadProfile_t 
{                                       
    bool isLoading;                     
    int profileEntryCount;              
    MapProfileEntry profileEntries[384]; 
    MapProfileEntry *currentEntry;      
    unsigned __int64 ticksStart;        
    unsigned __int64 ticksFinish;       
    unsigned __int64 ticksProfiled;     
    int elementAccessCount[3];          
    MapProfileElement elements[3];      
};
// statmonitor
struct statmonitor_s 
{                                       
    int endtime;                        
    void *material;                 
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