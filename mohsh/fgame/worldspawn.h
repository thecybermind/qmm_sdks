/*
===========================================================================
Copyright (C) 2015 the OpenMoHAA team

This file is part of OpenMoHAA source code.

OpenMoHAA source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

OpenMoHAA source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with OpenMoHAA source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/

// world.h: Global world information (fog and such).

#pragma once

#if defined(CGAME_DLL)
#    include "../cgame_hook/script/centity.h"
#elif defined(GAME_DLL)
#    include "entity.h"
#else
#    include "glb_local.h"
#    include "simpleentity.h"
#endif

#include "gamescript.h"

#define WORLD_CINEMATIC 1

typedef Container<SafePtr<SimpleEntity>> ConSimple;

class TargetList : public Class {
public:
    CLASS_PROTOTYPE(TargetList);

public:
    ConSimple list;
    str targetname;

public:
    TargetList();
    TargetList(const str& tname);

    void AddEntity(Listener* ent);
    void AddEntityAt(Listener* ent, int i);
    int GetEntityIndex(Listener* ent);
    void RemoveEntity(Listener* ent);
    SimpleEntity* GetNextEntity(SimpleEntity* ent);
};

template<>
class con_set_Entry<const_str, ConSimple>
{
    friend con_set<const_str, ConSimple>;
    friend con_set_enum<const_str, ConSimple>;

private:
    con_set_Entry *next;

public:
    const_str key;
    ConSimple value;

public:
    void *operator new(size_t size) { return con_set<const_str, ConSimple>::NewEntry(size); }

    void operator delete(void *ptr) { con_set<const_str, ConSimple>::DeleteEntry(ptr); }

    void Archive(Archiver& arc) {
        int num;

        arc.ArchiveUnsigned(&key);
        arc.ArchiveObjectPosition((LightClass*)&value);

        if (arc.Loading()) {
            arc.ArchiveInteger(&num);
            value.Resize(num);
        } else {
            num = value.NumObjects();
            arc.ArchiveInteger(&num);
        }
    }
    const_str& GetKey() { return key; }

    void SetKey(const const_str& newKey) { key = newKey; }
};

class World : public Entity
{
    Container<TargetList*> m_targetListContainer;
    qboolean world_dying;

public:
    // farplane variables
    float    farplane_distance;
    float    farplane_bias;
    Vector   farplane_color;
    qboolean farplane_cull;
    float    skybox_farplane;
    qboolean render_terrain;
    float    skybox_speed;
    float    farclip_override;
    Vector   farplane_color_override;
    float    animated_farplane_start;
    float    animated_farplane_end;
    float    animated_farplane_start_z;
    float    animated_farplane_end_z;
    float    animated_farplane_bias_start;
    float    animated_farplane_bias_end;
    float    animated_farplane_bias_start_z;
    float    animated_farplane_bias_end_z;
    Vector   animated_farplane_color_start;
    Vector   animated_farplane_color_end;
    float    animated_farplane_color_start_z;
    float    animated_farplane_color_end_z;

    // sky variables
    float    sky_alpha;
    qboolean sky_portal;

    // orientation variables
    float m_fAIVisionDistance;
    float m_fNorth;

public:
    CLASS_PROTOTYPE(World);

    World();
    ~World();

    void AddTargetEntity(SimpleEntity *ent);
    void AddTargetEntityAt(SimpleEntity *ent, int index);
    void RemoveTargetEntity(SimpleEntity *ent);

    void FreeTargetList();

    SimpleEntity *GetNextEntity(str targetname, SimpleEntity *ent);
    Listener     *GetScriptTarget(str targetname);
    Listener     *GetTarget(str targetname, bool quiet);
    int           GetTargetnameIndex(SimpleEntity *ent);

    TargetList *GetExistingTargetList(const str& targetname);
    TargetList *GetTargetList(str& targetname);

    void SetFarClipOverride(Event *ev);
    void SetFarPlaneColorOverride(Event *ev);
    void SetSoundtrack(Event *ev);
    void SetGravity(Event *ev);
    void SetNextMap(Event *ev);
    void SetMessage(Event *ev);
    void SetWaterColor(Event *ev);
    void SetWaterAlpha(Event *ev);
    void SetLavaColor(Event *ev);
    void SetLavaAlpha(Event *ev);
    void GetFarPlane_Color(Event *ev);
    void SetFarPlane_Color(Event *ev);
    void GetFarPlaneBias(Event *ev);
    void SetFarPlaneBias(Event *ev);
    void SetFarPlane_Cull(Event *ev);
    void GetSkyboxFarplane(Event *ev);
    void SetSkyboxFarplane(Event *ev);
    void SetAnimatedFarplaneColor(Event *ev);
    void SetAnimatedFarplane(Event *ev);
    void SetAnimatedFarplaneBias(Event *ev);
    void UpdateAnimatedFarplane(Event *ev);
    void GetRenderTerrain(Event *ev);
    void SetRenderTerrain(Event *ev);
    void GetSkyboxSpeed(Event *ev);
    void SetSkyboxSpeed(Event *ev);
    void GetFarPlane(Event *ev);
    void SetFarPlane(Event *ev);
    void SetSkyAlpha(Event *ev);
    void SetSkyPortal(Event *ev);
    void SetNumArenas(Event *ev);
    void SetAIVisionDistance(Event *ev);
    void SetNorthYaw(Event *ev);
    void UpdateConfigStrings(void);
    void UpdateFog(void);
    void UpdateSky(void);

    void Archive(Archiver& arc) override;
};

typedef SafePtr<World> WorldPtr;
extern WorldPtr        world;

bool WithinFarplaneDistance(const Vector& org);
