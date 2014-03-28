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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>

#include "SDL.h"

#include "main.h"
#include "init.h"
#include "platform.h"
#include "game.h"
#include "score.h"
#include "bg.h"
#include "text.h"
#include "audio.h"

static bool  WaitingForRelease = false;

static char* ScoreMessage      = NULL;

static const char* SavePath = ".hocoslamfy";
static const char* HighScoreFilePath = "highscore";

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

	SDL_Rect HeaderDestRect = {
		.x = (SCREEN_WIDTH - GameOverFrame->w) / 2,
		.y = ((SCREEN_HEIGHT / 4) - GameOverFrame->h) / 2,
		.w = GameOverFrame->w,
		.h = GameOverFrame->h
	};
	SDL_Rect HeaderSourceRect = {
		.x = 0,
		.y = 0,
		.w = GameOverFrame->w,
		.h = GameOverFrame->h
	};
	SDL_BlitSurface(GameOverFrame, &HeaderSourceRect, Screen, &HeaderDestRect);

	if (SDL_MUSTLOCK(Screen))
		SDL_LockSurface(Screen);
	PrintStringOutline32(ScoreMessage,
		SDL_MapRGB(Screen->format, 255, 255, 255),
		SDL_MapRGB(Screen->format, 0, 0, 0),
		Screen->pixels,
		Screen->pitch,
		0,
		SCREEN_HEIGHT / 4,
		SCREEN_WIDTH,
		SCREEN_HEIGHT - (SCREEN_HEIGHT / 4),
		CENTER,
		MIDDLE);
	if (SDL_MUSTLOCK(Screen))
		SDL_UnlockSurface(Screen);

	SDL_Flip(Screen);
}

void ToScore(uint32_t Score, enum GameOverReason GameOverReason, uint32_t HighScore)
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
			GameOverReasonString = "You flew too far away from the field";
			break;
		case RECTANGLE_COLLISION:
			GameOverReasonString = "You crashed into CAPITALISM!";
			break;
	}

	char HighScoreString[256];
	if (Score > HighScore)
	{
		snprintf(HighScoreString, 256, "NEW High Score: %" PRIu32, Score);
		PlaySFXHighScore();
	} else {
		snprintf(HighScoreString, 256, "High Score: %" PRIu32, HighScore);
	}

	while ((NewLength = snprintf(ScoreMessage, Length, "%s\n\nYour score was %" PRIu32 "\n\n%s\n\nPress %s to play again\nor %s to exit", GameOverReasonString, Score, HighScoreString, GetEnterGamePrompt(), GetExitGamePrompt())) >= Length)
	{
		Length = NewLength + 1;
		ScoreMessage = realloc(ScoreMessage, Length);
	}

	GatherInput = ScoreGatherInput;
	DoLogic     = ScoreDoLogic;
	OutputFrame = ScoreOutputFrame;
}

int MkDir(char *path)
{
	return mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
}

void SaveHighScore(uint32_t Score)
{
	struct passwd *pw = getpwuid(getuid());
	
	char path[256];
	snprintf(path, 256, "%s/%s", pw->pw_dir, SavePath);
	MkDir(path);
	
	snprintf(path, 256, "%s/%s/%s", pw->pw_dir, SavePath, HighScoreFilePath);
	FILE *fp = fopen(path, "w");

	if (!fp)
	{
		fprintf(stderr, "%s: Unable to open file.\n", path);
		return;
	}

	fprintf(fp, "%" PRIu32, Score);
	fclose(fp);
}

void GetFileLine(char *str, uint32_t size, FILE *fp)
{
	int i = 0;
	for (i = 0; i < size - 1; i++)
	{
		int c = fgetc(fp);
		if (c == EOF || c == '\n')
		{
			str[i] = '\0';
			break;
		}
		str[i] = c;
	}
	str[size - 1] = '\0';
}

uint32_t GetHighScore()
{
	char path[256];
	struct passwd *pw = getpwuid(getuid());
	snprintf(path, 256, "%s/%s/%s", pw->pw_dir, SavePath, HighScoreFilePath);

	FILE *fp = fopen(path, "r");

	if (!fp)
		return 0;

	char line[256];
	GetFileLine(line, 256, fp);
	fclose(fp);
	
	uint32_t hs = 0;
	if (sscanf(line, "%" SCNu32, &hs) != 1)
		return 0;

	return hs;
}

