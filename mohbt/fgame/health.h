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

// health.h: Health powerup
//

#pragma once

#include "g_local.h"
#include "item.h"
#include "sentient.h"
#include "item.h"

#define MAX_HEALTH_QUEUE 5

class Health : public Item
{
public:
    CLASS_PROTOTYPE(Health);

    Health();
    virtual void PickupHealth(Event *ev);

    void        EventPostSpawn(Event *ev);
    static void CompressHealthQueue();
    void        AddToHealthQueue();
    static void ResetHealthQueue();

    static void ArchiveStatic(Archiver& arc);
    void        DoRemoveProcess();

private:
    static SafePtr<Health> mHealthQueue[MAX_HEALTH_QUEUE];
};
