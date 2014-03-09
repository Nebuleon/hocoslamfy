/*
 * Hocoslamfy, sound playback code file
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

#include <stdlib.h>
#include <stdbool.h>

#include "SDL.h"
#include "SDL_mixer.h"

static Mix_Music* BGM = NULL;

bool InitializeAudio()
{
	if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2 /* stereo */, 4096 /* buffer size */))
	{
		printf("Mix_OpenAudio failed: %s\n", Mix_GetError());
		return false;
	}
	else
		printf("Mix_OpenAudio succeeded\n");

	BGM = Mix_LoadMUS("bgm.wav");
	if (BGM == NULL)
	{
		printf("%s: Mix_LoadMUS failed: %s\n", "bgm.wav", Mix_GetError());
		return false;
	}
	else
		printf("Successfully loaded %s\n", "bgm.wav");

	return true;
}

void FinalizeAudio()
{
	Mix_HaltMusic();
	Mix_FreeMusic(BGM);
	BGM = NULL;
	Mix_CloseAudio();
}

void StartBGM()
{
	Mix_PlayMusic(BGM, -1 /* loop indefinitely */);
}

void StopBGM()
{
	Mix_HaltMusic();
}
