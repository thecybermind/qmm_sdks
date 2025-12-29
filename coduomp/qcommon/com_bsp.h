#pragma once
//#include <xanim/xanim.h>
#define BSP_VERSION 22
struct DiskPrimaryLight_Version16 
{
    unsigned short falloffStart;
    unsigned char falloffSizeLessOne;
    unsigned char type;
    float color[3];
    float dir[3];
    float origin[3];
    float radius;
    float cosHalfFovOuter;
    float cosHalfFovInner;
    int exponent;
    char defName[40];
};
struct DiskPrimaryLight 
{
    unsigned char type;
    unsigned char canUseShadowMap;
    unsigned char unused[2];
    float color[3];
    float dir[3];
    float origin[3];
    float radius;
    float cosHalfFovOuter;
    float cosHalfFovInner;
    int exponent;
    float rotationLimit;
    float translationLimit;
    char defName[64];
};
enum LumpType 
{                                       
    LUMP_MATERIALS,
    LUMP_LIGHTBYTES,
    LUMP_LIGHTGRIDENTRIES,
    LUMP_LIGHTGRIDCOLORS,
    LUMP_PLANES,
    LUMP_BRUSHSIDES,
    LUMP_BRUSHSIDEEDGECOUNTS,
    LUMP_BRUSHEDGES,
    LUMP_BRUSHES,
    LUMP_TRIANGLES,
    LUMP_DRAWVERTS,
    LUMP_DRAWINDICES,
    LUMP_CULLGROUPS,
    LUMP_CULLGROUPINDICES,
    LUMP_OBSOLETE_1,
    LUMP_OBSOLETE_2,
    LUMP_OBSOLETE_3,
    LUMP_OBSOLETE_4,
    LUMP_OBSOLETE_5,
    LUMP_PORTALVERTS,
    LUMP_OBSOLETE_6,
    LUMP_OBSOLETE_7,
    LUMP_OBSOLETE_8,
    LUMP_OBSOLETE_9,
    LUMP_AABBTREES,
    LUMP_CELLS,
    LUMP_PORTALS,
    LUMP_NODES,
    LUMP_LEAFS,
    LUMP_LEAFBRUSHES,
    LUMP_LEAFSURFACES,
    LUMP_COLLISIONVERTS,
    LUMP_COLLISIONTRIS,
    LUMP_COLLISIONEDGEWALKABLE,
    LUMP_COLLISIONBORDERS,
    LUMP_COLLISIONPARTITIONS,
    LUMP_COLLISIONAABBS,
    LUMP_MODELS,
    LUMP_VISIBILITY,
    LUMP_ENTITIES,
    LUMP_PATHCONNECTIONS,
    LUMP_REFLECTION_PROBES,
    LUMP_VERTEX_LAYER_DATA,
    LUMP_PRIMARY_LIGHTS,
    LUMP_LIGHTGRIDHEADER,
    LUMP_LIGHTGRIDROWS,
    LUMP_OBSOLETE_10,
    LUMP_UNLAYERED_TRIANGLES,
    LUMP_UNLAYERED_DRAWVERTS,
    LUMP_UNLAYERED_DRAWINDICES,
    LUMP_UNLAYERED_CULLGROUPS,
    LUMP_UNLAYERED_AABBTREES,
    LUMP_LIGHTREGIONS,
    LUMP_LIGHTREGION_HULLS,
    LUMP_LIGHTREGION_AXES,
};
enum ComSaveLumpBehavior 
{                                       
    COM_SAVE_LUMP_AND_CLOSE,
    COM_SAVE_LUMP_AND_REOPEN,
};
struct BspChunk 
{                                       
    LumpType type;                      
    unsigned int length;                
};
struct BspHeader 
{                                       
    unsigned int ident;                 
    unsigned int version;               
    unsigned int chunkCount;            
    BspChunk chunks[100];               
};
struct BspGlob 
{                                       
    char name[64];                      
    BspHeader *header;                  
    unsigned int fileSize;              
    unsigned int checksum;              
    LumpType loadedLumpType;
    const void *loadedLumpData;         
};