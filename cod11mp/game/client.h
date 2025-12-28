#pragma once
#include "../qcommon/qcommon.h"

#include "../qcommon/ent.h"
#include "../qcommon/net_chan.h"

#include "../bgame/bg_local.h"

struct GfxConfiguration;

#define MAX_PARSE_ENTITIES 2048
#define MAX_PARSE_CLIENTS 2048
static_assert(((MAX_PARSE_ENTITIES) & (MAX_PARSE_ENTITIES - 1)) == 0, "MAX_PARSE_ENTITIES must be power of 2");
static_assert(((MAX_PARSE_CLIENTS) & (MAX_PARSE_CLIENTS - 1)) == 0, "MAX_PARSE_CLIENTS must be power of 2");

struct serverAddress_t 
{                                       
    uint8_t ip[4];              
    uint16_t port;              
};

struct trDebugString_t 
{
    float xyz[3];
    float color[4];
    float scale;
    char text[96];
};

struct clientDebugStringInfo_t 
{                                       
    int max;                            
    int num;                            
    trDebugString_t* strings;           
    int* durations;                     
};

struct trDebugLine_t 
{
    float start[3];
    float end[3];
    float color[4];
    int depthTest;
};

struct clientDebugLineInfo_t 
{                                       
    int max;                            
    int num;                            
    trDebugLine_t* lines;               
    int* durations;                     
};

struct clientDebug_t 
{                                       
    int prevFromServer;
    int fromServer;                     
    clientDebugStringInfo_t clStrings;  
    clientDebugStringInfo_t svStringsBuffer; 
    clientDebugStringInfo_t svStrings;  
    clientDebugLineInfo_t clLines;      
    clientDebugLineInfo_t svLinesBuffer; 
    clientDebugLineInfo_t svLines;      
};

struct GfxDebugPoly 
{
    float color[4];
    int firstVert;
    int vertCount;
};

struct GfxDebugPlume 
{
    float origin[3];
    float color[4];
    int score;
    int startTime;
    int duration;
};

struct DebugGlobals 
{                                       
    float (*verts)[3];
    int vertCount;
    int vertLimit;
    GfxDebugPoly* polys;
    int polyCount;
    int polyLimit;
    trDebugString_t* strings;
    int stringCount;
    int stringLimit;
    trDebugString_t* externStrings;
    int externStringCount;
    int externMaxStringCount;
    trDebugLine_t* lines;
    int lineCount;
    int lineLimit;
    trDebugLine_t* externLines;
    int externLineCount;
    int externMaxLineCount;
    GfxDebugPlume* plumes;              
    int plumeCount;                     
    int plumeLimit;                     
};

