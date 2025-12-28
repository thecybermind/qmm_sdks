#pragma once

#include "../qcommon/q_shared.h"

#include "scr_variable.h"

static const char *var_typename[] =
{
    "undefined",
    "object",
    "string",
    "localized string",
    "vector",
    "float",
    "int",
    "codepos",
    "precodepos",
    "function",
    "stack",
    "animation",
    "developer codepos",
    "include codepos",
    "thread",
    "thread",
    "thread",
    "thread",
    "struct",
    "removed entity",
    "entity",
    "array",
    "removed thread",
};

struct scrVarPub_t 
{
    char* fieldBuffer;
    unsigned short canonicalStrCount;
    bool developer;
    bool developer_script;
    bool evaluate;
    const char* error_message;
    int error_index;
    unsigned int time;
    unsigned int timeArrayId;
    unsigned int pauseArrayId;
    unsigned int levelId;
    unsigned int gameId;
    unsigned int animId;
    unsigned int freeEntList;
    unsigned int tempVariable;
    bool bInited;
    unsigned short savecount;
    unsigned int checksum;
    unsigned int entId;
    unsigned int entFieldName;
    HunkUser* programHunkUser;
    const char* programBuffer;
    const char* endScriptBuffer;
    unsigned short saveIdMap[32768];
    unsigned short saveIdMapRev[32768];
    bool bScriptProfile;
    float scriptProfileMinTime;
    bool bScriptProfileBuiltin;
    float scriptProfileBuiltinMinTime;
    unsigned int numScriptThreads;
    unsigned int numScriptValues;
    unsigned int numScriptObjects;
    const char* varUsagePos;
    int ext_threadcount;
    int totalObjectRefCount;
    volatile unsigned int totalVectorRefCount;
};

struct PrecacheEntry 
{                                       
    unsigned short filename;
    bool include;
    
    unsigned int sourcePos;
};
