#pragma once

#define MAX_MEM_TRACK 1024
#define MAX_HUNK_TRACK 0x80000
#define MAX_HUNKLOW_TRACK 0x10000

#define TRACK_FREE 1

struct meminfo_t // sizeof=0xA0
{                                       // ...
    int total;                          // ...
    int nonSwapTotal;                   // ...
    int nonSwapMinSpecTotal;            // ...
    int typeTotal[37];                  // ...
};

struct mem_track_t // sizeof=0x14
{                                       // ...
    const char* name;                   // ...
    const char* filename;
    int size;                           // ...
    int pos;                            // ...
    unsigned char type;               // ...
    unsigned char usageType;          // ...
    // padding byte
    // padding byte
};

struct mem_track_node_s // sizeof=0x20
{
    mem_track_t data;
    int project;
    mem_track_node_s* prev;
    mem_track_node_s* next;
};

#define TRACK_STATIC_ARR(glob, type) track_static_alloc_internal(glob, sizeof(glob), #glob, type)
#define TRACK_STATIC_DAT(glob, type) track_static_alloc_internal(&glob, sizeof(glob), #glob, type)