enum GfxWarningType
{                                       
    R_WARN_FRONTEND_ENT_LIMIT = 0x0,
    R_WARN_KNOWN_MODELS = 0x1,
    R_WARN_KNOWN_SPECIAL_MODELS = 0x2,
    R_WARN_MODEL_LIGHT_CACHE = 0x3,
    R_WARN_SCENE_ENTITIES = 0x4,
    R_WARN_TEMP_SKIN_BUF_SIZE = 0x5,
    R_WARN_MAX_SKINNED_CACHE_VERTICES = 0x6,
    R_WARN_MAX_SCENE_SURFS_SIZE = 0x7,
    R_WARN_PORTAL_PLANES = 0x8,
    R_WARN_MAX_CLOUDS = 0x9,
    R_WARN_MAX_DLIGHTS = 0xA,
    R_WARN_SMODEL_LIGHTING = 0xB,
    R_WARN_MAX_DRAWSURFS = 0xC,
    R_WARN_GFX_CODE_MESH_LIMIT = 0xD,
    R_WARN_GFX_MARK_MESH_LIMIT = 0xE,
    R_WARN_MAX_SCENE_DRAWSURFS = 0xF,
    R_WARN_MAX_FX_DRAWSURFS = 0x10,
    R_WARN_NONEMISSIVE_FX_MATERIAL = 0x11,
    R_WARN_NONLIGHTMAP_MARK_MATERIAL = 0x12,
    R_WARN_PRIM_DRAW_SURF_BUFFER_SIZE = 0x13,
    R_WARN_CMDBUF_OVERFLOW = 0x14,
    R_WARN_MISSING_DECL_NONDEBUG = 0x15,
    R_WARN_MAX_DYNENT_REFS = 0x16,
    R_WARN_MAX_SCENE_DOBJ_REFS = 0x17,
    R_WARN_MAX_SCENE_MODEL_REFS = 0x18,
    R_WARN_MAX_SCENE_BRUSH_REFS = 0x19,
    R_WARN_MAX_CODE_INDS = 0x1A,
    R_WARN_MAX_CODE_VERTS = 0x1B,
    R_WARN_MAX_CODE_ARGS = 0x1C,
    R_WARN_MAX_MARK_INDS = 0x1D,
    R_WARN_MAX_MARK_VERTS = 0x1E,
    R_WARN_DEBUG_ALLOC = 0x1F,
    R_WARN_SPOT_LIGHT_LIMIT = 0x20,
    R_WARN_FX_ELEM_LIMIT = 0x21,
    R_WARN_WORKER_CMD_SIZE = 0x22,
    R_WARN_UNKNOWN_STATICMODEL_SHADER = 0x23,
    R_WARN_UNKNOWN_XMODEL_SHADER = 0x24,
    R_WARN_DYNAMIC_INDEX_BUFFER_SIZE = 0x25,
    R_WARN_TOO_MANY_LIGHT_GRID_POINTS = 0x26,
    R_WARN_FOGABLE_2DTEXT = 0x27,
    R_WARN_FOGABLE_2DGLYPH = 0x28,
    R_WARN_COUNT = 0x29,
};

const char * const s_warnFormat[41] =
{
    "entity buffer exceeded - not drawing model",
    "too many existing models (more than %i)",
    "too many existing special models (more than %i)",
    "model light cache alloc failed - not drawing model",
    "too many scene entities (more than %i)",
    "TEMP_SKIN_BUF_SIZE exceeded - not skinning surface",
    "R_MAX_SKINNED_CACHE_VERTICES((1024 * 144)) exceeded - not drawing surface",
    "MAX_SCENE_SURFS_SIZE(131072) exceeded - not drawing surface",
    "Portal plane buffer full - flushing",
    "GFX_PARTICLE_CLOUD_LIMIT(256) exceeded - not drawing particle cloud",
    "MAX_ADDED_DLIGHTS(32) exceeded.",
    "Too many visible static models - not drawing static model",
    "MAX_DRAWSURFS(32768) exceeded - not drawing geometry",
    "GFX_CODE_MESH_LIMIT(2048) exceeded - not drawing code mesh",
    "GFX_MARK_MESH_LIMIT(1536) exceeded - not drawing mark mesh",
    "Max scene drawsurfs exceed from %s - not drawing surface",
    "Max fx drawsurfs %i exceed for region %i - not drawing surface",
    "non effect material ',27h,'%s',27h,' used for effect (or code geom)",
    "non impact mark material ',27h,'%s',27h,' used for impact mark",
    "PRIM_DRAW_SURF_BUFFER_SIZE((128 * 512)) exceeded - not drawing surface",
    "command buffer overflow - not drawing surface",
    "Missing decl %s techset %s tech %s shader %s (ignore for debug settings)",
    "Max dyn ent refs exceeded",
    "Max scene dobj refs (%i) exceeded",
    "Max scene model refs (%i) exceeded",
    "Max scene brush refs",
    "GFX_CODE_MESH_INDEX_LIMIT((2048 * 6 * 2)) exceeded",
    "GFX_CODE_MESH_VERT_LIMIT((2048 * 4 * 2)) exceeded",
    "GFX_CODE_MESH_ARGS_LIMIT(256) exceeded",
    "GFX_MARK_MESH_INDEX_LIMIT((1536 * 6)) exceeded",
    "GFX_MARK_MESH_VERT_LIMIT((1536 * 4)) exceeded",
    "Out of debug memory for (%s)",
    "FX_SPOT_LIGHT_LIMIT(1) exceeded - not spawning spot light effect",
    "FX_ELEM_LIMIT(2048) exceeded - not spawning fx elem",
    "worker command size exceeded for type %i",
    "Unknown static model shader",
    "Unknown xmodel shader",
    "DYNAMIC_INDEX_BUFFER_SIZE exceeded - speed warning",
    "Too many light grid points",
    "Fogable material %s used for 2D text %s",
    "Fogable material %s used for 2D glyph",
};

