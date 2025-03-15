/*
===========================================================================
Copyright (C) 2023 the OpenMoHAA team

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

// bg_compat.h: Compatibility layer between mohaa and mohta/mohtt

#pragma once

#include "q_shared.h"

#ifdef __cplusplus
extern "C" {
#endif

size_t CPT_NormalizeConfigstring(size_t num);
size_t CPT_DenormalizeConfigstring(size_t num);

uint32_t CPT_NormalizePlayerStateFlags(uint32_t flags);
uint32_t CPT_DenormalizePlayerStateFlags(uint32_t flags);

int CPT_NormalizeViewModelAnim(int iViewModelAnim);
int CPT_DenormalizeViewModelAnim(int iViewModelAnim);

#ifdef __cplusplus
}
#endif