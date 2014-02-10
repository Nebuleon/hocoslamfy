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
#include "platform.h"
#include "game.h"
#include "score.h"
#include "bg.h"
#include "text.h"

static bool  WaitingForRelease = false;

static char* ScoreMessage      = NULL;

void ScoreGatherInput(bool* Continue)
{
	SDL_Event ev;

	while (SDL_PollEvent(&ev))
	{
		if (IsEnterGamePressingEvent(&ev))
			WaitingForRelease = true;
		else if (IsEnterGameReleasingEvent(&ev))
		{
			WaitingForRelease = false;
			ToGame();
			if (ScoreMessage != NULL)
			{
				free(ScoreMessage);
				ScoreMessage = NULL;
			}
			return;
		}
		else if (IsExitGameEvent(&ev))
		{
			*Continue = false;
			if (ScoreMessage != NULL)
			{
				free(ScoreMessage);
				ScoreMessage = NULL;
			}
			return;
		}
	}
}

void ScoreDoLogic(bool* Continue, bool* Error, Uint32 Milliseconds)
{
	AdvanceBackground(Milliseconds);
}

void ScoreOutputFrame()
{
	DrawBackground();
	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline32(ScoreMessage,
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
	if (ScoreMessage != NULL)
	{
		free(ScoreMessage);
		ScoreMessage = NULL;
	}
	int Length = 2, NewLength;
	ScoreMessage = malloc(Length);

	const char* GameOverReasonString = "";
	switch (GameOverReason)
	{
		case FIELD_BORDER_COLLISION:
			GameOverReasonString = "You crashed into the wall";
			break;
		case RECTANGLE_COLLISION:
			GameOverReasonString = "You crashed into an object";
			break;
	}

	while ((NewLength = snprintf(ScoreMessage, Length, "GAME OVER\n%s\n\nYour score was %" PRIu32 "\n\nPress %s to play again\nor %s to exit", GameOverReasonString, Score, GetEnterGamePrompt(), GetExitGamePrompt())) >= Length)
	{
		Length = NewLength + 1;
		ScoreMessage = realloc(ScoreMessage, Length);
	}

	GatherInput = ScoreGatherInput;
	DoLogic     = ScoreDoLogic;
	OutputFrame = ScoreOutputFrame;
}
