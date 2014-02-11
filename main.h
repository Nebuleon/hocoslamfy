/*
 * Hocoslamfy, main program header
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

#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdbool.h>
#include "SDL.h"

#include "bg.h"

typedef void (*TGatherInput) (bool* Continue);
typedef void (*TDoLogic) (bool* Continue, bool* Error, Uint32 Milliseconds);
typedef void (*TOutputFrame) (void);

extern SDL_Surface* Screen;
extern SDL_Surface* BackgroundImages[BG_LAYER_COUNT];
extern SDL_Surface* CharacterFrames;
extern SDL_Surface* ColumnImage;
extern SDL_Surface* CollisionImage;
extern TGatherInput GatherInput;
extern TDoLogic     DoLogic;
extern TOutputFrame OutputFrame;

#endif /* !defined(_MAIN_H_) */
