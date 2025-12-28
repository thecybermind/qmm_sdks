#pragma once



struct MemoryNode // sizeof=0xC
{                                       // XREF: scrMemTreeGlob_t/r
    unsigned short prev;              // XREF: MT_Init(void)+46/w
    unsigned short next;              // XREF: MT_Init(void)+4E/w
    unsigned int padding[2];            // XREF: MT_RemoveHeadMemoryNode+61/w
};

#define MEMORY_NODE_BITS 16
#define MEMORY_NODE_COUNT 0x10000
#define NUM_BUCKETS 256

struct  scrMemTreeGlob_t // sizeof=0xC0380
{                                       // XREF: .data:scrMemTreeGlob/r
    MemoryNode nodes[MEMORY_NODE_COUNT];            // XREF: MT_Init(void)+46/w
                                        // MT_Init(void)+4E/w ...
    unsigned char leftBits[NUM_BUCKETS];      // XREF: MT_InitBits+89/w
                                        // MT_GetScore+88/r ...
    unsigned char numBits[NUM_BUCKETS];       // XREF: MT_InitBits+59/w
                                        // MT_GetScore+6A/r ...
    unsigned char logBits[NUM_BUCKETS];       // XREF: MT_InitBits+BB/w
                                        // MT_GetSize+55/r ...
    unsigned short head[MEMORY_NODE_BITS + 1];// 0x242E200          // XREF: MT_DumpTree(void)+14B/r
                                        // MT_Init(void)+3A/w ...
    // padding byte
    // padding byte
    int totalAlloc;                     // XREF: MT_DumpTree(void):loc_59E783/r
                                        // MT_DumpTree(void)+1FB/r ...
    int totalAllocBuckets;              // XREF: MT_DumpTree(void):loc_59E7AE/r
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
