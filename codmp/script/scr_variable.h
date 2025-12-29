#pragma once
#include "../qcommon/q_shared.h"
#include "scr_stringlist.h"
#undef GetObject
enum Vartype_t
{
    VAR_UNDEFINED,
    VAR_BEGIN_REF,
    VAR_POINTER,
    VAR_STRING,
    VAR_ISTRING,
    VAR_VECTOR,
    VAR_END_REF,
    VAR_FLOAT,
    VAR_INTEGER,
    VAR_CODEPOS,
    VAR_PRECODEPOS,
    VAR_FUNCTION,
    VAR_STACK,
    VAR_ANIMATION,
    VAR_DEVELOPER_CODEPOS,
    VAR_INCLUDE_CODEPOS,
    VAR_THREAD,
    VAR_NOTIFY_THREAD,
    VAR_TIME_THREAD,
    VAR_CHILD_THREAD,
    VAR_OBJECT,
    VAR_DEAD_ENTITY,
    VAR_ENTITY,
    VAR_ARRAY,
    VAR_DEAD_THREAD,
    VAR_COUNT,
    VAR_THREAD_LIST,
    VAR_ENDON_LIST,
};
enum var_stat_t
{
	VAR_STAT_FREE,
	VAR_STAT_MOVABLE,
	VAR_STAT_HEAD,
	VAR_STAT_EXTERNAL,
	VAR_STAT_MASK,
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
struct VariableStackBuffer 
{
    const char *pos;
    unsigned short size;
    unsigned short bufLen;
    unsigned short localId;
    unsigned char time;
    char buf[1];
};
union VariableUnion 
{                                       
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
struct VariableValue 
{   
    VariableUnion u;                    
    Vartype_t type;                           
};
union ObjectInfo_u 
{                                       
    unsigned short size;
    unsigned short entnum;
    unsigned short nextEntId;
    unsigned short self;
};
struct ObjectInfo 
{                                       
    unsigned short refCount;
    ObjectInfo_u u;
};
union Variable_u 
{                                       
    unsigned short prev;
    unsigned short prevSibling;
};
struct Variable 
{                                       
    unsigned short id;                
    Variable_u u;                       
};
union VariableValueInternal_u 
{                                       
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
    unsigned short next;
    VariableUnion u;
    ObjectInfo o;
};
union VariableValueInternal_w 
{                                       
    unsigned int status;
    unsigned int type;
    unsigned int name;
    unsigned int classnum;
    unsigned int notifyName;
    unsigned int waitTime;
    unsigned int parentLocalId;
};
union VariableValueInternal_v 
{                                       
    unsigned short next;
    unsigned short index;
};
struct VariableValueInternal 
{                                       
    Variable hash;                      
    VariableValueInternal_u u;          
    VariableValueInternal_w w;          
    VariableValueInternal_v v;          
    unsigned short nextSibling;       
};
struct scrVarDebugPub_t 
{                                       
    const char* varUsage[0x18000];
    unsigned short extRefCount[0x8000];
    unsigned short refCount[0x8000];
    int leakCount[0x18000];
    bool dummy;
};
struct scrVarGlob_t 
{                                       
    VariableValueInternal variableList[0x18000]; 
};
struct scr_entref_t 
{                                       
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
    unsigned short entnum;            
    unsigned short classnum;          
};
struct scr_classStruct_t 
{
    scr_classStruct_t(unsigned short _id, unsigned short _entArrayId, char _charID, const char* _name)
    {
        id = _id;
        entArrayId = _entArrayId;
        charId = _charID;
        name = _name;
    }
    unsigned short id;
    unsigned short entArrayId;
    char charId;
    const char *name;
};
struct VariableDebugInfo 
{
    const char *pos;
    const char *fileName;
    const char *functionName;
    int varUsage;
};
struct ThreadDebugInfo 
{                                       
    const char *pos[32];                
    int posSize;                        
    float varUsage;                     
    float endonUsage;                   
};