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
// VehicleCollisionEntity.h : MOHAA vehicle collision

#pragma once

#include "entity.h"

class VehicleCollisionEntity : public Entity
{
private:
    EntityPtr m_pOwner;

private:
    void EventDamage(Event *ev);
    void GetOwner(Event *ev);
    void Used(Event *ev);

public:
    CLASS_PROTOTYPE(VehicleCollisionEntity);

    VehicleCollisionEntity(Entity *ent);
    VehicleCollisionEntity();

    void Archive(Archiver& arc) override;

    void    Solid(void);
    void    NotSolid(void);
    Entity *GetOwner() const;
};

inline void VehicleCollisionEntity::Archive(Archiver& arc)
{
    Entity::Archive(arc);

    arc.ArchiveSafePointer(&m_pOwner);
}
