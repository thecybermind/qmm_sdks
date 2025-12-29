#pragma once
#include "../qcommon/q_shared.h"
struct gentity_s;
struct EntHandleInfo 
{                                       
    void *handle;
    uint16_t next;              
    uint16_t prev;              
};
struct EntHandleList 
{                                       
    uint16_t infoIndex;
};
struct EntHandle 
{                                       
    uint16_t number;
    uint16_t infoIndex;
    void setEnt(gentity_s *ent);
    gentity_s *ent() const;
    int32_t entnum();
    bool isDefined() const;
    static void Init();
    static void Shutdown();
};