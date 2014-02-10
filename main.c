/*
 * Hocoslamfy, main program file
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

#include <stdbool.h>
#include <stddef.h>

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "platform.h"
#include "SDL_image.h"

static bool         Continue            = true;
static bool         Error               = false;

       SDL_Surface* Screen              = NULL;
       SDL_Surface* BackgroundImage     = NULL;
       SDL_Surface* CharacterFrames     = NULL;
       SDL_Surface* ColumnImage         = NULL;

       TGatherInput GatherInput;
       TDoLogic     DoLogic;
       TOutputFrame OutputFrame;

int main(int argc, char* argv[])
{
	Initialize(&Continue, &Error);
	Uint32 Duration = 16;
	while (Continue)
	{
		GatherInput(&Continue);
		if (!Continue)
			break;
		DoLogic(&Continue, &Error, Duration);
		if (!Continue)
			break;
		OutputFrame();
		Duration = ToNextFrame();
	}
	Finalize();
	return Error ? 1 : 0;
}
