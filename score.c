/*
 * Hocoslamfy, score screen code file
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
#include <stdint.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "game.h"
#include "score.h"
#include "text.h"

static bool                WaitingForRelease = false;

static uint32_t            ScoreShown;
static enum GameOverReason GameOverReasonShown;

void ScoreGatherInput(bool* Continue)
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

void ScoreDoLogic(bool* Continue, bool* Error)
{
}

void ScoreOutputFrame()
{
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 48, 0));

	const char* GameOverReasonString = "";
	switch (GameOverReasonShown)
	{
		case FIELD_BORDER_COLLISION:
			GameOverReasonString = "You crashed into the wall";
			break;
		case RECTANGLE_COLLISION:
			GameOverReasonString = "You crashed into an object";
			break;
	}
	char Message[256];
	sprintf(Message, "GAME OVER\n%s\n\nYour score was %" PRIu32 "\n\nPress A or Start to play again\nor B or Select to exit", GameOverReasonString, ScoreShown);
	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline(Message,
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

void ToScore(uint32_t Score, enum GameOverReason GameOverReason)
{
	ScoreShown          = Score;
	GameOverReasonShown = GameOverReason;

	GatherInput = ScoreGatherInput;
	DoLogic     = ScoreDoLogic;
	OutputFrame = ScoreOutputFrame;
}