struct clSnapshot_t 
{                                       
                                        // clientActive_t/r ...
    int32_t valid;                          
                                        // CL_ParseSnapshot:loc_4A5715/w ...
    int32_t snapFlags;                      
    int32_t serverTime;                     
                                        // CL_ParseSnapshot+200/r ...
    int32_t messageNum;                     
                                        // CL_ParseSnapshot:loc_4A55D6/r ...
    int32_t deltaNum;                       
                                        // CL_ParseSnapshot+8F/w ...
    int32_t ping;
    int32_t cmdNum;
    playerState_s ps;                   
                                        // CL_ParseSnapshot+21B/o ...
    int32_t numEntities;
    int32_t numClients;
    int32_t parseEntitiesNum;
    int32_t parseClientsNum;
    int32_t serverCommandNum;               
};

struct gameState_t 
{                                       
    int32_t stringOffsets[2442];
    char stringData[131072];
    int32_t dataCount;
};

enum StanceState
{                                       
    CL_STANCE_STAND = 0x0,
    CL_STANCE_CROUCH = 0x1,
    CL_STANCE_PRONE = 0x2,
};

struct ClientArchiveData 
{                                       
    int32_t serverTime;
    float origin[3];
    float velocity[3];
    int32_t bobCycle;
    int32_t movementDir;
    float viewangles[3];
};

struct outPacket_t 
{                                       
    int32_t p_cmdNumber;
    int32_t p_serverTime;
    int32_t p_realtime;
};
enum sessionState_t
{                                       
    SESS_STATE_PLAYING = 0x0,
    SESS_STATE_DEAD = 0x1,
    SESS_STATE_SPECTATOR = 0x2,
    SESS_STATE_INTERMISSION = 0x3,
};

enum clientConnected_t
{                                       
    CON_DISCONNECTED = 0x0,
    CON_CONNECTING = 0x1,
    CON_CONNECTED = 0x2,
};
struct playerTeamState_t 
{                                       
    int32_t location;
};

struct clientState_s 
{                                       
                                        // ?MSG_ReadDeltaClient@@YAHPAUmsg_t@@HPBUclientState_s@@PAU2@H@Z/r ...
    int32_t clientIndex;
    team_t team;                        
    // SpectatorClientEndFrame(gentity_s *):loc_4F9A78/r ...
    int32_t modelindex;
    int32_t attachModelIndex[6];            
    // FX_SavePhysicsData+156/o ...
    int32_t attachTagIndex[6];              
    // AimTarget_IsTargetValid+228/o ...
    char name[16];                      
    // _memmove:UnwindDown2/o ...
    float maxSprintTimeMultiplier;      
    // R_ChangeState_0(GfxCmdBufState *,uint)+2E6/o
    int32_t rank;
    int32_t prestige;
    int32_t perks;
    int32_t attachedVehEntNum;
    int32_t attachedVehSlotIndex;           
};

struct clientSession_t 
{                                       
    sessionState_t sessionState;
    int32_t forceSpectatorClient;
    int32_t killCamEntity;
    int32_t status_icon;
    int32_t archiveTime;
    int32_t score;
    int32_t deaths;
    int32_t kills;
    int32_t assists;
    uint16_t scriptPersId;
    
    
    clientConnected_t connected;
    usercmd_s cmd;
    usercmd_s oldcmd;
    int32_t localClient;
    int32_t predictItemPickup;
    char newnetname[16];
    int32_t maxHealth;
    int32_t enterTime;
    playerTeamState_t teamState;
    int32_t voteCount;
    int32_t teamVoteCount;
    float moveSpeedScaleMultiplier;
    int32_t viewmodelIndex;
    int32_t noSpectate;
    int32_t teamInfo;
    clientState_s cs;
    int32_t psOffsetTime;
};

