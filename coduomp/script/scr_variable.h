#pragma once
#include "../qcommon/q_shared.h"
#include "scr_stringlist.h"

#undef GetObject

enum Vartype_t
{
    VAR_UNDEFINED = 0x0,
    VAR_BEGIN_REF = 0x1,
    VAR_POINTER = 0x1,
    VAR_STRING = 0x2,
    VAR_ISTRING = 0x3,
    VAR_VECTOR = 0x4,
    VAR_END_REF = 0x5,
    VAR_FLOAT = 0x5,
    VAR_INTEGER = 0x6,
    VAR_CODEPOS = 0x7,
    VAR_PRECODEPOS = 0x8,
    VAR_FUNCTION = 0x9,
    VAR_STACK = 0xA,
    VAR_ANIMATION = 0xB,
    VAR_DEVELOPER_CODEPOS = 0xC,
    VAR_INCLUDE_CODEPOS = 0xD,
    VAR_THREAD = 0xE,
    VAR_NOTIFY_THREAD = 0xF,
    VAR_TIME_THREAD = 0x10,
    VAR_CHILD_THREAD = 0x11,
    VAR_OBJECT = 0x12,
    VAR_DEAD_ENTITY = 0x13,
    VAR_ENTITY = 0x14,
    VAR_ARRAY = 0x15,
    VAR_DEAD_THREAD = 0x16,
    VAR_COUNT = 0x17,
    VAR_THREAD_LIST = 0x18,
    VAR_ENDON_LIST = 0x19,
};

enum var_stat_t
{
	VAR_STAT_FREE = 0x0,
	VAR_STAT_MOVABLE = 0x20,
	VAR_STAT_HEAD = 0x40,
	VAR_STAT_EXTERNAL = 0x60,
	VAR_STAT_MASK = 0x60,
};

#define VAR_STAT_FREE 0
#define VAR_STAT_MOVABLE 0x20
#define VAR_STAT_MASK 0x60
#define VAR_STAT_EXTERNAL 0x60

#define VAR_MASK 0x1F

#define FIRST_DEAD_OBJECT 0x16

#define CLASS_NUM_COUNT 4
#define VAR_NAME_BITS 8
#define VAR_NAME_LOW_MASK 0x00FFFFFF

#define MAX_ARRAYINDEX 0x800000

#define VARIABLELIST_CHILD_SIZE 0xFFFE
#define VARIABLELIST_CHILD_BEGIN 0x8002 // 32770 // XBOX(0x6000) // 
#define VARIABLELIST_PARENT_BEGIN 1
#define VARIABLELIST_PARENT_SIZE 0x8000

#define VAR_NAME_HIGH_MASK 0xFFFFFF00

#define OBJECT_STACK 0x18001

#define FIRST_OBJECT 15
#define FIRST_CLEARABLE_OBJECT 0x12
#define FIRST_NONFIELD_OBJECT 0x15
#define FIRST_DEAD_OBJECT 0x16

//#define VAR_NAME_LOW_MASK 0xFF000000

struct VariableStackBuffer // sizeof=0xC
{
    const char *pos;
    unsigned __int16 size;
    unsigned __int16 bufLen;
    unsigned __int16 localId;
    unsigned __int8 time;
    char buf[1];
};
union VariableUnion // sizeof=0x4
{                                       // ...
    VariableUnion(float f)
    {
        floatValue = f;
    }
    VariableUnion(int i)
    {
        intValue = i;
    }
    VariableUnion(char *str)
    {
        codePosValue = str;
    }
    VariableUnion(const char *str)
    {
        codePosValue = str;
    }
    VariableUnion()
    {
        intValue = 0;
    }

    int intValue;
    float floatValue;
    unsigned int stringValue;
    const float *vectorValue;
    const char *codePosValue;
    unsigned int pointerValue;
    VariableStackBuffer *stackValue;
    unsigned int entityOffset;
};
struct VariableValue // sizeof=0x8
{   
    // ...
    VariableUnion u;                    // ...
    Vartype_t type;                           // ...
};

union ObjectInfo_u // sizeof=0x2
{                                       // ...
    unsigned __int16 size;
    unsigned __int16 entnum;
    unsigned __int16 nextEntId;
    unsigned __int16 self;
};

struct ObjectInfo // sizeof=0x4
{                                       // ...
    unsigned __int16 refCount;
    ObjectInfo_u u;
};

union Variable_u // sizeof=0x2
{                                       // ...
    unsigned __int16 prev;
    unsigned __int16 prevSibling;
};

struct Variable // sizeof=0x4
{                                       // ...
    unsigned __int16 id;                // ...
    Variable_u u;                       // ...
};

union VariableValueInternal_u // sizeof=0x4
{                                       // ...
    operator int()
    {
        return u.intValue;
    }
    VariableValueInternal_u(int i)
    {
        u.intValue = i;
    }
    VariableValueInternal_u()
    {
        u.intValue = 0;
    }

    unsigned __int16 next;
    VariableUnion u;
    ObjectInfo o;
};
union VariableValueInternal_w // sizeof=0x4
{                                       // ...
    unsigned int status;
    unsigned int type;
    unsigned int name;
    unsigned int classnum;
    unsigned int notifyName;
    unsigned int waitTime;
    unsigned int parentLocalId;
};
union VariableValueInternal_v // sizeof=0x2
{                                       // ...
    unsigned __int16 next;
    unsigned __int16 index;
};
struct VariableValueInternal // sizeof=0x10
{                                       // ...
    Variable hash;                      // ...
    VariableValueInternal_u u;          // ...
    VariableValueInternal_w w;          // ...
    VariableValueInternal_v v;          // ...
    unsigned __int16 nextSibling;       // ...
};

struct scrVarDebugPub_t // sizeof=0xE0004
{                                       // ...
    const char* varUsage[0x18000];
    unsigned __int16 extRefCount[0x8000];
    unsigned __int16 refCount[0x8000];
    int leakCount[0x18000];
    bool dummy;
    // padding byte
    // padding byte
    // padding byte
};
struct scrVarGlob_t // sizeof=0x180000
{                                       // ...
    VariableValueInternal variableList[0x18000]; // ...
};

struct scr_entref_t // sizeof=0x4
{                                       // ...
    scr_entref_t()
    {
        entnum = 0;
        classnum = 0;
    }
    scr_entref_t(int i)
    {
        entnum = i;
        classnum = i;
    }
    unsigned __int16 entnum;            // ...
    unsigned __int16 classnum;          // ...
};

struct scr_classStruct_t // sizeof=0xC
{
    scr_classStruct_t(unsigned __int16 _id, unsigned __int16 _entArrayId, char _charID, const char* _name)
    {
        id = _id;
        entArrayId = _entArrayId;
        charId = _charID;
        name = _name;
    }
    unsigned __int16 id;
    unsigned __int16 entArrayId;
    char charId;
    // padding byte
    // padding byte
    // padding byte
    const char *name;
};

struct VariableDebugInfo // sizeof=0x10
{
    const char *pos;
    const char *fileName;
    const char *functionName;
    int varUsage;
};

struct ThreadDebugInfo // sizeof=0x8C
{                                       // ...
    const char *pos[32];                // ...
    int posSize;                        // ...
    float varUsage;                     // ...
    float endonUsage;                   // ...
};
