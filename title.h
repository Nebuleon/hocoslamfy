/*
 * Hocoslamfy, title screen header
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

#ifndef _TITLE_H_
#define _TITLE_H_

#include <stdbool.h>

#define TITLE_FRAME_TIME        50
#define TITLE_FRAME_COUNT        8
#define TITLE_ANIMATION_FRAMES 144

extern void ToTitleScreen(void);

#endif /* !defined(_TITLE_H_) */