typedef struct gclient_s 
{                                       
    playerState_s ps;
    clientSession_t sess;
    int32_t spectatorClient;
    int32_t noclip;
    int32_t ufo;
    int32_t bFrozen;
    int32_t lastCmdTime;
    int32_t buttons;
    int32_t oldbuttons;
    int32_t latched_buttons;
    int32_t buttonsSinceLastFrame;
    float oldOrigin[3];
    float fGunPitch;
    float fGunYaw;
    int32_t damage_blood;
    float damage_from[3];
    int32_t damage_fromWorld;
    int32_t accurateCount;
    int32_t accuracy_shots;
    int32_t accuracy_hits;
    int32_t inactivityTime;
    int32_t inactivityWarning;
    int32_t lastVoiceTime;
    int32_t switchTeamTime;
    float currentAimSpreadScale;
    gentity_s *persistantPowerup;
    int32_t portalID;
    int32_t dropWeaponTime;
    int32_t sniperRifleFiredTime;
    float sniperRifleMuzzleYaw;
    int32_t PCSpecialPickedUpCount;
    EntHandle useHoldEntity;
    int32_t useHoldTime;
    int32_t useButtonDone;
    int32_t iLastCompassPlayerInfoEnt;
    int32_t compassPingTime;
    int32_t damageTime;
    float v_dmg_roll;
    float v_dmg_pitch;
    float swayViewAngles[3];
    float swayOffset[3];
    float swayAngles[3];
    float vLastMoveAng[3];
    float fLastIdleFactor;
    float vGunOffset[3];
    float vGunSpeed[3];
    int32_t weapIdleTime;
    int32_t lastServerTime;
    int32_t lastSpawnTime;
    uint32_t lastWeapon;
    bool previouslyFiring;
    bool previouslyUsingNightVision;
    bool previouslySprinting;
    
    int32_t hasRadar;
    int32_t lastStand;
    int32_t lastStandTime;
} gclient_t;

struct clientActive_t 
{                                       
    bool usingAds;
    
    
    
    int32_t timeoutcount;
    clSnapshot_t snap;
    bool alwaysFalse;
    
    
    
    int32_t serverTime;
    int32_t oldServerTime;
    int32_t oldFrameServerTime;
    int32_t serverTimeDelta;
    int32_t oldSnapServerTime;
    int32_t extrapolatedSnapshot;
    int32_t newSnapshots;
    gameState_t gameState;
    char mapname[64];
    int32_t parseEntitiesNum;
    int32_t parseClientsNum;
    int32_t mouseDx[2];
    int32_t mouseDy[2];
    int32_t mouseIndex;
    bool stanceHeld;
    
    
    
    StanceState stance;
    StanceState stancePosition;
    int32_t stanceTime;
    int32_t cgameUserCmdWeapon;
    int32_t cgameUserCmdOffHandIndex;
    float cgameFOVSensitivityScale;
    float cgameMaxPitchSpeed;
    float cgameMaxYawSpeed;
    float cgameKickAngles[3];
    float cgameOrigin[3];
    float cgameVelocity[3];
    float cgameViewangles[3];
    int32_t cgameBobCycle;
    int32_t cgameMovementDir;
    int32_t cgameExtraButtons;
    int32_t cgamePredictedDataServerTime;
    float viewangles[3];
    int32_t serverId;
    int32_t skelTimeStamp;                  
    volatile uint32_t skelMemPos;            
    char skelMemory[262144];
    char *skelMemoryStart;              
                                        // CL_AllocSkelMemory(uint)+BB/r
    bool allowedAllocSkel;
    
    
    
