#pragma once

#include "q_shared.h"

enum FsThread
{                                       
    FS_THREAD_MAIN = 0x0,
    FS_THREAD_STREAM = 0x1,
    FS_THREAD_DATABASE = 0x2,
    FS_THREAD_BACKEND = 0x3,
    FS_THREAD_SERVER = 0x4,
    FS_THREAD_COUNT = 0x5,
    FS_THREAD_INVALID = 0x6,
};

enum fsMode_t
{                                       
    FS_READ = 0x0,
    FS_WRITE = 0x1,
    FS_APPEND = 0x2,
    FS_APPEND_SYNC = 0x3,
};

struct directory_t 
{
    char path[256];
    char gamedir[256];
};
struct fileInIwd_s 
{
    unsigned int pos;
    char* name;
    fileInIwd_s* next;
};
struct iwd_t 
{
    char iwdFilename[256];
    char iwdBasename[256];
    char iwdGamename[256];
    unsigned char* handle;
    int checksum;
    int pure_checksum;
    volatile unsigned int hasOpenFile;
    int numfiles;
    unsigned char referenced;
    
    
    
    unsigned int hashSize;
    fileInIwd_s** hashTable;
    fileInIwd_s* buildBuffer;
};
struct searchpath_s 
{
    searchpath_s *next;
    iwd_t *iwd;
    directory_t *dir;
    int bLocalized;
    int ignore;
    int ignorePureCheck;
    int language;
};

union qfile_gus 
{                                       
    FILE *o;
    unsigned char *z;
};
struct qfile_us 
{                                       
    qfile_gus file;
    int iwdIsClone;
};
struct fileHandleData_t 
{
    qfile_us handleFiles;
    int handleSync;
    int fileSize;
    int zipFilePos;
    iwd_t *zipFile;
    int streamed;
    char name[256];
};

enum FsListBehavior_e 
{                                       
    FS_LIST_PURE_ONLY = 0x0,
    FS_LIST_ALL = 0x1,
};
