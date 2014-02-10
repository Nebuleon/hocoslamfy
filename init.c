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

	Screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_HWSURFACE |
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

	BackgroundImage = IMG_Load("bg.png");
	if (!CheckImage(Continue, Error, BackgroundImage, "bg.png"))
		return;
	CharacterFrames = IMG_Load("player.png");
	if (!CheckImage(Continue, Error, CharacterFrames, "player.png"))
		return;
	ColumnImage = IMG_Load("column.png");
	if (!CheckImage(Continue, Error, ColumnImage, "column.png"))
		return;

	InitializePlatform();

	// Title screen. (-> title.c)
	ToTitleScreen();
}

void Finalize()
{
	SDL_FreeSurface(BackgroundImage);
	BackgroundImage = NULL;
	SDL_FreeSurface(CharacterFrames);
	CharacterFrames = NULL;
	SDL_FreeSurface(ColumnImage);
	ColumnImage = NULL;
	SDL_Quit();
}
