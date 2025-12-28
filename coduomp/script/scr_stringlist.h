#pragma once

#define HASH_STAT_FREE      0
#define HASH_STAT_MOVABLE   0x10000
#define HASH_STAT_HEAD      0x20000
#define HASH_STAT_MASK      0x30000

#define SL_MAX_STRING_INDEX 0x10000

#define STRINGLIST_SIZE 20'000

union HashEntry_unnamed_type_u
{           
    HashEntry_unnamed_type_u()
    {
        prev = 0;
    }
    HashEntry_unnamed_type_u(unsigned int val)
    {
        prev = val;
    }
    operator unsigned int() const
    {
        return prev;
    }
    unsigned int prev;
    unsigned int str;
};

struct HashEntry
{               
    unsigned int status_next;
    HashEntry_unnamed_type_u u;
};

struct __declspec(align(128)) scrStringGlob_t
{                                       
    HashEntry hashTable[20000];         
    bool inited;                        
    HashEntry *nextFreeEntry;
};

 struct RefString
 {
     union
     {
         struct
         {
             unsigned int refCount : 16;
             unsigned int user : 8;
             unsigned int byteLen : 8;
         };
         volatile unsigned int data;
     };
     char str[1];
 };

 struct RefVector
 {
     union
     {
         struct
         {
             unsigned int refCount : 16;
             unsigned int user : 8;
             unsigned int byteLen : 8;
         };
         volatile int head;
     };
     float vec[3];
 };

#define MT_NODE_SIZE 12
#define MT_SIZE 0xC0000

struct scrMemTreePub_t
{                     
    char *mt_buffer;  
};

struct scrStringDebugGlob_t
{
    volatile unsigned int refCount[65536];
    volatile unsigned int totalRefCount;
    int ignoreLeaks;
};
