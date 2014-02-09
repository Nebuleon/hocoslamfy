/*
 * Hocoslamfy, title screen code file
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

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "game.h"
#include "title.h"
#include "text.h"

static bool WaitingForRelease = false;

void TitleScreenGatherInput(bool* Continue)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
			case SDL_KEYDOWN:
				if (ev.key.keysym.sym == SDLK_LCTRL  /* GCW Zero: A */
				 || ev.key.keysym.sym == SDLK_RETURN /* GCW Zero: Start */)
					WaitingForRelease = true;
				else if (ev.key.keysym.sym == SDLK_LALT   /* GCW Zero: B */
				      || ev.key.keysym.sym == SDLK_ESCAPE /* GCW Zero: Select */)
				{
					*Continue = false;
					return;
				}
				break;
			case SDL_KEYUP:
				if (ev.key.keysym.sym == SDLK_LCTRL  /* GCW Zero: A */
				 || ev.key.keysym.sym == SDLK_RETURN /* GCW Zero: Start */)
				{
					WaitingForRelease = false;
					ToGame();
					return;
				}
				break;
			default:
				break;
		}
	}
}

void TitleScreenDoLogic(bool* Continue, bool* Error)
{
}

void TitleScreenOutputFrame()
{
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 48, 0));

	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline("Welcome to HOCOSLAMFY\n\nPress A or Start to play\nor B or Select to exit\n\nIn-game:\nA or B to rise\nStart to pause\nSelect to exit",
		SDL_MapRGB(Screen->format, 255, 255, 255),
		SDL_MapRGB(Screen->format, 0, 0, 0),
		Screen->pixels,
		Screen->pitch,
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		CENTER,
		MIDDLE);
	if (SDL_MUSTLOCK(Screen))
		SDL_UnlockSurface(Screen);

	SDL_Flip(Screen);
}

void ToTitleScreen(void)
{
	GatherInput = TitleScreenGatherInput;
	DoLogic     = TitleScreenDoLogic;
	OutputFrame = TitleScreenOutputFrame;
}