    usercmd_s cmds[128];
    int32_t cmdNumber;
    ClientArchiveData clientArchive[256];
    int32_t clientArchiveIndex;
    outPacket_t outPackets[32];
    clSnapshot_t snapshots[32];         
                                        // RB_LogPrintState_0(int,int)+19D/o ...
    entityState_s entityBaselines[1024];
    entityState_s parseEntities[2048];  
                                        // CountBitsEnabled(uint)+1B/o ...
    clientState_s parseClients[2048];   
                                        // AimTarget_IsTargetValid+228/o ...
    int32_t corruptedTranslationFile;
    char translationVersion[256];
    float vehicleViewYaw;
    float vehicleViewPitch;
};

struct clientConnection_t 
{                                       
    int32_t qport;
    int32_t clientNum;
    int32_t lastPacketSentTime;
    int32_t lastPacketTime;
    netadr_t serverAddress;
    int32_t connectTime;
    int32_t connectPacketCount;
    char serverMessage[256];
    int32_t challenge;
    int32_t checksumFeed;
    int32_t reliableSequence;
    int32_t reliableAcknowledge;
    char reliableCommands[128][1024];
    int32_t serverMessageSequence;
    int32_t serverCommandSequence;
    int32_t lastExecutedServerCommand;
    char serverCommands[128][1024];     
    bool isServerRestarting;
    
    
    
    int32_t lastClientArchiveIndex;
    char demoName[64];
    int32_t demorecording;
    int32_t demoplaying;
    int32_t isTimeDemo;
    int32_t demowaiting;
    int32_t firstDemoFrameSkipped;
    int32_t demofile;
    int32_t timeDemoLog;
    int32_t timeDemoFrames;
    int32_t timeDemoStart;
    int32_t timeDemoPrev;
    int32_t timeDemoBaseTime;
    netchan_t netchan;
    char netchanOutgoingBuffer[2048];
    char netchanIncomingBuffer[0x20000];
    netProfileInfo_t OOBProf;
    uint8_t statPacketsToSend;
    
    
    
    int32_t statPacketSendTime[7];
};




struct serverInfo_t 
{                                       
    netadr_t adr;                       
    uint8_t allowAnonymous;     
    uint8_t bPassword;
    uint8_t pure;
    char consoleDisabled;
    uint8_t netType;            
    uint8_t clients;            
    uint8_t maxClients;         
    uint8_t dirty;              
    char friendlyfire;
    char killcam;
    uint8_t hardware;
    uint8_t mod;
    uint8_t voice;
    uint8_t punkbuster;         
    uint8_t requestCount;       
    
    short minPing;                    
    short maxPing;                    
    short ping;                       
    char hostName[32];                  
    char mapName[32];                   
    char game[24];                      
    char gameType[16];                  
    
    
};

struct clientLogo_t 
{                                       
    int32_t startTime;                      
    int32_t duration;                       
    int32_t fadein;                         
    int32_t fadeout;                        
    void /*Material*/ *material[2];              
};
struct vidConfig_t 
{                                       
    uint32_t sceneWidth;            
    uint32_t sceneHeight;           
    uint32_t displayWidth;          
    uint32_t displayHeight;         
    uint32_t displayFrequency;      
    int32_t isFullscreen;                   
    float aspectRatioWindow;            
    float aspectRatioScenePixel;        
    float aspectRatioDisplayPixel;      
    uint32_t maxTextureSize;        
    uint32_t maxTextureMaps;        
    bool deviceSupportsGamma;           
    
    
    
};

struct Font_s;

