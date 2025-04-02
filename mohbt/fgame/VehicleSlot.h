/*
===========================================================================
Copyright (C) 2024 the OpenMoHAA team

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

// VehicleSlot.h
//

#pragma once

#include "g_local.h"
#include "class.h"
#include "entity.h"

#define SLOT_FREE   1
#define SLOT_BUSY   2
#define SLOT_UNUSED 4

class cVehicleSlot : public Class
{
public:
    SafePtr<Entity> ent;
    int             flags;
    int             boneindex;
    int             enter_boneindex;

protected:
    damage_t prev_takedamage;
    solid_t  prev_solid;
    int      prev_contents;

    //
    // Added in OPM
    //  Used for properly saving and restoring children solidity
    Entity *prev_children_ent[MAX_MODEL_CHILDREN];
    solid_t prev_children_solid[MAX_MODEL_CHILDREN];
    int     prev_num_children;

public:
    cVehicleSlot();

    virtual void NotSolid(void);
    virtual void Solid(void);
    void         Archive(Archiver& arc) override;
};

inline void cVehicleSlot::Archive(Archiver& arc)
{
    Class::Archive(arc);

    arc.ArchiveSafePointer(&ent);
    arc.ArchiveInteger(&flags);
    arc.ArchiveInteger(&boneindex);
    arc.ArchiveInteger(&enter_boneindex);
    ArchiveEnum(prev_takedamage, damage_t);
    ArchiveEnum(prev_solid, solid_t);
    arc.ArchiveInteger(&prev_contents);
}

class cTurretSlot : public cVehicleSlot
{
    damage_t owner_prev_takedamage;
    solid_t  owner_prev_solid;
    int      owner_prev_contents;

public:
    cTurretSlot();

    void NotSolid(void) override;
    void Solid(void) override;
    void Archive(Archiver& arc) override;
};

inline void cTurretSlot::Archive(Archiver& arc)
{
    cVehicleSlot::Archive(arc);

    ArchiveEnum(owner_prev_takedamage, damage_t);
    ArchiveEnum(owner_prev_solid, solid_t);
    arc.ArchiveInteger(&owner_prev_contents);
}
