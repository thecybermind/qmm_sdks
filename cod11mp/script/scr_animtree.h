#pragma once
//#include <xanim/xanim.h>
#include "../bgame/bg_local.h"

#define MAX_XANIMTREE_NUM       0x80 // 128

struct scrAnimPub_t 
{                                       
    unsigned int animtrees;             
    unsigned int animtree_node;         
    unsigned int animTreeNames;         
    scr_animtree_t xanim_lookup[2][MAX_XANIMTREE_NUM]; 
    unsigned int xanim_num[2];          
    unsigned int animTreeIndex;         
    bool animtree_loading;              
    
    
    
};

struct scrAnimGlob_t 
{                                       
    const char *start;                  
    const char *pos;                    
    unsigned short using_xanim_lookup[2][MAX_XANIMTREE_NUM]; 
    int bAnimCheck;                     
};
