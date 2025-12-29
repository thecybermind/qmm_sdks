#pragma once
#define CMD_MAX_NESTING 8
struct CmdArgs
{
    int nesting;
    int localClientNum[8];
    int controllerIndex[8];
    int argc[8];
    const char **argv[8];
};
struct CmdArgsPrivate
{
    char textPool[8192];
    const char *argvPool[512];
    int usedTextPool[8];
    int totalUsedArgvPool;
    int totalUsedTextPool;
};
struct cmd_function_s
{
    cmd_function_s *next;
    const char *name;
    const char *autoCompleteDir;
    const char *autoCompleteExt;
    void( *function)();
};
struct CmdText 
{                                       
    unsigned char *data;              
    int maxsize;                        
    int cmdsize;                        
};