struct clientStatic_t 
{                                       
    int32_t quit;                           
    int32_t hunkUsersStarted;               
    char servername[256];               
    int32_t rendererStarted;                
    int32_t soundStarted;                   
    int32_t uiStarted;                      
    int32_t devGuiStarted;                  
    int32_t frametime;                      
    int32_t realtime;                       
    int32_t realFrametime;                  
    clientLogo_t logo;                  
    float mapCenter[3];                 
    int32_t numlocalservers;                
    serverInfo_t localServers[128];     
    int32_t waitglobalserverresponse;       
    int32_t numglobalservers;               
    serverInfo_t globalServers[20000];  
    int32_t numfavoriteservers;             
    serverInfo_t favoriteServers[128];  
    int32_t pingUpdateSource;               
    netadr_t updateServer;
    char updateChallenge[1024];
    char updateInfoString[1024];        
    netadr_t authorizeServer;           
    void /*Material*/*whiteMaterial;            
    void /*Material*/*consoleMaterial;          
    Font_s *consoleFont;                
    char autoupdateServerNames[5][64];  
    netadr_t autoupdateServer;          
    vidConfig_t vidConfig;              
    clientDebug_t debug;                
    int32_t download;                       
    char downloadTempName[256];         
    char downloadName[256];             
    int32_t downloadNumber;
    int32_t downloadBlock;                  
    int32_t downloadCount;                  
    int32_t downloadSize;                   
    char downloadList[1024];            
    int32_t downloadRestart;                
    int32_t gameDirChanged;                 
    int32_t wwwDlDisconnected;              
    int32_t wwwDlInProgress;                
    int32_t downloadFlags;                  
    char originalDownloadName[64];      
    float debugRenderPos[3];            
};

enum connstate_t
{                                       
    CA_DISCONNECTED = 0x0,
    CA_CINEMATIC = 0x1,
    CA_LOGO = 0x2,
    CA_CONNECTING = 0x3,
    CA_CHALLENGING = 0x4,
    CA_CONNECTED = 0x5,
    CA_SENDINGSTATS = 0x6,
    CA_LOADING = 0x7,
    CA_PRIMED = 0x8,
    CA_ACTIVE = 0x9,
};

struct clientUIActive_t 
{
    bool active;
    bool isRunning;
    bool cgameInitialized;
    bool cgameInitCalled;
    int32_t keyCatchers;
    bool displayHUDWithKeycatchUI;
    
    
    
    connstate_t connectionState;
};

struct ClientVoicePacket_t 
{                                       
    uint8_t data[256];
    int32_t dataSize;
};
struct voiceCommunication_t 
{                                       
    ClientVoicePacket_t voicePackets[10];
    int32_t voicePacketCount;
    int32_t voicePacketLastTransmit;
};

struct VoicePacket_t 
{                                       
    uint8_t talker;             
    uint8_t data[256];          
    int32_t dataSize;                       
};

struct ping_t 
{                                       
    netadr_t adr;                       
    int32_t start;                          
    int32_t time;                           
    char info[1024];                    
};

#define MAX_CLIENTS 64

#define STATIC_MAX_LOCAL_CLIENTS 1 

// cl_cgame_mp
struct snapshot_s;
struct snd_alias_t;
struct refdef_s;
struct MemoryFile;

// cl_rank
enum rankTableColumns_t
{                                       
    MP_RANKTABLE_RANKID = 0x0,
    MP_RANKTABLE_RANK = 0x1,
    MP_RANKTABLE_MINXP = 0x2,
    MP_RANKTABLE_XPTONEXT = 0x3,
    MP_RANKTABLE_SHORTRANK = 0x4,
    MP_RANKTABLE_FULLRANK = 0x5,
    MP_RANKTABLE_ICON = 0x6,
    MP_RANKTABLE_MAXXP = 0x7,
    MP_RANKTABLE_WEAPUNLOCK = 0x8,
    MP_RANKTABLE_PERKUNLOCK = 0x9,
    MP_RANKTABLE_CHALLENGE = 0xA,
    MP_RANKTABLE_CAMO = 0xB,
    MP_RANKTABLE_ATTACHMENT = 0xC,
    MP_RANKTABLE_LEVEL = 0xD,
    MP_RANKTABLE_DISPLAYLEVEL = 0xE,
    MP_RANKTABLE_COUNT = 0xF,
};

// cl_input
struct kbutton_t 
{                                       
    int32_t down[2];                        
    uint32_t downtime;
    uint32_t msec;
    bool active;                        
    bool wasPressed;
    
    
};

// cl_ui_mp
struct uiClientState_s 
{                                       
    connstate_t connState;              
    int32_t connectPacketCount;             
    char servername[1024];              
    char updateInfoString[1024];
    char messageString[1024];           
};

