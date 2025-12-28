#pragma once

#include "../qcommon/q_shared.h"

struct gentity_s;

struct EntHandleInfo // sizeof=0x8 // (SP/MP same)
{                                       // ...
    void *handle;
    uint16_t next;              // ...
    uint16_t prev;              // ...
};

struct EntHandleList // sizeof=0x2 // (SP/MP same)
{                                       // ...
    uint16_t infoIndex;
};

struct EntHandle // sizeof=0x4 // (SP/MP same)
{                                       // ...
    uint16_t number;
    uint16_t infoIndex;

    void setEnt(gentity_s *ent);
    gentity_s *ent() const;
    int32_t entnum();
    bool isDefined() const;

    static void Init();
    static void Shutdown();
};
