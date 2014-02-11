/*
 * Hocoslamfy, initialisation code file
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
#include "SDL_image.h"

#include "main.h"
#include "init.h"
#include "platform.h"
#include "title.h"

static const char* BackgroundImageNames[BG_LAYER_COUNT] = {
	"Sky.png",
	"Mountains.png",
	"Clouds3.png",
	"Clouds2.png",
	"Clouds1.png",
	"Grass3.png",
	"Grass2.png",
	"Grass1.png"
};

static bool CheckImage(bool* Continue, bool* Error, const SDL_Surface* Image, const char* Name)
{
	if (Image == NULL)
	{
		*Continue = false;  *Error = true;
		printf("%s: IMG_Load failed: %s\n", Name, IMG_GetError());
		return false;
	}
	else
	{
		printf("Successfully loaded %s\n", Name);
		return true;
	}
}

static SDL_Surface* ConvertSurface(bool* Continue, bool* Error, SDL_Surface* Source, const char* Name)
{
	SDL_Surface* Dest;
	if (Source->format->Amask != 0)
		Dest = SDL_DisplayFormatAlpha(Source);
	else
		Dest = SDL_DisplayFormat(Source);
	if (Dest == NULL)
	{
		*Continue = false;  *Error = true;
		printf("%s: SDL_ConvertSurface failed: %s\n", Name, SDL_GetError());
		SDL_ClearError();
		return NULL;
	}
	else
	{
		printf("Successfully converted %s to the screen's pixel format\n", Name);
		SDL_FreeSurface(Source);
		return Dest;
	}
}

void Initialize(bool* Continue, bool* Error)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
	{
		*Continue = false;  *Error = true;
		printf("SDL initialisation failed: %s\n", SDL_GetError());
		SDL_ClearError();
		return;
	}
	else
		printf("SDL initialisation succeeded\n");

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE |
#ifdef SDL_TRIPLEBUF
		SDL_TRIPLEBUF
#else
		SDL_DOUBLEBUF
#endif
		);

	if (Screen == NULL)
	{
		*Continue = false;  *Error = true;
		printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
		SDL_ClearError();
		return;
	}
	else
		printf("SDL_SetVideoMode succeeded\n");

	SDL_ShowCursor(0);

	uint32_t i;
	for (i = 0; i < BG_LAYER_COUNT; i++)
	{
		BackgroundImages[i] = IMG_Load(BackgroundImageNames[i]);
		if (!CheckImage(Continue, Error, BackgroundImages[i], BackgroundImageNames[i]))
			return;
		if ((BackgroundImages[i] = ConvertSurface(Continue, Error, BackgroundImages[i], BackgroundImageNames[i])) == NULL)
			return;
	}
	CharacterFrames = IMG_Load("Bee.png");
	if (!CheckImage(Continue, Error, CharacterFrames, "Bee.png"))
		return;
	if ((CharacterFrames = ConvertSurface(Continue, Error, CharacterFrames, "Bee.png")) == NULL)
		return;
	CollisionImage = IMG_Load("Crash.png");
	if (!CheckImage(Continue, Error, CollisionImage, "Crash.png"))
		return;
	if ((CollisionImage = ConvertSurface(Continue, Error, CollisionImage, "Crash.png")) == NULL)
		return;
	ColumnImage = IMG_Load("column.png");
	if (!CheckImage(Continue, Error, ColumnImage, "column.png"))
		return;
	if ((ColumnImage = ConvertSurface(Continue, Error, ColumnImage, "column.png")) == NULL)
		return;

	InitializePlatform();

	// Title screen. (-> title.c)
	ToTitleScreen();
}

void Finalize()
{
	uint32_t i;
	for (i = 0; i < BG_LAYER_COUNT; i++)
	{
		SDL_FreeSurface(BackgroundImages[i]);
		BackgroundImages[i] = NULL;
	}
	SDL_FreeSurface(CharacterFrames);
	CharacterFrames = NULL;
	SDL_FreeSurface(ColumnImage);
	ColumnImage = NULL;
	SDL_Quit();
}
