#pragma once



struct MemoryNode 
{                                       
    unsigned short prev;              
    unsigned short next;              
    unsigned int padding[2];            
};

#define MEMORY_NODE_BITS 16
#define MEMORY_NODE_COUNT 0x10000
#define NUM_BUCKETS 256

struct  scrMemTreeGlob_t 
{                                       
    MemoryNode nodes[MEMORY_NODE_COUNT];            
                                        // MT_Init(void)+4E/w ...
    unsigned char leftBits[NUM_BUCKETS];      
                                        // MT_GetScore+88/r ...
    unsigned char numBits[NUM_BUCKETS];       
                                        // MT_GetScore+6A/r ...
    unsigned char logBits[NUM_BUCKETS];       
                                        // MT_GetSize+55/r ...
    unsigned short head[MEMORY_NODE_BITS + 1];// 0x242E200          
                                        // MT_Init(void)+3A/w ...
    
    
    int totalAlloc;                     
                                        // MT_DumpTree(void)+1FB/r ...
    int totalAllocBuckets;              
};

static const char* mt_type_names[22] =
{
    "empty",
    "thread",
    "vector",
    "notetrack",
    "anim tree",
    "small anim tree",
    "external",
    "temp",
    "surface",
    "anim part",
    "model part",
    "model part map",
    "duplicate parts",
    "model list",
    "script parse",
    "script string",
    "class",
    "tag info",
    "animscripted",
    "config string",
    "debugger string",
    "generic",
};
