#pragma once

#include "../qcommon/qcommon.h"

#include "../bgame/bg_public.h"
#include "../bgame/bg_local.h"

struct gentity_s;

struct entityHandler_t 
{
    void( *think)(gentity_s *);
    void( *reached)(gentity_s *);
    void( *blocked)(gentity_s *, gentity_s *);
    void( *touch)(gentity_s *, gentity_s *, int32_t);
    void( *use)(gentity_s *, gentity_s *, gentity_s *);
    void( *pain)(gentity_s *, gentity_s *, int32_t, const float *, const int32_t, const float *, const hitLocation_t, const int32_t);
    void( *die)(gentity_s *, gentity_s *, gentity_s *, int32_t, int32_t, const int, const float *, const hitLocation_t, int32_t);
    void( *controller)(const gentity_s *, int32_t *);
    int32_t methodOfDeath;
    int32_t splashMethodOfDeath;
};

struct trigger_info_t 
{                                       
    uint16_t entnum;
    uint16_t otherEntnum;
    int32_t useCount;
    int32_t otherUseCount;
};

struct cached_tag_mat_t 
{                                       
    int32_t time;
    int32_t entnum;
    uint16_t name;              
    
    
    float tagMat[4][3];                 
};

struct com_parse_mark_t 
{                                       
    int lines;                          
    const char *text;
    int ungetToken;
    int backup_lines;
    const char *backup_text;
};

struct level_locals_t 
{                                       
    struct gclient_s *clients;                 
    gentity_s *gentities;               
    int32_t gentitySize;
    int32_t num_entities;                   
    gentity_s *firstFreeEnt;            
    gentity_s *lastFreeEnt;             
    int32_t logFile;                        
    int32_t initializing;                   
    int32_t clientIsSpawning;               
    objective_t objectives[16];         
    int32_t maxclients;                     
    int32_t framenum;                       
    int32_t time;                           
    int32_t previousTime;                   
    int32_t frametime;                      
    int32_t startTime;                      
    int32_t teamScores[4];                  
    int32_t lastTeammateHealthTime;         
    int32_t bUpdateScoresForIntermission;   
    bool teamHasRadar[4];               
    int32_t manualNameChange;               
    int32_t numConnectedClients;            
    int32_t sortedClients[64];              
    char voteString[1024];              
    char voteDisplayString[1024];       
    int32_t voteTime;                       
    int32_t voteExecuteTime;                
    int32_t voteYes;                        
    int32_t voteNo;                         
    int32_t numVotingClients;               
    SpawnVar spawnVar;                  
    int32_t savepersist;                    
    EntHandle droppedWeaponCue[32];
    float fFogOpaqueDist;               
    float fFogOpaqueDistSqrd;           
    int32_t remapCount;
    int32_t currentPlayerClone;             
    trigger_info_t pendingTriggerList[256]; 
    trigger_info_t currentTriggerList[256]; 
    int32_t pendingTriggerListSize;         
    int32_t currentTriggerListSize;         
    int32_t finished;                       
    int32_t bPlayerIgnoreRadiusDamage;      
    int32_t bPlayerIgnoreRadiusDamageLatched; 
    int32_t registerWeapons;                
    int32_t bRegisterItems;                 
    int32_t currentEntityThink;             
    int32_t openScriptIOFileHandles[1];     
    char *openScriptIOFileBuffers[1];   
    com_parse_mark_t currentScriptIOLineMark[1]; 
    cached_tag_mat_t cachedTagMat;      
    int32_t scriptPrintChannel;             
    float compassMapUpperLeft[2];       
    float compassMapWorldSize[2];       
    float compassNorth[2];              
    scr_vehicle_s *vehicles;            
};
