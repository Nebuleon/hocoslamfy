/*
 * Hocoslamfy, background rendering header
 * Copyright (C) 2014 Nebuleon Fumika <nebuleon@gcw-zero.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef _BG_H_
#define _BG_H_

#include <stdint.h>

#include "game.h"

#define BG_LAYER_COUNT  8

#define BG_SPEED_1     (-FIELD_SCROLL * 1 / 8)
#define BG_SPEED_2     (-FIELD_SCROLL * 1 / 6)
#define BG_SPEED_3     (-FIELD_SCROLL * 1 / 4)
#define BG_SPEED_4     (-FIELD_SCROLL * 1 / 3)
#define BG_SPEED_5     (-FIELD_SCROLL * 1 / 2)

extern void AdvanceBackground(uint32_t Milliseconds);
extern void DrawBackground(void);

#endif /* !defined(_BG_H_) */
